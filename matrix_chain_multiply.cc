#include <iostream>
#include <stack>
using namespace std;

const int M = 7;

struct node
{
    int l, r;
    node(int i, int j) : l(i), r(j) {}
};

void matrix_chain_order(int* p, int m[M][M], int s[M][M])
{
    int j, q;
    for (int i = 1; i <= M; ++i)
        m[i][i] = 0;
    for (int len = 2; len <= M; ++len)
        for (int i = 1; i <= M - len + 1; ++i)
        {
            j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; ++k)
            {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
}

void rec_print(int s[M][M], int begin, int end)
{
    if (end == begin)
    {
        cout << "A" << begin;
        return;
    }
    cout << '(';
    rec_print(s, begin, s[begin][end]);
    rec_print(s, s[begin][end] + 1, end);
    cout << ')';
}

void print(int s[M][M], int begin, int end)
{
    stack<node> S;
    int LVal[M] = {0}, RVal[M] = {0};
    S.push(node(begin, end));
    while (!S.empty())
    {
        node tmp = S.top();
        S.pop();
        if (tmp.l != tmp.r)
        {
            ++LVal[tmp.l];
            ++RVal[tmp.r];
            S.push(node(s[tmp.l][tmp.r] + 1, tmp.r));
            S.push(node(tmp.l, s[tmp.l][tmp.r]));
        }
    }
    for (int i = 1; i < M; ++i)
    {
        for (int j = 0; j < LVal[i]; ++j)
            cout << '(';
        
        cout << "A" << i;
        
        for (int j = 0; j < RVal[i]; ++j)
            cout << ')';
    }
}

int main()
{
    int m[M][M], s[M][M];
    int p[M] = {30, 35, 15, 5, 10, 20, 25};
    
    matrix_chain_order(p, m, s);
    rec_print(s, 1, 6);
    cout << endl;
    print(s, 1, 6);
}