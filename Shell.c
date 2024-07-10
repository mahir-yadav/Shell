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
char *line;
char **args;
int noOfArguements;
size_t inputSize = 1000;
const char *Delimiter = " \t\r\n\a";
char **history;
int total_count;
int fd;
struct stat st;
char *SHELL_PATH;
char *pathCOLOR;
char *HISTORY_PATH;

void cd()
{
	int flagP = 0;
	int flagE = 0;
	int position = 0;
	for (int a = 0; a < noOfArguements; a++)
	{
		if (strcmp(args[a], "-P") == 0)
			flagP = 1;
		else if (strcmp(args[a], "-e") == 0)
			flagE = 1;
	}
	if (flagE + flagP + 2 < noOfArguements)
		printf("cd: Too many arguments\n");
	else if (flagE + flagP + 1 == noOfArguements)
	{
		char tmp[1024];
		if (flagE && getcwd(tmp, sizeof(tmp)) == NULL)
		{
			printf("Error no: %d", errno);
			perror("cd");
			return;
		}
		int status = chdir(SHELL_PATH);
		if (status == -1)
			perror("cd");
	}
	else
	{
		for (int a = 1; a < noOfArguements; a++)
		{
			if (strcmp(args[a], "-P") == 0 || strcmp(args[a], "-e") == 0)
				continue;
			if (args[a][0] == '~')
			{
				char temp10[1000];
				strcpy(temp10, SHELL_PATH);
				strcat(temp10, args[a] + 1);
				int status = chdir(temp10);
				if (status == -1)
					perror("cd ");
				return;
			}
			char tmp[1024];
			if (flagE && getcwd(tmp, sizeof(tmp)) == NULL)
			{
				printf("Error no: %d", errno);
				perror("cd");
				return;
			}
			int status = chdir(args[a]);
			if (status == -1)
				perror("cd");
		}
	}
}


void echo_checkbackslash(char *dest, char *argument)
{
	if (argument[0] == '\\')
	{
		if (argument[1] == 'a')
			strcat(dest, "\a");
		else if (argument[1] == 'b')
			strcat(dest, "\b");
		else if (argument[1] == '0')
			strcat(dest, "\0");
		else if (argument[1] == 'e')
			strcat(dest, "\e");
		else if (argument[1] == 'f')
			strcat(dest, "\f");
		else if (argument[1] == 'n')
			strcat(dest, "\n");
		else if (argument[1] == 'r')
			strcat(dest, "\r");
		else if (argument[1] == 't')
			strcat(dest, "\t");
		else if (argument[1] == 'v')
			strcat(dest, "\v");
		else if (argument[1] == '\\')
			strcat(dest, "\\");
		else if (argument[1] == '\"')
			strcat(dest, "\"");
		else if (argument[1] == '\'')
			strcat(dest, "\'");
		else if (argument[1] == '\?')
			strcat(dest, "\?");
		else
		{
			strcat(dest, argument);
			strcat(dest, " ");
		}
	}
	else
	{
		strcat(dest, argument);
		strcat(dest, " ");
	}
}

void echo()
{
	int statusEcho=0;
	if (noOfArguements == 1)
	{
		statusEcho=printf("\n");
		if(statusEcho==-1)
			perror("echo");
	}
	else
	{
		int isdashN = 0, isdashE = 0, st = 1;
		for (int a = 0; a < noOfArguements; a++)
		{
			if (strcmp(args[a], "-e") == 0)
				isdashE = 1, st++;
			if (strcmp(args[a], "-n") == 0)
				isdashN = 1, st++;
		}
		char dest[250];
		strcpy(dest, "");
		int start = isdashE + isdashN + 1;
		for (int i = start; i < noOfArguements; i++)
		{
			if (i == start && args[i][0] == '"')
			{
				args[i] = args[i] + 1;
				if (args[i][(strlen(args[i])) - 1] == '"')
					args[i][(strlen(args[i])) - 1] = '\0';
				if (isdashE == 1)
				{
					echo_checkbackslash(dest, args[i]);
					strcat(dest, " ");
				}
				else
				{
					strcat(dest, args[i]);
					strcat(dest, " ");
				}
			}
			else if (i == (noOfArguements - 1) && args[i][(strlen(args[i])) - 1] == '"')
			{
				args[i][(strlen(args[i])) - 1] = '\0';
				if (isdashE == 1)
				{
					echo_checkbackslash(dest, args[i]);
					strcat(dest, " ");
				}
				else
				{
					strcat(dest, args[i]);
					strcat(dest, " ");
				}
			}
			else
			{
				if (isdashE == 1)
				{
					echo_checkbackslash(dest, args[i]);
					strcat(dest, " ");
				}
				else
				{
					strcat(dest, args[i]);
					strcat(dest, " ");
				}
			}
		}
		if (isdashN == 1)
		{	statusEcho=printf("%s", dest);
			if(statusEcho==-1)
				perror("echo");
		}
		else{
			statusEcho=printf("%s \n", dest);
			if(statusEcho==-1)
				perror("echo");
		}
	}
}

