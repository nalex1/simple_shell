#include "shell.h"
/**
* builtin_env - Displays the environment in which the shell is running.
* @data: A structure containing program data.
* Return: Zero on success, or a non-zero value if specified in the arguments.
*/
int builtin_env(data_of_program *data)
{
int i;
char cpname[50] = {'\0'};
char *var_cpy = NULL;
/* if not arguments */
if (data->tokens[1] == NULL)
print_environ(data);
else
{
for (i = 0; data->tokens[1][i]; i++)
{/* checks if exists a char = */
if (data->tokens[1][i] == '=')
{/* checks if exists a var with the same name and change its
value*/
/* temporally */
var_cpy = _strdup(env_get_key(cpname, data));
if (var_cpy != NULL)
env_set_key(cpname, data->tokens[1] + i + 1, data);
/* print the environ */
print_environ(data);
if (env_get_key(cpname, data) == NULL)
{/* print the variable if it does not exist in the environ */
_print(data->tokens[1]);
_print("\n");
}
else
{/* returns the old value of the var*/
env_set_key(cpname, var_cpy, data);
free(var_cpy);
}
return (0);
}
cpname[i] = data->tokens[1][i];
}
errno = 2;
perror(data->command_name);
errno = 127;
}
return (0);
}
/**
* builtin_set_env - ...
* @data: The struct for the program's data
* Return: Zero if success, or another number if specified in the arguments
*/
int builtin_set_env(data_of_program *data)
{
/* validate args */
if (data->tokens[1] == NULL || data->tokens[2] == NULL)
return (0);
if (data->tokens[3] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}
env_set_key(data->tokens[1], data->tokens[2], data);
return (0);
}
/**
* builtin_unset_env - ...
* @data: A struct containing the program's data.
* Return: ...
*/
int builtin_unset_env(data_of_program *data)
{
/* validate args */
if (data->tokens[1] == NULL)
return (0);
if (data->tokens[2] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}
env_remove_key(data->tokens[1], data);
return (0);
}
