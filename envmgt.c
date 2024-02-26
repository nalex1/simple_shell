#include "shell.h"

/**
 * env_get_key - Fetch the value of an env variable
 * @key: Focal env variable
 * @data: A struct containing the program's data.
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, key_len = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (_strcmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[i] + key_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * env_set_key - overwrite the value of the env variable
 * or create it if does not exist.
 * @key: Name of the variable to be set
 * @value: New value
 * @data: A struct containing the program's data.
 * Return: 1 if the parameters are NULL, 2 on error or 0 on success.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_len = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (_strcmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->env[i]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[i] = _strcat(_strdup(key), "=");
	data->env[i] = _strcat(data->env[i], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - Remove key from the env.
 * @key: Key to be removed.
 * @data: A struct containing the program's data.
 * Return: 1 if the key was removed or 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, key_len = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{/* iterates through the environ and checks for coincidences */
		if (_strcmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{/* if key already exists, remove them */
			free(data->env[i]);

			/* move the others keys one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* put the NULL value at the new end of the list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * print_environ - Display the current env
 * @data: A struct containing the program's data.
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
