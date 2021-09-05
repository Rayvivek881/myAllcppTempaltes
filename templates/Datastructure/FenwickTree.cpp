template<typename T>
class FenwickTree{
public:
    int n;
    T *Tree;
    FenwickTree(int size) : n(size + 2) {
        Tree = new T[size + 2];
        for (int i = 0; i < size + 2; i++)
            Tree[i] = 0;
    }
    void updateUtil(int ind, int delta){
        for (++ind; ind < n; ind += ind & -ind)
            Tree[ind] += delta;
    }
    T queryUtil(int ind) {
        T ans = 0;
        for (++ind; ind > 0; ind -= ind & -ind)
            ans += Tree[ind];
        return ans;
    }
    void update(int i, int val){
        updateUtil(i, val); 
    }
    T query(int l, int r){
        return (queryUtil(r) - queryUtil(l-1));
    }
};
