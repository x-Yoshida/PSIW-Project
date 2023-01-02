#include "userhandling.h"

int login(int argc,char** argv)
{
    if(argc<2)
    {
        consoleWriteLine("Please enter username");
        consoleWriteLine("./projekt username");
        exit(1);
    }
    int file = open("config.txt",O_RDONLY);
    char buf[1024];
    for(int n=readWord(file,buf,' ');n>0;n=readWord(file,buf,' '))
    {
        //consoleWriteLine(buf);
        if(!strcmp(buf,argv[1]))
        {
            //consoleWriteLine("Yes");
            readWord(file,buf,' ');
            readWord(file,buf,' ');
            close(file);
            return atoi(buf);   
        }
        skipLine(file);
    }
    //consoleWriteLine("Bruh");
    close(file);
    return 0;
}


int msgInit(int key)
{
    int msgid = msgget(key,IPC_CREAT | IPC_EXCL | 0666);
    if(msgid == -1)
    {
        //perror("Queue error");
        msgid = msgget(key,IPC_CREAT | 0666);
        if(msgid == -1)
        {
            //perror("Queue error");
            exit(1);
        }
    }
    return msgid;
}

void sendMsg(int msgid,int key, BufElement *buf)
{
    buf->mtype=1;
    msgsnd(msgid,buf,sizeof(*buf),0);
}

void reciveMsg(int key,BufElement *buf)
{
    int msgid = msgget(key,IPC_CREAT | IPC_EXCL | 0666);
    if(msgid == -1)
    {
        //perror("Queue error");
        msgid = msgget(key,IPC_CREAT | 0666);
    }
    int rcv = msgrcv(msgid,buf,sizeof(*buf),1,IPC_NOWAIT);
    if(rcv<1)
    {
        buf->mtype=0;
    }
    else
    {
        buf->mtype=1;
    }
}