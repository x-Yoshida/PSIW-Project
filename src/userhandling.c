#include "userhandling.h"

int login(int argc,char** argv)
{
    if(argc<2)
    {
        consoleWriteLine("Please enter username");
        consoleWriteLine("./projekt username");
    }
    int file = open("config.txt",O_RDONLY);
    char buf[1024];
    for(int n=readWord(file,buf,' ');n>0;n=readWord(file,buf,' '))
    {
        consoleWriteLine(buf);
        if(!strcmp(buf,argv[1]))
        {
            consoleWriteLine("Yes");
            readWord(file,buf,' ');
            readWord(file,buf,' ');
            close(file);
            return atoi(buf);   
        }
        skipLine(file);
    }
    consoleWriteLine("Bruh");
    close(file);
    return 0;
}