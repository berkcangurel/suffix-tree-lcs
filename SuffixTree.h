#include <fstream>
#include "Node.h"

using namespace std;

class SuffixTree
{
public:
    SuffixTree(string* strings, int size);
    ~SuffixTree();

    void output();

private:
    Node* root;
    string* strings;
    int numberofwords;
    void addsuffix(string suffix, int source);
    void recursivedepth(Node* start);
    Node* bestnode;
    int bestvalue;
    void recursivetraverse(Node* start);
    void traverse();
    bool check(Node* start);
    void clear(Node* start);
    void addstring(string str, int source);
    int begindex(string text, string pattern);
};
