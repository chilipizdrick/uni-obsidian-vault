#include <iostream>

class Vector3 {
private:
    double x;
    double y;
    double z;

public:

    Vector3() {
        x = y = z = 0.0f;
    }
    Vector3(double xComp, double yComp, double zComp) {
        x = xComp;
        y = yComp;
        z = zComp;
    }
    Vector3(const Vector3& a) {
        x = a.x;
        y = a.y;
        z = a.z;
    }

    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    void setX(double xComp) { x = xComp; }
    void setY(double yComp) { y = yComp; }
    void setZ(double zComp) { z = zComp; }

    Vector3 operator+(Vector3 a) {
        return Vector3(x + a.getX(), y + a.getY(), z + a.getZ());
    }
    Vector3 operator-(Vector3 a) {
        return Vector3(x - a.getX(), y - a.getY(), z - a.getZ());
    }

    friend Vector3 operator+(double num, Vector3 vec);

    void print() {
        std::cout << "Vector3{ " << x << " ; " << y << " ; " << z << " }";
    }
};

Vector3 operator+(double num, Vector3 vec) {
    return Vector3(vec.x + num, vec.y + num, vec.z + num);
}

int main() {
    Vector3 v1(0.9, 2.1, 3.5);
    Vector3 v2(0.4, 3.7, 2.3);

    Vector3 v3 = v1 + v2;
    Vector3 v4 = v1 - v2;

    v3.print();
    std::cout << "\n";
    v4.print();
    std::cout << "\n";

    Vector3 v5(0.3, 4.5, 2.1);
    Vector3 v6 = 1.4 + v5;

    v6.print();
    std::cout << "\n";

    return 0;
}
