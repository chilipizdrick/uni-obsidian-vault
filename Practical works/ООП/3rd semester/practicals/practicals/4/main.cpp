#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>

using namespace std;

class Exception : public exception {
  protected:
    string message;

  public:
    Exception() { message = ""; }
    Exception(const string &message_) : message(message_) {}
    const char *what() const noexcept override { return message.c_str(); }
};

class EqualKeysException : public Exception {
  public:
    EqualKeysException() : Exception("error on equal keys in tree") {}
};

class NullIteratorException : public Exception {
  public:
    NullIteratorException()
        : Exception("manipulation of iterator pointing to nullptr") {};
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

    Element<T> *operator[](int idx) {
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
            throw NullIteratorException();
        return ptr->value();
    }

    ListIterator<T> operator++() {
        if (ptr == nullptr)
            throw NullIteratorException();
        prevPtr = ptr;
        ptr = ptr->next();
        return *this;
    }

    ListIterator<T> operator++(int v) {
        if (ptr == nullptr)
            throw NullIteratorException();
        ListIterator<T> res = *this;
        prevPtr = ptr;
        ptr = ptr->next();
        return res;
    }

    ListIterator<T> operator--() {
        if (prevPtr == nullptr)
            throw NullIteratorException();
        ptr = ptr->prev();
        return *this;
    }

