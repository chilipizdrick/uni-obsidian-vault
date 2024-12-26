#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <ostream>
#include <queue>

using namespace std;

class Exception : public exception {
  protected:
    string message;

  public:
    Exception() { message = ""; }
    Exception(const string &message_) : message(message_) {}
    const char *what() const noexcept override { return message.c_str(); }
};

class FullHeapException : public Exception {
  public:
    FullHeapException()
        : Exception("error on trying to add element to full heap") {}
};

class EmptyHeapException : public Exception {
  public:
    EmptyHeapException()
        : Exception("error on trying to remove element from empty heap") {}
};

class HeapIndexOutOfBoundsException : public Exception {
  public:
    HeapIndexOutOfBoundsException()
        : Exception("error on trying to access an element of heap with invalid "
                    "index") {}
};

class Doctor {
  public:
    string lastname;
    string firstname;
    string speciality;
    string post;
    int experience;
    double rating;

    Doctor(string lastname, string firstname, string speciality, string post,
           int experience, double rating)
        : lastname(lastname), firstname(firstname), speciality(speciality),
          post(post), experience(experience), rating(rating) {}

    Doctor()
        : lastname(""), firstname(""), speciality(""), post(""), experience(0),
          rating(0.0) {}

    bool operator<(const Doctor d) const {
        if (rating != d.rating)
            return rating < d.rating;
        if (experience != d.experience)
            return experience < d.experience;
        if (lastname != d.lastname)
            return lastname < d.lastname;
        return firstname < d.firstname;
    }
    bool operator>(Doctor d) const {
        if (rating != d.rating)
            return rating > d.rating;
        if (experience != d.experience)
            return experience > d.experience;
        if (lastname != d.lastname)
            return lastname > d.lastname;
        return firstname > d.firstname;
    }
    bool operator>=(Doctor d) const { return !(*this < d); }
    bool operator<=(Doctor d) const { return !(*this > d); }
    bool operator==(Doctor d) const { return !(*this < d || *this > d); }
    bool operator!=(Doctor d) const { return !(*this == d); }
};

ostream &operator<<(ostream &s, Doctor d) {
    s << "Doctor{ " << d.lastname << ", " << d.firstname << ", " << d.speciality
      << ", " << d.post << ", " << d.experience << ", " << d.rating << " }";
    return s;
}

