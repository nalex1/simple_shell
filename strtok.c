#include "shell.h"
/**
 * _strtok - Tokenize string on delims.
 * @line: A pointer to _getline array.
 * @delim: delimiters.
 * Return: A pointer to the tokenized strings.
*/
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *_cpystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			break;
		}
		if (delim[j] == '\0')
			break;
	}
	_cpystr = str;
	if (*_cpystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (_cpystr);
			}
		}
	}
	return (_cpystr);
}
