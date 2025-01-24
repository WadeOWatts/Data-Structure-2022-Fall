#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Chain;
class Node
{
    friend class Chain;
public:
    Node(string e = "0", Node* next = 0);
private:
    string data;
    Node *link;
    bool combined;
};

class Chain
{
public:
    Chain();
    void Insert(string&);
    void Delete(Node *x, Node *y);
    string get_data();
    bool getComb();
    void setComb();
    Node* getSFirst();
    Node* get1st();
    Node* getLast();
    Node* getFlag();
    void setIter(Node*);
    void moveIter();
    void StoF();
    void sfNext();
    Node* getIter();
    string getIterVal();
    string getSFdata();
    string getFldata();
    Node* getNextIter();
    string getNextIterData();
    Node* getFlagNext();
    bool IsEmpty();
    bool IsLast();
private:
    Node *first;
    Node *last;
    Node *flag;
    Node *iter;
    Node *searchFirst;
};

Chain::Chain()
{
    first = 0;
}
Node::Node(string e, Node* next)
{
    data = e;
    link = next;
    combined = false;
}
void Chain::Insert(string& e)
{
    if(first)
    {
        last -> link = new Node(e);
        last = last -> link;
        if(flag == NULL)
        {
            flag = last;
        }
    }
    else
        first = last = flag = searchFirst = new Node(e);
}
void Chain::Delete(Node *x, Node *y)
{
    if(x == first)
        first = first -> link;
    else
        y ->link = x ->link;
    delete x;
}
void Chain::StoF()
{
    searchFirst = flag;
}
string Chain::get_data()
{
    string s = flag -> data;
    flag = flag -> link;
    return s;
}
bool Chain::getComb()
{
    return iter->combined;
}
void Chain::setComb()
{
    iter->combined = true;
}
string Chain::getIterVal()
{
    string s = iter ->data;
    return s;
}
string Chain::getSFdata()
{
    string s = searchFirst->data;
    return s;
}
string Chain::getFldata()
{
    string s = flag->data;
    return s;
}
Node* Chain::getNextIter()
{
    Node* i = iter ->link;
    return i;
}
Node* Chain::getFlagNext()
{
    Node* i = flag ->link;
    return i;
}
Node* Chain::getSFirst()
{
    return searchFirst;
}
void Chain::sfNext()
{
    searchFirst = searchFirst->link;
}
Node* Chain::get1st()
{
    return first;
}
Node* Chain::getLast()
{
    return last->link;
}
Node* Chain::getFlag()
{
    return flag;
}
void Chain::setIter(Node* i)
{
    iter = i;
}
string Chain::getNextIterData()
{
    return iter->link->data;
}
void Chain::moveIter()
{
    iter = iter ->link;
}
Node* Chain::getIter()
{
    return iter;
}
bool Chain::IsEmpty()
{
    if(first == 0)
        return true;
    else
        return false;
}
bool Chain::IsLast()
{
    return flag == last;
}

string strForm(int n,int l);
int HowManyOnes(string s);
bool ondDiff(string, string);
string markDash(string, string);
void InitGroup(Chain [], int);
void Combination(Chain [], int);
void PrimeImp(Chain [], int);

int main()
{
    ifstream inp;
    inp.open("input1.txt");
    int l,n;
    char temp;
    string tempstr;
    inp >> l;
    getline(inp,tempstr);

    Chain* f = new Chain[l+1];
    while(!inp.eof())
    {
        inp >> n >> temp;
        string s = strForm(n,l);
        int one = HowManyOnes(s);
        f[one].Insert(s);
    }
    inp.close();
    InitGroup(f,l);
    Combination(f,l);
    PrimeImp(f,l);

    return 0;
}

