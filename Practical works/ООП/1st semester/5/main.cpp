#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <cmath>

class Exception : public std::exception {
protected:
    char* str;
public:
    Exception(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy_s(str, strlen(s) + 1, s);
    }

    Exception(const Exception& e) {
        str = new char[strlen(e.str) + 1];
        strcpy_s(str, strlen(e.str) + 1, e.str);
    }

    ~Exception() {
        delete[] str;
    }

    virtual void print() {
        std::cout << "Exception: " << str << "; " << what() << "\n";
    }
};

class InvalidOperation : public Exception {
public:
    InvalidOperation(const char* inpStr) : Exception(inpStr) {};

    void print() {
        std::cout << "InvalidOperation: " << str << "; " << what() << "\n";
    }
};

class IndexOutOfBounds : public Exception {
protected:
    int row;
    int column;
public:
    IndexOutOfBounds(const char* inpStr, int inpRow, int inpColumn) :
        Exception(inpStr) {
        row = inpRow;
        column = inpColumn;
    }

    void print() {
        std::cout << "IndexOutOfBounds: " << str << ": row = " << row <<
            ", column = " << column << "; " << what() << "\n";
    }
};

class WrongSize : public Exception {
protected:
    int height;
    int width;
public:
    WrongSize(const char* inpStr, int inpHeight, int inpWidth) :
        Exception(inpStr) {
        height = inpHeight;
        width = inpWidth;
    }

    void print() {
        std::cout << "WrongSize: " << str << ": height = " << height <<
            ", width = " << width << "; " << what() << "\n";
    }
};

class NonPositiveSize : public WrongSize {
public:
    NonPositiveSize(const char* inpStr, int inpHeight, int inpWidth) :
        WrongSize(inpStr, inpHeight, inpWidth) {
        height = inpHeight;
        width = inpWidth;
    }

    void print() {
        std::cout << "NonPositiveSize: " << str << ": height = " << height <<
            ", width = " << width << "; " << what() << "\n";
    }
};

class NegativeOrder : public Exception {
protected:
    int order;
public:
    NegativeOrder(const char* inpStr, int inpOrder) : Exception(inpStr) {
        order = inpOrder;
    }

    void print() {
        std::cout << "NegativeOrder: " << str << ": order = " << order << "; " << what() << "\n";
    }
};

class TooLargeSize : public WrongSize {
public:
    TooLargeSize(const char* inpStr, int inpHeight, int inpWidth) :
        WrongSize(inpStr, inpHeight, inpWidth) {
        height = inpHeight;
        width = inpWidth;
    }

    void print() {
        std::cout << "TooLargeSize: " << str << ": height = " << height <<
            ", width = " << width << "; " << what() << "\n";
    }
};

