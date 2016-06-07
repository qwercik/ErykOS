#ifndef STRING_H
#define STRING_H

#include <types.h>

uint16_t strlen(const string str);
int8_t strcmp(const string str1, const string str2);
string reverseString(string str);

#endif