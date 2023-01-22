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
    
    if(key)
    {
        char name[1024];
        memset(name,0,1024);
        strcpy(name,argv[1]); 
        int status;
        int child = fork();//Succes -> Parent child = Pid | Child child = 0 # Error Parent child = -1
        BufElement buffer;
        buffer.mtype=0;
        memset(buffer.message,0,1024);
        if(child<0)
        {
            consoleWriteLine("Failed to create child process");
            exit(1);
        }
        if(child)//Parent
        {
            int msgid;
            while(!(waitpid(child,&status,WNOHANG)))
            {
                msgid = msgInit(key);
            
                reciveMsg(msgid,&buffer);
                //perror("???");
                if(buffer.mtype==1)
                {
                    consoleWriteLine(buffer.message);
                    buffer.mtype=0;
                }
                msgClose(msgid);
                sleep(3);

            }
            consoleWriteLine("Parent");
        }
        else//Child
        {
            char consoleBuf[1024];
            bool running = true;
            while (running)
            {
                consoleRead(consoleBuf);
                if(!strcmp(consoleBuf,"exit"))
                {
                    running=false;
                }
                else
                {
                    int reciverKey=0;
                    char tmpBuf[1024];
                    strcpy(tmpBuf,consoleBuf);
                    substr(tmpBuf,0,strfind(tmpBuf,' '));
                    reciverKey=findKey(tmpBuf);
                    if(reciverKey)
                    {
                        int msgid = msgInit(reciverKey);
                        strcpy(buffer.message,consoleBuf);
                        sendMsg(msgid,&buffer);

                        //msgClose(msgid);
                    }
                    
                    
                }
            
            }
            int msgid = msgInit(key);
            msgClose(msgid);
            consoleWriteLine("Child");
        }
        //intToStr(buf,key);
        //consoleWriteLine(buf);
    }


    return 0;
}