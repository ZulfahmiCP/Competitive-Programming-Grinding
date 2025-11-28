#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct SuffixTree {
    struct Node {
        int start, end;
        map<char, int> children;
        int suffixLink;

        Node(int start, int end) : start(start), end(end), suffixLink(-1) {}
    };

    string text;
    vector<Node> nodes;
    int activeNode, activeEdge, activeLength;
    int remainingSuffixCount, leafEnd;
    int size;

    SuffixTree(const string& s) : text(s), size(s.length()) {
        nodes.emplace_back(-1, -1);  // Root node
        activeNode = 0;  // Start with root node
        activeEdge = -1;
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = -1;

        buildTree();
    }

    int edgeLength(int nodeIndex) {
        return nodes[nodeIndex].end - nodes[nodeIndex].start + 1;
    }

    bool walkDown(int nodeIndex) {
        int length = edgeLength(nodeIndex);
        if (activeLength >= length) {
            activeEdge += length;
            activeLength -= length;
            activeNode = nodeIndex;
            return true;
        }
        return false;
    }

    void extendSuffixTree(int pos) {
        leafEnd = pos;
        remainingSuffixCount++;
        int lastNewNode = -1;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0) {
                activeEdge = pos;
            }

            if (nodes[activeNode].children.find(text[activeEdge]) == nodes[activeNode].children.end()) {
                nodes[activeNode].children[text[activeEdge]] = nodes.size();
                nodes.emplace_back(pos, size - 1);

                if (lastNewNode != -1) {
                    nodes[lastNewNode].suffixLink = activeNode;
                    lastNewNode = -1;
                }
            } else {
                int next = nodes[activeNode].children[text[activeEdge]];
                if (walkDown(next)) continue;

                if (text[nodes[next].start + activeLength] == text[pos]) {
                    if (lastNewNode != -1 && activeNode != 0) {
                        nodes[lastNewNode].suffixLink = activeNode;
                        lastNewNode = -1;
                    }
                    activeLength++;
                    break;
                }

                int splitEnd = nodes[next].start + activeLength - 1;
                int split = nodes.size();
                nodes.emplace_back(nodes[next].start, splitEnd);
                nodes[activeNode].children[text[activeEdge]] = split;

                nodes[split].children[text[pos]] = nodes.size();
                nodes.emplace_back(pos, size - 1);
                nodes[next].start += activeLength;
                nodes[split].children[text[nodes[next].start]] = next;

                if (lastNewNode != -1) {
                    nodes[lastNewNode].suffixLink = split;
                }

                lastNewNode = split;
            }

            remainingSuffixCount--;

            if (activeNode == 0 && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            } else if (activeNode != 0) {
                activeNode = nodes[activeNode].suffixLink;
            }
        }
    }

    void buildTree() {
        for (int i = 0; i < size; i++) {
            extendSuffixTree(i);
        }
    }

    void printTreeDFS(int nodeIndex, int labelHeight) {
        if (nodeIndex == -1) return;

        if (nodes[nodeIndex].start != -1) {
            for (int i = nodes[nodeIndex].start; i <= nodes[nodeIndex].end; i++) {
                cout << text[i];
            }
        }

        int leaf = 1;
        for (auto& child : nodes[nodeIndex].children) {
            if (nodes[nodeIndex].start != -1) {
                leaf = 0;
            }
            printTreeDFS(child.second, labelHeight + edgeLength(child.second));
        }

        if (leaf == 1) {
            cout << " [" << size - labelHeight << "]" << endl;
        }
    }

    void printTree() {
        printTreeDFS(0, 0);
    }
};

int main() {
    string s = "xabxac#";
    SuffixTree tree(s);
    tree.printTree();

    return 0;
}