    ListIterator<T> operator--(int v) {
        if (prevPtr == nullptr)
            throw NullIteratorException();
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

template <typename K, typename V> class Node {
  protected:
    K key;
    V value;
    int height;
    Node<K, V> *left;
    Node<K, V> *right;
    Node<K, V> *parent;

  public:
    virtual V getValue() { return value; }
    virtual K getKey() { return key; }
    virtual int getHeight() { return height; }
    virtual Node<K, V> *getLeft() { return left; }
    virtual Node<K, V> *getRight() { return right; }
    virtual Node<K, V> *getParent() { return parent; }

    virtual void setValue(V value_) { value = value_; }
    virtual void setKey(K key_) { key = key_; }
    virtual void setHeight(int height_) { height = height_; }
    virtual void setLeft(Node<K, V> *left_) { left = left_; }
    virtual void setRight(Node<K, V> *right_) { right = right_; }
    virtual void setParent(Node<K, V> *parent_) { parent = parent_; }

    Node(K key_, V value_) {
        key = key_;
        value = value_;
        left = right = parent = nullptr;
        height = 0;
    }

    Node() {
        key = K();
        value = V();
        left = right = parent = nullptr;
        height = 0;
    }

    virtual ~Node() {}

    template <typename K_, typename V_>
    friend ostream &operator<<(ostream &stream, Node<K_, V_> &node);
};

template <typename K, typename V>
ostream &operator<<(ostream &stream, Node<K, V> &node) {
    stream << "Node{ key: " << node.key << ", value: " << node.value
           << ", height: " << node.height << " }";
    return stream;
}

template <typename K, typename V>
class TreeIterator : public iterator<input_iterator_tag, K, V> {
  private:
    Node<K, V> *ptr;
    Node<K, V> *prevPtr;

    Node<K, V> *max_node(Node<K, V> *node) {
        Node<K, V> *res = node;
        while (res->getRight()) {
            res = res->getRight();
        }
        return res;
    }

  public:
    TreeIterator() : ptr(nullptr), prevPtr(nullptr) {}
    TreeIterator(Node<K, V> *p, Node<K, V> *pp = nullptr)
        : ptr(p), prevPtr(pp) {}
    TreeIterator(const TreeIterator &it) : ptr(it.ptr), prevPtr(it.prevPtr) {}

    Node<K, V> *&ptr_() { return this->ptr; }
    Node<K, V> *&prevPtr_() { return this->prevPtr; }

    bool operator==(TreeIterator<K, V> const other) const {
        return ptr == other.ptr && prevPtr == other.prevPtr;
    }

    bool operator!=(TreeIterator<K, V> const other) const {
        return ptr != other.ptr || prevPtr != other.prevPtr;
    }

    Node<K, V> operator*() {
        if (ptr == nullptr)
            throw NullIteratorException();
        return *ptr;
    }

    TreeIterator<K, V> operator++() {
        if (ptr == nullptr)
            throw NullIteratorException();
        prevPtr = ptr;
        if (ptr->getRight() != nullptr) {
            ptr = ptr->getRight();
            while (ptr->getLeft() != nullptr)
                ptr = ptr->getLeft();
        } else {
            Node<K, V> *p;
            p = ptr->getParent();
            while (p != nullptr && ptr == p->getRight()) {
                ptr = p;
                p = p->getParent();
            }
            ptr = p;
        }
        return *this;
    }

    TreeIterator<K, V> operator++(int v) {
        TreeIterator<K, V> res = *this;
        ++*this;
        return res;
    }

    TreeIterator<K, V> operator--() {
        if (prevPtr == nullptr)
            throw NullIteratorException();
        ptr = prevPtr;
        if (prevPtr->getLeft() != nullptr)
            prevPtr = max_node(prevPtr->getLeft());
        else {
            Node<K, V> *p = prevPtr;
            prevPtr = prevPtr->getParent();
            while (prevPtr != nullptr && prevPtr->getLeft() == p) {
                p = prevPtr;
                prevPtr = prevPtr->getParent();
            }
        }
        return *this;
    }

    TreeIterator<K, V> operator--(int v) {
        TreeIterator<K, V> res = *this;
        --*this;
        return res;
    }

    TreeIterator<K, V> &operator=(const TreeIterator<K, V> &it) {
        ptr = it.ptr;
        prevPtr = it.prevPtr;
        return *this;
    }

    TreeIterator<K, V> &operator=(Node<K, V> *n) {
        ptr = n;
        prevPtr = nullptr;
        return *this;
    }

    template <typename K_, typename V_>
    friend ostream &operator<<(ostream &s, TreeIterator<K_, V_> &obj);
};

template <typename K, typename V>
ostream &operator<<(ostream &s, TreeIterator<K, V> &obj) {
    Node<K, V> node = *obj;
    s << node;
    return s;
}

template <typename K, typename V> class Tree {
  protected:
    Node<K, V> *root = nullptr;

    Node<K, V> *getMaxNode(Node<K, V> *node) {
        if (node->getLeft() == nullptr && node->getRight() == nullptr)
            return nullptr;
        if (node->getLeft() != nullptr && node->getRight() == nullptr)
            return node->getLeft();
        if (node->getLeft() == nullptr && node->getRight() != nullptr)
            return node->getRight();
        if (node->getLeft()->getKey() > node->getRight()->getKey())
            return node->getLeft();
        return node->getRight();
    }

  public:
    Tree() { root = nullptr; }

    Tree(const Tree<K, V> &tree) {
        root = new Node<K, V>(tree.root->getKey(), tree.root->getValue());
        copyTreeRecursive(root, tree.root);
    }

    virtual TreeIterator<K, V> begin() const {
        return TreeIterator<K, V>(min(), nullptr);
    }

    virtual TreeIterator<K, V> end() const {
        return TreeIterator<K, V>(nullptr, max());
    }

    void copyTreeRecursive(Node<K, V> *node, Node<K, V> *copiedNode) {
        if (copiedNode->getLeft() != nullptr) {
            node->setLeft(new Node<K, V>(copiedNode->getLeft()->getKey(),
                                         copiedNode->getLeft()->getValue()));
            copyTreeRecursive(node->getLeft(), copiedNode->getLeft());
        }
        if (copiedNode->getRight() != nullptr) {
            node->setRight(new Node<K, V>(copiedNode->getRight()->getKey(),
                                          copiedNode->getRight()->getValue()));
            copyTreeRecursive(node->getRight(), copiedNode->getRight());
        }
    }

    virtual ~Tree() {
        cout << "~Tree\n";
        postOrder([](Node<K, V> *node) {
            if (node != nullptr)
                delete node;
        });
    }

    virtual Node<K, V> *getRoot() const { return root; }

    virtual Node<K, V> *pushNodeRecursive(Node<K, V> *newNode) {
        return pushNodeRecursive(newNode, root);
    }
    virtual Node<K, V> *pushNodeRecursive(Node<K, V> *newNode,
                                          Node<K, V> *currNode) {
        if (newNode == nullptr)
            return nullptr;
        if (root == nullptr) {
            root = newNode;
            return root;
        }
        if (currNode->getKey() > newNode->getKey()) {
            if (currNode->getLeft()) {
                return pushNodeRecursive(newNode, currNode->getLeft());
            } else {
                currNode->setLeft(newNode);
                newNode->setParent(currNode);
                return newNode;
            }
        }
        if (currNode->getKey() < newNode->getKey()) {
            if (currNode->getRight()) {
                return pushNodeRecursive(newNode, currNode->getRight());
            } else {
                currNode->setRight(newNode);
                newNode->setParent(currNode);
                return newNode;
            }
        }
        if (currNode->getKey() == newNode->getKey())
            throw EqualKeysException();
        return nullptr;
    }

    virtual TreeIterator<K, V> push(K key, V value) {
        Node<K, V> *newNode = new Node<K, V>(key, value);
        pushNodeRecursive(newNode);
        return TreeIterator(newNode);
    }

    virtual Node<K, V> *min() const { return min(root); }
    virtual Node<K, V> *min(Node<K, V> *currNode) const {
        while (currNode->getLeft() != nullptr)
            currNode = currNode->getLeft();
        return currNode;
    }

    virtual Node<K, V> *max() const { return max(root); }
    virtual Node<K, V> *max(Node<K, V> *currNode) const {
        while (currNode->getRight() != nullptr)
            currNode = currNode->getRight();
        return currNode;
    }

    virtual TreeIterator<K, V> findByKey(function<bool(K)> f) const {
        return findByKey(f, root);
    }
    virtual TreeIterator<K, V> findByKey(function<bool(K)> f,
                                         Node<K, V> *currNode) const {
        for (TreeIterator<K, V> iter = this->begin(); iter != this->end();
             iter++) {
            if (f((*iter).getKey())) {
                return iter;
            }
        }
        return this->end();
    }

    virtual TreeIterator<K, V> findByValue(function<bool(V)> f) const {
        return findByValue(f, root);
    }
    virtual TreeIterator<K, V> findByValue(function<bool(V)> f,
                                           Node<K, V> *currNode) const {
        for (TreeIterator<K, V> iter = this->begin(); iter != this->end();
             iter++) {
            if (f((*iter).getValue())) {
                return iter;
            }
        }
        return this->end();
    }

    V _find(K key) { return _find(key, this->root); }
    V _find(K key, Node<K, V> *currNode) {
        if (key < currNode->getKey()) {
            return _find(key, currNode->getLeft());
        }
        if (key > currNode->getKey()) {
            return _find(key, currNode->getRight());
        }
        if (key == currNode->getKey()) {
            return currNode->getValue();
        }
        return V();
    }

    Node<K, V> *_findNode(K key) { return _findNode(key, this->root); }
    Node<K, V> *_findNode(K key, Node<K, V> *currNode) {
        if (key < currNode->getKey()) {
            return _findNode(key, currNode->getLeft());
        }
        if (key > currNode->getKey()) {
            return _findNode(key, currNode->getRight());
        }
        if (key == currNode->getKey()) {
            return currNode;
        }
        return nullptr;
    }

    // Не virtual т.к. у наследника MultiTree иной возвращаемый тип
    TreeIterator<K, V> operator[](K key) {
        return TreeIterator(_findNode(key));
    }

    virtual void preOrder(function<void(Node<K, V> *)> f) {
        return preOrder(root, f);
    }
    virtual void preOrder(Node<K, V> *node, function<void(Node<K, V> *)> f) {
        if (node != nullptr)
            f(node);
        if (node != nullptr && node->getLeft() != nullptr)
            preOrder(node->getLeft(), f);
        if (node != nullptr && node->getRight() != nullptr)
            preOrder(node->getRight(), f);
    }

    virtual void inOrder(function<void(Node<K, V> *)> f) {
        return inOrder(root, f);
    }
    virtual void inOrder(Node<K, V> *node, function<void(Node<K, V> *)> f) {
        if (node != nullptr && node->getLeft() != nullptr)
            inOrder(node->getLeft(), f);
        if (node != nullptr)
            f(node);
        if (node != nullptr && node->getRight() != nullptr)
            inOrder(node->getRight(), f);
    }

    virtual void postOrder(function<void(Node<K, V> *)> f) {
        return postOrder(root, f);
    }
    virtual void postOrder(Node<K, V> *node, function<void(Node<K, V> *)> f) {
        if (node != nullptr && node->getLeft() != nullptr)
            postOrder(node->getLeft(), f);
        if (node != nullptr && node->getRight() != nullptr)
            postOrder(node->getRight(), f);
        if (node != nullptr)
            f(node);
    }

    virtual void remove(Node<K, V> *node) {
        if (node->getRight() == nullptr && node->getLeft() == nullptr) {
            if (node == root) {
                root = nullptr;
                return;
            }
            Node<K, V> *parent = node->getParent();
            if (parent->getLeft() == node) {
                parent->setLeft(nullptr);
            } else {
                parent->setRight(nullptr);
            }
            node->setParent(nullptr);
            return;
        } else if (node->getLeft() == nullptr) {
            if (node == root) {
                root = root->getRight();
                return;
            }
            Node<K, V> *parent = node->getParent();
            if (parent->getLeft() == node) {
                parent->setLeft(node->getRight());
            } else {
                parent->setRight(node->getRight());
            }
            node->setParent(nullptr);
            return;
        } else if (node->getRight() == nullptr) {
            if (node == root) {
                root = root->getLeft();
                return;
            }
            Node<K, V> *parent = node->getParent();
            if (parent->getLeft() == node) {
                parent->setLeft(node->getLeft());
            } else {
                parent->setRight(node->getLeft());
            }
            node->setParent(nullptr);
            return;
        } else {
            Node<K, V> *maxNode = getMaxNode(node);
            remove(maxNode);
            maxNode->setLeft(node->getLeft());
            maxNode->setRight(node->getRight());
            maxNode->setParent(node->getParent());
            maxNode->setHeight(node->getHeight());
            if (node->getParent()) {
                if (node->getParent()->getLeft() == node) {
                    node->getParent()->setLeft(maxNode);
                } else {
                    node->getParent()->setRight(maxNode);
                }
            } else {
                this->root = maxNode;
            }
            node->setParent(nullptr);
            return;
        }
    }
};

template <typename K, typename V>
ostream &operator<<(ostream &s, Tree<K, V> &obj) {
    s << "Tree{ \n";
    for (TreeIterator<K, V> it = obj.begin(); it != obj.end(); it++) {
        s << "\t" << it << "\n";
    }
    s << "}\n";
    return s;
}

template <typename K, typename V> class AVLTree : public Tree<K, V> {
  protected:
    void updateHeight(Node<K, V> *node) {
        int heightLeft = 0;
        int heightRight = 0;
        if (node->getLeft() != nullptr) {
            heightLeft = node->getLeft()->getHeight();
        }
        if (node->getRight() != nullptr) {
            heightRight = node->getRight()->getHeight();
        }
        if (heightLeft > heightRight) {
            node->setHeight(heightLeft + 1);
        } else {
            node->setHeight(heightRight + 1);
        }
    }

    Node<K, V> *rotateLeft(Node<K, V> *node) {
        Node<K, V> *rightNode = node->getRight();
        Node<K, V> *rightLeftNode = rightNode->getLeft();
        Node<K, V> *parentNode = node->getParent();
        rightNode->setLeft(node);
        node->setRight(rightLeftNode);
        if (parentNode != nullptr) {
            if (node == parentNode->getLeft()) {
                parentNode->setLeft(rightNode);
            } else {
                parentNode->setRight(rightNode);
            }
            rightNode->setParent(node->getParent());
        } else {
            rightNode->setParent(nullptr);
            this->root = rightNode;
        }
        node->setParent(rightNode);
        if (rightLeftNode != nullptr) {
            rightLeftNode->setParent(node);
        }
        updateHeight(node);
        updateHeight(rightNode);
        return rightNode;
    }

    Node<K, V> *rotateRight(Node<K, V> *node) {
        Node<K, V> *leftNode = node->getLeft();
        Node<K, V> *leftRightNode = leftNode->getRight();
        Node<K, V> *parentNode = node->getParent();
        leftNode->setRight(node);
        node->setLeft(leftRightNode);
        if (parentNode != nullptr) {
            if (node == parentNode->getLeft()) {
                parentNode->setLeft(leftNode);
            } else {
                parentNode->setRight(leftNode);
            }
            leftNode->setParent(parentNode);
        } else {
            leftNode->setParent(nullptr);
            this->root = leftNode;
        }
        node->setParent(leftNode);
        if (leftRightNode != nullptr) {
            leftRightNode->setParent(node);
        }
        updateHeight(node);
        updateHeight(leftNode);
        return leftNode;
    }

    Node<K, V> *complexRotateLeft(Node<K, V> *node) {
        if (node->getRight() == nullptr) {
            return nullptr;
        }
        rotateRight(node->getRight());
        rotateLeft(node);
    }

    Node<K, V> *complexRotateRight(Node<K, V> *node) {
        if (node->getLeft() == nullptr) {
            return nullptr;
        }
        rotateLeft(node->getLeft());
        rotateRight(node);
    }

    Node<K, V> *balanceNode(Node<K, V> *node) {
        updateHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->getRight()) < 0) {
                rotateRight(node->getRight());
            }
            return rotateLeft(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->getLeft()) > 0) {
                rotateLeft(node->getLeft());
            }
            return rotateRight(node);
        }
        return node;
    }

  public:
    int balanceFactor(Node<K, V> *node) const {
        int heightLeft = 0;
        int heightRight = 0;
        if (node->getLeft() != nullptr) {
            heightLeft = node->getLeft()->getHeight();
        }
        if (node->getRight() != nullptr) {
            heightRight = node->getRight()->getHeight();
        }
        return heightRight - heightLeft;
    }

    virtual Node<K, V> *pushNodeRecursive(Node<K, V> *newNode) override {
        return pushNodeRecursive(newNode, this->root);
    }

    virtual Node<K, V> *pushNodeRecursive(Node<K, V> *newNode,
                                          Node<K, V> *currNode) override {
        Node<K, V> *node = Tree<K, V>::pushNodeRecursive(newNode, currNode);
        if (currNode != nullptr) {
            return balanceNode(currNode);
        }
        return node;
    }

    TreeIterator<K, V> push(K key, V value) override {
        Node<K, V> *newNode = new Node<K, V>(key, value);
        pushNodeRecursive(newNode);
        return TreeIterator(newNode);
    }

    virtual void remove(Node<K, V> *node) override {
        Node<K, V> *currNode = node->getParent();
        Tree<K, V>::remove(node);
        if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            while (currNode != nullptr) {
                updateHeight(currNode);
                balanceNode(currNode);
                currNode = currNode->getParent();
            }
        }
    }
};

