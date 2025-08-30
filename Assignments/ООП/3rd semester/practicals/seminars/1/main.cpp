#include <exception>
#include <fstream>
#include <functional>
#include <iostream>

using namespace std;

class Exception : public exception {
  private:
    string message;

  public:
    Exception(string s) : message(s) {}

    const char *what() { return message.c_str(); }
};

template <typename T> class Element {
  private:
    Element *next;
    Element *prev;
    T field;

  public:
    Element(T value = 0, Element<T> *next_ptr = nullptr,
            Element<T> *prev_ptr = nullptr)
        : field(value), next(next_ptr), prev(prev_ptr) {}

    virtual Element *getNext() { return next; }
    virtual void setNext(Element *value) { next = value; }

    virtual Element *getPrevious() { return prev; }
    virtual void setPrevious(Element *value) { prev = value; }

    virtual T getValue() { return field; }
    virtual void setValue(T value) { field = value; }

    template <typename U>
    friend ostream &operator<<(ostream &ustream, Element<T> &obj);
};

template <typename T> ostream &operator<<(ostream &ustream, Element<T> &obj) {
    ustream << obj.field;
    return ustream;
}

template <typename T> class LinkedListParent {
  protected:
    Element<T> *head;
    Element<T> *tail;
    int num;

  public:
    LinkedListParent() {
        cout << "Parent constructor\n";
        head = nullptr;
        num = 0;
    }

    virtual int Number() { return num; }
    virtual Element<T> *getBegin() { return head; }
    virtual Element<T> *getEnd() { return tail; }

    virtual Element<T> *push(T value) = 0;

    virtual Element<T> *pop() = 0;

    virtual ~LinkedListParent() { cout << "Parent destructor\n"; }

    virtual Element<T> *operator[](int i) {
        if (i < 0 || i > num)
            return nullptr;
        int k = 0;
        Element<T> *cur = head;
        for (k = 0; k < i; k++) {
            cur = cur->getNext();
        }
        return cur;
    }

    template <typename U>
    friend ostream &operator<<(ostream &ustream, LinkedListParent<U> &obj);

    template <typename U>
    friend istream &operator>>(istream &ustream, LinkedListParent<U> &obj);
};

template <typename T>
ostream &operator<<(ostream &ustream, LinkedListParent<T> &obj) {
    if (typeid(ustream).name() == typeid(ofstream).name()) {
        ustream << obj.num << "\n";
        for (Element<T> *current = obj.getBegin(); current != nullptr;
             current = current->getNext())
            ustream << current->getValue() << " ";
        return ustream;
    }
    ustream << "Length: " << obj.num << "\n";
    int i = 0;
    for (Element<T> *current = obj.getBegin(); current != nullptr;
         current = current->getNext(), i++)
        ustream << "arr[" << i << "] = " << current->getValue() << "\n";
    return ustream;
}

template <typename T>
istream &operator>>(istream &ustream, LinkedListParent<T> &obj) {
    int len;
    ustream >> len;
    double v = 0;
    for (int i = 0; i < len; i++) {
        ustream >> v;
        obj.push(v);
    }
    return ustream;
}

template <typename T>
class ListIterator : public std::iterator<std::input_iterator_tag, T> {
  private:
    Element<T> *ptr;

  public:
    ListIterator() { ptr = nullptr; }
    ListIterator(Element<T> *p) { ptr = p; }
    ListIterator(const ListIterator &it) { ptr = it.ptr; }

    bool operator!=(ListIterator<T> const &other) const {
        return ptr != other.ptr;
    }

    bool operator==(ListIterator<T> const &other) const {
        return ptr == other.ptr;
    }

    Element<T> &operator*() { return *ptr; }

    ListIterator<T> &operator++() {
        ptr = ptr->getNext();
        return *this;
    }

    ListIterator<T> &operator++(int v) {
        ListIterator<T> res = *this;
        ptr = ptr->getNext();
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
};

template <typename T> class IteratedLinkedList : public LinkedListParent<T> {
  public:
    ListIterator<T> iterator;

    IteratedLinkedList() : LinkedListParent<T>() {
        cout << "IteratedLinkedList constructor\n";
    }

    virtual ~IteratedLinkedList() { cout << "IteratedLinkedList destructor\n"; }

    ListIterator<T> begin() {
        ListIterator<T> it = LinkedListParent<T>::head;
        return it;
    }

    ListIterator<T> end() {
        ListIterator<T> it = LinkedListParent<T>::tail;
        return it;
    }
};

template <typename T> class Queue : public IteratedLinkedList<T> {
  public:
    ~Queue() {};
    Element<T> *push() {};
    Element<T> *pop() {};
};

template <typename T> class OrderedQueue : public Queue<T> {
    Element<T> *push() {};
};

template <typename T>
LinkedListParent<T> filter(LinkedListParent<T> &list, function<bool(T)> f) {
    IteratedLinkedList<T> res;
    Element<T> *ptr = list.getBegin();
    while (ptr != nullptr) {
        T value = ptr->getValue();
        if (f(value))
            res.push(value);
        ptr = ptr->getNext();
        if (ptr == nullptr)
            break;
    }
    return res;
}

int main() { return 0; }
