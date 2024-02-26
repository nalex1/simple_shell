#include "shell.h"

/**
 * expand_vars - It Expand variables.
 * @data: A pointer to a structure of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_vars(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_addition(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_addition(line, expansion);
			buffer_addition(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_addition(line, expansion);
			buffer_addition(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = env_get_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			buffer_addition(expansion, line + i + j);
			temp ? buffer_addition(line, temp) : 1;
			buffer_addition(line, expansion);
		}
	if (!_strcmp(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = _strdup(line);
	}
}

/**
 * expand_alias - It Expands aliases.
 * @data: A pointer to a structure of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(data_of_program *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_addition(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_addition(expansion, line + i + j);
			line[i] = '\0';
			buffer_addition(line, temp);
			line[_strlen(line)] = '\0';
			buffer_addition(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = _strdup(line);
	}
}

/**
 * buffer_addition - This append string at end of the buffer.
 * @buffer: This is a buffer.
 * @str_to_add: A string to be copied in the buffer.
 * Return: nothing, but sets errno.
 */
int buffer_addition(char *buffer, char *str_to_add)
{
	int length, i;

	length = _strlen(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
