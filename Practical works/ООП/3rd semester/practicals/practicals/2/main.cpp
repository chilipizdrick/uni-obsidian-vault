#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <ostream>

using namespace std;

class Exception : public exception {
  private:
    const string message;

  public:
    Exception(string s) : message(s) {}

    const char *what() { return message.c_str(); }
};

class UndefinedIteratorException : public Exception {
  public:
    UndefinedIteratorException(string s) : Exception(s) {};
};

template <typename T> class Element {
  private:
    Element<T> *next_;
    Element<T> *prev_;
    T value_;

  public:
    Element(T value = 0, Element<T> *next = nullptr, Element<T> *prev = nullptr)
        : value_(value), next_(next), prev_(prev) {}

    virtual Element<T> *&next() { return next_; }
    virtual Element<T> *&prev() { return prev_; }
    virtual T &value() { return value_; }

    template <typename U>
    friend ostream &operator<<(ostream &s, Element<U> &obj);
};

template <typename T> ostream &operator<<(ostream &s, Element<T> &obj) {
    s << obj.value_;
    return s;
}

template <typename T> class LinkedListParent {
  protected:
    Element<T> *head;
    Element<T> *tail;
    size_t length;

  public:
    LinkedListParent() {
        head = tail = nullptr;
        length = 0;
    }

    virtual size_t size() { return length; }
    virtual Element<T> *getHead() { return head; }
    virtual Element<T> *getTail() { return tail; }

    virtual Element<T> *push(T value) = 0;
    virtual Element<T> *pop() = 0;

    virtual ~LinkedListParent() {};

    virtual Element<T> *operator[](int idx) {
        if (idx < 0 || idx > length)
            return nullptr;
        int i = 0;
        Element<T> *cur = head;
        for (i = 0; i < idx; i++)
            cur = cur->next();
        return cur;
    }

    template <typename U>
    friend ostream &operator<<(ostream &s, LinkedListParent<U> &obj);
};

template <typename T>
ostream &operator<<(ostream &s, LinkedListParent<T> &obj) {
    s << "LinkedList(Length : " << obj.length << "){ ";
    for (Element<T> *current = obj.getHead(); current != nullptr;
         current = current->next())
        s << *current << " ";
    s << "}\n";
    return s;
}

template <typename T>
class ListIterator : public std::iterator<std::input_iterator_tag, T> {
  private:
    Element<T> *ptr;
    Element<T> *prevPtr;

  public:
    ListIterator() : ptr(nullptr) { prevPtr = nullptr; }
    ListIterator(Element<T> *p, Element<T> *pp = nullptr) : ptr(p) {
        if (p != nullptr) {
            prevPtr = p->prev();
            return;
        }
        prevPtr = pp;
    }
    ListIterator(const ListIterator &it) : ptr(it.ptr), prevPtr(it.prevPtr) {}

    Element<T> *&ptr_() { return this->ptr; }
    Element<T> *&prevPtr_() { return this->prevPtr; }

    bool operator!=(ListIterator<T> const &other) const {
        return ptr != other.ptr || prevPtr != other.prevPtr;
    }

    bool operator==(ListIterator<T> const &other) const {
        return ptr == other.ptr && prevPtr == other.prevPtr;
    }

    T &operator*() {
        if (ptr == nullptr)
            throw UndefinedIteratorException(
                "iterator does not point to a list element");
        return ptr->value();
    }

    ListIterator<T> operator++() {
        if (ptr == nullptr)
            throw UndefinedIteratorException(
                "iterator does not point to a list element");
        prevPtr = ptr;
        ptr = ptr->next();
        return *this;
    }

    ListIterator<T> operator++(int v) {
        if (ptr == nullptr)
            throw UndefinedIteratorException(
                "iterator does not point to a list element");
        ListIterator<T> res = *this;
        prevPtr = ptr;
        ptr = ptr->next();
        return res;
    }

    ListIterator<T> operator--() {
        if (prevPtr == nullptr)
            throw UndefinedIteratorException(
                "iterator does not point to a list element");
        ptr = ptr->prev();
        return *this;
    }