// Класс из задачи 1.5
template <typename T> using List = Queue<T>;

template <typename K, typename V>
class MultiTree : protected AVLTree<K, List<V> *> {
  public:
    virtual ~MultiTree() {
        cout << "~MultiTree\n";
        this->postOrder([](Node<K, List<V> *> *node) {
            if (node != nullptr) {
                delete node->getValue();
            }
        });
    }

    Node<K, List<V> *> *pushRecursive(K key, V value,
                                      Node<K, List<V> *> *currNode) {
        if (this->root == nullptr) {
            List<V> *list = new List<V>();
            list->push(value);
            this->root = new Node<K, List<V> *>(key, list);
            return this->root;
        }
        if (currNode->getKey() > key) {
            if (currNode->getLeft()) {
                return pushRecursive(key, value, currNode->getLeft());
            } else {
                List<V> *list = new List<V>();
                list->push(value);
                Node<K, List<V> *> *newNode = new Node<K, List<V> *>(key, list);
                currNode->setLeft(newNode);
                newNode->setParent(currNode);
                return newNode;
            }
        }
        if (currNode->getKey() < key) {
            if (currNode->getRight()) {
                return pushRecursive(key, value, currNode->getRight());
            } else {
                List<V> *list = new List<V>();
                list->push(value);
                Node<K, List<V> *> *newNode = new Node<K, List<V> *>(key, list);
                currNode->setRight(newNode);
                newNode->setParent(currNode);
                return newNode;
            }
        }
        if (currNode->getKey() == key) {
            currNode->getValue()->push(value);
            return currNode;
        }
        return nullptr;
    }

