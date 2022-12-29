#include "stringexpended.h"

long strfind(char* string,char _c)
{
    long length = strlen(string)+1;
    for(long i=0;i<length;i++)
    {
        if(string[i]==_c)
        {
            return i;
        }
    }
    return -1;
}


char* substr(char* _Src,int start, int finish)
{
    if(finish>strlen(_Src))
    {
        return _Src;
    }
    char* _Dst=(char*)malloc(strlen(_Src)+1);
    int j=0;
    for(int i=start;i<finish;i++)
    {
        _Dst[j++]=_Src[i];
    }
    _Dst[j]='\0';
    strcpy(_Src,_Dst);
    free(_Dst);
    return _Src;
}

char* revstr(char* _Dst)
{
    int size=strlen(_Dst);
    int hsize=size/2;
    size--;
    for(int i=0;i<hsize;i++)
    {
        char tmp = _Dst[i];
        _Dst[i] =_Dst[size-i];
        _Dst[size-i] = tmp;
    }
    return _Dst;
}

char* intToStr(char* _Dst,int num)
{
    memset(_Dst,0,1024);
    for(num;num>0;num/=10)
    {
        char currentNum = '0' + num%10;
        strcat(_Dst,&currentNum);
    }
    revstr(_Dst);
    return _Dst;
}