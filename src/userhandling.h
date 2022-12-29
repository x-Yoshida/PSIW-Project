#pragma once
#include <fcntl.h>
#include "iohandling.h"

typedef struct BufElement
{
    int mtype;
    char message[1024];
}

int login(int argc,char** argv);

