#ifndef DECIMAL_H
#define DECIMAL_H

#include <iostream>
// never using namespace std in header file as it will affect all files who include this header file
using std::cout;


//
class Decimal {
    public:
        Decimal();

        Decimal(int input);

        Decimal(const char* input);

        Decimal(const Decimal& another);

        ~Decimal();

        bool isNegative() const;

        Decimal flipSign() const;

        bool isLargerThan(const Decimal& another) const;

        Decimal add(const Decimal& another) const;

        void addToSelf(const Decimal& another);

        Decimal multiplyByPowerOfTen(int power) const;

        Decimal multiplyBySingleDigit(int multiplier) const;

        Decimal multiply(const Decimal& another) const;

        Decimal subtract(const Decimal& another) const;

        int countDigitsBeforeDP() const;

        int countDigitsAfterDP() const;

        void print() const // print the decimal number
        {
            cout << "\"";
            for (int i = 0; i < size; i++)
                cout << content[i];
            cout << "\"";
        };
    private:
        char* content;
        int size;
};

#endif // DECIMAL_H