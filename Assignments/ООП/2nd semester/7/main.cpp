#include <iostream>
#include <functional>
#include <algorithm>


class Exception : public std::exception {
protected:
    std::string message;
public:
    Exception() { message = ""; }
    Exception(const std::string& message_) : message(message_) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EqualKeysException : public Exception {
public:
    EqualKeysException() : Exception("error on equal keys in tree") {}
};

class FullHeapException : public Exception {
public:
    FullHeapException() : Exception("error on trying to add element to full heap") {}
};

class EmptyHeapException : public Exception {
public:
    EmptyHeapException() : Exception("error on trying to remove element from empty heap") {}
};

class HeapIndexOutOfBoundsException : public Exception {
public:
    HeapIndexOutOfBoundsException() : Exception("error on trying to access an element of heap with invalid index") {}
};


class Sportsman {
public:
    std::string firstname;
    std::string lastname;
    int age;
    std::string citizenship;
    std::string sport;
    int medalCount;

    Sportsman() {
        firstname = lastname = citizenship = sport = "";
        age = medalCount = 0;
    }

    Sportsman(const std::string& firstname_, const std::string& lastname_,
        const int& age_, const std::string& citizenship_,
        const std::string& sport_, const int& medalCount_) :
        firstname(firstname_), lastname(lastname_), age(age_),
        citizenship(citizenship_), sport(sport_),
        medalCount(medalCount_) {}

    virtual ~Sportsman() {}

    friend std::ostream& operator<<(std::ostream& stream, Sportsman& obj);

    friend class SportsmanPriority;
};

std::ostream& operator<<(std::ostream& stream, Sportsman& obj) {
    stream << "Sportsman{ ";
    stream << obj.firstname << ", ";
    stream << obj.lastname << ", ";
    stream << obj.age << ", ";
    stream << obj.citizenship << ", ";
    stream << obj.sport << ", ";
    stream << obj.medalCount << " }";
    return stream;
}

class SportsmanPriority {
protected:
    Sportsman obj;

public:
    SportsmanPriority() {}

    SportsmanPriority(const Sportsman& obj_) {
        obj = obj_;
    }

    virtual ~SportsmanPriority() {}

    bool operator<(const SportsmanPriority& priority) const {
        if (obj.medalCount != priority.obj.medalCount) {
            return obj.medalCount < priority.obj.medalCount;
        }
        if (obj.age != priority.obj.age) {
            return obj.age < priority.obj.age;
        }
        if (obj.firstname != priority.obj.firstname) {
            return obj.firstname < priority.obj.firstname;
        }
        return obj.lastname < priority.obj.lastname;
    }

    bool operator>(const SportsmanPriority& priority) const {
        return priority < (*this);
    }

    bool operator==(const SportsmanPriority& priority) const {
        return !((*this) < priority || (*this) > priority);
    }
};


template <typename K, typename V>
class Node {
protected:
    K key;
    V value;
    int height;
    Node<K, V>* left;
    Node<K, V>* right;
    Node<K, V>* parent;

public:
    virtual V getValue() { return value; }
    virtual K getKey() { return key; }
    virtual int getHeight() { return height; }
    virtual Node<K, V>* getLeft() { return left; }
    virtual Node<K, V>* getRight() { return right; }
    virtual Node<K, V>* getParent() { return parent; }

    virtual void setValue(V value_) { value = value_; }
    virtual void setKey(K key_) { key = key_; }
    virtual void setHeight(int height_) { height = height_; }
    virtual void setLeft(Node<K, V>* left_) { left = left_; }
    virtual void setRight(Node<K, V>* right_) { right = right_; }
    virtual void setParent(Node<K, V>* parent_) { parent = parent_; }

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

    // Деструктор не должнен удалять левого или правого ребенка,
    // т.к. это реализованно в деструкторе самого дерева
    virtual ~Node() {}

    virtual void print() { std::cout << (*this); }

    template <typename K_, typename V_>
    friend std::ostream& operator<<(std::ostream& stream, Node<K_, V_>& node);
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& stream, Node<K, V>& node) {
    stream << "Node{ key: " << node.key << ", value: " << node.value << ", height: " << node.height << " }\n";
    return stream;
}

template <typename K, typename V>
class BinarySearchTree {
protected:
    Node<K, V>* root = nullptr;

