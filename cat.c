#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
extern int errno;

int main(int noOfArguements, char *args[])
{
    if (noOfArguements == 1)
        printf("No file mentioned to open ");
    int flagN = 0, flagE = 0;
    for (int a = 0; a < noOfArguements; a++)
    {
        if (strcmp(args[a], "-E") == 0)
            flagE = 1;
        if (strcmp(args[a], "-n") == 0)
            flagN = 1;
    }
    int ini = 1;
    int count = 1;
    if (flagN)
        printf("\t%d\t", count++);
    while (ini < noOfArguements)
    {
        if (strcmp(args[ini], "-E") == 0 || strcmp(args[ini], "-n") == 0)
        {
            ini++;
            continue;
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
                    if (flagE && x == '\n')
                        printf("$");
                    printf("%c", x);
                    if (x == '\n')
                    {
                        if (flagN)
                            printf("\t%d\t", count++);
                        break;
                    }
                    idx++;
                }
                if (temp <= 0)
                    break;
            }
        }
        ini++;
    }
    printf("\n");
    return 0;
}
