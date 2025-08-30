#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

using namespace std;

// Функция, находящая максимальный поток в графе (транспортной сети), а также
// все увеличивающие пути, которые были задействованы в итоговом потоке.
// Реализация алгорима Форда-Фалкерсона.
pair<int, vector<pair<int, vector<int>>>>
maxStream(const vector<vector<int>> &graph) {
    // Копирование графа в остаточую сеть (необходимо для избежания мутации
    // графа, предоставляемого как аргумент функции)
    vector<vector<int>> residualNetwork(graph.size(),
                                        vector<int>(graph.size()));
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j)
            residualNetwork[i][j] = graph[i][j];
    }

    // Инициализация возвращаемых значений
    int maxFlow = 0;
    vector<pair<int, vector<int>>> paths;

    while (true) {
        // Инициализация необходимых для работы алгоритма переменных
        vector<int> flows(graph.size(), 0);
        vector<int> parent(graph.size(), -1);
        parent[0] = 0;
        flows[0] = 2147483647;

        // !
        // priority_queue<T> по умолчанию является max_queue. При сравнении двух
        // tuple<T, U, V> используется лексико-графический порядок, т.е. сначала
        // происходит сравнение по T (int), который в данной реализации кодирует
        // вес ребра в остаточной сети. Это гарантирует, что
        // priority_queue.top() всегда будет возвращать ребро с максимальной
        // пропускной способностью.
        // !
        priority_queue<tuple<int, int, int>> queue;

        // Добавление всех увеличивающих путей, которые необходимо рассмотреть
        // на данной итерации
        for (int i = 1; i < graph.size(); ++i)
            if (residualNetwork[0][i] != 0)
                queue.emplace(residualNetwork[0][i], 0, i);

        // Итерация по всем добавленным в рассмотрение ребрам
        while (!queue.empty()) {
            auto [flow, from, to] = queue.top();
            queue.pop();

            // Пропускаем те потоки, которые не увеличивают максимальный
            if (flows[to] >= flow)
                continue;

            // Иначе добавляем в очередь следующие доступные ребра
            flows[to] = flow;
            parent[to] = from;
            for (int neighbor = 0; neighbor < graph.size(); ++neighbor)
                if (residualNetwork[to][neighbor] != 0)
                    queue.emplace(min(flow, residualNetwork[to][neighbor]), to,
                                  neighbor);
        }

        // Если более не осталось путей из souce в target, завершаем алгоритм
        if (parent[graph.size() - 1] == -1)
            break;

        // Обновление максимального потока
        maxFlow += flows[graph.size() - 1];

        // Добавление пути в вывод
        vector<int> path;
        int curr = graph.size() - 1;
        while (curr != 0) {
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(0);
        reverse(path.begin(), path.end());
        paths.push_back({flows[graph.size() - 1], path});

        // Обновление остаточной сети
        for (int i = 0; i + 1 < path.size(); ++i) {
            auto curr = path[i];
            auto next = path[i + 1];
            residualNetwork[curr][next] -= flows[graph.size() - 1];
            residualNetwork[next][curr] += flows[graph.size() - 1];
        }
    }

    return {maxFlow, paths};
}

// Функция для проверки возможности добавить вершину v в гамильтонов путь на
// позицию position.
bool isVertexSafe(const int vertex, const vector<vector<bool>> &graph,
                  const vector<int> &path, const int position) {
    // Проверка на существование ребра для рассматриваемой вершины.
    if (!graph[path[position - 1]][vertex])
        return false;

    // Проверка на то, что рассматриваемая вершина отсутствует в текущем пути
    for (int i = 0; i < path.size(); ++i)
        if (path[i] == vertex)
            return false;

    return true;
}

// Функция предназначенная для решения задачи о поиске гамильтоного пути,
// вызываемая рекурсивно.
bool hamiltonianPathRecursive(const vector<vector<bool>> &graph,
                              vector<int> &path, const int position) {
    // Проверка на зацикленность пути убрана, теперь функция действительно
    // считает гамильтонов путь.
    if (position == graph.size()) {
        return true;
    }

    for (int i = 0; i < graph.size(); ++i) {
        if (isVertexSafe(i, graph, path, position)) {
            path[position] = i;
            if (hamiltonianPathRecursive(graph, path, position + 1))
                return true;
            path[position] = -1;
        }
    }

    return false;
}

