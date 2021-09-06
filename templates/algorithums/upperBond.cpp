template<typename T>
int upperSearch(vector<pair<T, T>> & lst, T val) {
    int l = 0, r = lst.size() - 1, ind = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (lst[mid].first > val) {
            r = mid - 1;
            if (ind == -1) ind = mid;
            else if (lst[mid].first <= lst[ind].first)
                ind = mid;
        } else {
            l = mid + 1;
            if (lst[mid].first == val)
                ind = mid;
        }
    }
    return ind;
}
template<typename T>
int upperSearch(vector<T> & lst, T val) {
    int l = 0, r = lst.size() - 1, ind = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (lst[mid] > val) {
            r = mid - 1;
            if (ind == -1) ind = mid;
            else if (lst[mid] <= lst[ind])
                ind = mid;
        } else {
            l = mid + 1;
            if (lst[mid] == val)
                ind = mid;
        }
    }
    return ind;
}