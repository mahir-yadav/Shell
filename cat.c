#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
extern int errno;
int main(int num, char *args[])
{
    if (num == 1)
        printf("No file given to open.\n");
    bool flagn = false;
    bool flage = false;
    for (int a = 0; a < num; a++)
    {
        if (strcmp(args[a], "-E") == 0)
            flage = true;
        if (strcmp(args[a], "-n") == 0)
            flagn = true;
    }
    int count = 1;
    int ini = 1;
    if (flagn)
        printf("\t%d\t", count++);
    if (strcmp(args[1], "-E") == 0 || strcmp(args[1], "-n") == 0)
    {
        ini = 2;
    }

    int fd4 = open(args[ini], O_RDONLY);
    if (fd4 == -1)
    {
        printf("Error no: %d ", errno);
        perror("cat ");
    }
    else
    {
        char x;
        int idx = 0;
        while (1)
        {
            int temp;
            idx = 0;
            while ((temp = read(fd4, &x, sizeof(char))) > 0)
            {
                if (temp == -1)
                {
                    printf("Error no: %d ", errno);
                    perror("cat ");
                }
                if (flage && x == '\n')
                    printf("$");
                printf("%c", x);
                if (x == '\n')
                {
                    if (flagn)
                        printf("\t%d\t", count++);
                    break;
                }
                idx++;
            }
            if (temp <= 0)
                break;
        }
    }

    printf("\n");
    return 0;
}