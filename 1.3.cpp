#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

class vertex {
    vertex *child1, *child2;
    int value;

public:
    vertex() {}

    vertex(vertex *child1, vertex *child2, int v) {
        this->child1 = child1;
        this->child2 = child2;
        this->value = v;
    }

    int getValue() {
        return this->value;
    }

    vertex *getChild1() {
        return this->child1;
    }

    vertex *getChild2() {
        return this->child2;
    }

    bool hasChildren() {
        return this->child1 != nullptr;
    }
};

vertex vertices[7];
vertex mainVertices[31];


bool isSubgraph(vertex *mainG, vertex *subG) {
    if (mainG->getValue() == subG->getValue()) {
        if (mainG->hasChildren() && subG->hasChildren())
            return isSubgraph(mainG->getChild1(), subG->getChild1()) &&
                   isSubgraph(mainG->getChild2(), subG->getChild2()) ||
                   isSubgraph(mainG->getChild1(), subG->getChild2()) &&
                   isSubgraph(mainG->getChild2(), subG->getChild1()) ||
                   isSubgraph(mainG->getChild1(), subG) ||
                   isSubgraph(mainG->getChild2(), subG);
        if (subG->hasChildren() && !mainG->hasChildren()) return false;
        return true;
    } else {
        if (mainG->hasChildren())
            return isSubgraph(mainG->getChild1(), subG) ||
                   isSubgraph(mainG->getChild2(), subG);
        return false;
    }
}

vertex buildMainGraph(string graphStr) {
    for (int i = 0; i < graphStr.length(); i++) {
        if (2 * i + 2 < graphStr.length())
            mainVertices[i] = vertex(&mainVertices[2 * i + 1], &mainVertices[2 * i + 2], graphStr[i] == 'A');
        else
            mainVertices[i] = vertex(nullptr, nullptr, graphStr[i] == 'A');
    }
    return mainVertices[0];
}

vertex buildGraph(string graphStr) {
    for (int i = 0; i < graphStr.length(); i++) {
        if (2 * i + 2 < graphStr.length())
            vertices[i] = vertex(&vertices[2 * i + 1], &vertices[2 * i + 2], graphStr[i] == 'A');
        else
            vertices[i] = vertex(nullptr, nullptr, graphStr[i] == 'A');
    }
    return vertices[0];
}


int main() {
    string mainGraphStr, subGraphStr;
    string allMPermutations = "AAAAAAAAAAAAAAAAAAAAAAAAOOOOOOOOOOOOOOOOOOOOOOOO";
    ofstream out("out.out");
    mainGraphStr = allMPermutations.substr(9, 31);
    do {
        bool isOk = true;
        string allPermutations = "AAAAAAAOOOOOOO";
        vertex mainG = buildMainGraph(mainGraphStr);
        for (int i = 0; i < 8; i++) {
            subGraphStr = allPermutations.substr(i, 7);
            do {
                vertex subG = buildGraph(subGraphStr);
                if (!isSubgraph(&mainG, &subG)) {
                    isOk = false;
                    break;
                }
            } while (next_permutation(subGraphStr.begin(), subGraphStr.end()));
            if (!isOk) break;
        }
        if (isOk) out << mainGraphStr << endl;
    } while (next_permutation(mainGraphStr.begin(), mainGraphStr.end()));
    return 0;
}
