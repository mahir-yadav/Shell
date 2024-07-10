#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
extern int errno;
int main(int noOfArguements, char *args[])
{
	int flaga = 0;
	int flagA = 0;
	DIR *dir;
	for (int a = 0; a < noOfArguements; a++)
	{
		if (strcmp(args[a], "-A") == 0)
			flagA = 1;
		if (strcmp(args[a], "-a") == 0)
			flaga = 1;
	}
	if (flaga + flagA + 1 == noOfArguements)
	{
		args[1] = (char *)malloc(2 * sizeof(char));
		args[1][0] = '.';
		args[1][1] = '\0';
	}
	if (noOfArguements == 1)
		noOfArguements = 2;
	for (int a = 1; a < noOfArguements; a++)
	{
		if (strcmp(args[a], "-A") == 0 || strcmp(args[a], "-a") == 0)
			continue;
		dir = opendir(args[a]);
		if (dir == NULL)
		{
			printf("Error no %d\n",errno );
			perror("ls");
			return 0;
		}
		struct dirent *fileHere;
		fileHere = readdir(dir);
		if (fileHere == NULL)
			perror("ls");
		if (flagA + flaga + 2 != noOfArguements)
			printf("%s : \n ", args[a]);
		while (fileHere != NULL)
		{
			char tmp[1024];
			if (fileHere->d_name[0] == '.')
			{
				if (flaga)
					printf("%s ", fileHere->d_name);
				else if (flagA && strcmp(fileHere->d_name, ".") && strcmp(fileHere->d_name, ".."))
					printf("%s ", fileHere->d_name);
			}
			else
				printf("%s ", fileHere->d_name);
			fileHere = readdir(dir);
		}
		printf("\n");
	}
	return 0;
}