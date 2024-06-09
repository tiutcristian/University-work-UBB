#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("input.txt");
ofstream fout ("output.txt");
int cnt;

void number_of_bases(int n, unsigned long long &result)
{
    /*
        Z_2 ^ n ==> 2^n vectors in the basis

        Each vector can be chosen in 2^n - [the 0 vector] - [each linear combination of the already chosen vectors]

        So we have:

        1st vector ==> 2^n - (0 choose 0) = 2^n - 1 ways
        2nd vector ==> 2^n - (1 choose 0) - (1 choose 1) = 2^n - 2 ways
        3rd vector ==> 2^n - (2 choose 0) - (2 choose 1) - (2 choose 2) = 2^n - 4 ways = 2^n - 2^2 ways
        ...
        nth vector ==> 2^n - (n-1 choose 0) - ... - (n-1 choose n-1) = 2^n - 2^(n-1) ways

        Hence, we can choose a basis in:
        (2^n - 2^0) * ... * (2^n - 2^(n-1)) ways.
    */
    result = 1;                           // result (initialised with 1)
    unsigned long long pow_of_2 = 1 << n; // 2^n (obtained shifting a 1 bit with n positions to the left)
    unsigned long long crt = 1;           // current power of 2 to be subtracted from 2^n (initialised with 1)
    while (crt < pow_of_2)
    {
        result *= pow_of_2 - crt; // multiply the result with difference between 2^n and current power of 2
        crt <<= 1;                // multiply the current power of 2 by 2 (shift 1 position to the left)
    }
}

// --------------------------------------------------------------
void tipar(const vector<vector<int>> &st)   // print a basis
{
    for (auto v : st)
    {
        fout << "( ";
        for (auto elem : v)
            fout << elem << ' ';
        fout << ") ";
    }
    fout << endl;
}

vector<int> sum(vector<int> a, vector<int> b)   // sum of 2 vectors
{   
    vector<int> c;
    for (int i = 0; i < a.size(); i++)
        c.push_back((a[i]+b[i])%2);
    return c;
}

bool equal(vector<int> a, vector<int> b)    // verify if 2 vectors are equal
{
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

bool valid(int k, vector<vector<int>> &st)  // check validity for backtracking
{   
    // as the scalars are from Z_2, 
    // for any previous vector we either add it to the sum or not
    // and if the sum is equal to the vector with index k
    // then it can be written as a linear combination o the ones before it

    // for k >= 1
    for (int i = 0; i <= k - 1; i++)
        if (equal(st[i], st[k]))
            return false;
    
    // for k >= 2
    for (int i = 0; i < k-1; i++)
        for (int j = i+1; j <= k-1; j++)
            if (equal(sum(st[i], st[j]), st[k]))
                return false;
    
    // for k == 3
    if (k == 3)
        if (equal(
            sum(
                sum(st[0], st[1]), 
                st[2]
            ),
            st[3]
        ))
        return false;
    return true;
}

void back(const vector<vector<int>> &vectors, int k, int n, vector<vector<int>> &st)
{
    for (int i = 1; i < (1 << n); i++)  // starting from 1 (not taking into consideration the 0 vector)
    {
        st[k] = vectors[i];
        if (valid(k, st))
            if (k == n-1)
                tipar(st), cnt++;
            else
                back(vectors, k+1, n, st);
    }
}
// --------------------------------------------------------------

void print_bases(int n)
{
    // create an initial vector with the vectors 0 and 1
    vector<vector<int>> vectors;
    vector<int> tmp(1);
    tmp[0] = 0;
    vectors.push_back(tmp);
    tmp[0] = 1;
    vectors.push_back(tmp);
    for (int i = 2; i <= n; i++)
    {
        // then add to a new list the vectors obtained by taking
        // each vector in the current list and adding 0 or 1
        // we do this until we obtain vectors with n components
        vector<vector<int>> new_vectors_list;
        for (auto i : vectors)
        {
            vector<int> tmp = i;
            tmp.push_back(0);
            new_vectors_list.push_back(tmp);
            tmp.pop_back();
            tmp.push_back(1);
            new_vectors_list.push_back(tmp);
        }
        vectors = new_vectors_list; // current list becomes the new list and the process repeats
    }
    vector<vector<int>> st(n);  // vector where each solution is built
    back(vectors, 0, n, st);    // we use backtracking to generate each possible solution
}

int main()
{
    int n;
    fin >> n;

    unsigned long long result;
    number_of_bases(n, result);
    fout << result << " bases\n\n";
    print_bases(n);
    
    // verification
    if (result == cnt)
        cout << "ok";    

    fin.close();
    fout.close();
    return 0;
}