class Trie {
private:
    struct TrieNode {
        struct TrieNode *children[26];
        bool isEndOfWord;
    };
    struct TrieNode *getNode(void) {
        struct TrieNode *newNode = new TrieNode;
        newNode->isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            newNode->children[i] = NULL;
        return newNode;
    }
public:
    struct TrieNode *root = getNode();
    void insert(string str1) {
        struct TrieNode *temp = root;
        for(int i = 0; i < str1.size(); i++) {
            int ind = str1[i] - 'a';
            if (temp->children[ind] == NULL)
                temp->children[ind] = getNode();
            temp = temp->children[ind];
        }
        temp->isEndOfWord = true;
    }
    bool search(string str1) {
        struct TrieNode *temp = root;
        for (int i = 0; i < str1.size(); i++) {
            int ind = str1[i] - 'a';
            if (temp->children[ind] == NULL)
                return false;
            temp = temp->children[ind];
        }
        return temp->isEndOfWord;
    }
};
