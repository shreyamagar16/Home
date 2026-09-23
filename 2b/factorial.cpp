#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <number>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    unsigned long long fact = 1;

    if (n < 0)
    {
        cout << "Factorial is not defined for negative numbers." << endl;
        return 1;
    }

    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }

    cout << "Factorial of " << n << " = " << fact << endl;

    return 0;
}