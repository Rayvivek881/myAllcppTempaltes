template<typename T>
int lowerSearch(vector<T> & lst, T val) {
    int l = 0, r = lst.size() - 1, ind = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (lst[mid] < val) {
            l = mid + 1;
            ind = max(ind, mid);
        } else {
            r = mid - 1;
            if (lst[mid] == val) {
                if (lst[ind] < lst[mid] || ind == -1)
                    ind = mid;
                else ind = min(ind, mid);
            }
        }
    }
    return ind;
}
template<typename T>
int lowerSearch(vector<pair<T, T>> & lst, T val) {
    int l = 0, r = lst.size() - 1, ind = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (lst[mid].first < val) {
            l = mid + 1;
            ind = max(ind, mid);
        } else {
            r = mid - 1;
            if (lst[mid].first == val) {
                if (lst[ind].first < lst[mid].first || ind == -1)
                    ind = mid;
                else ind = min(ind, mid);
            }
        }
    }
    return ind;
}
