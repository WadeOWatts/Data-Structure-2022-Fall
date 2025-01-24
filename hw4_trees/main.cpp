#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void input(istream&, int, int[][2], char[]);
void height(int,int[][2],char[],int[]);
void DFS(int,int,int&,int[][2],int,bool[],int);
int mini(int[],int);
void SAT(int,int[][2],int[],char[],int,ostream&);
void setBool(int,int,bool[],int[][2],char[],int,bool&,ostream&);
bool sat(int,int[][2],char[],bool[],int,int);

int main()
{
    ifstream inp;
    ofstream oup;
    inp.open("input2.txt");
    oup.open("output.txt");
    int n;
    inp >> n;
    int edge[2*n-2][2], degree[n] = {0};
    char oper[n] = {0};
    input(inp,n,edge,oper);
    inp.close();

    height(n,edge,oper,degree);
    int m = mini(degree,n);

    SAT(n,edge,degree,oper,m,oup);
    oup.close();
    return 0;
}

void input(istream& inp, int n, int edge[][2], char oper[])
{
    string temp;
    getline(inp,temp);
    for(int i = 0;i < n-1;i++)
    {
        getline(inp,temp);
        edge[i][0] = temp.at(1)-48;
        edge[n-1+i][1] = temp.at(1)-48;
        edge[i][1] = temp.at(4)-48;
        edge[n-1+i][0] = temp.at(4)-48;
    }
    while(!inp.eof())
    {
        int i;
        char ii;
        string temp;
        inp >> i >> ii >> temp;
        if(temp == "AND")
            oper[i] = 'A';
        else if(temp == "OR")
            oper[i] = 'O';
        else if(temp == "NAND")
            oper[i] = 'D';
        else if(temp == "NOR")
            oper[i] = 'R';
        else if(temp == "XOR")
            oper[i] = 'X';
        else if(temp == "XNOR")
            oper[i] = 'N';
        else;

        getline(inp,temp);
    }
}
void height(int n,int edge[][2],char oper[],int degree[])
{
    for(int i = 0;i < n;i++)
    {
        if(oper[i] != 0)
        {
            bool visit[n] = {false};
            int recH = 1;
            DFS(i,1,recH,edge,n,visit,-1);
            degree[i] = recH;
        }
    }
}
void DFS(int root,int nowH,int& recH,int edge[][2],int n,bool visit[],int back)
{
    for(int i = 0;i < 2*n-2; i++)
    {
        if(edge[i][0] == root && edge[i][1] != back)
            DFS(edge[i][1],nowH+1,recH,edge,n,visit,edge[i][0]);
        else
        {
            visit[root] = true;
            if(nowH > recH)
                recH = nowH;
        }
    }
}
int mini(int degree[],int n)
{
    int m = 4;
    for(int i = 0;i < n;i++)
    {
        if(degree[i] < 4 && degree[i] != 0)
            m = degree[i];
    }
    return m;
}
void SAT(int n,int edge[][2],int degree[],char oper[],int m, ostream& oup)
{
    for(int i = 0;i < n;i++)
    {
        if(degree[i] == m)
        {
            oup << "root = " << i << endl;
            bool value[n] = {false},found = false;
            setBool(n,0,value,edge,oper,i,found,oup);
            if(found == false)
                oup << "UNSAT" << endl;
        }
    }
}
void setBool(int n,int c,bool value[],int edge[][2],char oper[],int root,bool& found,ostream& oup)
{
    for(int i = 0;i < 2;i++)
    {
        if(i == 0)
            value[c] = false;
        else
            value[c] = true;
        if(n-1 > c)
            setBool(n,c+1,value,edge,oper,root,found,oup);
        else
        {
            bool root_bool = sat(root,edge,oper,value,n,-1);
            if(root_bool == true)
            {
                oup << "SAT" << endl;
                for(int j = 0;j < n; j++)
                {
                    if(oper[j] == 0)
                        oup << j << ": " << value[j] << endl;
                }
                found = true;
                return;
            }
        }
        if(found == true)
            return;
    }
}
bool sat(int root,int edge[][2],char oper[],bool value[],int n,int back)
{
    int a[n] = {0};
    int s = 0;

    for(int i = 0;i < 2*n-2;i++)
    {
        if(edge[i][0] == root && edge[i][1] != back)
        {
            a[s] = edge[i][1];
            s++;

            if(oper[edge[i][1]] != 0)
                value[edge[i][1]] = sat(edge[i][1], edge,oper,value,n,edge[i][0]);
        }
    }

    if(oper[root] == 'A')
    {
        if(s == 1)
            return value[root] = value[a[0]] && value[a[0]];
        else
        {
            bool temp = true;
            for(int i = 0;i < s;i++)
                temp = temp && value[a[i]] ;
            return value[root] = temp;
        }
    }
    else if(oper[root] == 'O')
    {
        if(s == 1)
            return value[root] = value[a[0]] || value[a[0]];
        else
        {
            bool temp = false;
            for(int i = 0;i < s;i++)
                temp = temp || value[a[i]];
            return value[root] = temp;
        }
    }
    if(oper[root] == 'D')
    {
        if(s == 1)
            return value[root] = !(value[a[0]] && value[a[0]]);
        else
        {
            bool temp = true;
            for(int i = 0;i < s;i++)
                temp = temp && value[a[i]];
            return value[root] = !temp;
        }
    }
    if(oper[root] == 'R')
    {
        if(s == 1)
            return value[root] = !(value[a[0]] || value[a[0]]);
        else
        {
            bool temp = false;
            for(int i = 0;i < s;i++)
                temp = temp || value[a[i]];
            return value[root] = !temp;
        }
    }
    if(oper[root] == 'X')
    {
        if(s == 1)
            return value[root] = value[a[0]] ^ value[a[0]];
        else
        {
            bool temp = value[a[0]] ^ value[a[1]];
            for(int i = 2;i < s;i++)
                temp = temp ^ value[a[i]];
            return value[root] = temp;
        }
    }
    if(oper[root] == 'N')
    {
        if(s == 1)
            return value[root] = !(value[a[0]] ^ value[a[0]]);
        else
        {
            bool temp = value[a[0]] ^ value[a[1]];
            for(int i = 2;i < s;i++)
                temp = temp ^ value[a[i]];
            return value[root] = !temp;
        }
    }
}