    ListIterator<T> operator--(int v) {
        if (prevPtr == nullptr)
            throw UndefinedIteratorException(
                "iterator does not point to a list element");
        ListIterator<T> res = *this;
        ptr = ptr->prev();
        return res;
    }

    ListIterator<T> &operator=(const ListIterator &it) {
        ptr = it.ptr;
        return *this;
    }

    ListIterator<T> &operator=(Element<T> *p) {
        ptr = p;
        return *this;
    }

    template <typename U>
    friend ostream &operator<<(ostream &s, ListIterator<U> &obj);
};

template <typename T> ostream &operator<<(ostream &s, ListIterator<T> &obj) {
    s << *obj;
    return s;
}

template <typename T> class IteratedLinkedList : public LinkedListParent<T> {
  public:
    IteratedLinkedList() : LinkedListParent<T>() {}

    virtual ~IteratedLinkedList() {}

    ListIterator<T> begin() { return ListIterator<T>(this->head); }
    ListIterator<T> end() { return ListIterator<T>(nullptr, this->tail); };

    Element<T> *front() { return this->head; }
    Element<T> *back() { return this->tail; }

    template <typename U>
    friend ostream &operator<<(ostream &s, IteratedLinkedList<U> &obj);
};

template <typename T>
ostream &operator<<(ostream &s, IteratedLinkedList<T> &obj) {
    s << "LinkedList(Length : " << obj.length << "){ ";
    ListIterator<T> iter = obj.begin();
    for (ListIterator<T> iter = obj.begin(); iter != obj.end(); ++iter)
        s << *iter << " ";
    s << "}\n";
    return s;
}

template <typename T> class Queue : public IteratedLinkedList<T> {
  public:
    ~Queue() {
        if (this->head == nullptr) {
            return;
        }
        Element<T> *previous = this->head;
        Element<T> *current = this->head->next();
        while (current != nullptr) {
            delete previous;
            previous = current;
            current = current->next();
        }
        delete this->tail;
        this->length = 0;
        this->head = this->tail = nullptr;
        cout << "~Queue()\n";
    };

    Element<T> *push(T value) {
        this->length++;
        Element<T> *elem = new Element<T>(value);
        if (this->tail == nullptr) {
            this->head = this->tail = elem;
            return elem;
        }
        this->tail->next() = elem;
        elem->prev() = this->tail;
        this->tail = elem;
        return elem;
    };

    Element<T> *pop() {
        if (this->head == nullptr)
            throw Exception("empty list");
        Element<T> *res = this->head;
        this->head = this->head->next();
        res->next() = nullptr;
        this->length--;
        return res;
    };
};

template <typename T> class OrderedQueue : protected Queue<T> {
  public:
    // Переопределены с использованием итераторов
    ListIterator<T> pushIter(T value) {
        ListIterator<T> pos = this->begin();
        while (pos != this->end()) {
            if (*pos > value)
                break;
            pos++;
        }
        return this->insert(pos, value);
    }

    ListIterator<T> insert(ListIterator<T> iter, T value) {
        this->length++;
        Element<T> *elem = new Element<T>(value);
        if (this->begin().ptr_() == nullptr) {
            this->head = this->tail = elem;
            return ListIterator<T>(elem);
        }
        if (iter == this->end()) {
            this->tail->next() = elem;
            elem->prev() = this->tail;
            this->tail = elem;
            return ListIterator<T>(elem);
        }
        if (iter == this->begin()) {
            this->head->prev() = elem;
            elem->next() = this->head;
            this->head = elem;
            return ListIterator<T>(elem);
        }
        iter.ptr_()->prev()->next() = elem;
        elem->prev() = iter.ptr_()->prev();
        iter.ptr_()->prev() = elem;
        elem->next() = iter.ptr_();
        return ListIterator<T>(elem);
    }

    // Переопределены с использованием итераторов
    ListIterator<T> popIter() {
        if (this->begin().ptr_() == nullptr)
            throw Exception("empty list");
        this->length--;
        Element<T> *res = this->front();
        if (this->front()->next() != nullptr)
            this->front()->next()->prev() = nullptr;
        this->head = this->front()->next();
        res->next() = nullptr;
        return ListIterator<T>(res);
    }

    template <typename U>
    friend ostream &operator<<(ostream &s, OrderedQueue<U> &obj);
};

