#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <fcntl.h>
#include "stringexpended.h"

void makeFifo(char* name);
void runCommand(char*cmd,char* name);
void recivefromFifo(char* name);