    Node<K, V>* getMaxNode(Node<K, V>* node) {
        if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            return nullptr;
        }
        if (node->getLeft() != nullptr && node->getRight() == nullptr) {
            return node->getLeft();
        }
        if (node->getLeft() == nullptr && node->getRight() != nullptr) {
            return node->getRight();
        }
        if (node->getLeft()->getKey() > node->getRight()->getKey()) {
            return node->getLeft();
        }
        return node->getRight();
    }

public:
    BinarySearchTree() { root = nullptr; }

    BinarySearchTree(const BinarySearchTree<K, V>& tree) {
        root = new Node<K, V>(tree.root->getKey(), tree.root->getValue());
        copyTreeRecursive(root, tree.root);
    }

    void copyTreeRecursive(Node<K, V>* node, Node<K, V>* copiedNode) {
        if (copiedNode->getLeft() != nullptr) {
            node->setLeft(new Node<K, V>(copiedNode->getLeft()->getKey(), copiedNode->getLeft()->getValue()));
            copyTreeRecursive(node->getLeft(), copiedNode->getLeft());
        }
        if (copiedNode->getRight() != nullptr) {
            node->setRight(new Node<K, V>(copiedNode->getRight()->getKey(), copiedNode->getRight()->getValue()));
            copyTreeRecursive(node->getRight(), copiedNode->getRight());
        }
    }

    virtual ~BinarySearchTree() {
        std::cout << "~BinarySearchTree\n";
        postOrder([](Node<K, V>* node) { if (node != nullptr) { delete node; } });
    }

    virtual Node<K, V>* getRoot() const { return root; }

    virtual Node<K, V>* pushNodeRecursive(Node<K, V>* newNode) { return pushNodeRecursive(newNode, root); }
    virtual Node<K, V>* pushNodeRecursive(Node<K, V>* newNode, Node<K, V>* currNode) {
        if (newNode == nullptr) { return nullptr; }
        if (root == nullptr) {
            root = newNode;
            return root;
        }
        if (currNode->getKey() > newNode->getKey()) {
            if (currNode->getLeft()) { return pushNodeRecursive(newNode, currNode->getLeft()); }
            else {
                currNode->setLeft(newNode);
                newNode->setParent(currNode);
                return newNode;
            }
        }
        if (currNode->getKey() < newNode->getKey()) {
            if (currNode->getRight()) { return pushNodeRecursive(newNode, currNode->getRight()); }
            else {
                currNode->setRight(newNode);
                newNode->setParent(currNode);
                return newNode;
            }
        }
        if (currNode->getKey() == newNode->getKey()) { throw EqualKeysException(); }
        return nullptr;
    }

    virtual Node<K, V>* push(K key, V value) {
        Node<K, V>* newNode = new Node<K, V>(key, value);
        pushNodeRecursive(newNode);
        return newNode;
    }

    virtual Node<K, V>* min() const { return min(root); }
    virtual Node<K, V>* min(Node<K, V>* currNode) const {
        while (currNode->getLeft() != nullptr) { currNode = currNode->getLeft(); }
        return currNode;
    }

    virtual Node<K, V>* max() const { return max(root); }
    virtual Node<K, V>* max(Node<K, V>* currNode) const {
        while (currNode->getRight() != nullptr) { currNode = currNode->getRight(); }
        return currNode;
    }

    virtual Node<K, V>* find(const K& key) const { return find(key, root); }
    virtual Node<K, V>* find(const K& key, Node<K, V>* currNode) const {
        if (currNode == nullptr) { return nullptr; }
        if (currNode->getKey() == key) { return currNode; }
        if (currNode->getKey() > key) { return find(key, currNode->getLeft()); }
        if (currNode->getKey() < key) { return find(key, currNode->getRight()); }
        return nullptr;
    }

    virtual void preOrder(std::function<void(Node<K, V>*)> f) { return preOrder(root, f); }
    virtual void preOrder(Node<K, V>* node, std::function<void(Node<K, V>*)> f) {
        if (node != nullptr) { f(node); }
        if (node != nullptr && node->getLeft() != nullptr) { preOrder(node->getLeft(), f); }
        if (node != nullptr && node->getRight() != nullptr) { preOrder(node->getRight(), f); }
    }

    virtual void inOrder(std::function<void(Node<K, V>*)> f) { return inOrder(root, f); }
    virtual void inOrder(Node<K, V>* node, std::function<void(Node<K, V>*)> f) {
        if (node != nullptr && node->getLeft() != nullptr) { inOrder(node->getLeft(), f); }
        if (node != nullptr) { f(node); }
        if (node != nullptr && node->getRight() != nullptr) { inOrder(node->getRight(), f); }
    }

