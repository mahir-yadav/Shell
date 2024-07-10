#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
extern int errno;
int fd;
struct stat st;

int main(int noOfArguements, char *args[])
{	
	if(noOfArguements==1)
		printf("rm: missing operand \n" );
	else{
		int flagV = 0, flagI = 0;
	    for (int a = 0; a < noOfArguements; a++)
	    {
	        if (strcmp(args[a], "-i") == 0)
	            flagI = 1;
	        if (strcmp(args[a], "-v") == 0)
	            flagV = 1;
	    }
	    int ini=1;
	    while(ini<noOfArguements)
	    {
	    	if (strcmp(args[ini], "-i") == 0 || strcmp(args[ini], "-v") == 0)
	        {
	            ini++;
	            continue;
	        }
	        else if (stat(args[ini], &st) == 0 && S_ISREG(st.st_mode)){
	        	if(flagI==1)
	        	{	char str[20];
	        		printf("rm: remove regular file %s? ",args[ini] );
	        		scanf("%s", str);
		        	if(strcmp(str,"y")==0 || strcmp(str,"Y")==0)
		        	{
		        		if(remove(args[ini])==0)
		        		{
		        			if(flagV==1)
		        				printf("removed %s \n",args[ini] );
		        		}
		        		else
		        		{
		        			printf("Error no %d \n",errno);
		        			perror("rm");
		        		}
		        		int len=strlen(str);

		        		for(int abc=0;abc<len;abc++)
		        			str[abc]='\0';   
					}
				}
				if(flagI==0)
				{
		        	if(remove(args[ini])==0)
		        	{
		        		if(flagV==1)
		        			printf("removed %s \n",args[ini] );
	        		}
	        		else
	        		{
	        			printf("Error no %d \n",errno);
	        			perror("rm");
	        		}
				}
				ini++;
			}
	        else{
	        	printf("cannot remove %s \n",args[ini] );
	        	ini++;
	        	}
	        }
	    }
	return 0;
} 