#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "stringexpended.h"
#include "iohandling.h"
#include "userhandling.h"

int main(int argc, char** argv)
{

    int key=login(argc,argv);
    /*
    char buf[1024];
    int readCount;
    int plik = open("config.txt",O_RDONLY);
    skipLine(plik);
    readLine(plik,buf);
    consoleWriteLine(buf);
    close(plik);
    */
    if(key)
    {
        int status;
        int child = fork();//Succes -> Parent child = Pid | Child child = 0 # Error Parent child = -1
        if(child<0)
        {
            consoleWriteLine("Failed to create child process");
            exit(1);
        }
        char buf[1024];
        if(child)//Parent
        {
            while(!(waitpid(child,&status,WNOHANG)))
            {


            }
            consoleWriteLine("Parent");
        }
        else//Child
        {
            bool running = true;
            {
                while (running)
                {
                    consoleRead(buf);
                    if(!strcmp(buf,"exit"))
                    {
                        running=false;
                    }
                }
            }
            consoleWriteLine("Child");
        }
        intToStr(buf,key);
        consoleWriteLine(buf);
    }


    return 0;
}