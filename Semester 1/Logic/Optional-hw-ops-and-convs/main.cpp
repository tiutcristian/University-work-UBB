/**
 * *Operations project*
 * Name: Tiut Cristian
 * Group: 917
*/

#include "iostream"
#include "cstring"
#include "vector"

using namespace std;

int cmp(const vector<int> &a, const vector<int> &b)
{
    /*
     We will use the following system to suggest the comparison result:
        * -1 means "a < b"
        * 0 means "a = b"
        * 1 means "a > b"
    */
    if (a.size() > b.size()) // if a has more digits, then a > b
        return 1;
    else if (a.size() < b.size())  // if b has more digits, then b > a
        return -1; 
    else // a.size = b.size
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] > b[i])
                return 1;
            else if (a[i] < b[i])
                return -1;
    return 0;
}

bool check_valid_vector(const vector<int> &number, int base)
{
    int max_digit = 0;  // set max digit to 0
    for (auto digit : number)  // iterate through the number
        if (digit > max_digit)  
            max_digit = digit;  // update max digit if necesarry
    return max_digit < base;  // return true only if the number fits the base limits
}

void print_number(const vector<int> &number, bool sgn)
{
    if (sgn)  // if the number is negative, print '-'
        cout << '-';
    for (int i = number.size()-1; i >= 0; i--)
    // iterate through the number in reverse order
        if (number[i] < 10)
            cout << number[i];
        else  // if the stored number is greater than 10 we print the corresponding letter
            cout << (char)('A' + number[i] - 10);
    cout << "\n\n\n";  // add some clearance :)
}

void add (int base, const vector<int> &a, const vector<int> &b, vector<int> &res)
{
    res.clear();  // clear previous result

    // error handling
    if (base <= 1)  // check if base is valid
    {               // and print an error otherwise
        cout << "Operation could not be performed. Base must be strictly greater than 1.\n";
        return;
    }
    if (!check_valid_vector(a, base) || !check_valid_vector(b, base))  // check if numbers are valid
    {                                                                  // and print an error otherwise
        cout << "Operation could not be performed. Operands' digits exceed base limits.\n";
        return;
    }
    
    int i = 0;
    int carry = 0;  // clear carry in the beginning

    while (i < a.size() && i < b.size())  // iterate through the numbers until one finishes
    {
        int curr_sum = a[i] + b[i] + carry;  // compute sum 
        res.push_back(curr_sum % base);  // add the result mod base to the result
        carry = curr_sum / base;  // if the result exceeds the base limits, carry will be set
        ++i;
    }

    while (i < a.size())  // perform same process if a hasn't finnished
    {
        int curr_sum = a[i] + carry;
        res.push_back(curr_sum % base);
        carry = curr_sum / base;
        ++i;
    }

    while (i < b.size())  // perform same process if b hasn't finnished
    {
        int curr_sum = b[i] + carry;
        res.push_back(curr_sum % base);
        carry = curr_sum / base;
        ++i;
    }

    if (carry)                 // if at the end we remain with a carry, 
        res.push_back(carry);  // it will be added separately
}

void sub (int base, const vector<int> &a, const vector<int> &b, vector<int> &res, bool &sgn)
{
    res.clear();  // clear previous result

    // error handling
    if (base <= 1)  // check if base is valid
    {               // and print an error otherwise
        cout << "Operation could not be performed. Base must be strictly greater than 1.\n";
        return;
    }
    if (!check_valid_vector(a, base) || !check_valid_vector(b, base))  // check if numbers are valid
    {                                                    // and print an error otherwise
        cout << "Operation could not be performed. Operands' digits exceed base limits.\n";
        return;
    }
    
    sgn = 0;  // initially set sgn to 0
    if (cmp(a, b) >= 0)  // a >= b
    {
        res.resize(a.size());  // max length of result is the biggest number's size
        int lenb = b.size();  // min (a.size, b.size) is always b.size
        int borrow = 0;
        for (int i = 0; i < lenb; i++)  // iterate through the vectors 
        {                               // up to the length of the shortest one
            res[i] = a[i] - b[i] - borrow;  // perform subtraction with borrow (borrow can be 0)
            borrow = 0;  // reset the borrow
            if (res[i] < 0)  // if the obtained result is negative we need to borrow
            {
                res[i] += base;  // so we add to the result the base
                borrow = 1;  // and set the borrow such that it will subtract 1 
            }                // from the next result digit
        }
        int lena = a.size();
        res[lenb] = a[lenb]  - borrow;
        for (int j = lenb + 1; j < lena; j++)
            res[j] = a[j];
    }
    else  // a < b
    {
        res.resize(b.size());  // max length of result is the biggest number's size
        sub(base, b, a, res, sgn);  // call function inverting the numbers
        sgn = 1;  // set sign
    }

    int reslen = res.size();
    if (res[reslen-1] == 0)  // if the first digit of the result is 0 
        res.resize(reslen - 1);  //then it can be eliminated
}

