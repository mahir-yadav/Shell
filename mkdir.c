#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
extern int errno;
char *temp;
char inicwd[1024];
char* iniCD;

void implementP(int flagV)
{	iniCD=(char *)malloc(sizeof(char)*1024);
    const char del[2] = "/";
    char *token;
    token = strtok(temp, del);
    strcpy(iniCD,"");
    strcat(iniCD,token);
    while (token != NULL)
    {
        int status = mkdir(token, 0777);
        if (status == -1)
           { printf("Error no %d\n", errno);
            perror("mkdir ");}
        else
        {
    	    if(flagV==1)
    	        printf("created directory '%s'\n",iniCD );
            int status = chdir(token);
            if (status == -1)
                perror("mkdir ");
        }
        strcat(iniCD,"/");
        token = strtok(NULL, del);
        strcat(iniCD,token);
    }
    chdir(inicwd);
    return;
}

int main(int noOfArguements, char *args[])
{
    getcwd(inicwd, sizeof(inicwd));
    int flagV = 0;
    int flagP = 0;
    int ini = 1;
    for (int a = 1; a < noOfArguements; a++)
    {
        if (strcmp(args[a], "-p") == 0)
            flagP = 1;
        if (strcmp(args[a], "-v") == 0)
            flagV = 1;
    }
    int temp5 = 1 + flagV + flagP;
    if (noOfArguements == temp5)
        printf("missing operand\n");
    while (ini < noOfArguements)
    {
        if (strcmp(args[ini], "-p") == 0 || strcmp(args[ini], "-v") == 0)
        {
            ini++;
            continue;
        }
        else if (flagP == 0)
        {
            int status = mkdir(args[ini], 0777);
            if (status == -1)
            {
                printf("Error no %d\n",errno );
                perror("mkdir ");}
            if (flagV)
                printf("created directory '%s'\n", args[ini]);
            ini++;
        }
        else
        {
            temp = args[ini];
            implementP(flagV);
            int len = strlen(temp);
            for (int abc = 0; abc < len; abc++)
                temp[abc] = '\0';
            ini++;
        }
    }
    return 0;
}