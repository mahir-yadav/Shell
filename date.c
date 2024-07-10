#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
extern int getdate_err;
extern int errno;
struct tm *timeT;

int main(int noOfArguements, char *args[])
{
	int flagU = 0, flagR = 0;
    for (int a = 0; a < noOfArguements; a++)
    {
        if (strcmp(args[a], "-u") == 0)
            flagU = 1;
        if (strcmp(args[a], "-R") == 0)
            flagR = 1;
    }
    int temp=flagU+flagR+1;
    if(noOfArguements>temp)
    	printf("too many arguements\n");
    else{
    	char buf[500];
    	char buf1[500];
    	char buf2[500];
    	time_t t= time(NULL);
    	if(t==-1)
    	{
    		printf("Error no: %d \n", errno);
    		perror("date ");
    	}
    	timeT=localtime(&t);
    	if(timeT==NULL)
    	{
    		printf("Error no %d \n",errno );
    		perror("date");
    	}
        if(flagU==1)
        {
        	timeT=gmtime(&t);
        }
        if(flagR==1)
             strftime(buf, 500,"%z",timeT);
        else
            strftime(buf, 500,"%Z",timeT);
			strftime(buf1,500,"%a", timeT);
	        strftime(buf2,500,"%b", timeT);
	        if(flagR==1)
	        	printf("%s, %02d %s %d %02d:%02d:%02d %s \n",buf1,timeT->tm_mday,buf2 ,timeT->tm_year+1900,timeT->tm_hour, timeT->tm_min, timeT->tm_sec, buf);
	        else if(flagU==1)
	        	printf("%s %s %02d %02d:%02d:%02d UTC %d \n",buf1,buf2,timeT->tm_mday ,timeT->tm_hour, timeT->tm_min, timeT->tm_sec, timeT->tm_year+1900);
	        else
	        	printf("%s %s %02d %02d:%02d:%02d %s %d \n",buf1,buf2,timeT->tm_mday ,timeT->tm_hour, timeT->tm_min, timeT->tm_sec,buf, timeT->tm_year+1900);
		    memset(buf, 0, 500);
		    memset(buf1, 0, 500);
		    memset(buf2, 0, 500);
}
    return 0;
}
