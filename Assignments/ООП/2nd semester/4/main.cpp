#include <iostream>
#include<string.h>

class BaseString {
protected:
    char* ptr;
    int len;
    int cap;
public:
    BaseString(int capacity = 256) {
        std::cout << "BaseString(int capacity = 256)\n";

        cap = capacity;
        len = 0;
        ptr = new char[cap];
        ptr[0] = '\0';
    }

    BaseString(char* inputPtr) {
        std::cout << "BaseString(char* charPtr)\n";

        char* inputPtrPos = inputPtr;
        while (*inputPtrPos != '\0') {
            inputPtrPos++;
        }

        len = inputPtrPos - inputPtr;
        cap = len + 1;
        ptr = new char[cap];

        inputPtrPos = inputPtr;
        char* ptrPos = ptr;

        while (*inputPtrPos != '\0') {
            *ptrPos++ = *inputPtrPos++;
        }
        *ptrPos = *inputPtrPos;
    }

    BaseString(const char* inputPtr) {
        std::cout << "BaseString(char* charPtr)\n";

        char* inputPtrPos = (char*)inputPtr;
        while (*inputPtrPos != '\0') {
            inputPtrPos++;
        }

        len = inputPtrPos - inputPtr;
        cap = len + 1;
        ptr = new char[cap];

        inputPtrPos = (char*)inputPtr;
        char* ptrPos = ptr;

        while (*inputPtrPos != '\0') {
            *ptrPos++ = *inputPtrPos++;
        }
        *ptrPos = *inputPtrPos;
    }

    BaseString(BaseString& s) {
        std::cout << "BaseString(BaseString& s)\n";

        char* inputPtrPos = s.ptr;
        while (*inputPtrPos != '\0') {
            inputPtrPos++;
        }

        len = inputPtrPos - s.ptr;
        cap = len + 1;
        ptr = new char[cap];

        inputPtrPos = s.ptr;
        char* ptrPos = ptr;
        while (*inputPtrPos != '\0') {
            *ptrPos++ = *inputPtrPos++;
        }
        *ptrPos = *inputPtrPos;
    }

    BaseString(const BaseString& s) {
        std::cout << "BaseString(BaseString& s)\n";

        char* inputPtrPos = s.ptr;
        while (*inputPtrPos != '\0') {
            inputPtrPos++;
        }

        len = inputPtrPos - s.ptr;
        cap = len + 1;
        ptr = new char[cap];

        inputPtrPos = s.ptr;
        char* ptrPos = ptr;
        while (*inputPtrPos != '\0') {
            *ptrPos++ = *inputPtrPos++;
        }
        *ptrPos = *inputPtrPos;
    }

    ~BaseString() {
        std::cout << "~BaseString()\n";
        if (ptr != NULL) {
            delete[] ptr;
        }
    }

    int getLen() { return len; }
    int getCap() { return cap; }
    //char* get() {return ptr;}
    char& operator[](int i) {
        if (i > len) {
            throw std::out_of_range("index out of range");
        }
        if (i == len && len >= cap) {
            throw std::out_of_range("capacity is filled");
        }
        if (i == len && len < cap) {
            len++;
            ptr[i+1] = '\0';
            return ptr[i];
        }
        return ptr[i];
    }

    BaseString& operator=(BaseString& s) {
        std::cout << "BaseString operator=(BaseString& s) \n";

        char* inputPtrPos = s.ptr;
        while (*inputPtrPos != '\0') {
            inputPtrPos++;
        }

        len = inputPtrPos - s.ptr;
        cap = len + 1;
        delete[] ptr;
        ptr = new char[cap];

        inputPtrPos = s.ptr;
        char* ptrPos = ptr;
        while (*inputPtrPos != '\0') {
            *ptrPos++ = *inputPtrPos++;
        }
        *ptrPos = *inputPtrPos;

        return *this;
    }

    virtual void print() {
        char* ptrPos = ptr;
        while (*ptrPos != '\0') {
            std::cout << *ptrPos;
            ptrPos++;
        }

        // for (int i = 0; i < len; i++) {
        //     std::cout << ptr[i];
        // }

        std::cout << "\n";
    }
};

class Exception : public std::exception {
protected:
    char* str;
public:
    Exception(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    Exception(char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    Exception(const Exception& e) {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }

    ~Exception() {
        delete[] str;
    }

    virtual void print() {
        std::cout << "Exception: " << str << "; " << what() << "\n";
    }
};

class NotValidNumber : public Exception {
    char* num;
public:
    NotValidNumber(char* s, char* number) : Exception(s) { num = number; };
    NotValidNumber(const char* s, char* number) : Exception(s) { num = (char*)number; };

    void print() {
        std::cout << "NotValidNumber: " << str << ": " << num << "; " << what() << "\n";
    }
};

class String : public BaseString {
private:
    bool isInString(const char* str, char character) {
        const char* inputPtrPos = str;
        while (*inputPtrPos != '\0') {
            if (*inputPtrPos == character) {
                return true;
            }
            inputPtrPos++;
        }
        return false;
    }

    bool isValidNumber() {
        const char VALID_NUMBER_SYMBOLS[] = "1234567890.";
        const char* inputPtrPos = ptr;
        while (*inputPtrPos != '\0') {
            if (!isInString(VALID_NUMBER_SYMBOLS, *inputPtrPos)) {
                return false;
            }
            inputPtrPos++;
        }
        return true;
    }

    // double parseDouble() {
    //     return std::stod(ptr);
    // }

public:
    String(int capacity = 256) : BaseString(capacity) { std::cout << "String(int capacity = 256)\n"; }
    String(char* inputPtr) : BaseString(inputPtr) { std::cout << "String(char* inputPtr)\n"; }
    String(const char* inputPtr) : BaseString(inputPtr) { std::cout << "String(const char* inputPtr)\n"; }
    String(const String& s) : BaseString(s) { std::cout << "String(String& s)\n"; }
    String(String& s) : BaseString(s) { std::cout << "String(const String& s)\n"; }

    // Написать функцию string_to_number(), проверяющую, является ли содержимое 
    // строки числом, и возвращающую это число в случае утвердительного ответа.
    double stringToNumber() {
        if (!isValidNumber()) {
            throw NotValidNumber("Contained string is not a valid number", ptr);
        }
        return std::stod(ptr);
        // return parseDouble();
    }
};

int main() {
    // operator[] and BaseString(int) constructor
    BaseString s0 = BaseString();
    s0[0] = 'a';
    s0[1] = 'b';
    s0[2] = 'c';
    s0.print();
    s0[1] = 'f';
    s0.print();

    std::cout << "\n";

    // BaseString(char*) constructor
    BaseString s1("Test BaseString");
    s1.print();

    // opertator=(BaseString&)
    BaseString s2 = BaseString();
    s2 = s1;
    s2.print();

    // BaseString(BaseString&) constructor
    BaseString s3(s2);
    s3.print();

    std::cout << "\n";


    // String(char*) constructor
    String ss1("Test String");
    ss1.print();

    // opertator=(String&)
    String ss2 = String();
    ss2 = ss1;
    ss2.print();

    // String(String&) constructor
    String ss3(ss2);
    ss3.print();

    std::cout << "\n";

    // Функция из варианта
    String numString = String("0.2315");
    std::cout << numString.stringToNumber() << "\n";

    std::cout << "\n";

    String numString2 = String("12not-a-number34");
    try {
        std::cout << numString2.stringToNumber() << "\n";
    }
    catch (NotValidNumber e) {
        e.print();
    }

    return 0;
}
