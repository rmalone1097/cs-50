from cs50 import get_int

def main():
    while True:
        height = get_int("Height: ")
        if height >= 1 and height <= 8:
            width = height
            break

    for i in range(1, height+1):
        hashes = i
        print(" " * (width - hashes), end="")
        print("#" * hashes, end="")
        print("  ", end="")
        print("#" * hashes)

if __name__ == "__main__":
    main()