template <typename T>
class BaseMatrix {
protected:
    T** ptr;
    int height;
    int width;
public:
    BaseMatrix(int h = 2, int w = 2) {
        if (h <= 0 || w <= 0) {
            throw NonPositiveSize("Non-positive size of matrix", h, w);
        }
        height = h;
        width = w;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++) {
                ptr[i][j] = T();
            }
        }
    }

    BaseMatrix(const BaseMatrix& obj) {
        height = obj.height;
        width = obj.width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++) {
                ptr[i][j] = obj.ptr[i][j];
            }
        }
    }

    BaseMatrix(T** inpPtr, int h, int w) {
        if (inpPtr == NULL || inpPtr[0] == NULL) {
            throw NonPositiveSize("Spplied pointer to is NULL", 0, 0);
        }
        if (h <= 0 || w <= 0) {
            throw NonPositiveSize("Invalid matrix size", h, w);
        }
        height = h;
        width = w;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++) {
                ptr[i][j] = inpPtr[i][j];
            }
        }
    }

    virtual ~BaseMatrix() {
        if (ptr != NULL) {
            for (int i = 0; i < height; i++) {
                delete[] ptr[i];
            }
            delete[] ptr;
            ptr = NULL;
        }
    }

    BaseMatrix& operator=(BaseMatrix& obj) {
        if (ptr != NULL) {
            for (int i = 0; i < height; i++) {
                delete[] ptr[i];
            }
            delete[] ptr;
            ptr = NULL;
        }
        height = obj.height;
        width = obj.width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++) {
                ptr[i][j] = obj.ptr[i][j];
            }
        }
        return *this;
    }

    T& operator()(int row, int column) {
        if (row < 0 || column < 0 || row >= height || column >= width) {
            throw IndexOutOfBounds("Index is out of bounds", row, column);
        }
        return ptr[row][column];
    }

    BaseMatrix operator+(BaseMatrix& obj) {
        if (height != obj.height || width != obj.width) {
            throw InvalidOperation("Cannot add up matricies of different sizes");
        }

        BaseMatrix retObj = BaseMatrix(height, width);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                retObj.ptr[i][j] = ptr[i][j] + obj.ptr[i][j];
            }
        }

        return retObj;
    }

    BaseMatrix operator*(BaseMatrix& obj) {
        if (width != obj.height) {
            throw InvalidOperation("Cannot multiply matricies of unmatched sizes");
        }

        BaseMatrix retObj = BaseMatrix(height, obj.width);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < obj.width; j++) {
                T tempSum = T();
                for (int k = 0; k < width; k++) {
                    tempSum += ptr[i][k] * obj.ptr[k][j];
                }
                retObj.ptr[i][j] = tempSum;
            }
        }

        return retObj;
    }

    T tr() {
        if (width != height) {
            throw InvalidOperation("Cannot calculate trace of a non-square matrix");
        }
        T tempSum = T();
        for (int i = 0; i < std::min(height, width); i++) {
            tempSum += ptr[i][i];
        }
        return tempSum;
    }

    // Вычислиние определителя происходит рекурсивно по разложению Лагранжа
    T det() {
        if (width != height) {
            throw InvalidOperation("Cannot calculate determinant of a non-square matrix");
        }
        if (height == 1) {
            return ptr[0][0];
        }
        if (height == 2) {
            return ptr[0][0] * ptr[1][1] - ptr[0][1] * ptr[1][0];
        }
        T tempSum = T();
        for (int j = 0; j < width; j++) {
            T sign = T(j % 2 == 0 ? 1.0 : -1.0);
            tempSum += excludeRowColumn(0, j).det() * ptr[0][j] * sign;
        }
        return tempSum;
    }

    BaseMatrix excludeRowColumn(int row, int column) {
        BaseMatrix retObj(height - 1, width - 1);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i != row && j != column) {
                    int iIndex, jIndex;
                    if (i > row) {
                        iIndex = i - 1;
                    }
                    else {
                        iIndex = i;
                    }
                    if (j > column) {
                        jIndex = j - 1;
                    }
                    else {
                        jIndex = j;
                    }
                    retObj.ptr[iIndex][jIndex] = ptr[i][j];
                }
            }
        }
        return retObj;
    }

    virtual void print(const char* sep = " ") {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << ptr[i][j] << sep;
            }
            std::cout << "\n";
        }
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& ustream, BaseMatrix<U>& obj);

    template <typename U>
    friend std::istream& operator>>(std::istream& ustream, BaseMatrix<U>& obj);
};

template <typename T>
std::ostream& operator<<(std::ostream& ustream, BaseMatrix<T>& obj) {
    if (typeid(ustream).name() == typeid(std::ofstream).name()) {
        ustream << obj.height << " " << obj.width << " ";
        for (int i = 0; i < obj.height; i++) {
            for (int j = 0; j < obj.width; j++) {
                ustream << obj.ptr[i][j] << " ";
            }
        }
        ustream << "\n";
        return ustream;
    }
    for (int i = 0; i < obj.height; i++) {
        for (int j = 0; j < obj.width; j++) {
            ustream << obj.ptr[i][j] << " ";
        }
        ustream << "\n";
    }
    return ustream;
}

template <typename T>
std::istream& operator>>(std::istream& ustream, BaseMatrix<T>& obj) {
    if (typeid(ustream) == typeid(std::ifstream)) {
        int h, w;
        ustream >> h >> w;
        // В случае если матрица неподходящего размера, изменим его
        if (obj.height != h || obj.width != w) {
            obj.~BaseMatrix();
            obj.height = h;
            obj.width = w;
            obj.ptr = new T * [h];
            for (int i = 0; i < h; i++) {
                obj.ptr[i] = new T[w];
            }
        }
    }
    for (int i = 0; i < obj.height; i++) {
        for (int j = 0; j < obj.width; j++) {
            ustream >> obj.ptr[i][j];
        }
    }
    return ustream;
}

