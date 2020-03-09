# Censors string input using list of restricted strings
# Usage: speller [dictionary] text

from cs50 import get_string
import sys
from sys import argv

banned_words = set()

def main():

    # TODO
    if len(sys.argv) != 2:
        sys.exit("Usage: python bleep.py dictionary")
        return 1
    load(argv[1])
    print("what message would you like to censor?")
    text = get_string("")
    check(text)
    return 0

def load(dictionary):
    file = open(dictionary, "r")
    for line in file:
        banned_words.add(line.rstrip("\n"))
    file.close()
    #print(f"{len(banned_words)}")

def check(message):
    words = message.split()
    for word in words:
        if word.lower() in banned_words:
            banned = True
        else:
            banned = False
        for c in word:
            if banned is True:
                print("*", end="")
            if banned is False:
                print(f"{c}", end="")
        print(" ", end="")
    print()


if __name__ == "__main__":
    main()
