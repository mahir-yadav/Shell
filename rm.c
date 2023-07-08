#include <stdio.h>
#include <string.h>
#include<stdbool.h>
int main(int argc, char *argv[])
{
    bool flag1 = false;  // for no flag
    bool flag2 = false; // for -i
    bool flag3 = false; // for -d
    if(argc==1){
        printf("No file to remove.\n");
    }
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            flag2 = true;
        }
        if (strcmp(argv[i], "-d") == 0)
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
        for (int i = 1; i < argc; i++)
        {
            int status = remove(argv[i]);
            if (status != 0)
            {
                printf("cannot remove %s: Is a directory\n", argv[i]);
            }
        }
    }
    if (flag2 == true)
    {
        for (int i = 2; i < argc; i++)
        {
            char check;
            printf("rm: remove regular file %s?", argv[i]);
            scanf("%c", &check);
            if (check == 'y')
            {
                int status = remove(argv[i]);
                if (status != 0)
                {
                    printf("cannot remove %s: Is a directory\n", argv[i]);
                }
            }
        }
    }
    if (flag3 == true)
    {
        for (int i = 2; i < argc; i++)
        {
            int status = remove(argv[i]);
            if (status != 0)
            {
                printf("failed to remove 'new': Directory not empty   \n");
            }
        }
    }

    return 0;
}