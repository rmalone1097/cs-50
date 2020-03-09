//Inputs credit card number, outputs type of card (Visa, Amex, Mastercard)

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cc_num = get_long("Number: ");
    long multM = 10;
    long sumM = 0;
    long digM = 0;
    long digLM = 0;
    long digRM = 0;
    long firstDig = 0;
    long secondDig = 0;
    long length = 0;

    do
    {
        digM = (cc_num / multM % 10) * 2;
        if (digM > 9)
        {
            digLM = digM / 10 % 10;
            digRM = digM % 10;
            sumM = sumM + digLM + digRM;
        }
        else
        {
            sumM = sumM + digM;
        }
        if (cc_num / multM < 10 && cc_num / multM != 0)
        {
            firstDig = digM / 2;
        }
        else if (cc_num / multM < 100 && cc_num / multM >= 10)
        {
            secondDig = digM / 2;
        }
        multM = multM * 100;
        length = length + 1;
        //printf("%li\n", digM/2);
    }
    while (cc_num / multM != 0);
    //printf("%li\n", firstDig);
    long mult = 1;
    long sum = 0;
    long dig = 0;

    do
    {
        dig = (cc_num / mult % 10);
        sum = sum + dig;
        if (cc_num / mult < 10 && cc_num / mult != 0)
        {
            firstDig = dig;
        }
        else if (cc_num / mult < 100 && cc_num / mult >= 10)
        {
            secondDig = dig;
        }
         mult = mult * 100;
        length = length + 1;
        //printf("%li\n", dig);
    }
    while (cc_num / mult != 0);
    long totSum = sum + sumM;

    if (length == 15 && firstDig == 3 && totSum % 10 == 0)
    {
        if (secondDig == 4 || secondDig == 7)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 16 && firstDig == 5 && totSum % 10 == 0)
    {
        if (secondDig == 1 || secondDig == 2 || secondDig == 3 || secondDig == 4 || secondDig == 5)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (firstDig == 4 && totSum % 10 == 0)
    {
        if (length == 13 || length == 16)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
