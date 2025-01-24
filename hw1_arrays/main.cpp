#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class division
{
    public:
        division();
        void readf(istream& ins);
        void move_f_to_r();
        void ass_ind();
        void set_g();
        void set_x();
        void r_x();
        void output(ostream& ous);
        bool cond();

    private:
        vector<int> f;
        vector<int> d;
        vector<double> q;
        vector<double> r;
        vector<double> x;
        unsigned int ind;
        double g;
        int dsize;
};
division::division()
{
    ind = 0;
}

void division::readf(istream& ins)
{
    string line;
    getline(ins, line);
    istringstream ss(line);
    int temp;
    while(ss >> temp)
        f.push_back(temp);

    getline(ins, line);
    istringstream iss(line);
    while(iss >> temp)
        d.push_back(temp);

    dsize = d.size();
}
void division::move_f_to_r()
{
    for(unsigned int i = 0; i < dsize; i++)
    {
        r.push_back(f[ind + i]);
    }
}
void division::ass_ind()
{
    ind++;
}
void division::set_g()
{
    g = r[0]/d[0];
    q.push_back(g);
}
void division::set_x()
{
    if(ind == 0)
    {
        for(unsigned int i = 0;i < dsize;i++)
        {
            x.push_back(d[i] * g);
        }
    }
    else
    {
        for(unsigned int i = 0;i < dsize;i++)
        {
            x[i] = d[i] * g;
        }
    }
}
void division::r_x()
{
    for(unsigned int i = 1; i < dsize; i++)
    {
        r[i-1] = r[i] - x[i];
    }
    r.pop_back();
    if(ind + dsize >= f.size()){
    }
    else
    {
        r.push_back(f[ind + dsize]);
    }
}

void division::output(ostream& ous)
{
    for(unsigned int i = 0; i < q.size(); i++)
        ous << q[i] << " ";
    ous << endl;
    for(unsigned int i = 0; i < r.size(); i++)
        ous << r[i] << " ";
}
bool division::cond()
{
    if(ind + dsize > f.size())
        return 0;
    else
        return 1;
}


int main()
{
    division F;

    ifstream inp;
    ofstream oup;

    inp.open("input.txt");
    oup.open("output.txt");
    F.readf(inp);
    F.move_f_to_r();

    while(F.cond())
    {
        F.set_g();
        F.set_x();
        F.r_x();
        F.ass_ind();
    }
    F.output(oup);

    inp.close();
    oup.close();

    return 0;
}
