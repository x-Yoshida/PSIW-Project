#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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
        char name[1024];
        memset(name,0,1024);
        strcpy(name,argv[1]); 
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
                int file = open("config.txt",O_RDONLY);
                for(int n = readLine(file,buf);n>0;n = readLine(file,buf))
                {
                    char senderName[1024];
                    char senderKey[1024];
                    strcpy(senderName,buf);
                    if(!strcmp(substr(senderName,0,strfind(senderName,' ')),name))
                    {
                        continue;
                    }
                    strcpy(senderKey,buf);
                    if(strfind(senderKey,':')==-1)
                    {
                        continue;
                    }
                    substr(senderKey,strfind(senderKey,':')+2,strlen(senderKey));
                    consoleWriteSeperated(' ',3,senderName,senderKey,"\n");
                    sleep(2);
                }
                

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
        //intToStr(buf,key);
        //consoleWriteLine(buf);
    }


    return 0;
}