#include "Node.h"

using namespace std;

Node::Node(string str, bool isLeaf, Node* parent, int depth,int source, int numberofvalues)
{
    this -> arraysize = numberofvalues;
    this -> values = new bool[arraysize];
    this -> str = str;
    this -> isLeaf = isLeaf;
    this -> parent = parent;
    this -> depth = depth;
    this -> source = source;
    this -> stringdepth = str.length();

    for(int i=0; i<numberofvalues; i++)
        values[i] = false;
    if(getisLeaf())
        values[source] = true;
}

Node::~Node()
{
    delete this;
}

string Node::getstr()
{
    return this->str;
}

bool Node::getisLeaf()
{
    return this->isLeaf;
}

vector<Node*> Node::getchildren()
{
    return this->children;
}

Node* Node::getparent()
{
    return this->parent;
}

int Node::getdepth()
{
    return this->depth;
}

int Node::getstringdepth()
{
    return this->stringdepth;
}

int Node::getsource()
{
    return this->source;
}

bool* Node::getarray()
{
    return this->values;
}

void Node::setstr(string newstring)
{
    this->str = newstring;
    this->stringdepth = newstring.length();
}

void Node::setdepth(int depth)
{
    this -> depth = depth;
}

void Node::setparent(Node* parent)
{
    this -> parent = parent;
}

void Node::addchildren(Node* newchild)
{
    this -> children.push_back(newchild);
    if(this->isLeaf)
    {
        this -> isLeaf = false;
        this -> source = -1;
    }

    equalize(newchild,this);
}

void Node::equalize(Node* childnode, Node* parentnode)
{
    bool* childarray = childnode->getarray();
    bool* parentarray = parentnode->getarray();

    for(int i=0; i<arraysize; i++)
    {
        if(childarray[i]== true)
            parentarray[i] = true;
    }

    if(parentnode->getparent())
        equalize(parentnode,parentnode->getparent());
}

bool Node::isfull()
{
    for(int i=0; i<arraysize; i++)
    {
        if(values[i]==false)
            return false;
    }
    return true;
}

void Node::removechild(Node* child)
{
    int index = 0;

    for(vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
    {
        Node* current = *it;

        if(current == child)
        {
            children.erase(children.begin()+index);
            return;
        }

        index++;
    }
}