    virtual void postOrder(std::function<void(Node<K, V>*)> f) { return postOrder(root, f); }
    virtual void postOrder(Node<K, V>* node, std::function<void(Node<K, V>*)> f) {
        if (node != nullptr && node->getLeft() != nullptr) { postOrder(node->getLeft(), f); }
        if (node != nullptr && node->getRight() != nullptr) { postOrder(node->getRight(), f); }
        if (node != nullptr) { f(node); }
    }

    virtual V operator[](const K& key) const {
        return find(key)->getValue();
    }

    virtual void remove(Node<K, V>* node) {
        if (node->getRight() == nullptr && node->getLeft() == nullptr) {
            if (node == root) {
                root = nullptr;
                return;
            }
            Node<K, V>* parent = node->getParent();
            if (parent->getLeft() == node) {
                parent->setLeft(nullptr);
            }
            else {
                parent->setRight(nullptr);
            }
            node->setParent(nullptr);
            return;
        }
        else if (node->getLeft() == nullptr) {
            if (node == root) {
                root = root->getRight();
                return;
            }
            Node<K, V>* parent = node->getParent();
            if (parent->getLeft() == node) {
                parent->setLeft(node->getRight());
            }
            else {
                parent->setRight(node->getRight());
            }
            node->setParent(nullptr);
            return;
        }
        else if (node->getRight() == nullptr) {
            if (node == root) {
                root = root->getLeft();
                return;
            }
            Node<K, V>* parent = node->getParent();
            if (parent->getLeft() == node) {
                parent->setLeft(node->getLeft());
            }
            else {
                parent->setRight(node->getLeft());
            }
            node->setParent(nullptr);
            return;
        }
        else {
            Node<K, V>* maxNode = getMaxNode(node);
            remove(maxNode);
            maxNode->setLeft(node->getLeft());
            maxNode->setRight(node->getRight());
            maxNode->setParent(node->getParent());
            maxNode->setHeight(node->getHeight());
            if (node->getParent()) {
                if (node->getParent()->getLeft() == node) {
                    node->getParent()->setLeft(maxNode);
                }
                else {
                    node->getParent()->setRight(maxNode);
                }
            }
            else {
                this->root = maxNode;
            }
            node->setParent(nullptr);
            return;
        }
    }
};

