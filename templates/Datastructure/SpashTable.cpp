#include <bits/stdc++.h>
using namespace std;
template <typename T, class func = function<T(const T &, const T &)>>
class spashTable {
public:
    int n, Log;
    func myfunc;
    T **Table, *arr;
    spashTable(vector<T> & lst, const func & F) : myfunc(F) { 
        n = lst.size(), Log = ceil(log2((int)lst.size())) + 5;
        arr = new T[n + 1];
        Table = new T*[n + 1];
        for(int i = 0; i < n; i++) {
            Table[i] = new T[Log];
            arr[i] = lst[i], Table[i][0] = lst[i];
        }
        buildTable();
    }
	void buildTable() {
		for (int j = 1; j <= Log; j++) {
			for (int i = 0; (i + (1 << j) - 1) < n; i++)
				Table[i][j] = myfunc(Table[i][j - 1], Table[i + (1 << (j - 1))][j - 1]);
		}
	}
	T query(int l, int r){
		int j = log2(r - l + 1);
		return myfunc(Table[l][j], Table[r - (1 << j) + 1][j]);
	}
};
int main(int argc, char const *argv[]){
	vector<int> lst = {2, 4, 1, 5, 3, 0, 3, 1};
	spashTable<int> st(lst, [&](int a, int b) { return min(a, b);});
	cout << st.query(1, 3) << endl;
	cout << st.query(2, 5) << endl;
	return 0;
}
