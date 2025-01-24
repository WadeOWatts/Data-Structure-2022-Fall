#include <iostream>
#include <stack>
#include <fstream>
#include <vector>

using namespace std;

class City
{
public:
    void set_data(unsigned int,string);
    void set_visit();
    string getname();
    unsigned int getindex();
    bool get_visit();
private:
    unsigned int index;
    string name;
    bool visit;
};
class Path
{
public:
    void set_data_p(unsigned int,unsigned int,unsigned int);
    unsigned int get_SC();
    unsigned int get_Des();
    unsigned int get_Dis();
private:
    unsigned int SCindex;
    unsigned int destenation;
    unsigned int distance;
};

unsigned int find_target(string t, vector<City*> v);
bool DFS(int n, vector<Path*> p, vector<City*>,ostream &);

string City::getname()
{
    return name;
}
unsigned int City::getindex()
{
    return index;
}
bool City::get_visit()
{
    return visit;
}
void City::set_visit()
{
    visit = true;
}

void City::set_data(unsigned int a,string s)
{
    index = a;
    name = s;
    visit = false;
}
void Path::set_data_p(unsigned int a,unsigned int b,unsigned int c)
{
    SCindex = a;
    destenation = b;
    distance = c;
}
unsigned int Path::get_SC()
{
    return SCindex;
}
unsigned int Path::get_Des()
{
    return destenation;
}
unsigned int Path::get_Dis()
{
    return distance;
}

int main()
{
    ifstream inp;
    ofstream oup;
    inp.open("input.txt");
    oup.open("output.txt");

    unsigned int c,p;
    vector<City*> v1;
    vector<Path*> v2;

    inp >> c;
    string t;
    getline(inp,t);

    City h[c];
    for(unsigned int i = 0; i < c;i++)
    {
        string temp;
        getline(inp, temp);
        h[i].set_data(i,temp);
        v1.push_back(&h[i]);
    }


    inp >> p;
    getline(inp,t);
    Path d[p];
    unsigned int ptree[c][2];
    for(int i = 0;i < p;i++)
    {
        unsigned int a,b,c;
        inp >> a >> b >> c;
        ptree[b][0] = a;
        ptree[b][1] = c;
        d[i].set_data_p(a,b,c);
        v2.push_back(&d[i]);
    }
    getline(inp,t);
    string target;
    getline(inp,target);


    inp.close();

    unsigned int tind = find_target(target,v1);

    bool path_found = DFS(tind,v2,v1,oup);

    unsigned int sum = 0, sc = 1,d1 = tind;
    while(sc != 0)
    {
        sc = ptree[d1][0];
        sum = sum + ptree[d1][1];
        d1 = sc;
    }
    oup << sum << endl;

    return 0;
}
unsigned int find_target(string t, vector<City*> v)
{
    for(unsigned int i = 0; i < v.size();i++)
    {
        if(t == v[i]->getname())
        {
            return v[i]->getindex();
            break;
        }

    }
}

bool DFS(int n, vector<Path*> p, vector<City*> c,ostream& oup)
{
    stack<unsigned int> s;
    int N = 0;
    s.push(N);
    oup << "push " << N << endl;
    while(s.top() != n)
    {
        if(s.empty())
            return false;
        N = s.top();
        s.pop();
        oup << "pop " << N << endl;
        for(int i = 0;i < p.size();i++)
        {
            if(p[i]->get_SC() == N)
            {
                unsigned int a = p[i]->get_Des();
                if(!c[a]->get_visit())
                {
                    s.push(a);
                    oup << "push " << a << endl;
                    c[a]->set_visit();
                }
            }
        }

    }
    return true;
}
