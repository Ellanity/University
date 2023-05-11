#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
  
//// gettimestart
// https://stackoverflow.com/questions/3756323/how-to-get-the-current-time-in-milliseconds-from-c-in-linux
#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


/*struct tm {
    int tm_sec;   // seconds of minutes from 0 to 61
    int tm_min;   // minutes of hour from 0 to 59
    int tm_hour;  // hours of day from 0 to 24
    int tm_mday;  // day of month from 1 to 31
    int tm_mon;   // month of year from 0 to 11
    int tm_year;  // year since 1900
    int tm_wday;  // days since sunday
    int tm_yday;  // days since January 1st
    int tm_isdst; // hours of daylight savings time
}*/

void print_current_time_with_ms (void)
{	
    struct tm *ltm;
    time_t now = time(NULL);
    ltm = localtime(&now);
    
    time_t          s;  // Seconds
    long            ms; // Milliseconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    if (ms > 999) {
        s++;
        ms = 0;
    }
    printf("time: H:%d M:%d S:%d MS:%03ld\n", ltm->tm_hour, ltm->tm_min, ltm->tm_sec, ms);
}
//// gettimeend 


//// mainfuncstart
// https://acm.bsu.by/wiki/Unix2017b/%D0%A2%D0%B5%D1%85%D0%BD%D0%B8%D0%BA%D0%B0_fork_%E2%80%94_exec
int main() 
{
    int status;
    pid_t pid0, pid1;
    
    // first child start
    pid0 = fork();
    if (pid0 == -1) 
        fprintf(stderr, "Unable to fork\n");
        
    else if (pid0 > 0) 
    {
        printf("I am parent %d\n", getpid());
        printf("Child is %d\n", pid0);
        //wait(&status);
        //waitpid(pid0, &status, 0);
        //printf("Wait OK\n");
        
        // second child start
        pid_t pid1 = fork();
        if (pid1 == -1) 
            fprintf(stderr, "Unable to fork\n");
        
        else if (pid1 > 0) 
        {
            printf("I am parent %d\n", getpid());
            printf("Child is %d\n", pid1);
            // wait(&status);
            //waitpid(pid1, &status, 0);
            //printf("Wait OK\n");
            system("ps -x");
        } 
        else 
        {
            // second child end  
            printf("I am child %d of %d\n", getpid(), getppid());
            print_current_time_with_ms();
            /*if (execlp("ps", "ps", "-x", NULL) == -1) 
            {
                fprintf(stderr, "Unable to exec\n");
            }*/
        }
        
    } 
    else 
    {
        // first child end   
        printf("I am child %d of %d\n", getpid(), getppid());
        print_current_time_with_ms();
        /*if (execlp("ls", "ls", "-l", NULL) == -1) 
        {
            fprintf(stderr, "Unable to exec\n");
        }*/
    }
}
//// mainfuncend

// to compile with gcc add -lm in the end of request. example: gcc main.c -o main.exe -lm