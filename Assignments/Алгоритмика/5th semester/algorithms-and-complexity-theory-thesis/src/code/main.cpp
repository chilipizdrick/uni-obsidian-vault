#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct point {
  double x;
  double y;

  point operator-(point a) const { return {a.x - x, a.y - y}; }

  double operator^(point a) const { return x * a.y - y * a.x; }

  double distance_squared(point b) const {
    return pow(b.x - x, 2) + pow(b.y - y, 2);
  }

  bool operator==(const point &a) const {
    return abs(x - a.x) < 1e-10 && abs(y - a.y) < 1e-10;
  }
};

double polar_angle(point p0, point a, point b) { return ((a - p0) ^ (b - p0)); }

vector<point> jarvis_convex_hull(vector<point> points) {
  if (points.size() == 1)
    return points;
  point p0 = points[0];
  for (point p : points)
    if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
      p0 = p;
  point p00 = p0;
  vector<point> hull = {p0};
  while (true) {
    point t;
    if (p0 == points[0])
      t = points[1];
    else
      t = points[0];
    for (point p : points)
      if (((p - p0) ^ (t - p0)) > 0)
        t = p;
    if (t == p00)
      break;
    else {
      p0 = t;
      hull.push_back(t);
    }
  }
  return hull;
}

vector<point> graham(vector<point> points) {
  if (points.empty())
    return {};
  point p0 = points.front();
  for (auto p : points)
    if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
      p0 = p;

  sort(points.begin(), points.end(), [&](auto a, auto b) {
    auto angle = polar_angle(p0, a, b);
    if (angle > 0)
      return true;
    if (angle < 0)
      return false;
    return p0.distance_squared(a) < p0.distance_squared(b);
  });

  vector<point> hull;
  for (point p : points) {
    while (hull.size() >= 2) {
      point new_vector = p - hull.back();
      point last_vector = hull.back() - hull[hull.size() - 2];
      if ((new_vector ^ last_vector) > 0)
        hull.pop_back();
      else
        break;
    }
    hull.push_back(p);
  }
  return hull;
}

enum Orientation { COLLINEAR = 0, CLOCKWISE = 1, COUNTERCLOCKWISE = 2 };

// Function to find the orientation of the triplet (p, q, r)
Orientation orientation(point p, point q, point r) {
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val == 0)
    return Orientation::COLLINEAR;
  return (val > 0) ? Orientation::CLOCKWISE : Orientation::COUNTERCLOCKWISE;
}

// Function to find the farthest point from line segment [p, q]
point farthest_point(point p, point q, vector<point> &points) {
  point farthest = {0, 0};
  int max_dist = 0;
  for (auto &point : points) {
    int dist = abs((q.y - p.y) * point.x - (q.x - p.x) * point.y + q.x * p.y -
                   q.y * p.x);
    if (dist > max_dist) {
      max_dist = dist;
      farthest = point;
    }
  }
  return farthest;
}

void quick_hull(point p, point q, vector<point> &points, vector<point> &hull) {
  if (points.empty())
    return;

  point farthest = farthest_point(p, q, points);
  hull.push_back(farthest);

  vector<point> left_set, right_set;
  for (auto &point : points) {
    if (point == farthest)
      continue;
    if (orientation(p, farthest, point) == Orientation::COUNTERCLOCKWISE)
      left_set.push_back(point);
    else if (orientation(farthest, q, point) == Orientation::COUNTERCLOCKWISE)
      right_set.push_back(point);
  }

  quick_hull(p, farthest, left_set, hull);
  quick_hull(farthest, q, right_set, hull);
}

vector<point> quick_hull(vector<point> &points) {
  if (points.size() < 3)
    return {};

  vector<point> hull;
  point left_most =
      *min_element(points.begin(), points.end(), [](point a, point b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
      });
  point right_most =
      *max_element(points.begin(), points.end(), [](point a, point b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
      });

  hull.push_back(left_most);
  hull.push_back(right_most);

  vector<point> above, below;
  for (auto &point : points) {
    if (point == left_most)
      continue;
    if (orientation(left_most, right_most, point) ==
        Orientation::COUNTERCLOCKWISE)
      above.push_back(point);
    else
      below.push_back(point);
  }

  quick_hull(left_most, right_most, above, hull);
  quick_hull(right_most, left_most, below, hull);

  return hull;
}

int main() {
  cout << "Введите 0 для тестового примера, 1 для тестов Грэхэма, 2 для "
          "тестов Джарвиса и 3 для тестов алгоритма QuickHull.";
  int type;
  cin >> type;
  if (type == 0) {
    vector<point> data = {{1, 1}, {2, 5}, {1, 9}, {4, 3},
                          {6, 4}, {5, 7}, {8, 2}, {8, 9}};
    auto result = quick_hull(data);
    cout << "Точки, вошедшие в оболочку:\n";
    for (auto &[a, b] : result) {
      cout << "(" << a << ", " << b << ")\n";
    }
  } else {
    vector<int> sizes = {10, 100, 1000, 10'000, 1'000'000, 10'000'000};
    for (auto N : sizes) {
      cout << "[" << N << "], ";
    }
    cout << "\n";
    for (auto N : sizes) {
      vector<point> points(N);

      random_device rd;
      mt19937 gen(rd());
      uniform_real_distribution<> dis(-100.0, 100.0);

      for (auto &p : points) {
        p.x = dis(gen);
        p.y = dis(gen);
      }

      // Measure execution time
      auto start = chrono::high_resolution_clock::now();
      if (type == 1)
        graham(points);
      else if (type == 2)
        jarvis_convex_hull(points);
      else if (type == 3)
        quick_hull(points);
      auto end = chrono::high_resolution_clock::now();

      chrono::duration<double> elapsed = end - start;
      cout << "[" << elapsed.count() << "], ";
      cout.flush();
    }
  }
  return 0;
}
