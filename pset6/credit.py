from cs50 import get_int
from math import floor

def main():
    cc_num = get_int("Number: ")
    dig1 = 0
    dig2 = 0
    digCounter = 0
    evens = 0
    odds = 0

    while cc_num > 0:
        dig2 = dig1
        dig1 = cc_num % 10

        if digCounter % 2 == 0:
            evens += dig1
        else:
            mult = dig1*2
            odds += (mult // 10) + (mult % 10)

        cc_num //= 10
        digCounter += 1

    is_valid = (evens + odds) % 10 == 0
    first_two_digits = (dig1 * 10) + dig2

    if dig1 == 4 and digCounter >= 13 and digCounter <= 16 and is_valid:
        print("VISA")

    elif first_two_digits >= 51 and first_two_digits <= 55 and digCounter == 16 and is_valid:
        print("MASTERCARD")

    elif (first_two_digits == 34 or first_two_digits == 37) and digCounter == 15 and is_valid:
        print("AMEX")

    else:
        print("INVALID")

if __name__ == "__main__":
    main()