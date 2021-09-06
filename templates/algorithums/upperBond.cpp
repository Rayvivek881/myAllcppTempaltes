template<typename T>
int upperSearch(vector<T> & lst, T val) {
    int l = 0, r = lst.size() - 1, ind = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (lst[mid] > val) {
            r = mid - 1;
            if (ind == -1) ind = mid;
            else ind = min(ind, mid);
        } else {
            l = mid + 1;
            if (lst[mid] == val) {
                if (ind == -1 || lst[ind] > lst[mid])
                    ind = mid;
                else ind = max(ind, mid);
            }
        }
    }
    return ind;
}
template<typename T>
int upperSearch(vector<pair<T, T>> & lst, T val) {
    int l = 0, r = lst.size() - 1, ind = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (lst[mid].first > val) {
            r = mid - 1;
            if (ind == -1) ind = mid;
            else ind = min(ind, mid);
        } else {
            l = mid + 1;
            if (lst[mid].first == val) {
                if (ind == -1 || lst[ind].first > lst[mid].first)
                    ind = mid;
                else ind = max(ind, mid);
            }
        }
    }
    return ind;
}
