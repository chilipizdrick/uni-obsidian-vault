#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>

class Exception : public std::exception {
protected:
    std::string message;
public:
    Exception(const std::string& message_) : message(message_) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

template <typename T>
class Element {
protected:
    Element<T>* next_;
    Element<T>* prev_;
    T data_;
public:
    Element(T data) {
        next_ = prev_ = NULL;
        data_ = data;
    }

    Element(Element<T>* next, Element<T>* prev, T data) {
        next_ = next;
        prev_ = prev;
        data_ = data;
    }

    Element(const Element<T>& obj) {
        next_ = obj.next_;
        prev_ = obj.prev_;
        data_ = obj.data_;
    }

    Element<T>*& next() {
        return next_;
    }
    Element<T>*& prev() {
        return prev_;
    }
    T& data() {
        return data_;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& s, Element<U>& obj);
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, Element<T>& elem) {
    stream << elem.data_;
    return stream;
}

template<typename T>
std::istream& operator>>(std::istream& stream, Element<T>& elem) {
    stream >> elem.data_;
    return stream;
}

template <typename T>
class LinkedList {
protected:
    Element<T>* head;
    Element<T>* tail;
    int length;
public:
    LinkedList() {
        head = tail = NULL;
        length = 0;
    }

    LinkedList(const LinkedList<T>& list) {
        this->length = list.length;
        this->head = new Element<T>(list.head->data());
        Element<T>* currNewElem = list.head;
        Element<T>* currElem = this->head;
        while (currNewElem->next() != NULL) {
            currElem->next() = new Element<T>(currNewElem->next()->data());
            currNewElem = currNewElem->next();
            currElem = currElem->next();
        }
        this->tail = currElem;
    }

    virtual ~LinkedList() {
        std::cout << "~LinkedList()\n";
        if (head == NULL) {
            return;
        }
        Element<T>* previous = head;
        Element<T>* current = head->next();
        while (current != NULL) {
            delete previous;
            previous = current;
            current = current->next();
        }
        delete tail;
        length = 0;
        head = tail = NULL;
    }

    virtual Element<T>* getHead() {
        return head;
    }
    virtual Element<T>* getTail() {
        return tail;
    }
    virtual int getLength() {
        return length;
    }

    virtual T& front() {
        return LinkedList<T>::head->data();
    }
    virtual T& back() {
        return LinkedList<T>::tail->data();
    }

    virtual Element<T>* operator[](int index) {
        if (LinkedList<T>::head == NULL /*length == 0*/) {
            throw Exception("index out of bounds when accessing element of LinkedList");
        }
        Element<T>* currElem = LinkedList<T>::head;
        for (int i = 0; i < index && currElem != NULL; i++) {
            currElem = currElem->next();
        }
        if (currElem == NULL) {
            throw Exception("index out of bounds when accessing element of LinkedList");
        }
        return currElem;
    }

    virtual T pop() = 0;
    virtual Element<T>* push(T value) = 0;


    template<typename U>
    friend void save(LinkedList<U>& list, std::string filename);
    template<typename U>
    friend void load(LinkedList<U>& list, std::string filename);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& s, LinkedList<U>& obj);
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, LinkedList<T>& list) {
    if (typeid(stream).name() == typeid(std::ofstream).name()) {
        stream << list.length << "\n";
        Element<T>* currElem = list.LinkedList<T>::head;
        while (currElem != NULL) {
            stream << *currElem << "\n";
            currElem = currElem->next();
        }
        return stream;
    }

    stream << "LinkedList{ ";
    for (Element<T>* currElem = list.head;
        currElem != NULL; currElem = currElem->next()) {
        stream << *currElem;
        if (currElem != list.tail) {
            stream << "; ";
        }
    }
    stream << " }\n";
    return stream;
}

template <typename T>
std::istream& operator>>(std::istream& stream, LinkedList<T>& list) {
    int listLength;
    stream >> listLength;
    for (int i = 0; i < listLength; i++) {
        T data;
        stream >> data;
        list.push(data);
    }
    return stream;
}

