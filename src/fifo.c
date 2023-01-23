#include "fifo.h"

void makeFifo(char* name)
{
    char location[1024]="/tmp/";
    strcat(location,name);
    mkfifo(location,0666);    
}

void runCommand(char*cmd,char* name)
{
    char location[1024]="/tmp/";
    strcat(location,name);
    int size=0;
    char** cmdVec = itemizeString(cmd,&size);
    if(!fork())
    {
        int fd=open(location,O_WRONLY);
        dup2(fd,1);
        execvp(cmdVec[0],cmdVec);
    }

}
void recivefromFifo(char* name)
{
    char location[1024]="/tmp/";
    strcat(location,name);
    int fd = open(location,O_RDONLY);
    int n = 0;
    char buf[1024];
    n=read(fd,buf,1024);
    while(n>0)
    {
        write(1,buf,n);
        n=read(fd,buf,1024);
    }
    close(fd);
    unlink(location);
}