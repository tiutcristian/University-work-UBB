/**
 * 1-dimensional: (2^n - 1) / (2 - 1) 
 * 
 *                      (2^n − 1)(2^n − 2)(2^n − 2^2) ... (2^n − 2^(k−1))
 * => k-dimensional:    -------------------------------------------------
 *                                              k!
 * 
 *                      (2^n − 1)(2^n − 2)(2^n − 2^2) ... (2^n − 2^(k−1))
 *                      -------------------------------------------------  linearly independent subsets
 *                                              k!
 * 
 * A subspace can be spanned by more different linearly independent subsets.
 * These are actually the bases of that subspace, and from project 3 it resulted that we have:
 * 
 *                      (2^k − 1)(2^k − 2)(2^k − 2^2) ... (2^k − 2^(k−1))
 *                      -------------------------------------------------  bases for Z2^k
 *                                              k!
 * 
 * So we get that there are
 * 
 * (2^n − 1)(2^n − 2)(2^n − 2^2) ... (2^n − 2^(k−1))                        k!                             (2^n − 1)(2^n − 2)(2^n − 2^2) ... (2^n − 2^(k−1)) 
 * ------------------------------------------------- * ------------------------------------------------- = -------------------------------------------------  k-dimensional subspaces
 *                        k!                           (2^k − 1)(2^k − 2)(2^k − 2^2) ... (2^k − 2^(k−1))   (2^k − 1)(2^k − 2)(2^k − 2^2) ... (2^k − 2^(k−1))
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

vector<vector<bool>> subspaces;
vector<int> st(70);
int k, n;
unsigned long long cnt;
unsigned long long cnt2;

void subspaces_counter()
{
    unsigned long long den = 1;
    unsigned long long num = 1;
    for (int i = 0; i < k; i++)
    {
        den *= (1<<n) - (1<<i);
        num *= (1<<k) - (1<<i);
    }
    cnt = den / num;
}

void tipar()
{
    for (int i = 1; i <= k; i++)
        fout << st[1<<(i-1)] << ' ';
    fout << '\n';
}

bool valid(int index)
{
    for (int i = 1; i < index; i++)
        if ((st[i]^st[index]) == 0)
            return false;
    return true;
}

void add_combinations(int index)
{
    for(int i = 1; i < index; i++)
        st[index+i] = st[index]^st[i];
}

bool verif_subspace(const vector<bool> &used)
{
    for (auto subspace : subspaces)
    {
        bool same = true;
        for (int i = 1; i <= (1<<n)-1; i++)
            if (subspace[i] != used[i])
                same = false;
        if (same == true)
            return false;
    }
    return true;
}

void back(int index)
{
    for (int i = 1; i < (1<<n); i++)
    {
        st[index] = i;
        if (valid(index))
        {
            add_combinations(index);
            if (index == 1<<(k-1))
            {
                vector<bool> used(70, false);
                for (int i = 1; i <= (1<<k)-1; i++)
                    used[st[i]] = true;
                if (verif_subspace(used))
                {
                    subspaces.push_back(used);
                    cnt2++;
                    tipar();        
                }
            }
            else
                back(index<<1);
        } 
    }
}

int main()
{
    fin >> k >> n;
    
    subspaces_counter();
    fout << cnt << endl;

    back(1);
    cout << "finished\n\n\n";
    if (cnt2 == cnt)
        cout << "ok\n\n";

    fin.close();
    fout.close();

    return 0;
}
