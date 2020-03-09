# Implements caesar cipher
# Usage: python caesar.py n

import sys
from cs50 import get_string

def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python caesar.py n")

    key = int(sys.argv[1])
    if key == 0:
        sys.exit("Usage: python caesar.py n")

    plain = get_string("plaintext: ")
    plainL = len(plain)
    print("ciphertext: ")

    for c in plain:
        ch = ord(c)
        if c.isupper():
            print(chr(((ch - 65 + key) % 26) + 65), end="")
        elif c.islower():
            print(chr(((ch - 97 + key) % 26) + 97), end="")
        else:
            print(chr(ch), end="")
    print()


if __name__ == "__main__":
    main()
