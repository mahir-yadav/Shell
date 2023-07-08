#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int num, char *argv[])
{
    bool flag1 = false; // for no flag
    bool flag2 = false; // for -p no warning
    bool flag3 = false; // for -v
    if (num == 1)
    {
        printf("Give directory name which you want to create.\n");
    }
    for (int i = 0; i < num; i++)
    {
        if (strcmp(argv[i], "-p") == 0)
        {
            flag2 = true;
        }
        if (strcmp(argv[i], "-v") == 0)
        {
            flag3 = true;
        }
    }
    if (flag2 == true && flag3 == true)
    {
        printf("Enter right command\n");
        return 0;
    }
    if (flag2 == false && flag3 == false)
    {
        flag1 = true;
    }

    if (flag1 == true)
    {
        for (int i = 1; i < num; i++)
        {
            int check = mkdir(argv[i], 0777);
            if (check != 0)
                printf(" cannot create directory %s: File exists \n", argv[i]);
        }
    }
    if (flag2 == true)
    {
        for (int i = 2; i < num; i++)
        {
            int check = mkdir(argv[i], 0777);
            if (check != 0)
                printf(" cannot create directory %s: File exists \n", argv[i]);
        }
    }
    if (flag3 == 1)
    {
        int check = mkdir(argv[2], 0777);
        if (check != 0)
            printf(" cannot create directory %s: File exists \n", argv[2]);
        printf("mkdir: created directory %s", argv[2]);
        printf("\n");
    }
}