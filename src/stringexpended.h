#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Finds index of first appearance of character
* string - string in which we are looking for character
* _c - character to be found
*/
long strfind(char* string,char _c);


long strfindLast(char* string,char _c);

/*
* Makes substring of _Src by replacing it
* and returns substring
* 
*/
char* substr(char* _Src ,int start, int finish);

char* revstr(char* _Dst);

char* intToStr(char* _Dst,int num);

char** itemizeString(char* string,int *size);

char*** makeFifoVector(char ***strTab,int *size);

