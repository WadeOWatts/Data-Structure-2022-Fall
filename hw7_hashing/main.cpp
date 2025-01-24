#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Chain;
class Node
{
    friend class Chain;
public:
    Node(int k = 0, int v = 0, Node* next = 0);
private:
    int key;
    int value;
    Node *link;
};

class Chain
{
public:
    Chain();
    void Insert(int,int);
    Node* getFirst();
    Node* getLast();
    void setIter(Node*);
    void moveIter();
    Node* getIter();
    int getIterKey();
    int getIterVal();
private:
    Node *first;
    Node *last;
    Node *iter;
};
Node::Node(int k, int v, Node* next)
{
    key = k;
    value = v;
    link = next;
}
Chain::Chain()
{
    first = 0;
}
void Chain::Insert(int k,int v)
{
    if(first)
    {
        last -> link = new Node(k,v);
        last = last -> link;
    }
    else
        first = last = new Node(k,v);
}
Node* Chain::getFirst()
{
    return first;
}
Node* Chain::getLast()
{
    return last->link;
}
void Chain::setIter(Node* i)
{
    iter = i;
}
void Chain::moveIter()
{
    iter = iter ->link;
}
Node* Chain::getIter()
{
    return iter;
}
int Chain::getIterKey()
{
    int s = iter -> key;
    return s;
}
int Chain::getIterVal()
{
    int d = iter -> value;
    return d;
}

int primeFact(int);
int pushIntoBuc(istream &inp, Chain* bucket,int x);
void Find(Chain *bucket, int size, int x,int target,ostream&);

int main()
{
    ifstream inp;
    ofstream oup;

    inp.open("input.txt");
    oup.open("output.txt");

    int t,x;
    inp >> t;

    x = primeFact(t);

    if(x == 1)
    {
        Chain *bucket = new Chain [t];
        int i = pushIntoBuc(inp,bucket,t);
        Find(bucket, i,t,t,oup);
    }
    else
    {
        Chain *bucket = new Chain [x];
        int i = pushIntoBuc(inp,bucket,x);
        Find(bucket, i,x,t,oup);
    }

    inp.close();
    return 0;
}
int primeFact(int t)
{
    int x = 1;
    for(int i = 2; i <= sqrt(t); i++)
    {
        if(t % i == 0)
            x = i;
    }
    return x;
}
int pushIntoBuc(istream &inp, Chain* bucket,int x)
{
    int next, i = 0,temp;
    while(inp >> next)
    {
        if(next % x < 0)
            temp = x + next % x;
        else
            temp = next % x;
        bucket[temp].Insert(i,next);
        i++;
    }
    return i;
}
void Find(Chain *bucket, int size, int x,int target,ostream& oup)
{
    int ans,ansi;
    for(int i = 0;i < size; i++)
    {
        for(int j = 0; j < x; j++)
        {
            bucket[j].setIter(bucket[j].getFirst());
            while(bucket[j].getIter() != 0)
            {
                if(bucket[j].getIterKey() == i)
                {
                    ans = bucket[j].getIterVal();
                    ansi = i;
                    int temp;
                    if(j == 0)
                        temp = 0;
                    else
                        temp = x-j;
                    bucket[temp].setIter(bucket[temp].getFirst());
                    while(bucket[temp].getIter() != 0)
                    {
                        if(bucket[temp].getIterVal() == target - ans)
                        {
                            oup << ansi << endl;
                            oup << bucket[temp].getIterKey() << endl;
                            return;
                        }
                        bucket[temp].moveIter();
                    }
                }
                bucket[j].moveIter();
            }
        }
    }
}
