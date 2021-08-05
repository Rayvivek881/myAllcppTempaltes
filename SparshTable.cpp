#include <bits/stdc++.h>
using namespace std;
template <typename T, class func = function<T(const T &, const T &)>>
class spashTable
{
public:
    int n, Log;
    func myfunc;
    vector<vector<T>> Table;
	vector<T> arr;
    spashTable(vector<T> & lst, const func & F) : myfunc(F), arr(lst)
    	{ buildTable(); }
	void buildTable()
	{
		n = arr.size(), Log = ceil(log2((int)arr.size()));
		Table.resize(n);
		for (int i = 0; i < n; i++)
		{
			Table[i].resize(Log);
			Table[i][0] = arr[i];
		}
		for (int j = 1; j <= Log; j++)
		{
			for (int i = 0; (i + (1 << j) - 1) < n; i++)
				Table[i][j] = myfunc(Table[i][j - 1], Table[i + (1 << (j - 1))][j - 1]);
		}
	}
	T query(int l, int r)
	{
		int j = log2(r - l + 1);
		return myfunc(Table[l][j], Table[r - (1 << j) + 1][j]);
	}
};
int main(int argc, char const *argv[])
{
	vector<int> lst = {2, 4, 1, 5, 3, 0, 3, 1};
	spashTable<int> st(lst, [&](int a, int b) { return min(a, b);});
	cout << st.query(1, 3) << endl;
	cout << st.query(2, 5) << endl;
	return 0;
}
