#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Exception : public exception {
  private:
    string message;

  public:
    Exception(const string &s) : message(s) {}
    virtual const char *what() { return message.c_str(); }
};

template <typename K> class NotUniqueKeyException : public Exception {
  private:
    string message;
    K key;

  public:
    NotUniqueKeyException(const string &s, const K &k) : Exception(s) {
        message = s;
        key = k;
    }
    virtual const char *what() override {
        stringstream ss;
        ss << this->message << ": \"" << key << "\"";
        this->message = ss.str();
        return this->message.c_str();
    }
};

template <typename K> class InvalidKeyException : public Exception {
  private:
    K key;
    string message;

  public:
    InvalidKeyException(const string &s, const K &k) : Exception(s) {
        message = s;
        key = k;
    };
    virtual const char *what() override {
        stringstream ss;
        ss << this->message << ": \"" << key << "\"";
        this->message = ss.str();
        return this->message.c_str();
    }
};

template <typename V> class InvalidValueException : public Exception {
  private:
    string message;
    V value;

  public:
    InvalidValueException(const string &s, const V &v) : Exception(s) {
        message = s;
        value = v;
    }
    virtual const char *what() override {
        stringstream ss;
        ss << this->message << ": \"" << value << "\"";
        this->message = ss.str();
        return this->message.c_str();
    }
};

template <typename K, typename V> pair<K, V> find_by_key(map<K, V> m, K key) {
    typename map<K, V>::iterator iter = m.find(key);
    if (iter == m.end()) {
        throw InvalidKeyException("Cannot find object with key", key);
    }
    return *iter;
}

template <typename K, typename V>
vector<pair<K, V>> find_by_key(multimap<K, V> m, K key) {
    typename map<K, V>::iterator iter = m.find(key);
    if (iter == m.end()) {
        throw InvalidKeyException("Cannot find object with key", key);
    }
    vector<pair<K, V>> res;
    while (iter->first == key) {
        res.push_back(*iter);
        iter++;
    }
    return res;
}

template <typename K, typename V> void insert(map<K, V> &m, K key, V value) {
    try {
        pair<K, V> res = find_by_key(m, key);
        throw NotUniqueKeyException<K>("Not unique key", key);
    } catch (InvalidKeyException<K> _) {
        m[key] = value;
    }
}

template <typename K, typename V>
void insert(multimap<K, V> &m, K key, V value) {
    m.insert({key, value});
}

template <typename K, typename V>
pair<K, V> find_by_value(map<K, V> m, V &value) {
    for (typename map<K, V>::iterator iter = m.begin(); iter != m.end();
         iter++) {
        if (iter->second == value) {
            return *iter;
        }
    }
    throw InvalidValueException("Cannot find object with value", value);
}

template <typename K, typename V>
pair<K, V> find_by_value(multimap<K, V> m, V &value) {
    for (typename multimap<K, V>::iterator iter = m.begin(); iter != m.end();
         iter++) {
        if (iter->second == value) {
            return *iter;
        }
    }
    throw InvalidValueException("Cannot find object with value", value);
}

template <typename K, typename V>
ostream &operator<<(ostream &s, map<K, V> &m) {
    s << "Map{\n";
    for (typename map<K, V>::iterator iter = m.begin(); iter != m.end();
         iter++) {
        s << "Key: " << iter->first << ", Value: " << iter->second << "\n";
    }
    s << "}\n";
    return s;
}

template <typename K, typename V>
ostream &operator<<(ostream &s, multimap<K, V> &m) {
    s << "Multimap{\n";
    for (typename multimap<K, V>::iterator iter = m.begin(); iter != m.end();
         iter++) {
        s << "Key: " << iter->first << ", Value: " << iter->second << "\n";
    }
    s << "}\n";
    return s;
}

template <typename K, typename V>
ostream &operator<<(ostream &s, pair<K, V> &p) {
    s << "Key: " << p.first << ", Value: " << p.second << " ";
    return s;
}

template <typename K, typename V> map<K, V> filter(map<K, V> &m, K k) {
    return map<K, V>(m.upper_bound(k), m.end());
}

// Фильтр, построенный на бин. поиске
template <typename K, typename V>
map<K, V> filter_inclusive(map<K, V> &m, K k) {
    typename map<K, V>::iterator iter = m.find(k);
    if (iter == m.end()) {
        throw InvalidKeyException<K>("Key with specified value not found", k);
    }
    return map<K, V>(iter, m.end());
}

template <typename K, typename V>
multimap<K, V> filter(multimap<K, V> &m, K k) {
    return multimap<K, V>(m.upper_bound(k), m.end());
}