template <typename T>
class Stack : virtual public LinkedList<T> {
public:
    Stack() : LinkedList<T>() {};

    Stack(const Stack<T>& list) {
        this->length = list.length;
        this->head = new Element<T>(list.head->data());
        Element<T>* currNewElem = list.head;
        Element<T>* currElem = this->head;
        while (currNewElem->next() != NULL) {
            currElem->next() = new Element<T>(currNewElem->next()->data());
            currNewElem = currNewElem->next();
            currElem = currElem->next();
        }
        this->tail = currElem;
    }

    Element<T>* push(T value) {
        Element<T>* newElemPtr = new Element<T>(value);
        if (LinkedList<T>::tail == NULL /*length == 0*/) {
            // newElemPtr->next = NULL;
            LinkedList<T>::head = LinkedList<T>::tail = newElemPtr;
        }
        else {
            // newElemPtr->next = NULL;
            LinkedList<T>::tail->next() = newElemPtr;
            LinkedList<T>::tail = newElemPtr;
        }
        LinkedList<T>::length++;
        return LinkedList<T>::tail;
    }

    T pop() {
        if (LinkedList<T>::head == NULL /*length == 0*/) {
            throw Exception("error calling pop() on empty LinkedList");
        }
        T res;
        if (LinkedList<T>::head->next() == NULL /*length == 0*/) {
            res = LinkedList<T>::head->data();
            LinkedList<T>::head->next() = LinkedList<T>::tail->next() = NULL;
            LinkedList<T>::head = LinkedList<T>::tail = NULL;
            LinkedList<T>::length--;
            return res;
        }
        res = LinkedList<T>::tail->data();
        Element<T>* currElem = LinkedList<T>::head;
        while (currElem->next() != LinkedList<T>::tail) {
            currElem = currElem->next();
        }
        LinkedList<T>::tail = currElem;
        LinkedList<T>::tail->next() = NULL;
        LinkedList<T>::length--;
        return res;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& s, Stack<U>& obj);
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, Stack<T>& list) {
    stream << "Stack{ ";
    for (Element<T>* currElem = list.head;
        currElem != NULL; currElem = currElem->next()) {
        stream << *currElem;
        if (currElem != list.tail) {
            stream << "; ";
        }
    }
    stream << " }\n";
    return stream;
}

template <typename T>
class Queue : virtual public LinkedList<T> {
public:
    Queue() : LinkedList<T>() {};

    Queue(const Queue<T>& list) {
        this->length = list.length;
        this->head = new Element<T>(list.head->data());
        Element<T>* currNewElem = list.head;
        Element<T>* currElem = this->head;
        while (currNewElem->next() != NULL) {
            currElem->next() = new Element<T>(currNewElem->next()->data());
            currNewElem = currNewElem->next();
            currElem = currElem->next();
        }
        this->tail = currElem;
    }

    Element<T>* push(T value) {
        Element<T>* newElemPtr = new Element<T>(value);
        if (LinkedList<T>::tail == NULL /*length == 0*/) {
            // newElemPtr->next = NULL;
            LinkedList<T>::head = LinkedList<T>::tail = newElemPtr;
        }
        else {
            // newElemPtr->next = NULL;
            LinkedList<T>::tail->next() = newElemPtr;
            LinkedList<T>::tail = newElemPtr;
        }
        LinkedList<T>::length++;
        return LinkedList<T>::tail;
    }

    T pop() {
        if (LinkedList<T>::head == NULL /*length == 0*/) {
            throw Exception("error calling pop() on empty LinkedList");
        }
        T res = LinkedList<T>::head->data();
        LinkedList<T>::head = LinkedList<T>::head->next();
        LinkedList<T>::length--;
        return res;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& s, Queue<U>& obj);
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, Queue<T>& list) {
    stream << "Queue{ ";
    for (Element<T>* currElem = list.head;
        currElem != NULL; currElem = currElem->next()) {
        stream << *currElem;
        if (currElem != list.tail) {
            stream << "; ";
        }
    }
    stream << " }\n";
    return stream;
}

