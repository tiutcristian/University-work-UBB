// We will use constant reference to reduce the execution time as much as possible.
// All the results from any function are provided through output parameters.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

long long counter;

// read a number n and a set of n numbers
void read(int &n, vector<int> &numbers_set)
{
    fin >> n;
    numbers_set.resize(n);
    for (int i = 0; i < n; i++)
        fin >> numbers_set[i];
}

void factorial(const int &n, long long &result)
{
    result = 1;
    for(int i = 2; i <= n; i++)
        result *= i;
}

void power(const int &base, const int &exp, long long &result)
{
    result = 1;
    for(int i = 1; i <= exp; i++)
        result *= base;
}

void combinations(const int &n, const int &k, long long &result)
{
    result = 1;
    for(int i = 1; i <= k; i++)
        result = result * (n - i + 1) / i;
}

void number_of_onto_functions(const int &n, const int &k, long long &result)
{
    // S(n,k) = sum( (-1)^(k-r) * C(k,r) * r^n )
    // where r goes from 1 to n
    // and C(k,r) = combinations of k taken r
    result = 0;
    int sign = (k%2 == 0) ? 1 : -1;
    for(int r = 1; r <= n; r++)
    {
        sign *= -1;
        long long comb;
        combinations(k, r, comb);
        long long nth_power;
        power(r, n, nth_power);
        result += sign * comb * nth_power;
    }
}

void number_of_partitions(const int &n, long long &result)
{
    // N = sum( S(n,k) / k! )
    // where k goes from 1 to n
    // and S(n,k) is the number of onto functions
    // from a set with n elements to a set with k elements
    result = 0;
    for(int k = 1; k <= n; k++)
    {
        long long fact;
        factorial(k, fact);
        long long no_of_onto_functions;
        number_of_onto_functions(n, k, no_of_onto_functions);
        result += no_of_onto_functions / fact;
    }
}

void print_partition(const vector<vector<int>> &part)
{
    fout << "Partition " << ++counter << ":\n";
    for (auto i : part)
    {
        fout << "{ ";
        for (auto element : i)
            fout << element << ' ';
        fout << "} ";
    }
    fout << '\n';
    fout << "Equivalence relations:\n";
    for (auto i : part)
        for (auto elem1 : i)
            for (auto elem2: i)
                fout << '(' << elem1 << ',' << elem2 << ") ";
    fout << "\n-------------------------------------------------\n";
}

void partition_rec(const vector<int> &numbers_set, int index, vector<vector<int>> &part)
{
    if (index == numbers_set.size())
    {
        print_partition(part);
        return;
    }
    for (int i = 0; i < part.size(); i++)
    {
        part[i].push_back(numbers_set[index]);
        partition_rec(numbers_set, index + 1, part);
        part[i].pop_back();
    }
    part.push_back({numbers_set[index]});
    partition_rec(numbers_set, index + 1, part);
    part.pop_back();
}

void generate_partitions(const vector<int> &numbers_set)
{
    vector<vector<int>> v;
    partition_rec(numbers_set, 0, v);
}

int main()
{
    // read data
    int n;
    vector<int> numbers_set;
    read(n, numbers_set);

    // compute number of partitions
    long long no_of_partitions;
    number_of_partitions(n, no_of_partitions);
    fout << "There are " << no_of_partitions << " partitions.\n\n";

    // generate all partitions and their equivalent relations
    fout << "All partition of the set will be : " << endl;
    generate_partitions(numbers_set);


    fin.close();
    fout.close();
    return 0;
}
