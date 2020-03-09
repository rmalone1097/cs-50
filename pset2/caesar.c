#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int key = atoi(argv[1]);
        if (key != 0)
        {
            string plain = get_string("plaintext: ");
            int plainL = strlen(plain);
            printf("ciphertext: ");
            for (int i = 0; i < plainL; i++)
            {
                char c = plain[i];
                if (isupper(c))
                {
                    printf("%c", ((c - 65 + key) % 26) + 65);
                }
                else if (islower(c))
                {
                    printf("%c", ((c - 97 + key) % 26) + 97);
                }
                else
                {
                    printf("%c", c);
                }
            }
            printf("\n");
            return 0;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