template <typename T>
class StackQueue : virtual protected Stack<T>, virtual protected Queue<T> {
public:
    StackQueue() : Stack<T>(), Queue<T>() {};

    StackQueue(const StackQueue<T>& list) {
        this->length = list.length;
        this->head = new Element<T>(list.head->data());
        Element<T>* currNewElem = list.head;
        Element<T>* currElem = this->head;
        while (currNewElem->next() != NULL) {
            currElem->next() = new Element<T>(currNewElem->next()->data());
            currNewElem = currNewElem->next();
            currElem = currElem->next();
        }
        this->tail = currElem;
    }

    virtual ~StackQueue() {
        std::cout << "~StackQueue()\n";
        if (LinkedList<T>::head == NULL) {
            return;
        }
        Element<T>* previous = LinkedList<T>::head;
        Element<T>* current = LinkedList<T>::head->next();
        while (current != NULL) {
            delete previous;
            previous = current;
            current = current->next();
        }
        delete LinkedList<T>::tail;
        LinkedList<T>::length = 0;
        LinkedList<T>::head = LinkedList<T>::tail = NULL;
    }

    Element<T>* pushFront(T value) {
        Element<T>* newElemPtr = new Element<T>(value);
        if (Stack<T>::head == NULL /*length == 0*/) {
            // newElemPtr->next = NULL;
            Stack<T>::head = Stack<T>::tail = newElemPtr;
        }
        else {
            // newElemPtr->next = NULL;
            newElemPtr->next() = Stack<T>::head;
            Stack<T>::head = newElemPtr;
        }
        Stack<T>::length++;
        return Stack<T>::head;
    }

    Element<T>* pushBack(T value) {
        return Stack<T>::push(value);
    }

    T popFront() {
        return Queue<T>::pop();
    }

    T popBack() {
        return Stack<T>::pop();
    }

    // Для совместимости с интерфейсом LinkedList<T>
    T pop() {
        return Stack<T>::pop();
    }

    Element<T>* push(T value) {
        return Stack<T>::push(value);
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& s, StackQueue<U>& obj);
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, StackQueue<T>& list) {
    stream << "StackQueue{ ";
    for (Element<T>* currElem = list.Stack<T>::head;
        currElem != NULL; currElem = currElem->next()) {
        stream << *currElem;
        if (currElem != list.Stack<T>::tail) {
            stream << "; ";
        }
    }
    stream << " }\n";
    return stream;
}



template <typename T>
class DoublyLinkedStack : public Stack<T> {
protected:
    Element<T>* getElementByIndex(int index) {
        if (LinkedList<T>::tail == NULL /*length == 0*/) {
            throw Exception("index out of bounds when accessing element of LinkedList");
        }
        Element<T>* currElem;
        if (index <= LinkedList<T>::length / 2) {
            currElem = LinkedList<T>::head;
            for (int i = 0; i < index && currElem != NULL; i++) {
                currElem = currElem->next();
            }
        }
        else {
            currElem = LinkedList<T>::tail;
            for (int i = LinkedList<T>::length - 1; i > index && currElem != NULL; i--) {
                currElem = currElem->prev();
            }
        }
        if (currElem == NULL) {
            throw Exception("index out of bounds when accessing element of LinkedList");
        }
        return currElem;
    }

public:
    DoublyLinkedStack() : Stack<T>() {};

    DoublyLinkedStack(const DoublyLinkedStack<T>& list) {
        this->length = list.length;
        this->head = new Element<T>(list.head->data());
        Element<T>* currNewElem = list.head;
        Element<T>* currElem = this->head;
        while (currNewElem->next() != NULL) {
            currElem->next() = new Element<T>(currNewElem->next()->data());
            currElem->next()->prev() = currElem;
            currNewElem = currNewElem->next();
            currElem = currElem->next();
        }
        this->tail = currElem;
    }

