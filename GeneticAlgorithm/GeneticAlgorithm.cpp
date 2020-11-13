#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime> 
#include<vector>
using namespace std;

//transform range from -1->15 to -2^15 to 2^15 - 1

int SIZE = 100;
int GENERATION = 20;
double TARGET = -11.0408;
double CROSS_RATE = 0.5;
double MUTATION_RATE = 0.05;

vector<int> cur_seq;
vector<int> child_seq;

// a very large int -> the number of the chro
// a double -> the actual number

double inline f(double x)
{
    return x * sin(x);
}

inline double encode(int x)
{
    double tmp = x;
    double res;
    res = tmp / (pow(2,16) - 1);
    res += 0.5;
    res *= 16;
    res -= 1;
    return res;
}

inline int code(double x)
{
    x -= 0.5;
    double res = x * (pow(2, 16) - 1.0);
    return int(res);
}

void init()
{
    srand((unsigned)time(NULL));
    cur_seq.resize(SIZE);
    child_seq.resize(SIZE);
    for (int i = 0; i < SIZE; ++i)
    {
        double tmp = double(rand());
        cur_seq[i] = code(tmp/double(RAND_MAX));
    }
}

int main()
{
    init();
    double bestAns = 0;
    //for (int i = 0; i < SIZE; ++i) cout << cur_seq[i] << endl;
    for (int i = 0; i < GENERATION; ++i)
    {      
        //if (abs(bestAns - 11.0857) < 0.0002) break;
        // get the cost done in order of propotion
        vector<double> cost(SIZE);
        double Sum = 0.0;
        int index = -1;
        double Max = 0.0001;
        for (int j = 0; j < SIZE; ++j)
        {
            //if (f(encode(cur_seq[j])) - TARGET <= 0.0001) cost[j] = 10000;
            //else cost[j] = 1.0 / (f(encode(cur_seq[j])) - TARGET);
            //cout << encode(cur_seq[j]) << " " << f(encode(cur_seq[j])) << endl;
            //cout << cost[j] << endl;
            cost[j] = 1.0 / (f(encode(cur_seq[j])) - TARGET);
            Sum += cost[j];
            if (cost[j] > Max)
            {
                index = j;
                Max = cost[j];
            }
        }
        for (int j = 0; j < SIZE; ++j) cost[j] /= Sum;
        for (int k = 0; k < SIZE; ++k)
        {                                  
            double tmp = double(rand()) / double(RAND_MAX);
            //cout << "tmp=" << tmp << endl;
            double s = 0.0;
            int j;
            // get the selected thing
            for (j = 0; j < SIZE ; ++j)
            {
                s += cost[j];
                if (s >= tmp) break;
                //cout << "s = " << s << endl;
            }
            child_seq[k] = cur_seq[j];
        }
        for (int j = 0; j < SIZE / 2; ++j)
        {
            double rate = double(rand()) / double(RAND_MAX);
            if (rate > CROSS_RATE) continue;
            rate = double(rand()) / double(RAND_MAX);
            double a = rate * double(child_seq[j * 2]) + (1 - rate) * double(child_seq[j * 2 + 1]);
            double b = rate * double(child_seq[j * 2 + 1]) + (1 - rate) * double(child_seq[j * 2]);
            child_seq[j * 2] = int(a);
            child_seq[j * 2 + 1] = int(b);
        }
        for (int j = 0; j < SIZE; ++j)
        {
            double rate = double(rand()) / double(RAND_MAX);
            if (rate > MUTATION_RATE) continue;
            int tmp = 0;
            int place = int(rate * 15.0);
            for (int k = 0; k < place; ++k)
            {
                tmp += (child_seq[j] % 2) * pow(2, k);
                child_seq[j] /= 2;
            }
            if (child_seq[j] % 2 == 0) tmp += (child_seq[j] % 2) * pow(2, place);
            child_seq[j] /= 2;
            for (int k = place + 1; k < 16; ++k)
            {
                tmp += (child_seq[j] % 2) * pow(2, k);
                child_seq[j] /= 2;
            }
            child_seq[j] = tmp;
        }
        bestAns = encode(cur_seq[index]);
        cout << "generation " << i + 1 << ":  ";
        //cout << "father" << endl;
        //for (int j = 0; j < SIZE; ++j) cout << encode(cur_seq[j]) << endl;
        //cout << "child" << endl;
        //for (int j = 0; j < SIZE; ++j) cout << encode(child_seq[j]) << endl;
        cur_seq = child_seq;
        cout << bestAns << endl;
    }
    return 0;
}