template <typename T>
class DerivedMatrix : public BaseMatrix<T> {
public:
    DerivedMatrix(int h = 2, int w = 2) : BaseMatrix<T>(h, w) {};
    DerivedMatrix(DerivedMatrix<T>& obj) : BaseMatrix<T>(obj) {};
    DerivedMatrix(BaseMatrix<T>& obj) : BaseMatrix<T>(obj) {};
    DerivedMatrix(const BaseMatrix<T>& obj) : BaseMatrix<T>(obj) {};
    DerivedMatrix(T** inpPtr, int h, int w) : BaseMatrix<T>(inpPtr, h, w) {};

    void randomFill(T lwr = T(0.0), T upr = T(1.0)) {
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                this->ptr[i][j] = T(lwr + ((double)rand() / RAND_MAX) * (upr - lwr));
            }
        }
    }

    void randomFillInt(T lwr = T(0), T upr = T(1)) {
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                this->ptr[i][j] = T(std::floor(lwr + ((double)rand() / RAND_MAX) * (upr - lwr)));
            }
        }
    }

    DerivedMatrix rhombalPascalTriangle(int n) {
        if (n < 0) {
            throw NegativeOrder("Cannot build a pascal triangle to a negative order row", n);
        }
        DerivedMatrix retObj(n + 1, n + 1);
        for (int i = 0; i < n + 1; i++) {
            retObj(0, i) = T(1);
            retObj(i, 0) = T(1);
            retObj(n, i) = T(1);
            retObj(i, n) = T(1);
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (i + j <= n) {
                    retObj(i, j) = retObj(i - 1, j) + retObj(i, j - 1);
                }
            }
        }
        for (int i = n - 1; i > 0; i--) {
            for (int j = n - 1; j > 0; j--) {
                if (i + j > n) {
                    retObj(i, j) = retObj(i + 1, j) + retObj(i, j + 1);
                }
            }
        }
        return retObj;
    }
};

// Класс-обертка для массива матриц
template <typename T>
class MatrixArray {
protected:
    BaseMatrix<T>* ptr;
    int length;
public:
    MatrixArray(int len = 1) {
        length = len;
        ptr = new BaseMatrix<T>[length];
    }

    MatrixArray(BaseMatrix<T>* pointer, int len) {
        length = len;
        ptr = pointer;
    }

    ~MatrixArray() {
        if (ptr != NULL) {
            delete[] ptr;
        }
    }

    int getLength() {
        return length;
    }

    BaseMatrix<T>& operator[](int index) {
        if (index < 0 || index >= length) {
            throw IndexOutOfBounds("Index out of bounds", 0, index);
        }
        return ptr[index];
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& s, MatrixArray<U>& a);
    template <typename U>
    friend std::ostream& operator<<(std::ostream& s, MatrixArray<U>& a);
};

template <typename T>
std::ostream& operator<<(std::ostream& ustream, MatrixArray<T>& arr) {
    if (typeid(ustream).name() == typeid(std::ofstream).name()) {
        ustream << arr.length << "\n";
        for (int i = 0; i < arr.length; i++) {
            ustream << arr.ptr[i];
        }
        return ustream;
    }
    ustream << "MatrixArray:\n";
    for (int i = 0; i < arr.length; i++) {
        ustream << "(" << i << "):\n" << arr.ptr[i];
    }
    return ustream;

}

template <typename T>
std::istream& operator>>(std::istream& ustream, MatrixArray<T>& arr) {
    int newLength;
    ustream >> newLength;
    BaseMatrix<T>* newPtr = new BaseMatrix<T>[newLength];
    for (int i = 0; i < newLength; i++) {
        ustream >> newPtr[i];
    }

    arr.length = newLength;
    arr.ptr = newPtr;

    return ustream;
}

