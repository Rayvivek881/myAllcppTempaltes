#include <bits/stdc++.h>
using namespace std;
struct Point {
    double x, y;
};
int orientation(Point a, Point b, Point c) {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}
vector<Point> convex_hull(vector<Point> & a) {
    Point p0 = *min_element(a.begin(), a.end(), [](Point a, Point b)
                    { return make_pair(a.y, a.x) < make_pair(b.y, b.x); });
    sort(a.begin(), a.end(), [&p0](const Point &a, const Point &b){
        int o = orientation(p0, a, b);
        if (o == 0) return (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y) 
            < (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y);
        return o < 0;
    });
    vector<Point> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && orientation(st[st.size() - 2], st.back(), a[i]) >= 0)
            st.pop_back();
        st.push_back(a[i]);
    }
    return st;
}
int main(int argc, char const *argv[])
{
    vector<Point> lst = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    vector<Point> val = convex_hull(lst);
    for (auto & i : val) cout << i.x << ' ' << i.y << endl;
    return 0;
}
