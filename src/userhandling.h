#pragma once
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "iohandling.h"

typedef struct BufElement
{
    long mtype;
    char message[1024];
} BufElement;

int findKey(char* usrName);
int login(int argc,char** argv);
int msgInit(int key);
void msgClose(int msgid);
void sendMsg(int msgid, BufElement *buf);
void reciveMsg(int key,BufElement *buf);