void mul (int base, const vector<int> &a, int digit, vector<int> &res)
{
    res.clear();  // clear previous result

    // error handling
    if (base <= 1)  // check if base is valid
    {               // and print an error otherwise
        cout << "Operation could not be performed. Base must be strictly greater than 1.\n";
        return;
    }
    if (!check_valid_vector(a, base) || digit >= base)  // check if numbers are valid
    {                                                   // and print an error otherwise
        cout << "Operation could not be performed. Operands' digits exceed base limits.\n";
        return;
    }
    
    int carry = 0;  // initialize carry with
    for (auto d: a)  // iterate through a's digits 
    {
        int tmp = d * digit + carry;  // perform the multiplication and then the addition with the carry
        res.push_back(tmp % base);  // put the obtained number's remainder from the division with the base in the result
        carry = tmp / base;  // the carry becomes the quotient of the above mentioned division
    }
    if (carry)  // if in the end we still have anything in the carry
        res.push_back(carry);  // we also put the carry in the result
}

void read_number(vector<int> &number)
{
    number.clear();
    char s[30];
    cin >> s;  // read array of chars
    for (int i = strlen(s)-1; i >= 0; i--)  // add the digits in reverse order to the number
        if ('0' <= s[i] && s[i] <= '9')  // if the character is a decimal digit
            number.push_back(s[i]-'0');  // we add that digit (int)
        else                                // otherwise
            number.push_back(s[i]-'A'+10);  // we add the corresponding letter from the hexadecimal digits
}

void print_menu()  // prints to the console the option menu
{
    cout << "\nChoose an option:"
         << "\n1. Add two numbers in a base"
         << "\n2. Subtract 2 numbers in a base"
         << "\n3. Multiply a number by a digit in a base"
         << "\n4. Quit";
}

int get_user_input()
{
    int tmp;
    cout << "\n>>> ";
    cin >> tmp; 
    return tmp;
}

int main() 
{
    cout << "============= Operations and Conversions project =============\n"
         << "Name: Tiut Cristian\n"
         << "Group: 917\n\n\n";

    bool repeat_loop = true;
    while (repeat_loop)
    {
        int user_input, base;
        bool sgn;
        vector<int> result, a, b;

        print_menu();
        user_input = get_user_input(); 

        switch (user_input)
        {
        case 1:
            // addition
            cout << "base = "; cin >> base;
            cout << "first number = "; read_number(a);
            cout << "second number = "; read_number(b);
            add(base, a, b, result);
            if (result.size())
            {
                cout << "result = "; 
                print_number(result, 0);
            }
            break;
        case 2:
            // subtraction
            cout << "base = "; cin >> base;
            cout << "first number = "; read_number(a);
            cout << "second number = "; read_number(b);
            sub(base, a, b, result, sgn);
            if (result.size())
            {
                cout << "result = "; 
                print_number(result, sgn);
            }
            break;
        case 3:
            // multiplication
            int digit;
            cout << "base = "; cin >> base;
            cout << "number = "; read_number(a);
            cout << "digit = "; cin >> digit;
            mul(base, a, digit, result);
            if (result.size())
            {
                cout << "result = "; 
                print_number(result, 0);
            }
            break;
        case 4:
            // quit
            cout << "Goodbye!\n\n";
            repeat_loop = false;
            break;
        default:
            cout << "Incorrect input!\n";
            break;
        }
    }
    
    return 0;
}