    Element<T>* push(T value) {
        Element<T>* newElemPtr = new Element<T>(value);
        if (LinkedList<T>::tail == NULL /*length == 0*/) {
            // newElemPtr->next = NULL;
            // newElemPtr->prev = NULL;
            LinkedList<T>::head = LinkedList<T>::tail = newElemPtr;
        }
        else {
            // newElemPtr->next = NULL;
            newElemPtr->prev() = LinkedList<T>::tail;
            LinkedList<T>::tail->next() = newElemPtr;
            LinkedList<T>::tail = newElemPtr;
        }
        LinkedList<T>::length++;
        return LinkedList<T>::tail;
    }

    T pop() {
        if (LinkedList<T>::tail == NULL /*length == 0*/) {
            throw Exception("error calling pop() on empty stack");
        }
        T res = LinkedList<T>::tail->data();
        LinkedList<T>::tail = LinkedList<T>::tail->prev();
        LinkedList<T>::tail->next()->prev() = NULL;
        LinkedList<T>::tail->next() = NULL;
        LinkedList<T>::length--;
        return res;
    }

    // Переопределение операции индексации с оптимизацией работы на двусвязном списке
    Element<T>* operator[](int index) {
        return getElementByIndex(index);
    }

    Element<T>* insert(T value, Element<T>* elem) {
        Element<T>* newElem = new Element<T>(value);

        newElem->next() = elem;
        newElem->prev() = elem->prev();
        elem->prev()->next() = newElem;
        elem->prev() = newElem;
        LinkedList<T>::length += 1;

        return newElem;
    }

    T remove(Element<T>* elem) {
        elem->prev()->next() = elem->next();
        elem->next()->prev() = elem->prev();
        T value = elem->data();
        delete elem;
        LinkedList<T>::length -= 1;

        return value;
    }

    Element<T>* find(std::function<bool(T)> findFunc) {
        Element<T>* currElem = LinkedList<T>::head;
        while (currElem != NULL) {
            if (findFunc(currElem->data())) {
                return currElem;
            }
            currElem = currElem->next();
        }
        if (currElem == NULL) {
            throw Exception("item not found");
        }
        return NULL;
    }

    Element<T>* find(T value) {
        return find([value](T x) { return x == value; });
    }

    Element<T>* findRecursive(T value, Element<T>* currElem) {
        if (currElem == NULL) {
            throw Exception("element not found in LinkedList");
        }
        if (currElem->data() == value) {
            return currElem;
        }
        return findRecursive(value, currElem->next());
    }

    DoublyLinkedStack<T> filter(std::function<bool(T)> filterFunc) {
        DoublyLinkedStack<T> res = DoublyLinkedStack<T>();
        Element<T>* currElem = LinkedList<T>::head;
        while (currElem != NULL) {
            if (filterFunc(currElem->data())) {
                res.push(currElem->data());
            }
            currElem = currElem->next();
        }
        return res;
    }

    DoublyLinkedStack<T> filterRecursive(std::function<bool(T)> filterFunc, Element<T>* currElem, DoublyLinkedStack<T>* res = NULL) {
        if (res == NULL) {
            res = new DoublyLinkedStack<T>();
        }
        if (currElem == NULL) {
            return *res;
        }
        if (filterFunc(currElem->data())) {
            res->push(currElem->data());
        }
        return filterRecursive(filterFunc, currElem->next(), res);
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& s, DoublyLinkedStack<U>& obj);
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, DoublyLinkedStack<T>& list) {
    stream << "DoublyLinkedStack{ ";
    for (Element<T>* currElem = list.Stack<T>::head;
        currElem != NULL; currElem = currElem->next()) {
        stream << *currElem;
        if (currElem != list.Stack<T>::tail) {
            stream << "; ";
        }
    }
    stream << " }\n";
    return stream;
}