void viewHistory()
{
	int fd3 = open(HISTORY_PATH, O_RDWR, 0);
	if(fd3==-1)
		perror("history");
	if (noOfArguements >= 2 && strcmp(args[1], "-c") == 0)
	{
		if(close(fd)<0)
			perror("history");
		fd = open(HISTORY_PATH, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, S_IRWXO | S_IRWXG | S_IRWXU);
		if(fd==-1)
			perror("history");
	}
	else if (noOfArguements >= 2 && strcmp(args[1], "-d") == 0)
	{
		int offset = atoi(args[2]);
		if (offset > total_count)
			printf("%s\n", "history position out of range");
		else
		{
			char lineTemp2[1000];
			int temp;
			int temp5 = 0;
			int idx = 0;
			while (temp5 < (offset - 1))
			{
				idx = 0;
				while ((temp = read(fd3, &lineTemp2[idx], sizeof(char))) > 0)
				{
					if(temp==-1)
						perror("history");
					if (lineTemp2[idx] == '\n')
						break;
					idx++;
				}
				temp5++;
				int len = strlen(lineTemp2);
				for (int a = 0; a < len; a++)
					lineTemp2[a] = '\0';
			}
			idx = 0;
			while ((temp5 = read(fd3, &lineTemp2[idx], sizeof(char))) > 0)
			{
				lseek(fd3, -1, SEEK_CUR);
				int statustemp=write(fd3, "\b", sizeof(char) * strlen("\b"));
				if(statustemp==-1)
					perror("history");
				if (lineTemp2[idx] == '\n' || lineTemp2[idx] == '\0')
					break;
			}
		}
	}
	else
	{
		if (noOfArguements > 2)
			printf("%s\n", "too many arguements");
		else
		{
			int value = total_count;
			if (noOfArguements == 2)
				value = atoi(args[1]);
			int temp = 0;
			if (value < 0)
				printf("%s\n", "invalid option");
			else
			{
				int idx = 0;
				int initial = 1;
				int count = 1;
				while (initial < (total_count - value + 1))
				{
					char lineTemp2[350] = {'\0'};
					int temp;
					idx = 0;
					char checkBackspace;
					while ((temp = read(fd3, &checkBackspace, sizeof(char))) > 0)
					{
						if(temp==-1)
							perror("history");
						if (checkBackspace != '\b')
							lineTemp2[idx] = checkBackspace;
						else
							continue;
						if (lineTemp2[idx] == '\n')
							break;
						idx++;
					}
					initial++;
					count++;
				}
				while (1)
				{
					char lineTemp2[350] = {'\0'};
					int temp;
					idx = 0;
					char checkBackspace;
					while ((temp = read(fd3, &checkBackspace, sizeof(char))) > 0)
					{
						if(temp==-1)
							perror("history");
						if (checkBackspace != '\b')
							lineTemp2[idx] = checkBackspace;
						else
							continue;
						if (lineTemp2[idx] == '\n')
							break;
						idx++;
					}
					if (temp <= 0)
						break;
					printf("%d %s", count, lineTemp2);
					count++;
				}
			}
		}
	}
	if(close(fd3)<0)
		perror("history");
}

