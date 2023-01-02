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
            while(!(waitpid(child,&status,WNOHANG)))
            {
                char tmpBuf[1024];
                int file = open("config.txt",O_RDONLY);
                for(int n = readLine(file,tmpBuf);n>0;n = readLine(file,tmpBuf))
                {
                    char senderName[1024];
                    char senderKey[1024];
                    strcpy(senderName,tmpBuf);
                    if(!strcmp(substr(senderName,0,strfind(senderName,' ')),name))
                    {
                        continue;
                    }
                    strcpy(senderKey,tmpBuf);
                    if(strfind(senderKey,':')==-1)
                    {
                        continue;
                    }
                    substr(senderKey,strfind(senderKey,':')+2,strlen(senderKey));
                    //consoleWriteSeperated(' ',3,senderName,senderKey,"\n");
                    reciveMsg(atoi(senderKey),&buffer);
                    //consoleWriteLine("OwO");
                    if(buffer.mtype==1)
                    {
                        consoleWriteLine(buffer.message);
                        buffer.mtype=0;
                    }
                    sleep(5);
                }
                close(file);

            }
            consoleWriteLine("Parent");
        }
        else//Child
        {
            char consoleBuf[1024];
            bool running = true;
            int msgid = msgInit(key);
            {
                while (running)
                {
                    consoleRead(consoleBuf);
                    if(!strcmp(consoleBuf,"exit"))
                    {
                        running=false;
                    }
                    else
                    {
                        char buf[1024];
                        strcpy(buf,consoleBuf);
                        char reciverName[1024];
                        strcpy(reciverName,substr(buf,0,strfind(buf,' ')));
                        if(!strcmp(substr(reciverName,0,strfind(reciverName,' ')),name))
                        {

                        }
                        else
                        {
                            int file = open("config.txt",O_RDONLY);
                            for(int n = readLine(file,buf);n>0;n = readLine(file,buf))
                            {
                                char tmpReciverName[1024];
                                char reciverKey[1024];
                                strcpy(tmpReciverName,buf);
                                if(strcmp(substr(tmpReciverName,0,strfind(tmpReciverName,' ')),reciverName))
                                {
                                    continue;
                                }
                                strcpy(reciverKey,buf);
                                if(strfind(reciverKey,':')==-1)
                                {
                                    continue;
                                }
                                substr(reciverKey,strfind(reciverKey,':')+2,strlen(reciverKey));
                                consoleWriteSeperated(' ',3,reciverName,reciverKey,"\n");
                                strcpy(buffer.message,consoleBuf);
                                sendMsg(msgid,atoi(reciverKey),&buffer);
                                //reciveMsg(atoi(reciverKey),&buffer);
                                //if(buffer.mtype==1)
                                //{
                                //    consoleWriteLine(buffer.message);
                                //    buffer.mtype=0;
                                //}
                            }
                            close(file);
                        }
                    }
                }
            }
            msgctl(msgid,IPC_RMID,NULL);
            consoleWriteLine("Child");
        }
        //intToStr(buf,key);
        //consoleWriteLine(buf);
    }


    return 0;
}