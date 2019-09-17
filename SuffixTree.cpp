#include "SuffixTree.h"

using namespace std;

SuffixTree::SuffixTree(string* strings, int size)
{
    this->root = new Node("",true,NULL,1,-1,size);
    this->numberofwords = size;
    this->bestnode = root;
    this->bestvalue = 0;
    this->strings = strings;

    for(int i=0; i<numberofwords; i++)
        addstring(strings[i],i);

    traverse();
}

SuffixTree::~SuffixTree()
{
    clear(root);
}

void SuffixTree::clear(Node* start)
{
    if(start->getisLeaf())
    {
        delete start;
        start = NULL;
    }
    else
    {
        vector<Node*> grandchildren = start->getchildren();
        for(vector<Node*>::iterator it2 = grandchildren.begin(); it2 != grandchildren.end(); ++it2)
        {
            Node* current = *it2;
            clear(current);
        }

        delete start;
        start = NULL;
    }
}

void SuffixTree::addstring(string str, int source)
{
    string word = str + '$';
    string current;

    for(unsigned int i=0; i<word.length(); i++)
    {
        current = word.substr(i,word.length()-i);
        addsuffix(current,source);
    }
}

void SuffixTree::addsuffix(string suffix, int source)
{
    if(root->getisLeaf())
    {
        Node* newnode = new Node(suffix,true,root,root->getdepth()+1,source,numberofwords);
        root->addchildren(newnode);
        newnode = NULL;
        return;
    }

    Node* trace = root;

    vector<Node*> children = trace->getchildren();

    for(vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
    {
        Node* currentchild = *it;
        string currentstring = currentchild->getstr();

        unsigned int matchcount = 0;

        int terminal = (suffix.length() < currentstring.length()) ? suffix.length() : currentstring.length();

        for(int i=0; i<terminal; i++)
        {
            if(currentstring[i] == suffix[i])
                matchcount++;
            else
                break;
        }

        if(matchcount>0)
        {
            if(matchcount < currentstring.length())
            {
                if(currentchild->getisLeaf())
                {
                    Node* newnode = new Node(currentstring,true,currentchild,currentchild->getdepth()+1,currentchild->getsource(),numberofwords);
                    Node* newnode2 = new Node(suffix,true,currentchild,currentchild->getdepth()+1,source,numberofwords);
                    currentchild->setstr(currentstring.substr(0,matchcount));
                    currentchild->addchildren(newnode);
                    currentchild->addchildren(newnode2);
                    newnode = NULL;
                    newnode2 = NULL;
                }
                else
                {
                    Node* newnode = new Node(currentstring.substr(0,matchcount),false,trace,trace->getdepth()+1,-1,numberofwords);
                    Node* newnode2 = new Node(suffix,true,newnode,newnode->getdepth()+1,source,numberofwords);
                    newnode->addchildren(currentchild);
                    newnode->addchildren(newnode2);
                    trace->addchildren(newnode);
                    currentchild->setparent(newnode);
                    recursivedepth(currentchild);
                    trace->removechild(currentchild);
                }
            }
            else if(matchcount == currentstring.length())
            {
                unsigned int newcount = matchcount;
                unsigned int previous = newcount;
                bool cont;
                do
                {
                    cont = false;
                    vector<Node*> grandchildren = currentchild->getchildren();
                    for(vector<Node*>::iterator it2 = grandchildren.begin(); it2 != grandchildren.end(); ++it2)
                    {
                        unsigned int newmatchcount = 0;
                        Node* currentgrandchild = *it2;
                        string currentgrandstring = currentgrandchild->getstr();
                        int newterminal = (suffix.length() < currentgrandstring.length()) ? suffix.length() : currentgrandstring.length();
                        for(int i=0; i<newterminal; i++)
                        {
                            if(currentgrandstring[i] == suffix[i])
                                newmatchcount++;
                        }
                        if(newmatchcount>matchcount)
                        {
                            previous = matchcount;
                            currentchild = currentgrandchild;
                            matchcount = newmatchcount;
                            cont = true;
                            newcount = newmatchcount;
                        }
                    }
                }while(cont);

                if(!currentchild->getisLeaf())
                {
                    if(newcount!=currentchild->getstr().length())
                    {
                        Node* newnode = new Node(currentchild->getstr().substr(0,newcount),false,currentchild->getparent(),currentchild->getdepth(),-1,numberofwords);
                        Node* newnode2 = new Node(suffix,true,newnode,newnode->getdepth()+1,source,numberofwords);
                        newnode->addchildren(currentchild);
                        newnode->addchildren(newnode2);
                        (currentchild->getparent())->addchildren(newnode);
                        currentchild->setparent(newnode);
                        recursivedepth(currentchild);
                        (newnode->getparent())->removechild(currentchild);
                    }
                    else
                    {
                        Node* newnode = new Node(suffix,true,currentchild,currentchild->getdepth()+1,source,numberofwords);
                        currentchild->addchildren(newnode);
                        newnode = NULL;
                    }
                }
                else
                {
                    if(newcount==suffix.length())
                    {
                        if(suffix.length()>1)
                        {
                            if(newcount-previous>1)
                            {
                                Node* newnode = new Node(currentchild->getstr(),true,currentchild,currentchild->getdepth()+1,currentchild->getsource(),numberofwords);
                                Node* newnode2 = new Node(suffix,true,currentchild,currentchild->getdepth()+1,source,numberofwords);
                                currentchild->setstr(currentchild->getstr().substr(0,newcount-1));
                                currentchild->addchildren(newnode);
                                currentchild->addchildren(newnode2);
                                newnode = NULL;
                                newnode2 = NULL;
                            }
                            else
                            {
                                Node* newnode = new Node(suffix,true,currentchild->getparent(),currentchild->getdepth(),source,numberofwords);
                                (currentchild->getparent())->addchildren(newnode);
                                newnode = NULL;
                            }
                        }
                        else
                        {
                            Node* parent = currentchild->getparent();
                            Node* newnode = new Node(suffix,true,parent,currentchild->getdepth(),source,numberofwords);
                            parent->addchildren(newnode);
                            newnode = NULL;
                        }

                    }
                    else
                    {
                        Node* newnode = new Node(currentchild->getstr(),true,currentchild,currentchild->getdepth()+1,currentchild->getsource(),numberofwords);
                        Node* newnode2 = new Node(suffix,true,currentchild,currentchild->getdepth()+1,source,numberofwords);
                        currentchild->setstr(currentchild->getstr().substr(0,newcount));
                        currentchild->addchildren(newnode);
                        currentchild->addchildren(newnode2);
                        newnode = NULL;
                        newnode2 = NULL;
                    }

                }

            }
        return;
        }
    }
    Node* newnode = new Node(suffix,true,root,root->getdepth()+1,source,numberofwords);
    root->addchildren(newnode);
    newnode = NULL;
    return;
}

void SuffixTree::recursivetraverse(Node* start)
{
    if(start->getsource()==-1)
    {
        if(start->getstringdepth()>=bestvalue)
        {
            if(start->getstringdepth()==bestvalue)
            {
                string temp = start->getstr();

                if(temp.compare(bestnode->getstr())==-1)
                {
                    if(check(start))
                    {
                        bestvalue = start->getstringdepth();
                        bestnode = start;
                    }
                }
            }

            else
            {
                if(check(start))
                {
                    bestvalue = start->getstringdepth();
                    bestnode = start;
                }
            }
        }
    }

    if(start->getisLeaf())
        return;
    else
    {
        vector<Node*> grandchildren = start->getchildren();
        for(vector<Node*>::iterator it2 = grandchildren.begin(); it2 != grandchildren.end(); ++it2)
        {
            Node* current = *it2;
            recursivetraverse(current);
        }
    }
}

void SuffixTree::traverse()
{
    recursivetraverse(root);
}

bool SuffixTree::check(Node* start)
{
    return start->isfull();
}

void SuffixTree::recursivedepth(Node* start)
{
    start->setdepth(start->getdepth()+1);
    if(start->getisLeaf())
        return;
    else
    {
        vector<Node*> grandchildren = start->getchildren();
        for(vector<Node*>::iterator it2 = grandchildren.begin(); it2 != grandchildren.end(); ++it2)
        {
            Node* current = *it2;
            recursivedepth(current);
        }
    }
}

int SuffixTree::begindex(string text, string pattern)
{
    for(unsigned int i=0; i<text.length()-pattern.length()+1;i++)
    {
        if(text.substr(i,pattern.length()).compare(pattern)==0)
            return i;
    }
    return -1;
}

void SuffixTree::output()
{
    ofstream outputFile;
    outputFile.open("lcs.txt");

    if(bestvalue<1)
        outputFile << -1;
    else
    {
        outputFile << bestvalue << endl;
        outputFile << bestnode->getstr() << endl;
        for(int i=0; i<numberofwords; i++)
        {
            outputFile << begindex(strings[i],bestnode->getstr()) << endl;
        }
        outputFile.close();
    }
    cout << "Text file created.\n";
}