template <typename T> ostream &operator<<(ostream &s, OrderedQueue<T> &obj) {
    s << "LinkedList(Length : " << obj.length << "){ ";
    ListIterator<T> iter = obj.begin();
    for (ListIterator<T> iter = obj.begin(); iter != obj.end(); ++iter)
        s << *iter << " ";
    s << "}\n";
    return s;
}

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

    bool operator<(Doctor &d) {
        if (rating < d.rating)
            return true;
        else if (rating > d.rating)
            return false;
        else if (experience < d.experience)
            return true;
        else if (experience > d.experience)
            return false;
        else if (lastname < d.lastname)
            return true;
        else if (lastname > d.lastname)
            return false;
        else if (firstname < d.firstname)
            return true;
        else
            return false;
    }
    bool operator>(Doctor &d) {
        if (rating > d.rating)
            return true;
        else if (rating < d.rating)
            return false;
        else if (experience > d.experience)
            return true;
        else if (experience < d.experience)
            return false;
        else if (lastname > d.lastname)
            return true;
        else if (lastname < d.lastname)
            return false;
        else if (firstname > d.firstname)
            return true;
        else
            return false;
    }
    bool operator>=(Doctor &d) { return !(*this < d); }
    bool operator<=(Doctor &d) { return !(*this > d); }
    bool operator==(Doctor &d) {
        if (rating != d.rating)
            return false;
        if (experience != d.experience)
            return false;
        if (lastname != d.lastname)
            return false;
        if (firstname != d.firstname)
            return false;
        return true;
    }
    bool operator!=(Doctor &p) { return !(*this == p); }
};

ostream &operator<<(ostream &s, Doctor d) {
    s << "Doctor{ " << d.lastname << ", " << d.firstname << ", " << d.speciality
      << ", " << d.post << ", " << d.experience << ", " << d.rating << " }\n";
    return s;
}

std::string rstr(size_t length) {
    auto randchar = []() -> char {
        const char charset[] = "0123456789"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

template <typename T>
Queue<T> filter(LinkedListParent<T> &list, function<bool(T)> f) {
    Queue<T> res;
    Element<T> *ptr = list.getHead();
    while (ptr != nullptr) {
        T value = ptr->value();
        if (f(value))
            res.push(value);
        ptr = ptr->next();
        if (ptr == nullptr)
            break;
    }
    return res;
}

int main() {
    Queue<int> q;
    for (int i = 0; i < 10; i++)
        q.push(i);
    cout << q;
    cout << *q.pop() << "\n";
    cout << *q.pop() << "\n";
    cout << *q.pop() << "\n";
    cout << *q.pop() << "\n";
    cout << *q.pop() << "\n";
    cout << q;

    for (int i = 10; i < 20; i++)
        q.push(i);
    cout << q;
    auto qf = filter<int>(q, [](int x) { return x > 14; });
    cout << qf;

    OrderedQueue<int> oq;
    for (int i = 0; i < 10; i++) {
        int ran = rand() / 1000000;
        oq.pushIter(ran);
    }
    cout << oq;
    for (int i = 0; i < 5; i++)
        cout << *oq.popIter() << "\n";
    cout << oq;

    OrderedQueue<Doctor> dq;

    dq.pushIter(Doctor(rstr(5), rstr(6), rstr(5), rstr(7), 5, 38.53));
    dq.pushIter(Doctor(rstr(4), rstr(7), rstr(4), rstr(8), 8, 85.67));
    dq.pushIter(Doctor(rstr(3), rstr(5), rstr(7), rstr(6), 7, 23.92));
    dq.pushIter(Doctor(rstr(6), rstr(7), rstr(5), rstr(4), 4, 75.43));
    dq.pushIter(Doctor(rstr(4), rstr(5), rstr(7), rstr(9), 2, 70.25));
    cout << dq;

    return 0;
}
