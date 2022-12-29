#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "stringexpended.h"

int consoleRead(char *_DstBuf);
int readLine(int _FileHandle,char *_DstBuf);
int readWord(int _FileHandle,char *_DstBuf,char separator);
void skipLine(int _FileHandle);
void consoleWrite(char* _Buf);
void consoleWriteSeperated(char separator,int num,...);
void consoleWriteLine(char* _Buf);