void pwd()
{
	if (noOfArguements == 1)
	{
		char tmp[1000];
		if (getcwd(tmp, sizeof(tmp)) == NULL)
		{
			printf("Error no : %d\n", errno);
			perror("pwd ");
		}
		else{
			printf("%s\n",tmp );
		}

	}
	else
	{
		if (strcmp(args[1], "-L") == 0)
		{
			if (getenv("PWD") == NULL)
				perror("pwd");
			else
				printf("%s\n", getenv("PWD"));
		}
		else
		{
			if (strcmp(args[1], "-P")==0 && noOfArguements > 2)
				printf("%s\n", "too many arguements");
			else
			{
				char tmp2[1000];
				if (getcwd(tmp2, sizeof(tmp2)) == NULL)
				{	printf("Error no : %d\n", errno);
					perror("pwd");
				}
				else{
					printf("%s\n", tmp2);
				}
			}
		}
	}
}

void callExit()
{
	exit(0);
}

int main()
{
	args = (char **)malloc(sizeof(char *) * inputSize);
	HISTORY_PATH= (char *)malloc(sizeof(char)*1000);
	char pathS[1000];
	SHELL_PATH = getcwd(pathS, 1000);
	strcpy(HISTORY_PATH,SHELL_PATH);
	strcat(HISTORY_PATH,"/history.txt");
	fd = open(HISTORY_PATH, O_RDWR | O_CREAT | O_APPEND, S_IRWXO | S_IRWXG | S_IRWXU);
	if (fd == -1)
	{
		printf("Error no %d\n", errno);
		perror("open ");
	}
    printf("\n\t======================================================\n");
    printf("\t              Welcome to Mahir's shell\n");
    printf("\t========================================================\n\n");
	while (1)
	{  	char pathColor[1000];
		pathCOLOR= getcwd(pathColor, 1000);
		printf("\033[1;32mShell\033[1;34m%s> \033[0m",pathCOLOR);
		getline(&line, &inputSize, stdin);
		if(strlen(line)==1)
			continue;
		int temp102=write(fd, line, strlen(line));
		if(temp102==-1)
			perror("write");
		char *temp = strtok(line, Delimiter);
		noOfArguements = 0;
		while (temp != NULL)
		{
			args[noOfArguements] = temp;
			noOfArguements++;
			temp = strtok(NULL, Delimiter);
		}
		args[noOfArguements] = NULL;
		if (strcmp(args[0], "cd") == 0)
			cd();
		else if (strcmp(args[0], "echo") == 0)
			echo();
		else if (strcmp(args[0], "history") == 0)
		{
			int fd2 = open(HISTORY_PATH, O_RDONLY, 0);
			if(fd2==-1)
				perror("history");
			total_count = 0;
			char lineTemp[300];
			int idx = 0;
			while (1)
			{
				int temp;
				idx = 0;
				while ((temp = read(fd2, &lineTemp[idx], sizeof(char))) > 0)
				{
					if(temp==-1)
						perror("history");
					if (lineTemp[idx] == '\n')
						break;
					idx++;
				}

				if (temp <= 0)
					break;
				total_count++;
				int len = strlen(lineTemp);
				for (int a = 0; a < len; a++)
					lineTemp[a] = '\0';
			}
			if(close(fd2)==-1)
				perror("history");
			viewHistory();
		}
		else if (strcmp(args[0], "pwd") == 0)
			pwd();
		else if (strcmp(args[0], "exit") == 0)
		{
			if (close(fd) < 0)
				perror("exit ");
			callExit();
		}
		else
		{
			pid_t pid = fork();
			if (pid < 0)
				printf("Could not create a child process\n");
			else if (pid == 0)
			{
				char tmp[1024];
				strcpy(tmp, SHELL_PATH);
				if (strcmp(args[0], "ls") == 0)
					strcat(tmp, "/ls");
				else if (strcmp(args[0], "cat") == 0)
					strcat(tmp, "/cat");
				else if (strcmp(args[0], "date") == 0)
					strcat(tmp, "/date");
				else if (strcmp(args[0], "rm") == 0)
					strcat(tmp, "/rm");
				else if (strcmp(args[0], "mkdir") == 0)
					strcat(tmp, "/mkdir");
				else
				{
					printf("Command not found\n");
					callExit();
				}
				if (execv(tmp, args) < 0)
					perror("execv");
				callExit();
			}
			else if (pid > 0)
			{
				pid_t pTEMP=waitpid(pid, NULL, WUNTRACED);
				if(pTEMP<0)
				{
					printf("Error no %d\n", errno);
					perror("waitpid");
				}
			}

		}
	}
	return 0;
}
