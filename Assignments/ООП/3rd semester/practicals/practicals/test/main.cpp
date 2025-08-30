// Вариант 5

#include <iostream>
#include <ostream>
// Для реализации п. 1. стоит использовать контейнер STL priority_queue.
// В случае, если заявки не отличаются по уровню (приоритету),
// стоит использовать контейнер queue.
#include <queue>

using namespace std;

// 1.

// Функция добавления заявки
void insert(priority_queue<int> &q, int v) { q.push(v); }

// Функция поиска заявки самого высокого уровня
int max(priority_queue<int> &q) { return q.top(); }

// Функция удаления заявки самого высокого уровня
int extract_max(priority_queue<int> &q) {
    int res = q.top();
    q.pop();
    return res;
}

// Вывод элементов контейнера в поток
ostream &operator<<(ostream &s, priority_queue<int> &q) {
    priority_queue<int> copied_q = q;
    while (!copied_q.empty()) {
        cout << copied_q.top() << "\n";
        copied_q.pop();
    }
    return s;
}

// Функция добавления заявки, меняющая уровень заявки на противоположный
void insert_inverse(priority_queue<int> q, int v) { q.push(-v); }

// 2.

// Функция, возвращающая вектор со сдвинутыми на n элементами
vector<int> shift_vector(vector<int> v, int n) {
    int length = v.size();
    vector<int> new_v(length);
    for (int i = 0; i < length; ++i) {
        new_v[(length - n + i) % length] = v[i];
    }
    return new_v;
}

ostream &operator<<(ostream &s, vector<int> &v) {
    for (int elem : v) {
        cout << elem << "\n";
    }
    return s;
}

int main() {
    // 1.
    cout << "part 1\n";
    priority_queue<int> pq;
    for (int i = 0; i < 10; ++i) {
        insert(pq, i);
    }
    cout << pq;
    cout << max(pq) << "\n";
    cout << extract_max(pq) << "\n";
    cout << extract_max(pq) << "\n";

    // 2.
    cout << "part 2\n";
    vector<int> v(10);
    for (int i = 0; i < 10; ++i) {
        v[i] = i;
    }
    cout << v;
    vector<int> shifted_v = shift_vector(v, 3);
    cout << shifted_v;

    return 0;
}