class Customer {
public:
    std::string firstname, lastname, city, street;
    int houseNumber, apartmentNumber, avgCheck;
    long long accountNumber;

    Customer() {
        firstname = lastname = city = street = "";
        houseNumber = apartmentNumber = avgCheck = 0;
        accountNumber = 0;
    }

    Customer(const std::string firstname_, const std::string lastname_,
        const std::string city_, const std::string street_,
        int houseNumber_, int apatrmentNumber_, int avgCheck_,
        long long accountNumber_) :
        firstname(firstname_), lastname(lastname_), city(city_),
        street(street_), houseNumber(houseNumber_),
        apartmentNumber(apatrmentNumber_), avgCheck(avgCheck_),
        accountNumber(accountNumber_) {}
};

std::ostream& widthManipulator(std::ostream& stream) {
    stream.width(5);
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Customer obj) {
    if (typeid(stream).name() == typeid(std::ofstream).name()) {
        stream << obj.firstname << "\n";
        stream << obj.lastname << "\n";
        stream << obj.city << "\n";
        stream << obj.street << "\n";
        stream << obj.houseNumber << "\n";
        stream << obj.apartmentNumber << "\n";
        stream << obj.accountNumber << "\n";
        stream << obj.avgCheck << "\n";
        return stream;
    }

    stream << "Customer{";
    stream << obj.firstname << ",";
    stream << obj.lastname << ",";
    stream << obj.city << ",";
    stream << obj.street << ",";
    stream << obj.houseNumber << widthManipulator << ",";
    stream << obj.apartmentNumber << widthManipulator << ",";
    stream << obj.accountNumber << widthManipulator << ",";
    stream << obj.avgCheck << widthManipulator << "}";
    return stream;
}

std::istream& operator>>(std::istream& stream, Customer& obj) {
    stream >> obj.firstname;
    stream >> obj.lastname;
    stream >> obj.city;
    stream >> obj.street;
    stream >> obj.houseNumber;
    stream >> obj.apartmentNumber;
    stream >> obj.accountNumber;
    stream >> obj.avgCheck;
    return stream;
}

template <typename T>
class List : protected DoublyLinkedStack<T> {
public:
    List() : DoublyLinkedStack<T>() {};

    List(const List<T>& list) {
        this->length = list.length;
        this->head = new Element<T>(list.head->data());
        Element<T>* currNewElem = list.head;
        Element<T>* currElem = this->head;
        while (currNewElem->next() != NULL) {
            currElem->next() = new Element<T>(currNewElem->next()->data());
            currElem->next()->prev() = currElem;
            currNewElem = currNewElem->next();
            currElem = currElem->next();
        }
        this->tail = currElem;
    }

    virtual ~List() {
        std::cout << "~List()\n";
        if (DoublyLinkedStack<T>::head == NULL) {
            return;
        }
        Element<T>* previous = DoublyLinkedStack<T>::head;
        Element<T>* current = DoublyLinkedStack<T>::head->next();
        while (current != NULL) {
            delete previous;
            previous = current;
            current = current->next();
        }
        delete DoublyLinkedStack<T>::tail;
        DoublyLinkedStack<T>::length = 0;
        DoublyLinkedStack<T>::head = DoublyLinkedStack<T>::tail = NULL;
    }

    Element<T>* push(T value) {
        return DoublyLinkedStack<T>::push(value);
    }

    T pop() {
        if (DoublyLinkedStack<T>::head == NULL /*length == 0*/) {
            throw Exception("error calling pop() on empty LinkedList");
        }
        T res = DoublyLinkedStack<T>::head->data();
        DoublyLinkedStack<T>::head = DoublyLinkedStack<T>::head->next();
        DoublyLinkedStack<T>::length--;
        return res;
    }

    Element<T>* find(T value) {
        return DoublyLinkedStack<T>::find(value);
    }

