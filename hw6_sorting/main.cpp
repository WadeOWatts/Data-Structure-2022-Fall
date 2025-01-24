#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

void InsertSort(int l[], int n);
void insert(int e, int l[], int i);
void newArray(int l[], int index, int b);
void CreateQ(int l[], int& b, queue<int> &q, istream& inp);
void Sort(istream &inp,int a,int b,int &count,int l[], queue<int> &q);
void FindHL(int b, int l[], int &low, int &lowi, int &high, int &highi);\
void Sort_A(int b,int l[], int &low, int &lowi,int &high,int &highi,int &index, int &count, queue<int> &q);
void Sort_B(int a, int b, int l[], int &low,int &lowi,int &high,int &highi, int &index,int &count,queue<int> &q);
void GetOneDealOne(int &a,istream &inp,int &n, char &tem, queue<int> &q,int b,int l[], int &low,int &lowi,int &high,int &highi, int &index, int &count);

int main()
{
    ifstream inp;
    ofstream oup;
    int a, b, count = 0;
    inp.open("input.txt");
    oup.open("output.txt");
    string temp;
    getline(inp,temp);
    inp >> a >> b;
    inp.close();
    inp.open("input.txt");
    int* l = new int [b+2];
    queue<int> q;

    CreateQ(l,b,q,inp);
    Sort(inp,a,b,count,l,q);
    oup << count << endl;
    return 0;
}

void InsertSort(int l[], int n)
{
    l[0] = INT_MIN;
    for(int j = 2; j <= n; ++j)
        insert(l[j], l, j-1);
}
void insert(int e, int l[], int i)
{
    while(e < l[i])
    {
        l[i+1] = l[i];
        --i;
    }
    l[i+1] = e;
}
void newArray(int l[], int index, int b)
{
    int t;
    for(int i = 1;i <= b+1; i++)
    {
        if(l[i] == index)
        {
            t = i;
            break;
        }
    }
    for(int i = t; i <= b; i++)
    {
        l[i] = l[i+1];
    }
}
void CreateQ(int l[], int& b, queue<int> &q, istream& inp)
{
    for(int i = 1;i <= b+1; i++)
    {
        int j;
        inp >> j;
        l[i] = j;
        q.push(j);
    }
}
void Sort(istream &inp,int a,int b,int &count,int l[], queue<int> &q)
{
    int index = q.front(), high = index + a, low = index - a, highi, lowi, n;
    char tem;

    Sort_A(b,l,low,lowi,high,highi,index,count,q);
    GetOneDealOne(a,inp,n,tem,q,b,l,low,lowi,high,highi,index,count);
    for(int j = 1;j < b; j++)
        Sort_B(a,b-j,l,low,lowi,high,highi,index,count,q);
}
void FindHL(int b, int l[], int &low, int &lowi, int &high, int &highi)
{
    for(int i = 1;i <= b+1; i++)
    {
        if(l[i] >= low)
        {
            lowi = i;
            break;
        }
    }
    for(int i = lowi + 1;i <= b+1 ; i++)
    {
        if(i == b+1 && l[i] <= high)
            highi = i;
        else if(l[i] > high)
        {
            highi = i-1;
            break;
        }
    }
}
void Sort_A(int b,int l[], int &low, int &lowi,int &high,int &highi,int &index, int &count, queue<int> &q)
{
    q.pop();
    InsertSort(l,b+1);
    FindHL(b,l,low,lowi,high,highi);
    count += (highi - lowi);
    newArray(l,index,b);
}
void GetOneDealOne(int &a,istream &inp,int &n, char &tem, queue<int> &q,int b,int l[], int &low,int &lowi,int &high,int &highi, int &index, int &count)
{
    do
    {
        inp >> n;
        inp.get(tem);
        l[b+1] = n;
        q.push(n);
        Sort_B(a,b,l,low,lowi,high,highi,index,count,q);
    }while(tem != '\n');
}
void Sort_B(int a, int b, int l[], int &low,int &lowi,int &high,int &highi, int &index,int &count,queue<int> &q)
{
    index = q.front();
    high = index + a;
    low = index - a;
    Sort_A(b,l,low,lowi,high,highi,index,count,q);
}
