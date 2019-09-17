#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    Node(string suffix, bool isLeaf, Node* parent, int depth,int source,int numberofvalues);
    ~Node();

    string getstr();
    bool getisLeaf();
    vector<Node*> getchildren();
    Node* getparent();
    int getdepth();
    int getsource();
    int getstringdepth();
    bool isfull();

    void setstr(string newstring);
    void setdepth(int depth);
    void setparent(Node* parent);
    void addchildren(Node* newchild);
    void removechild(Node* child);

private:
    string str;
    bool isLeaf;
    vector<Node*> children;
    Node* parent;
    int depth;
    int source;
    int stringdepth;
    bool* values;
    int arraysize;
    void equalize(Node* childnode, Node* parentnode);
    bool* getarray();
};
