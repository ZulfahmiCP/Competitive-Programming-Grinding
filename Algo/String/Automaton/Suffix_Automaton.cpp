#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

struct SuffixAutomaton {
    struct State {
        int len, link;
        map<char, int> next;
    };

    vector<State> st;
    int last;

    SuffixAutomaton(const string& s) {
        st.reserve(2 * s.size());
        st.push_back({0, -1});
        last = 0;

        for (char c : s) {
            extend(c);
        }
    }

    void extend(char c) {
        int cur = st.size();
        st.push_back({st[last].len + 1, -1});
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back({st[p].len + 1, st[q].link, st[q].next});
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    int countDistinctSubstrings() {
        int count = 0;
        for (const auto& state : st) {
            count += state.len - st[state.link].len;
        }
        return count;
    }
};

int main() {
    string s = "abacaba";
    SuffixAutomaton sam(s);

    cout << "Number of distinct substrings: " << sam.countDistinctSubstrings() << endl;

    return 0;
}