    Element<T>* find(std::function<bool(T)> findFunc) {
        return DoublyLinkedStack<T>::find(findFunc);
    }

    List<T> filter(std::function<bool(T)> filterFunc) {
        List<T> res = List<T>();
        Element<T>* currElem = LinkedList<T>::head;
        while (currElem != NULL) {
            if (filterFunc(currElem->data())) {
                res.push(currElem->data());
            }
            currElem = currElem->next();
        }
        return res;
    }

    template <typename U>
    friend void save(List<U>& list, std::string filename);
    template <typename U>
    friend void load(List<U>& list, std::string filename);
    template <typename U>
    friend std::ostream& operator<<(std::ostream& s, List<U>& obj);
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, List<T>& list) {
    if (typeid(stream).name() == typeid(std::ofstream).name()) {
        stream << list.length << "\n";
        Element<T>* currElem = list.List<T>::head;
        while (currElem != NULL) {
            stream << *currElem << "\n";
            currElem = currElem->next();
        }
        return stream;
    }

    stream << "List{\n";
    for (Element<T>* currElem = list.Stack<T>::head;
        currElem != NULL; currElem = currElem->next()) {
        stream << "\t" << *currElem;
        if (currElem != list.Stack<T>::tail) {
            stream << ";\n";
        }
    }
    stream << "\n}\n";
    return stream;
}

template <typename T>
std::istream& operator>>(std::istream& stream, List<T>& list) {
    int listLength;
    stream >> listLength;
    for (int i = 0; i < listLength; i++) {
        T data;
        stream >> data;
        list.push(data);
    }
    return stream;
}

template <typename T>
void fillRand(LinkedList<T>& list, int length, T lwr = (T)0, T upr = (T)10) {
    for (int i = 0; i < length; i++) {
        list.push(T(lwr + ((double)rand() / RAND_MAX) * (upr - lwr)));
    }
}

template <typename T>
void load(LinkedList<T>& list, std::string filename) {
    if (list.LinkedList<T>::head != NULL) {
        std::cout << "[WARNING] Writing to non empty list (default behaviour is to append input at the end of the list)\n";
    }
    std::ifstream fin;
    fin.open(filename);
    fin >> list;
    fin.close();
}

template <typename T>
void save(LinkedList<T>& list, std::string filename) {
    std::ofstream fout;
    fout.open(filename);
    fout << list;
    fout.close();
}

template <typename T>
void load(List<T>& list, std::string filename) {
    if (list.List<T>::head != NULL) {
        std::cout << "[WARNING] Writing to non empty list\n";
    }
    std::ifstream fin;
    fin.open(filename);
    fin >> list;
    fin.close();
}

template <typename T>
void save(List<T>& list, std::string filename) {
    std::ofstream fout;
    fout.open(filename);
    fout << list;
    fout.close();
}