int main() {
    // T& operator()(int row, int column)
    BaseMatrix<double> bm1(2, 3);
    bm1(1, 2) = 3.0;
    bm1(0, 1) = 6.0;
    bm1.print();
    std::cout << "\n";

    // BaseMatrix(double** p, int h, int w)
    double arr1[3] = { 1,2,3 };
    double arr2[3] = { 4,5,6 };
    double** arr = new double* [2];
    arr[0] = arr1;
    arr[1] = arr2;
    BaseMatrix<double> bm2(arr, 2, 3);
    bm2.print();
    std::cout << "\n";

    // operator=(BaseMatrix& obj)
    BaseMatrix<double> bm3(1, 1);
    bm3 = bm2;
    bm3.print();
    std::cout << "\n";

    // Функция случайного заполнения
    DerivedMatrix<double> dm1 = DerivedMatrix<double>(4, 4);
    dm1.randomFill(3.0, 7.0);
    dm1.print();
    std::cout << "\n";

    // Постоение "ромба Паскаля" (вариант 4)
    DerivedMatrix<double> dm2 = dm1.rhombalPascalTriangle(6);
    dm2.print("\t");
    std::cout << "\n";

    // operator+
    BaseMatrix<double> matPlus = bm1 + bm2;
    matPlus.print();
    std::cout << "\n";

    // operator*
    DerivedMatrix<double> dm3(2, 3);
    dm3.randomFillInt(1, 6);
    dm3.print();
    std::cout << "  *  \n";
    DerivedMatrix<double> dm4(3, 2);
    dm4.randomFillInt(1, 6);
    dm4.print();
    std::cout << "  =  \n";
    DerivedMatrix<double> matMult = dm3 * dm4;
    matMult.print();
    std::cout << "\n";

    // След матрицы
    std::cout << "Trace = " << matMult.tr() << "\n";
    std::cout << "\n";

    // Исключить строку и столбец для вычисления определителя
    dm2.print("\t");
    std::cout << "\n";
    dm2.excludeRowColumn(2, 3).print("\t");
    std::cout << "\n";

    // Определитель матрицы
    DerivedMatrix<double> rand1(3, 3);
    rand1.randomFillInt(1, 6);
    rand1.print("\t");
    std::cout << "Determinant = " << rand1.det() << "\n";
    std::cout << "\n";

    // Обработка ошибок
    try {
        BaseMatrix<double> wrong00(2, 4);
        BaseMatrix<double> wrong01(2, 5);
        BaseMatrix<double> wrong10 = wrong00 * wrong01;
        std::cout << wrong10 << "\n";
    }
    catch (InvalidOperation err) {
        std::cout << "Caught error: ";
        err.print();
    }
    try {
        BaseMatrix<double> wrong1(-1, 0);
    }
    catch (NonPositiveSize err) {
        std::cout << "Caught error: ";
        err.print();
    }
    try {
        BaseMatrix<double> wrong2(2, 3);
        std::cout << wrong2(4, 3) << "\n";
    }
    catch (IndexOutOfBounds err) {
        std::cout << "Caught error: ";
        err.print();
    }
    try {
        DerivedMatrix<double> wrong3(2, 3);
        wrong3.rhombalPascalTriangle(-2);
        wrong3.print();
    }
    catch (NegativeOrder err) {
        std::cout << "Caught error: ";
        err.print();
    }
    std::cout << "\n";

    // Запись в / чтение из файла
    std::cout << "Writing to out.txt..." << "\n";
    MatrixArray<double> matArr(4);
    matArr[0] = dm1;
    matArr[1] = dm2;
    matArr[2] = dm3;
    matArr[3] = dm4;
    std::ofstream fout;
    fout.open("out.txt");
    if (fout) {
        fout << bm1 << bm2 << matArr;
        fout.close();
    }

    std::cout << "Reading from out.txt..." << "\n";
    std::ifstream fin;
    fin.open("out.txt");
    if (fin) {
        BaseMatrix<double> im1(1, 1), im2(2, 2);
        MatrixArray<double> ima1(1);
        fin >> im1 >> im2 >> ima1;
        std::cout << "Written:\n" << bm1;
        std::cout << "Read:\n";
        im1.print();
        std::cout << "\n";
        std::cout << "Written:\n" << bm2;
        std::cout << "Read:\n";
        im2.print();
        std::cout << "\n";
        std::cout << "Written:\n" << matArr;
        std::cout << "Read:\n";
        std::cout << ima1 << "\n";
        std::cout << "\n";
        fin.close();
    }

    return 0;
}