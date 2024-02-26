#include "shell.h"

/**
 * _print - Display an array of chars to the STDOUT
 * @string: a pointer to the array of chars
 * Return: the number of bytes displayed.
 * On error, -1 is returned and errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, _strlen(string)));
}
/**
 * _printe - Display an array of chars to the STDERR
 * @string: A pointer to the array of chars
 * Return: the number of bytes displayed.
 * On error, -1 is returned and errno is set appropriately.
 */
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, _strlen(string)));
}

/**
 * _print_error - Display an array of chars to the STDERR
 * @data: a pointer to program's data
 * @errorcode: an error code to be printed
 * Return: the number of bytes displayed.
 * On error, -1 is returned and errno is set appropriately.
 */
int _print_error(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->tokens[0]);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