// Фильтр, построенный на бин. поиске
template <typename K, typename V>
multimap<K, V> filter_inclusive(multimap<K, V> &m, K k) {
    typename multimap<K, V>::iterator iter = m.find(k);
    if (iter == m.end()) {
        throw InvalidKeyException<K>("Key with specified value not found", k);
    }
    return multimap<K, V>(iter, m.end());
}

template <typename K, typename V> vector<V> unique_values(map<K, V> &m) {
    set<V> res;
    for (typename map<K, V>::iterator iter = m.begin(); iter != m.end();
         iter++) {
        res.insert(iter->second);
    }
    return vector(res.begin(), res.end());
}

template <typename K, typename V> vector<V> unique_values(multimap<K, V> &m) {
    set<V> res;
    for (typename multimap<K, V>::iterator iter = m.begin(); iter != m.end();
         iter++) {
        res.insert(iter->second);
    }
    return vector(res.begin(), res.end());
}

template <typename V> ostream &operator<<(ostream &s, vector<V> &v) {
    s << "Vector{\n";
    for (V elem : v)
        s << elem << "\n";
    return s << "}\n";
}

class Doctor {
  public:
    string lastname;
    string firstname;
    string speciality;
    string post;
    int experience;
    double rating;

    Doctor()
        : lastname(""), firstname(""), speciality(""), post(""), experience(0),
          rating(0.0) {}
    Doctor(string lastname, string firstname, string speciality, string post,
           int experience, double rating)
        : lastname(lastname), firstname(firstname), speciality(speciality),
          post(post), experience(experience), rating(rating) {}
    bool operator<(const Doctor &d) const {
        if (rating < d.rating)
            return true;
        return false;
    }
    bool operator>=(const Doctor &d) const { return !(*this < d); }
    bool operator>(const Doctor &d) const {
        if (rating > d.rating)
            return true;
        return false;
    }
    bool operator<=(const Doctor &d) const { return !(*this > d); }
    bool operator==(const Doctor &d) const {
        if (rating != d.rating)
            return false;
        return true;
    }
    bool operator!=(const Doctor &p) const { return !(*this == p); }
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

int main() {
    // map
    cout << "--- map ---\n\n";
    map<string, Doctor> doctors;
    Doctor doctor;
    string firstname, lastname;
    for (int i = 0; i < 10; i++) {
        firstname = rstr(5);
        lastname = rstr(6);
        double rating =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        doctor = Doctor(lastname, firstname, rstr(5), rstr(5), 6, rating);
        insert(doctors, firstname + " " + lastname, doctor);
    }
    cout << doctors;

    cout << "\n";

    auto elem1 =
        find_by_key<string, Doctor>(doctors, firstname + " " + lastname);
    cout << elem1 << "\n";

    auto elem2 = find_by_value<string, Doctor>(doctors, doctor);
    cout << elem2 << "\n";

    cout << "\n";

    cout << "Filtered map:\n";
    map<string, Doctor> good_doctors = filter<string, Doctor>(doctors, "abc");
    cout << good_doctors;

    cout << "Invclusively filtered map:\n";
    try {
        map<string, Doctor> good_doctors2 =
            filter_inclusive<string, Doctor>(doctors, "abc");
        cout << good_doctors2;
    } catch (InvalidKeyException<string> e) {
        cout << e.what();
    }

    cout << "\n";

    cout << "Unique values:\n";
    auto v1 = unique_values(doctors);
    cout << v1;

    // multimap
    cout << "\n--- multimap ---\n\n";
    multimap<string, Doctor> doctors2;
    for (int i = 0; i < 10; i++) {
        firstname = rstr(5);
        lastname = rstr(6);
        double rating =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        doctor = Doctor(lastname, firstname, rstr(5), rstr(5), 6, rating);
        insert(doctors2, firstname + " " + lastname, doctor);
        // Вставка объектов по идентичным ключам
        if (i % 2 == 1)
            insert(doctors2, firstname + " " + lastname, doctor);
    }
    cout << doctors2;

    cout << "\n";

    cout << "find_by_key() для multimap выводит все элемены по данному ключу\n";
    auto elem3 =
        find_by_key<string, Doctor>(doctors2, firstname + " " + lastname);
    cout << elem3;

    auto elem4 = find_by_value<string, Doctor>(doctors2, doctor);
    cout << elem4;

    cout << "\n";

    cout << "Filtered multimap:\n";
    map<string, Doctor> good_doctors3 = filter<string, Doctor>(doctors, "abc");
    cout << good_doctors3;

    cout << "Inclusively filtered multimap:\n";
    try {
        map<string, Doctor> good_doctors4 =
            filter_inclusive<string, Doctor>(doctors, "abc");
        cout << good_doctors4;
    } catch (InvalidKeyException<string> e) {
        cout << e.what();
    }

    cout << "\n";

    cout << "Unique values:\n";
    auto v2 = unique_values(doctors2);
    cout << v2;
}
