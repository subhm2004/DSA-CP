#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class BaseConverter
{
public:
    // Function to convert a number to any base (2 to 36)
    static string convertToBaseN(int num, int base)
    {
        if (base < 2 || base > 36)
        {
            throw invalid_argument("Base must be between 2 and 36.");
        }

        if (num == 0)
        {
            return "0";
        }

        const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string result;
        bool isNegative = num < 0;
        num = abs(num);

        while (num > 0)
        {
            result.insert(result.begin(), digits[num % base]);
            num /= base;
        }

        if (isNegative)
        {
            result.insert(result.begin(), '-');
        }

        return result;
    }
};

int main()
{
    int num, base;

    cout << "Enter number: ";
    cin >> num;

    cout << "Enter base (2-36): ";
    cin >> base;

    try
    {
        string converted = BaseConverter::convertToBaseN(num, base);
        cout << "Converted number: " << converted << endl;
    }
    catch (const invalid_argument &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
