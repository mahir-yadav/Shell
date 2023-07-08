#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include<stdbool.h>
#include <time.h>
extern int errno;
struct tm *timeT;
int main(int num, char *args[])
{
    bool flagu = false;
    bool flagr = false;
    for (int a = 0; a < num; a++)
    {
        if (strcmp(args[a], "-u") == 0)
            flagu = true;
        if (strcmp(args[a], "-R") == 0)
            flagr = true;
    }
    if (num > 2)
        printf("too many arguements\n");
    else
    {
        char buf[500];
        char buf1[500];
        char buf2[500];
        time_t t = time(NULL);
        if (t == -1)
        {
            printf("Error no: %d \n", errno);
            perror("date ");
        }
        timeT = localtime(&t);
        if (timeT == NULL)
        {
            printf("Error no %d \n", errno);
            perror("date");
        }
        if (flagu == true)
        {
            timeT = gmtime(&t);
        }
        if (flagr == true)
            strftime(buf, 500, "%z", timeT);
        else
            strftime(buf, 500, "%Z", timeT);
        strftime(buf1, 500, "%a", timeT);
        strftime(buf2, 500, "%b", timeT);
        if (flagr == true)
            printf("%s, %02d %s %d %02d:%02d:%02d %s \n", buf1, timeT->tm_mday, buf2, timeT->tm_year + 1900, timeT->tm_hour, timeT->tm_min, timeT->tm_sec, buf);
        else if (flagu == true)
            printf("%s %s %02d %02d:%02d:%02d UTC %d \n", buf1, buf2, timeT->tm_mday, timeT->tm_hour, timeT->tm_min, timeT->tm_sec, timeT->tm_year + 1900);
        else
            printf("%s %s %02d %02d:%02d:%02d %s %d \n", buf1, buf2, timeT->tm_mday, timeT->tm_hour, timeT->tm_min, timeT->tm_sec, buf, timeT->tm_year + 1900);
    }
    return 0;
}