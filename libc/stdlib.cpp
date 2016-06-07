#include <stdlib.h>
#include <string.h>
#include <types.h>


char * itoa (int32_t value, char* buffer, int base)
{
	int32_t valueBackup = value;	
 	int16_t index = 0;
    
    if (value < 0)
    	value = -value;
 
    do 
    {
        buffer[index++] = value % 10 + '0'; // '0' + digit = '>>this digit<<'; 
        value /= 10; // value is integer, so we can remove digits by dividing by 10
    } while (value > 0); 
    
    if (valueBackup < 0)
        buffer[index++] = '-';

    buffer[index] = '\0';

    reverseString(buffer);
    return buffer;
}