template <typename K, typename V>
class AVLTree : public BinarySearchTree<K, V> {
protected:
    void updateHeight(Node<K, V>* node) {
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
        }
        else {
            node->setHeight(heightRight + 1);
        }
    }

    Node<K, V>* rotateLeft(Node<K, V>* node) {
        Node<K, V>* rightNode = node->getRight();
        Node<K, V>* rightLeftNode = rightNode->getLeft();
        Node<K, V>* parentNode = node->getParent();
        rightNode->setLeft(node);
        node->setRight(rightLeftNode);
        if (parentNode != nullptr) {
            if (node == parentNode->getLeft()) {
                parentNode->setLeft(rightNode);
            }
            else {
                parentNode->setRight(rightNode);
            }
            rightNode->setParent(node->getParent());
        }
        else {
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

    Node<K, V>* rotateRight(Node<K, V>* node) {
        Node<K, V>* leftNode = node->getLeft();
        Node<K, V>* leftRightNode = leftNode->getRight();
        Node<K, V>* parentNode = node->getParent();
        leftNode->setRight(node);
        node->setLeft(leftRightNode);
        if (parentNode != nullptr) {
            if (node == parentNode->getLeft()) {
                parentNode->setLeft(leftNode);
            }
            else {
                parentNode->setRight(leftNode);
            }
            leftNode->setParent(parentNode);
        }
        else {
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

    Node<K, V>* complexRotateLeft(Node<K, V>* node) {
        if (node->getRight() == nullptr) {
            return nullptr;
        }
        rotateRight(node->getRight());
        rotateLeft(node);
    }

    Node<K, V>* complexRotateRight(Node<K, V>* node) {
        if (node->getLeft() == nullptr) {
            return nullptr;
        }
        rotateLeft(node->getLeft());
        rotateRight(node);
    }

    Node<K, V>* balanceNode(Node<K, V>* node) {
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
    int balanceFactor(Node<K, V>* node) const {
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

    Node<K, V>* pushNodeRecursive(Node<K, V>* newNode) override {
        return pushNodeRecursive(newNode, this->root);
    }

    Node<K, V>* pushNodeRecursive(Node<K, V>* newNode, Node<K, V>* currNode) override {
        Node<K, V>* node = BinarySearchTree<K, V>::pushNodeRecursive(newNode, currNode);
        if (currNode != nullptr) {
            return balanceNode(currNode);
        }
        return node;
    }

    Node<K, V>* push(K key, V value) override {
        Node<K, V>* newNode = new Node<K, V>(key, value);
        pushNodeRecursive(newNode);
        return newNode;
    }

    void remove(Node<K, V>* node) override {
        Node<K, V>* currNode = node->getParent();
        BinarySearchTree<K, V>::remove(node);
        if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            while (currNode != nullptr) {
                updateHeight(currNode);
                balanceNode(currNode);
                currNode = currNode->getParent();
            }
        }
    }
};


template <typename P, typename T>
class Pair {
protected:
    P priority;
    T value;
public:
    Pair() {
        priority = P();
        value = T();
    }

    Pair(P priority_, T value_) {
        priority = priority_;
        value = value_;
    }

    virtual ~Pair() {}

    P getPriority() const { return priority; }
    T getValue() const { return value; }

    void setPriority(P priority_) { priority = priority_; }
    void setValue(T value_) { value = value_; }
};

template <typename P, typename T>
class Heap {
protected:
    Pair<P, T>* arr = nullptr;
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

    int getLeftIndex(int index) {
        return (index << 1) + 1;
    }

    int getRightIndex(int index) {
        return (index << 1) + 2;
    }

    int getParentIndex(int index) {
        return (index - 1) >> 1;
    }

    void swap(int index1, int index2) {
        validateIndex(index1);
        validateIndex(index2);
        Pair<P, T> tmp = arr[index1];
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
            }
            else {
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
        arr = new Pair<P, T>[capacity];
    }

    Heap(const Heap<P, T>& heap) {
        length = heap.length;
        capacity = heap.capacity;
        arr = new Pair<P, T>[capacity];
        for (int i = 0; i < length; i++) {
            arr[i] = heap.arr[i];
        }
    }

    ~Heap() {
        std::cout << "~Heap()\n";
        delete[] arr;
    }

    int getLength() { return length; }
    int getCapacity() { return capacity; }

    void push(P priority, T value) {
        if (isFull()) { throw FullHeapException(); }
        arr[length] = Pair(priority, value);
        length++;
        siftUp(length - 1);
    }

    T remove(int index) {
        validateIndex(index);
        Pair<P, T> res = arr[index];
        swap(index, length - 1);
        length--;

        // Теперь просеивание происходит в зависимости от приоритета
        if (index != 0 /*То есть есть родитель*/) {
            if (arr[index].getPriority() > arr[getParentIndex(index)].getPriority()) {
                siftUp(index);
                return res.getValue();
            }
        }
        siftDown(index);
        return res.getValue();
    }

    T extractMax() {
        if (isEmpty()) { throw EmptyHeapException(); }
        Pair<P, T> res = arr[0];
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

    void print() {
        for (int i = 0; i < length; i++) {
            std::cout << arr[i].getValue() << " ";
        }
        std::cout << "\n";
    }
};

void printInfo(AVLTree<int, std::string>& tree, Node<int, std::string>* node) {
    std::cout << "Balance Factor: " << tree.balanceFactor(node);
    node->print();
}

int main() {
    std::cout << "--- BinarySearchTree ---\n";
    std::cout << "\n";

    BinarySearchTree<int, std::string> tree1;
    tree1.push(12, "12");
    tree1.push(40, "40");
    tree1.push(23, "23");
    tree1.push(7, "7");
    tree1.push(15, "15");
    tree1.push(33, "33");

    std::cout << "Min: " << tree1.min()->getValue() << "\n";
    std::cout << "Max: " << tree1.max()->getValue() << "\n";
    std::cout << "find(15): " << tree1.find(15)->getValue() << "\n";
    std::cout << "operator[33]: " << tree1[33] << "\n";

    std::cout << "preOrder:\n";
    tree1.preOrder([](Node<int, std::string>* x) { x->print(); });
    std::cout << "inOrder:\n";
    tree1.inOrder([](Node<int, std::string>* x) { x->print(); });
    std::cout << "postOrder:\n";
    tree1.postOrder([](Node<int, std::string>* x) { x->print(); });

    std::cout << "Remove 7 => min = 12...?\n";
    tree1.remove(tree1.find(7));
    std::cout << "Min: " << tree1.min()->getValue() << "\n";
    std::cout << "Remove 40 => max = 33...?\n";
    tree1.remove(tree1.find(40));
    std::cout << "Max: " << tree1.max()->getValue() << "\n";
    std::cout << "\n";

    std::cout << "--- Storing Sportsman class objects (printing in order) ---\n";
    std::cout << "\n";

    std::vector<Sportsman> sportsmen = {
        Sportsman("Larisa", "Latynina", 89, "USSR", "Gymnastics", 46),
        Sportsman("Stanislav", "Pozdnyakov", 50, "Russian Federation", "Fencing", 39),
        Sportsman("Svetlana", "Romashina", 34, "Russian Federation", "Synchronized swimming", 44),
        Sportsman("Alexander", "Popov", 52, "Russian Federation", "Swimming", 47),
        Sportsman("Lyubov", "Yegorova", 58, "USSR, Russian Federation", "Skiing", 18),
    };

    BinarySearchTree<std::string, Sportsman> sportsmanTree;
    for (auto elem : sportsmen) {
        sportsmanTree.push(elem.firstname + " " + elem.lastname, elem);
    }

    sportsmanTree.inOrder([](Node<std::string, Sportsman>* x) { x->print(); });
    std::cout << "\n";

    std::cout << "--- AVL Tree ---\n";
    std::cout << "\n";

    AVLTree<int, std::string> avlTree;
    std::string values[10];
    for (int i = 0; i < 10; i++) {
        values[i] = std::to_string(i);
    }
    for (int i = 0; i < 10; i++) {
        avlTree.push(i, values[i]);
    }
    avlTree.preOrder(
        [&avlTree](Node<int, std::string>* node) {
            std::cout << "bfactor: " << avlTree.balanceFactor(node) << ", ";
            node->print();
        }
    );
    std::cout << "\n";

    std::cout << "Root: " << avlTree[avlTree.getRoot()->getKey()] << "\n";
    std::cout << "Min: " << avlTree[avlTree.min()->getKey()] << "\n";
    std::cout << "Max: " << avlTree[avlTree.max()->getKey()] << "\n";
    std::cout << "\n";

    avlTree.remove(avlTree.getRoot());
    avlTree.remove(avlTree.min());
    avlTree.remove(avlTree.max());
    avlTree.preOrder(
        [&avlTree](Node<int, std::string>* node) {
            std::cout << "bfactor: " << avlTree.balanceFactor(node) << ", ";
            node->print();
        }
    );
    std::cout << "\n";

    std::cout << "--- Heap ---\n";
    std::cout << "\n";

    std::vector<Sportsman> testVector = {
        Sportsman("a", "b", 2, "-", "-", 1),
        Sportsman("a", "b", 1, "-", "-", 1),
        Sportsman("a", "c", 2, "-", "-", 2),
        Sportsman("a", "b", 1, "-", "-", 2),
        Sportsman("b", "c", 2, "-", "-", 2),
        Sportsman("a", "b", 2, "-", "-", 2),
        Sportsman("a", "b", 1, "-", "-", 3),
        Sportsman("b", "c", 3, "-", "-", 3),
        Sportsman("a", "b", 3, "-", "-", 2),
        Sportsman("g", "k", 3, "-", "-", 3),
        Sportsman("m", "n", 3, "-", "-", 2),
    };

    Heap<SportsmanPriority, Sportsman> testHeap(20);
    for (auto elem : testVector) {
        testHeap.push(SportsmanPriority(elem), elem);
    }

    int length = testHeap.getLength();
    for (int i = 0; i < length; i++) {
        auto tmp = testHeap.extractMax();
        std::cout << tmp << "\n";
    }
    std::cout << "\n";

    Heap<int, int> testHeap2(20);
    std::vector<int> intVector = {};
    for (int i = 0; i < 20; i++) {
        intVector.push_back(i);
    }
    std::random_shuffle(intVector.begin(), intVector.end());
    for (int i : intVector) {
        testHeap2.push(i, i);
    }
    testHeap2.remove(1);
    testHeap2.remove(3);
    testHeap2.remove(7);
    testHeap2.remove(13);
    testHeap2.print();

    std::cout << "\n";

    return 0;
}