    Node<K, List<V> *> *push(K key, V value) {
        return pushRecursive(key, value, this->root);
    }

    List<V> *operator[](K key) { return Tree<K, List<V> *>::_find(key); }

    template <typename K_, typename V_>
    friend ostream &operator<<(ostream &s, MultiTree<K_, V_> &obj);
};

template <typename K, typename V>
ostream &operator<<(ostream &s, MultiTree<K, V> &obj) {
    s << "MultiTree{ \n";
    for (TreeIterator<K, List<V> *> it = obj.begin(); it != obj.end(); it++) {
        s << "\t{ Key: " << (*it).getKey() << ", Value: " << *(*it).getValue()
          << "\n";
    }
    s << "}\n";
    return s;
}

template <class K, class V> class SplayTree : protected AVLTree<K, V> {
    void splay(Node<K, V> *node) {
        while (node->getParent()) {
            if (node == node->getParent()->getLeft()) {
                if (!node->getParent()->getParent()) {
                    AVLTree<K, V>::rotateRight(node->getParent());
                } else if (node->getParent() ==
                           node->getParent()->getParent()->getLeft()) {
                    AVLTree<K, V>::rotateRight(node->getParent()->getParent());
                    AVLTree<K, V>::rotateRight(node->getParent());
                } else {
                    AVLTree<K, V>::rotateRight(node->getParent());
                    AVLTree<K, V>::rotateLeft(node->getParent());
                }
            } else {
                if (!node->getParent()->getParent()) {
                    AVLTree<K, V>::rotateLeft(node->getParent());
                } else if (node->getParent() ==
                           node->getParent()->getParent()->getRight()) {
                    AVLTree<K, V>::rotateLeft(node->getParent()->getParent());
                    AVLTree<K, V>::rotateLeft(node->getParent());
                } else {
                    AVLTree<K, V>::rotateLeft(node->getParent());
                    AVLTree<K, V>::rotateRight(node->getParent());
                }
            }
        }
    }

    Node<K, V> *pushNodeRecursive(Node<K, V> *node,
                                  Node<K, V> *currentNode) override {
        if (node == nullptr)
            return nullptr;

        if (this->root == nullptr) {
            this->root = node;
            return node;
        }

        if (currentNode->getKey() > node->getKey()) {
            if (currentNode->getLeft() != nullptr)
                return pushNodeRecursive(node, currentNode->getLeft());
            else {
                currentNode->setLeft(node);
                node->setParent(currentNode);
            }
        }
        if (currentNode->getKey() < node->getKey()) {
            if (currentNode->getRight() != nullptr)
                return pushNodeRecursive(node, currentNode->getRight());
            else {
                currentNode->setRight(node);
                node->setParent(currentNode);
            }
        }
        return node;
    }

  public:
    TreeIterator<K, V> operator[](K key) {
        splay(Tree<K, V>::_findNode(key));
        return TreeIterator(Tree<K, V>::root);
    }

    TreeIterator<K, V> push(K key, V value) override {
        Node<K, V> *res = new Node(key, value);
        Tree<K, V>::pushNodeRecursive(res);
        splay(res);
        return TreeIterator(Tree<K, V>::root);
    }

    TreeIterator<K, V> find(K key,
                            function<bool(const K &, const K &)> f = nullptr) {
        if (f == nullptr)
            return TreeIterator(Tree<K, V>::_findNode(key));
        for (TreeIterator<K, V> it = this->begin(); it != this->end(); ++it) {
            if (f(key, (*it).getKey()))
                return it;
        }
        return this->end();
    }

    TreeIterator<K, V> begin() const override {
        return TreeIterator<K, V>(Tree<K, V>::min(), nullptr);
    }

    TreeIterator<K, V> end() const override {
        return TreeIterator<K, V>(nullptr, Tree<K, V>::max());
    }

    template <typename K_, typename V_>
    friend ostream &operator<<(ostream &s, SplayTree<K_, V_> &obj);
};

