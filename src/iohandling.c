#include "iohandling.h"

int consoleRead(char *_DstBuf)
{
    read(0,_DstBuf,1024);
    _DstBuf[strfind(_DstBuf,'\n')]='\0';
    return strlen(_DstBuf);
}

int readLine(int _FileHandle,char *_DstBuf)
{
    char buf[1024];
    memset(buf,0,1024);
    int readCount = read(_FileHandle,buf,1024);
    if(readCount == 0)
    {
        return 0;
    }
    int newLineIndex = strfind(buf,'\n');
    int endStringIndex = strfind(buf,'\0');
    if(endStringIndex>-1)
    {
        if((newLineIndex>endStringIndex)||newLineIndex<0)
        {
            newLineIndex=endStringIndex;
        }
    }
    lseek(_FileHandle,newLineIndex-readCount+1,SEEK_CUR);
    strcpy(_DstBuf,substr(buf,0,newLineIndex));
    return newLineIndex;
}

int readWord(int _FileHandle,char *_DstBuf,char separator)
{
    char buf[1024];
    memset(buf,0,1024); 
    int readCount = read(_FileHandle,buf,1024);
    if(readCount == 0)
    {
        return 0;
    }
    int separatorIndex = strfind(buf,separator);
    int newLineIndex = strfind(buf,'\n');
    int endStringIndex = strfind(buf,'\0');
    if(newLineIndex>-1)
    {
        if((separatorIndex>newLineIndex)||separatorIndex<0)
        {
            separatorIndex=newLineIndex;
        }
    }
    if(endStringIndex>-1)
    {
        if((separatorIndex>endStringIndex)||separatorIndex<0)
        {
            separatorIndex=endStringIndex;
        }
    }
    lseek(_FileHandle,separatorIndex-readCount+1,SEEK_CUR);
    strcpy(_DstBuf,substr(buf,0,separatorIndex));
    return separatorIndex;
}

void skipLine(int _FileHandle)
{    
    char buf[1024];
    memset(buf,0,1024);
    int readCount = read(_FileHandle,buf,1024);
    int newLineIndex = strfind(buf,'\n');   
    int endStringIndex = strfind(buf,'\0');
    if(endStringIndex>-1)
    {
        if((newLineIndex>endStringIndex)||newLineIndex<0)
        {
            newLineIndex=endStringIndex;
        }
    }
    lseek(_FileHandle,newLineIndex-readCount+1,SEEK_CUR);

}

void consoleWrite(char* _Buf)
{
    write(1,_Buf,strlen(_Buf));
}

void consoleWriteLine(char* _Buf)
{
    write(1,_Buf,strlen(_Buf));
    write(1,"\n",1);
}

