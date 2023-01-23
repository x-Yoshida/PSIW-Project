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

long strfindLast(char* string,char _c)
{
    long length = strlen(string);
    for(long i=length;i>-1;i--)
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


char*** makeFifoVector(char ***strTab,int *size)
{
    (*size) = 1;
    int i = 0;
    char* tmp = (*strTab)[i++];
    while (tmp)
    {
        if((tmp) && !strcmp(tmp,"|"))
        {
            (*size)++;
            tmp=(*strTab)[i++];
        }
        tmp=(*strTab)[i++];
    }
    //i--;
    i=0;
    tmp = (*strTab)[i];

    char*** fifoVector = (char***)malloc(((*size)+1)*sizeof(char**));
    for(int j=0;j<*size;j++)
    {
        
        int tmpSize = 0;
        int startingIterator=i;
        tmp = (*strTab)[i++];
        if(tmp)
        {
            while(tmp && strcmp(tmp,"|"))
            {
                tmp=(*strTab)[i++];
                tmpSize++;
            }
            fifoVector[j]=(char**)malloc((tmpSize+1)*sizeof(char*));
            for(int k=0;k<tmpSize;k++)
            {
                fifoVector[j][k]=(char*)malloc(1024*sizeof(char));
                memset(fifoVector[j][k],0,1024);
            }
            fifoVector[j][tmpSize]=NULL;
            tmp=(*strTab)[startingIterator++];
            int iterator=0;
            while((tmp) && strcmp(tmp,"|"))
            {
                //printf("%s\n",tmp);
                strcpy(fifoVector[j][iterator++],tmp);
                tmp=(*strTab)[startingIterator++];
            }
            fifoVector[j][iterator]=NULL;
            //printf("i: %d\n",i);
            tmp=(*strTab)[i];
        }

        
    }
    fifoVector[*size] = NULL;
    return fifoVector;
}


char** itemizeString(char* string,int *size)
{
    *size = 1;
    for(int i=0;i<strlen(string);i++)
    {
        if(string[i]==' ')
        {
            (*size)++;
        }
    }
    char** stringsTab = (char**)malloc(((*size)+1)*sizeof(char*));
    for(int i=0;i<*size;i++)
    {
        stringsTab[i] = (char*)malloc(1024*sizeof(char));
        memset(stringsTab[i],0,1024);
    }
    stringsTab[*size]=NULL;
    int i = 0;
    int j=0;
    while (i<strlen(string))
    {
        int k=0;
        while (string[i]!=' ')
        {
            stringsTab[j][k]=string[i];
            i++;
            k++;
        }
        i++;
        j++;
    }
    
    return stringsTab;
}