// Функция - обертка для функции hamiltonianPathRecursive, возвращающая
// optional (если путь найден, то он будет содержаться в возвращаемом
// объекте, иначе объект будет пустой).
optional<vector<int>> hamiltonianPath(const vector<vector<bool>> &graph) {
    vector<int> path(graph.size());
    // Добавлен цикл для обработки всех путей (начинающихся в каждой вершине).
    for (int begin = 0; begin < graph.size(); ++begin) {
        for (int i = 0; i < graph.size(); ++i)
            path[i] = -1;
        path[0] = begin;
        if (hamiltonianPathRecursive(graph, path, 1)) {
            return path;
        }
    }
    return {};
}

// Вспомогательная функция, предназначенная для конвертации взвешеного графа,
// данного в задании, в невзвешенный
vector<vector<bool>> toUnweightedGraph(const vector<vector<int>> &graph) {
    vector<bool> tmp(graph.size());
    vector<vector<bool>> result(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
        result[i] = tmp;
    }
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            result[i][j] = graph[i][j] > 0 ? 1 : 0;
        }
    }
    return result;
}

int main() {
    vector<vector<int>> graph = {
        {0, 1, 3, 0, 1, 3, 6, 6, 7, 1}, {1, 0, 1, 8, 6, 0, 0, 0, 8, 8},
        {3, 1, 0, 6, 6, 4, 5, 7, 6, 2}, {0, 8, 6, 0, 1, 3, 0, 3, 4, 3},
        {1, 6, 6, 1, 0, 4, 6, 8, 5, 7}, {3, 0, 4, 3, 4, 0, 1, 3, 6, 1},
        {6, 0, 5, 0, 6, 1, 0, 4, 7, 1}, {6, 0, 7, 3, 8, 3, 4, 0, 1, 8},
        {7, 8, 6, 4, 5, 6, 7, 1, 0, 1}, {1, 8, 2, 3, 7, 1, 1, 8, 1, 0}};

    cout << "Search for the biggest flow in transport network\n";
    auto [flow, paths] = maxStream(graph);
    cout << "Flow: " << flow << "\n";
    for (auto path : paths) {
        cout << "Path (" << path.first << "): ";
        for (int node : path.second) {
            cout << " -> " << node;
        }
        cout << "\n";
    }

    /*
     * Вывод программы:
     * Search for the biggest flow in transport network
     * Flow: 28
     * Path (7):  -> 0 -> 8 -> 1 -> 9
     * Path (6):  -> 0 -> 7 -> 9
     * Path (6):  -> 0 -> 6 -> 4 -> 9
     * Path (3):  -> 0 -> 5 -> 8 -> 3 -> 9
     * Path (2):  -> 0 -> 2 -> 8 -> 6 -> 7 -> 9
     * Path (1):  -> 0 -> 9
     * Path (1):  -> 0 -> 4 -> 9
     * Path (1):  -> 0 -> 2 -> 9
     * Path (1):  -> 0 -> 1 -> 9
     */

    cout << "\n";

    cout << "Search for hamiltonian path in graph\n";
    vector<vector<bool>> unweighted_graph = toUnweightedGraph(graph);
    auto result = hamiltonianPath(unweighted_graph);
    if (!result.has_value()) {
        cout << "Hamiltonian path does not exist.\n";
        return 0;
    }
    auto hamiltonian_path = result.value();
    cout << "Hamiltonian path: ";
    for (auto node : hamiltonian_path) {
        cout << " -> " << node;
    }
    cout << "\n";

    /*
     * Вывод программы:
     * Search for hamiltonian path in graph
     * Hamiltonian path:  -> 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9
     */

    // Проверка для Гамильтоного пути, начинающегося в другой вершины (возьмем
    // другой граф)
    vector<vector<int>> graph2 = {{0, 1, 1, 0, 0},
                                  {1, 0, 1, 0, 1},
                                  {1, 1, 0, 1, 0},
                                  {0, 0, 1, 0, 0},
                                  {0, 1, 0, 0, 0}};
    vector<vector<bool>> unweighted_graph2 = toUnweightedGraph(graph2);
    auto result2 = hamiltonianPath(unweighted_graph2);
    if (!result2.has_value()) {
        cout << "Hamiltonian path does not exist.\n";
        return 0;
    }
    auto hamiltonian_path2 = result2.value();
    cout << "Hamiltonian path 2: ";
    for (auto node : hamiltonian_path2) {
        cout << " -> " << node;
    }
    cout << "\n";
    // Вывод программы:
    /*
     * Hamiltonian path 2:  -> 3 -> 2 -> 0 -> 1 -> 4
     */

    return 0;
}
