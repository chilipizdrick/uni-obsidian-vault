#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Exception : public exception {
  private:
    string str;

  public:
    Exception(string s) : str(s) {}

    const char *what() { return str.c_str(); }
};

template <typename T> void push(list<T> &lst, T elem) {
    typename list<T>::iterator pos = lst.begin();
    while (pos != lst.end()) {
        if (*pos > elem)
            break;
        pos++;
    }
    lst.insert(pos, elem);
}

template <typename T> T pop(list<T> &lst) {
    if (lst.size() == 0)
        throw Exception("empty list");
    T res = lst.back();
    lst.pop_back();
    return res;
}

template <typename T> list<T> filter(list<T> &lst, function<bool(T)> f) {
    list<T> res;
    for (typename list<T>::iterator iter = lst.begin(); iter != lst.end();
         iter++) {
        if (f(*iter)) {
            res.push_back(*iter);
        }
    }
    return res;
}

template <typename T> ostream &operator<<(ostream &s, list<T> lst) {
    s << "list{ ";
    for (typename list<T>::iterator iter = lst.begin(); iter != lst.end();
         iter++) {
        s << *iter << " ";
    }
    s << "}\n";
    return s;
}

class Point2D {
  public:
    double x, y;

    Point2D(double x, double y) : x(x), y(y) {}

    bool operator<(Point2D &p) {
        double dist1 = sqrt(pow(x, 2) + pow(y, 2));
        double dist2 = sqrt(pow(p.x, 2) + pow(p.y, 2));
        return dist1 < dist2;
    }
    bool operator>(Point2D &p) {
        double dist1 = sqrt(pow(x, 2) + pow(y, 2));
        double dist2 = sqrt(pow(p.x, 2) + pow(p.y, 2));
        return dist1 > dist2;
    }
    bool operator>=(Point2D &p) { return !(*this < p); }
    bool operator<=(Point2D &p) { return !(*this > p); }
    bool operator==(Point2D &p) {
        double dist1 = sqrt(pow(x, 2) + pow(y, 2));
        double dist2 = sqrt(pow(p.x, 2) + pow(p.y, 2));
        return dist1 - dist2 < 0.001;
    }
    bool operator!=(Point2D &p) { return !(*this == p); }
};

ostream &operator<<(ostream &s, Point2D p) {
    s << "Point2D{ " << p.x << ", " << p.y << " }";
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

int main() {
    list<Point2D> l;
    push(l, Point2D(5, -1));
    push(l, Point2D(-6, 3));
    push(l, Point2D(3, 4));
    push(l, Point2D(-2, 2));
    push(l, Point2D(-3, -5));
    push(l, Point2D(0, -4));
    push(l, Point2D(-1, 6));
    push(l, Point2D(2, -1));
    list<Point2D> ll = l;
    cout << l;
    cout << pop(l) << "\n";
    cout << l;
    cout << pop(l) << "\n";

    cout << "\n";

    cout << filter<Point2D>(ll, [](Point2D p) { return p.x < 0 && p.y > 0; });

    cout << "\n";

    list<Doctor> l2;
    push(l2, Doctor(rstr(5), rstr(6), rstr(5), rstr(7), 5, 38.53));
    push(l2, Doctor(rstr(4), rstr(7), rstr(4), rstr(8), 8, 85.67));
    push(l2, Doctor(rstr(3), rstr(5), rstr(7), rstr(6), 7, 23.92));
    push(l2, Doctor(rstr(6), rstr(7), rstr(5), rstr(4), 4, 75.43));
    push(l2, Doctor(rstr(4), rstr(5), rstr(7), rstr(9), 2, 70.25));
    cout << l2;
    cout << "Element with highest priority: " << pop(l2);
    cout << l2;
}
