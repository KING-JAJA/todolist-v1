#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

int multSecondtoLastDigits(long long ccnum);
int sumlastdigits(long long ccnum);
bool checksum(long long ccnum);
int check_card_length(long long ccnum);
void print_card_name(long long ccnum);

int main(void)
{
    //initializing variable to store credit card number
    long long ccnum;

    //prompt user to enter a credit card number
    do
    {
        ccnum = get_long("Enter credit card number: ");
    }
    while (ccnum <= 0);

    int cardLength = check_card_length(ccnum);

    if ((cardLength == 13 || cardLength == 15 || cardLength == 16) && checksum(ccnum))
    {
        print_card_name(ccnum);
    }
    else
    {
        printf("INVALID\n") ;
    }
}

//defining a function checksum
bool checksum(long long ccnum)
{
    int sum = sumlastdigits(ccnum) + multSecondtoLastDigits(ccnum);

    return (sum % 10) == 0;
}

int sumlastdigits(long long ccnum)
{
    int lastdigitsum = 0;
    long long cardnum = ccnum;

    //calculating the sum of every other number starting with the last digit and jumping two intervals at a time
    while(cardnum > 0)
    {
        int lastdigit = cardnum % 10;
        lastdigitsum = lastdigitsum + lastdigit;

        cardnum = cardnum / 100;
    }

    return lastdigitsum;
}

int multSecondtoLastDigits(long long ccnum)
{
    int secondToLoastDigitsum = 0;
    long long cardnum = ccnum;

    //removing the last number
    cardnum = cardnum / 10;

    //multiplying every second to last digit by 2, then adding them
    while(cardnum > 0)
    {
        int secondToLoastDigit = (cardnum % 10);
        int multSecondToLoastDigit = secondToLoastDigit * 2;

        secondToLoastDigitsum = secondToLoastDigitsum + multSecondToLoastDigit;

        cardnum = cardnum / 100;
    }

    return secondToLoastDigitsum;
}

//defining a function to check the length of card numbers
int check_card_length(long long ccnum)
{
    int length = 0;

    while (ccnum != 0)
    {
        ccnum = ccnum / 10;
        length++;
    }
    return length;
}

//defining a function to check first two digits and print the card name
void print_card_name(long long ccnum)
{
    // 34e13 is first two digits and followed by 13 zeros as AMEX is 15 digits long
    if ((ccnum >= 34e13 && ccnum < 35e13) || (ccnum >= 37e13 && ccnum < 38e13))
    {
        printf("AMEX\n");
    }

    else if (ccnum >= 51e14 && ccnum < 56e14)
    {
        printf("MASTERCARD\n");
    }

    else if ((ccnum >= 4e12 && ccnum < 5e12) || (ccnum >= 4e15 && ccnum < 5e15))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}