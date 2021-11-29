#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

struct node {
    int n;    
    char c;
    node* left=NULL; //1
    node* right=NULL;//0
};


vector<pair<int,char>> countEntry(string s) {
    map<char, int> m;//Key, count
    vector<pair<int, char>> v;//Count, key
    
    for (int i = 0; i < s.length(); ++i) {
        m[s[i]]++;
    }
    for (auto& i : m) {
        v.push_back(std::make_pair(i.second, i.first));
    }
    sort(v.begin(),v.end());
    return v;
}


node* makeHuffmanTree(vector<pair<int,char>> v) {
    vector<node*> st;
    for (auto& i : v) {
        node* tmp = new node;
        tmp->n = i.first;
        tmp->c = i.second;
        st.push_back(tmp);
    }
    while (!st.empty()) {
        node* right = st.back();
        st.pop_back();
        if (st.empty()) {
            return right;
        }
        else {
            node* tmp = new node();
            node* left = st.back();
            st.pop_back();
            tmp->n = left->n + right->n;
            tmp->left = left;
            tmp->right = right;
            
            for (int i = 0; i< st.size(); i++) {
                if (st[i]->n < tmp->n) {
                    st.insert(st.begin()+i, tmp);
                    goto x;
                }
            }
            st.push_back(tmp);
        x:;
        }
    }
    return NULL;

}

void traversal(node* myNode, int l) {
    int i;
    if (myNode) {
        traversal(myNode->right, l + 1);
        for (int i = 1; i <= l; i++) cout << "   ";
        cout << myNode ->n << '|' << myNode->c << '\n';
        traversal(myNode->left, l + 1);
    }
}

map<char, string> mChSt;
map<string, char> mStCh;

void makeMap(node* N, string path) {
    if (N == NULL) return;
    if (N->left==NULL&&N->right==NULL) {
        mChSt[N->c] = path;
        mStCh[path] = N->c;
    }
    else {
        makeMap(N->left, path + "0");
        makeMap(N->right, path + "1");
    }
}



string codeString(string s) {
    string ans = "";
    for (int i = 0; i < s.length(); ++i) {
        ans += mChSt[s[i]];
    }
    return ans;
}

string decodeString(string s) {
    string ans = "";
    string tmp="";
    for (int i = 0; i < s.length(); ++i) {
        tmp += s[i];
        if (mStCh.find(tmp) != mStCh.end()) {
            ans += mStCh[tmp];
            tmp = "";
        }
    }
    return ans;
}

int main()
{
    string s = "aaaaaaaaaabbbbbbbbccccccdddddeeeefff";
    cin >> s;
    vector<pair<int,char>> st = countEntry(s);
    node* tree = makeHuffmanTree(st);
    traversal(tree, 0);
    makeMap(tree, "");
    for (auto& i : mChSt) {
        cout << i.first << ' ' << i.second << '\n';
    }
    int n = 0;
    string endCode = codeString(s);
    cout << "Result: "<<endCode <<'\n';
    cout << "Decoded result: " << decodeString(endCode) << '\n';
    cout << "Uncoded size: " << s.length() * 8 << " bits\n";
    cout << "End size:     " << endCode.length() << " bits\n";
    



}