template <typename K, typename V>
ostream &operator<<(ostream &s, SplayTree<K, V> &obj) {
    s << "SplayTree{ \n";
    for (TreeIterator<K, V> it = obj.begin(); it != obj.end(); it++) {
        s << "\t{ Key: " << (*it).getKey() << ", Value: " << (*it).getValue()
          << "\n";
    }
    s << "}\n";
    return s;
}

int main() {
    AVLTree<string, Doctor> doctors;
    Doctor doctor;
    string firstname, lastname;
    for (int i = 0; i < 10; i++) {
        firstname = rstr(5);
        lastname = rstr(6);
        double rating =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        doctor = Doctor(lastname, firstname, rstr(5), rstr(5), 6, rating);
        doctors.push(firstname + " " + lastname, doctor);
    }

    cout << doctors;

    for (TreeIterator<string, Doctor> iter = --doctors.end();
         iter != doctors.begin(); iter--) {
        auto a = *iter;
        cout << a << "\n";
    }
    cout << "\n";

    TreeIterator<string, Doctor> res =
        doctors.findByKey([firstname, lastname](string k) {
            return k == (firstname + " " + lastname);
        });

    cout << res << "\n";

    MultiTree<string, Doctor> multidoctors;
    for (int i = 0; i < 10; i++) {
        firstname = rstr(5);
        lastname = rstr(6);
        double rating =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        doctor = Doctor(lastname, firstname, rstr(5), rstr(5), 6, rating);
        multidoctors.push(firstname + " " + lastname, doctor);
    }
    double rating =
        static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
    multidoctors.push(firstname + " " + lastname,
                      Doctor(lastname, firstname, rstr(5), rstr(5), 6, rating));
    rating = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
    multidoctors.push(firstname + " " + lastname,
                      Doctor(lastname, firstname, rstr(5), rstr(5), 6, rating));

    cout << multidoctors << "\n";
    cout << *multidoctors[firstname + " " + lastname] << "\n";

    SplayTree<string, Doctor> splaydoctors;
    for (int i = 0; i < 10; i++) {
        firstname = rstr(5);
        lastname = rstr(6);
        double rating =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        doctor = Doctor(lastname, firstname, rstr(5), rstr(5), 6, rating);
        splaydoctors.push(firstname + " " + lastname, doctor);
    }

    cout << splaydoctors << "\n";
    string fullname = firstname + " " + lastname;
    cout << (*splaydoctors.find(fullname)).getValue() << "\n";
    auto lambda = [](const string &a, const string &b) { return a == b; };
    cout << (*splaydoctors.find(fullname, lambda)).getValue() << "\n";

    return 0;
}