string rstr(size_t length) {
    auto randchar = []() -> char {
        const char charset[] = "0123456789"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    string str(length, 0);
    generate_n(str.begin(), length, randchar);
    return str;
}

template <typename T> ostream &operator<<(ostream &s, priority_queue<T> obj) {
    s << "priority_queue{ \n";
    while (!obj.empty()) {
        s << "\t" << obj.top() << "\n";
        obj.pop();
    }
    s << "}\n";
    return s;
}

template <typename P, typename T> class Node {
  protected:
    P priority;
    T value;

  public:
    Node() {
        priority = P();
        value = T();
    }

    Node(P priority_, T value_) {
        priority = priority_;
        value = value_;
    }

    virtual ~Node() {}

    P getPriority() const { return priority; }
    T getValue() const { return value; }

    void setPriority(P priority_) { priority = priority_; }
    void setValue(T value_) { value = value_; }
};

template <typename P, typename T> class Heap {
  protected:
    Node<P, T> *arr = nullptr;
    int length = 0;
    int capacity = 0;

    bool isFull() { return length == capacity; }
    bool isEmpty() { return length == 0; }
    bool isValidIndex(int index) { return index >= 0 && index < length; }
    void validateIndex(int index) {
        if (!isValidIndex(index)) {
            throw(HeapIndexOutOfBoundsException());
        }
    }

    int getLeftIndex(int index) { return (index << 1) + 1; }

    int getRightIndex(int index) { return (index << 1) + 2; }

    int getParentIndex(int index) { return (index - 1) >> 1; }

    void swap(int index1, int index2) {
        validateIndex(index1);
        validateIndex(index2);
        Node<P, T> tmp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = tmp;
    }

    void siftUp(int index) {
        int parentIndex = getParentIndex(index);
        while (isValidIndex(parentIndex) &&
               arr[index].getPriority() > arr[parentIndex].getPriority()) {
            swap(index, parentIndex);
            index = parentIndex;
            parentIndex = getParentIndex(index);
        }
    }

    void siftDown(int index = 0) {
        int leftIndex = getLeftIndex(index);
        while (isValidIndex(leftIndex)) {
            int biggerIndex = leftIndex;
            int rightIndex = getRightIndex(index);
            if (isValidIndex(rightIndex) &&
                arr[rightIndex].getPriority() > arr[leftIndex].getPriority()) {
                biggerIndex = rightIndex;
            }
            if (arr[biggerIndex].getPriority() > arr[index].getPriority()) {
                swap(biggerIndex, index);
                index = biggerIndex;
                leftIndex = getLeftIndex(index);
            } else {
                break;
            }
        }
    }

  public:
    Heap() {
        arr = nullptr;
        length = 0;
        capacity = 0;
    }

    Heap(int capacity_) {
        capacity = capacity_;
        length = 0;
        arr = new Node<P, T>[capacity];
    }

    Heap(const Heap<P, T> &heap) {
        length = heap.length;
        capacity = heap.capacity;
        arr = new Node<P, T>[capacity];
        for (int i = 0; i < length; i++) {
            arr[i] = heap.arr[i];
        }
    }

    ~Heap() {
        cout << "~Heap()\n";
        delete[] arr;
    }

    int getLength() { return length; }
    int getCapacity() { return capacity; }

    void push(P priority, T value) {
        if (isFull()) {
            throw FullHeapException();
        }
        arr[length] = Node(priority, value);
        length++;
        siftUp(length - 1);
    }

    T remove(int index) {
        validateIndex(index);
        Node<P, T> res = arr[index];
        swap(index, length - 1);
        length--;

        if (index != 0) {
            if (arr[index].getPriority() >
                arr[getParentIndex(index)].getPriority()) {
                siftUp(index);
                return res.getValue();
            }
        }
        siftDown(index);
        return res.getValue();
    }

    T extractMax() {
        if (isEmpty()) {
            throw EmptyHeapException();
        }
        Node<P, T> res = arr[0];
        swap(0, length - 1);
        length--;
        siftDown();
        return res.getValue();
    }

    T operator[](P priority) {
        for (int i = 0; i < length; i++) {
            if (arr[i].getPriority() == priority) {
                return arr[i].getValue();
            }
        }
    }

    void setPriority(int index, P priority) {
        validateIndex(index);
        Node<P, T> res = arr[index];
        P currPriority = res.getPriority();
        arr[index].setPriority(priority);
        if (priority < currPriority)
            siftDown(index);
        else if (priority > currPriority)
            siftUp(index);
    }

    template <typename P_, typename T_>
    friend ostream &operator<<(ostream &s, Heap<P_, T_> obj);
};

template <typename P, typename T>
ostream &operator<<(ostream &s, Heap<P, T> obj) {
    s << "Heap{\n";
    while (!obj.isEmpty()) {
        s << "\t" << obj.extractMax() << "\n";
    }
    s << "}\n";
    return s;
}

template <typename P, typename T> class FibonacciHeap;

template <typename P, typename T> class FibonacciNode {
  private:
    list<FibonacciNode *> elements;
    FibonacciNode *child;
    FibonacciNode *parent;
    P priority;
    T value;
    int degree;
    bool marked;

  public:
    friend class FibonacciHeap<P, T>;
    FibonacciNode *getPrev() { return prev; }
    FibonacciNode *getNext() { return next; }
    FibonacciNode *getChild() { return child; }
    FibonacciNode *getParent() { return parent; }
    P getPriority() { return priority; }
    T getValue() { return value; }
    bool isMarked() { return marked; }

    bool hasChildren() { return child; }
    bool hasParent() { return parent; }

    template <typename P_, typename T_>
    friend ostream &operator<<(ostream &s, FibonacciNode<P_, T_> obj);
};
template <typename P, typename T>
ostream &operator<<(ostream &s, FibonacciNode<P, T> obj) {
    s << "FibonacciNode{ Priority: " << obj.priority << ", Value: " << obj.value
      << " }";
    return s;
}

template <typename P, typename T> class FibonacciHeap {
  private:
    FibonacciNode<P, T> *_empty() { return nullptr; }

    FibonacciNode<P, T> *_singleton(P priority, T value) {
        FibonacciNode<P, T> *n = new FibonacciNode<P, T>;
        n->priority = priority;
        n->value = value;
        n->degree = 0;
        n->marked = false;
        n->child = nullptr;
        n->parent = nullptr;
        return n;
    }
    FibonacciNode<P, T> *_merge(FibonacciNode<P, T> *a,
                                FibonacciNode<P, T> *b) {
        if (a == nullptr)
            return b;
        if (b == nullptr)
            return a;
        if (a->priority < b->priority) {
            swap(a, b);
        }

        a->elements.push_back(b);
        b->parent = a;
        return a;
    }

    void _deleteAll(FibonacciNode<P, T> *n) {
        if (n != nullptr) {
            for (FibonacciNode<P, T> *c : n->elements) {
                _deleteAll(c->child);
            }
            delete n;
        }
    }

    void _addChild(FibonacciNode<P, T> *parent, FibonacciNode<P, T> *child) {
        child->parent = parent;
        ++parent->degree;
        parent->child = _merge(parent->child, child);
    }

    void _unMarkAndUnParentAll(FibonacciNode<P, T> *n) {
        if (n == nullptr)
            return;
        for (FibonacciNode<P, T> *c : n->elements) {
            c->marked = false;
            c->parent = nullptr;
        }
    }

    void _consolidate() {
        vector<FibonacciNode<P, T> *> degreeArray(64);
        vector<FibonacciNode<P, T> *>
            nodesToDelete; // Узлы удаляются после цикла, чтобы не сломать
                           // порядок итерации
        for (FibonacciNode<P, T> *node : heap->elements) {
            if (degreeArray[node->degree] != nullptr) {
                FibonacciNode<P, T> *parent = degreeArray[node->degree];
                int prevDegree = parent->degree;
                _addChild(parent, node);
                degreeArray[prevDegree] = nullptr;
                degreeArray[parent->degree] = parent;
                nodesToDelete.push_back(node);
            } else {
                degreeArray[node->degree] = node;
            }
        }
        for (FibonacciNode<P, T> *node : nodesToDelete)
            heap->elements.remove(node);
    }

    FibonacciNode<P, T> *_removeMaximum(FibonacciNode<P, T> *n) {
        if (n == nullptr)
            return nullptr;

        _unMarkAndUnParentAll(n);

        FibonacciNode<P, T> *newMax = nullptr;
        for (FibonacciNode<P, T> *it : n->elements)
            if (newMax == nullptr || it->priority > newMax->priority)
                newMax = it;

        for (FibonacciNode<P, T> *it : n->elements)
            if (it != newMax)
                newMax = _merge(newMax, it);

        _consolidate();

        return newMax;
    }

  protected:
    FibonacciNode<P, T> *heap;

  public:
    FibonacciHeap() { heap = _empty(); }
    virtual ~FibonacciHeap() {
        if (heap != nullptr) {
            _deleteAll(heap);
        }
    }
    FibonacciNode<P, T> *push(P priority, T value) {
        FibonacciNode<P, T> *ret = _singleton(priority, value);
        heap = _merge(heap, ret);
        return ret;
    }
    void merge(FibonacciHeap<P, T> &other) {
        heap = _merge(heap, other.heap);
        other.heap = _empty();
    }

    bool isEmpty() { return heap == nullptr; }

    FibonacciNode<P, T> getMaximum() { return *heap; }

    FibonacciNode<P, T> extractMax() {
        FibonacciNode<P, T> *old = heap;
        heap = _removeMaximum(heap);
        FibonacciNode<P, T> ret = *old;
        delete old;
        return ret;
    }
};

template <typename P, typename T>
ostream &operator<<(ostream &s, FibonacciHeap<P, T> obj) {
    s << "FibonacciHeap{\n";
    while (!obj.isEmpty()) {
        s << "\t" << obj.extractMax() << "\n";
    }
    s << "}\n";
    return s;
}

int main() {
    priority_queue<Doctor> doctors;
    Doctor doctor;
    string firstname, lastname;
    for (int i = 0; i < 10; i++) {
        firstname = rstr(5);
        lastname = rstr(6);
        double rating =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        int experience = rand();
        doctor =
            Doctor(lastname, firstname, rstr(5), rstr(5), experience, rating);
        doctors.push(doctor);
    }
    cout << doctors;

    Heap<Doctor, Doctor> doctors2(100);
    for (int i = 0; i < 10; i++) {
        firstname = rstr(5);
        lastname = rstr(6);
        double rating =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        int experience = rand();
        doctor =
            Doctor(lastname, firstname, rstr(5), rstr(5), experience, rating);
        doctors2.push(doctor, doctor);
    }
    cout << doctors2;
    doctors2.setPriority(2, doctor);
    cout << doctors2;

    // Действительно max_heap
    FibonacciHeap<int, int> testing;
    for (int i = 0; i < 10; i++) {
        testing.push(i, i);
    }
    cout << testing;

    FibonacciHeap<Doctor, Doctor> doctors3;
    for (int i = 0; i < 10; i++) {
        firstname = rstr(5);
        lastname = rstr(6);
        double rating =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        int experience = rand();
        doctor =
            Doctor(lastname, firstname, rstr(5), rstr(5), experience, rating);
        doctors3.push(doctor, doctor);
    }
    cout << doctors3;

    return 0;
}
