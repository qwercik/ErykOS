#include <string.h>
#include <types.h>

uint16_t strlen (const string str)
{
	int length = 0;
	while (str[length++] != '\0');
	return --length;
}

int8_t strcmp (const string str1, const string str2)
{
	int i = 0;

	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return str1[i] < str2[i] ? -1 : 1;

		i++;
	}

	return 0;
}

string reverseString(string str)
{
	int i, j;
    char tempCharacter;
 
    for (i = 0, j = strlen(str)-1; i<j; i++, j--) {
        tempCharacter = str[i];
        str[i] = str[j];
        str[j] = tempCharacter;
    }
}