string strForm(int n,int l)
{
    int r = 0;
    string s,temp[l];
    for(int i = 0;i < l;i++)
    {
        r = n % 2;
        temp[l-1-i] = to_string(r);
        n /= 2;
    }
    for(int i = 0;i < l;i++)
    {
        s = s + temp[i];
    }
    return s;
}
int HowManyOnes(string s)
{
    int c = 0;
    for(int i = 0;i < s.size();i++)
    {
        if(s.at(i) == '1')
            c++;
    }
    return c;
}
bool ondDiff(string i, string j)
{
    int c = 0;
    for(int k = 0;k < i.size();k++)
    {
        if(i.at(k) != j.at(k))
            c++;
    }

    return (c == 1);
}
string markDash(string i, string j)
{
    string s = i;
    for(int k = 0;k < i.size();k++)
    {
        if(i.at(k) != j.at(k))
        {
            s.at(k) = '-';
            break;
        }
    }
    return s;
}
void InitGroup(Chain f[], int l)
{
    cout << "Initail Grouping" << endl;
    for(int i = 0;i < l+1;i++)
    {
        cout << i << ": ";
        if(f[i].IsEmpty())
            cout << endl;
        else
        {
            while(!f[i].IsLast())
                cout << f[i].get_data() << ",";

            cout << f[i].get_data() << endl;
        }
    }
}
void Combination(Chain f[], int l)
{
    for(int a = 1; a <= l; a++)//changed
    {
        for(int i = 0;i < l;i++)//changed
        {
            if(!f[i].IsEmpty() && f[i].getSFirst() != NULL && !f[i+1].IsEmpty() && f[i+1].getSFirst() != NULL)
            {
                for(f[i].setIter(f[i].getSFirst()); f[i].getIter() != f[i].getFlag(); f[i].moveIter())
                {
                    bool comb = false;
                    for(f[i+1].setIter(f[i+1].getSFirst()); f[i+1].getIter() != f[i+1].getFlag(); f[i+1].moveIter())
                    {
                        bool b = ondDiff(f[i].getIterVal(),  f[i+1].getIterVal());
                        if(b)
                        {
                            comb = true;
                            f[i+1].setComb();
                            string newS = markDash(f[i].getIterVal(),  f[i+1].getIterVal());
                            Chain *m = new Chain;
                            bool had = false;
                            for(m->setIter(f[i].getFlag());m->getIter() != f[i].getLast(); m->moveIter())
                            {
                                if(m->getIterVal() == newS)
                                {
                                    had = true;
                                    break;
                                }
                            }
                            delete m;
                            if(had == false)
                                f[i].Insert(newS);
                        }
                    }
                    if(comb)
                    {
                        Chain *m = new Chain;
                        if(f[i].getIter() == f[i].get1st())
                            m->setIter(NULL);
                        else
                        {
                            for(m->setIter(f[i].getSFirst()); m->getIter() != m->getFlag(); m->moveIter())
                            {
                                if(m->getNextIter() == f[i].getIter())
                                    break;
                            }
                        }
                        if(f[i].getSFirst() == f[i].getIter())
                        {
                            f[i].sfNext();
                        }
                        f[i].Delete(f[i].getIter(),m->getIter());
                        delete m;
                    }
                }
            }
            for(f[i].setIter(f[i].getSFirst()); f[i].getIter() != f[i].getFlag(); )
            {
                if(f[i].getComb() == true)
                {
                    Chain *m = new Chain;
                    if(f[i].getIter() == f[i].get1st())
                        m->setIter(NULL);
                    else
                    {
                        for(m->setIter(f[i].getSFirst()); m->getIter() != m->getFlag(); m->moveIter())
                        {
                            if(m->getNextIter() == f[i].getIter())
                                break;
                        }
                    }

                    if(f[i].getSFirst() == f[i].getIter())
                    {
                        f[i].sfNext();
                    }
                    Node* temp = new Node;
                    temp = f[i].getIter();
                    f[i].moveIter();
                    f[i].Delete(temp,m->getIter());
                    delete m;
                }
                else
                    f[i].moveIter();
            }
        }

        int count = 0;
        for(int i = 0;i < l+1; i++)
        {
            if(f[i].IsEmpty() || f[i].getFlag() == NULL)
                count++;
        }
        if(count == l+1)
            break;

        cout << "Combination " << a << endl;
        for(int i = 0;i < l+1;i++)
        {
            f[i].StoF();
            cout << i << ": ";

            if(f[i].IsEmpty())
                cout  << endl;
            else if(f[i].getFlag() == NULL)
                cout  << endl;
            else
            {
                while(!f[i].IsLast())
                    cout << f[i].get_data() << ",";

                cout << f[i].get_data() << endl;

            }
        }
    }
}
void PrimeImp(Chain f[], int l)
{
    cout << "Prime Implicants" << endl;
    bool needComma = false;
    for(int i = 0;i < l; i++)
        if(!f[i].IsEmpty())
            for(f[i].setIter(f[i].get1st()); f[i].getIter() != f[i].getLast(); f[i].moveIter())
                if(needComma == true)
                    cout << "," << f[i].getIterVal();
                else
                {
                    cout << f[i].getIterVal();
                    needComma = true;
                }

}
