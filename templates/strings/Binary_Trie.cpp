class Binary_Trie {
    struct Trie_Node {
        int Count;
        struct Trie_Node * child[2];
        Trie_Node () {
            Count = 0;
            child[0] = child[1] = nullptr;
        }
    };
    struct Trie_Node * root = new Trie_Node();
public:
    void insert(long long value) {
        struct Trie_Node * temp = root;
        for (int i = 30; i >= 0; i--) {
            int bit = ((1 << i) & value) != 0;
            if (temp->child[bit] == nullptr)
                temp->child[bit] = new Trie_Node();
            temp = temp->child[bit], temp->Count += 1;
        }
    }
    bool find(long long value) {
        struct Trie_Node * temp = root;
        for (int i = 30; i >= 0; i--) {
            int bit = ((1 << i) & value) != 0;
            if (temp->child[bit] == nullptr || temp->child[bit]->Count <= 0)
                return false;
            temp = temp->child[bit];
        }
        return true;
    }
    bool erase(long long value) {
        if (!find(value)) return false;
        struct Trie_Node * temp = root;
        for (int i = 30; i >= 0; i--) {
            int bit = ((1 << i) & value) != 0;
            temp = temp->child[bit], temp->Count -= 1;
        }
        return true;
    }
};
