#include <iostream>

class A1 {
protected:
    int a1;
public:
    A1(int value=0) {
        a1 = value;
    }

    virtual void print() {
        std::cout << "Class: A1{ a1 = " << a1 << " }" << std::endl;
    }

    virtual void show() {
        std::cout << "A1 : a1 = " << a1 << std::endl;
    }
};

class B1 : virtual public A1 {
protected:
    int b1;
public:
    B1(int value=0) : A1(value) {
        b1 = value;
    }

    void print() {
        std::cout << "Class: B1{ b1 = " << b1 << " }" << std::endl;
    }

    void show() {
        std::cout << "B1 : a1 = " << A1::a1 << std::endl;
        std::cout << "B1 : b1 = " << b1 << std::endl;
    }
};

class B2 : virtual public A1 {
protected:
    int b2;
public:
    B2(int value=0) : A1(value) {
        b2 = value;
    }

    void print() {
        std::cout << "Class: B2{ b2 = " << b2 << " }" << std::endl;
    }

    void show() {
        std::cout << "B2 : a1 = " << A1::a1 << std::endl;
        std::cout << "B2 : b2 = " << b2 << std::endl;
    }
};

class C1 : public B1, public B2 {
protected:
    int c1;
public:
    C1(int value=0) : B1(value - 1), B2(value + 1) {
        c1 = value;
    }

    void print() {
        std::cout << "Class: C1{ c1 = " << c1 << " }" << std::endl;
    }

    void show() {
        std::cout << "C1 : a1 = " << A1::a1 << std::endl;
        std::cout << "C1 : b1 = " << B1::b1 << std::endl;
        std::cout << "C1 : b2 = " << B2::b2 << std::endl;
        std::cout << "C1 : c1 = " << c1 << std::endl;
    }
};

class C2 : public B1, public B2 {
protected:
    int c2;
public:
    C2(int value=0) : B1(value - 1), B2(value + 1) {
        c2 = value;
    }

    void print() {
        std::cout << "Class: C2{ c2 = " << c2 << " }" << std::endl;
    }

    void show() {
        std::cout << "C2 : a1 = " << A1::a1 << std::endl;
        std::cout << "C2 : b1 = " << B1::b1 << std::endl;
        std::cout << "C2 : b2 = " << B2::b2 << std::endl;
        std::cout << "C2 : c2 = " << c2 << std::endl;
    }
};

int main() {
    A1 a1 = A1(1);
    a1.print();
    a1.show();

    B1 b1 = B1(2);
    b1.print();
    b1.show();

    B2 b2 = B2(3);
    b2.print();
    b2.show();

    C1 c1 = C1(4);
    c1.print();
    c1.show();

    C2 c2 = C2(5);
    c2.print();
    c2.show();

    A1* ptr = &b1;
    ptr->print();
    ptr->show();

    ptr = &c1;
    ptr->print();
    ptr->show();

    return 0;
}