int main() {
    std::cout << "----- Task 6.1 -----\n";
    std::cout << "--- Stack ---\n";
    Stack<int> s;
    fillRand(s, 5, 0, 10);
    std::cout << s;
    s.push(123);
    std::cout << s;
    std::cout << s.pop() << "\n";
    std::cout << s.pop() << "\n";
    std::cout << s.pop() << "\n";
    std::cout << s;
    std::cout << "\n";

    std::cout << "--- Queue ---\n";
    Queue<double> q;
    fillRand(q, 5, 0.0, 10.0);
    std::cout << q;
    q.push(123);
    q.push(321);
    std::cout << q;
    std::cout << q.pop() << "\n";
    std::cout << q.pop() << "\n";
    std::cout << q;
    std::cout << "\n";

    std::cout << "--- StackQueue ---\n";
    StackQueue<std::string> sq;
    for (int i = 0; i < 5; i++) {
        sq.pushBack(std::to_string(i));
    }
    sq.pushFront("Push Front");
    sq.pushBack("Push Back");
    std::cout << sq;
    std::cout << sq.popFront() << "\n";
    std::cout << sq.popBack() << "\n";
    std::cout << sq;
    std::cout << "\n";

    std::cout << "--- DoublyLinkedStack ---\n";
    DoublyLinkedStack<int> dls;
    fillRand(dls, 10, 0, 10);
    std::cout << dls;
    dls.push(123);
    std::cout << dls;
    std::cout << dls.pop() << "\n";
    std::cout << dls.pop() << "\n";
    std::cout << dls.pop() << "\n";
    std::cout << dls;
    std::cout << dls[3]->data() << "\n";
    std::cout << dls[4]->data() << "\n";
    std::cout << dls[5]->data() << "\n";
    std::cout << dls[6]->data() << "\n";
    dls.insert(100, dls[4]);
    std::cout << dls;
    std::cout << dls.remove(dls[4]) << "\n";
    std::cout << dls;
    dls.find(5)->data() = 200;
    std::cout << dls;
    dls.findRecursive(3, dls.getHead())->data() = 300;
    std::cout << dls;
    DoublyLinkedStack<int> dls2 = dls.filter([](int x) { return x < 5 && x >= 0; });
    std::cout << dls2;
    DoublyLinkedStack<int> dls3 = dls.filterRecursive([](int x) { return x < 5 && x >= 0; }, dls.getHead());
    std::cout << dls3;
    std::cout << "\n";

    std::cout << "--- List ---\n";
    std::cout << "Numbers are misplaced because of the implemented widthManipulator (set width to 5 while displaying numbers)." << "\n";
    List<Customer> cl;
    cl.push(Customer("a", "b", "c", "d", 1, 2, 3, 4));
    cl.push(Customer("e", "f", "g", "h", 5, 6, 7, 8));
    cl.push(Customer("i", "j", "k", "l", 9, 10, 11, 12));
    cl.push(Customer("m", "n", "o", "p", 13, 14, 15, 16));
    cl.push(Customer("w", "x", "y", "z", 17, 18, 19, 20));
    std::cout << cl;
    std::cout << cl.pop() << "\n";
    std::cout << cl;
    std::cout << "Search by lastname (\"j\"): \n";
    std::cout << cl.find([](Customer x) {return x.lastname == "j";})->data() << "\n";
    std::cout << "Filter by avgCheck (x > 10):\n";
    List cl2 = cl.filter([](Customer x) { return x.avgCheck > 10; });
    std::cout << cl2;
    std::cout << "\n";

    std::cout << "----- Task 6.2 -----\n";
    std::cout << "Custom filter function: \n";
    List cl3 = cl.filter([](Customer x) { return x.avgCheck > 10 && x.houseNumber < 12; });
    std::cout << cl3;
    std::cout << "\n";

    LinkedList<int>* memoryTest = new Stack<int>();
    fillRand(*memoryTest, 5, 0, 10);
    std::cout << *memoryTest;
    Stack<int>* memoryTest2 = dynamic_cast<Stack<int>*>(memoryTest);
    // Деструктор работает при вызове delete для любого из указателей
    std::cout << *memoryTest2;
    // delete memoryTest;
    delete memoryTest2;
    std::cout << "\n";

    Stack<double> s1, s2;
    fillRand(s1, 10, 0.0, 1.0);
    std::cout << "Saving object s1: " << s1;
    save(s1, "a.txt");
    load(s2, "a.txt");
    std::cout << "Loading object s2: " << s2;
    List<Customer> cl4;
    std::cout << "Saving object cl: " << cl;
    save(cl, "b.txt");
    load(cl4, "b.txt");
    std::cout << "Loading object cl4: " << cl4;
    std::cout << "\n";

    std::cout << "Copy constructor:\n";
    Stack<int> s3 = Stack(s);
    std::cout << s3;
    DoublyLinkedStack<int> dls5 = DoublyLinkedStack(dls);
    std::cout << dls5;
    std::cout << "\n";

    // В итоге отработали все деструкторы (13 из 13)

    return 0;
}
