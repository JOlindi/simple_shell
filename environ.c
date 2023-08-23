#include "shell.h"


/**
 * _myenv - Prints the current environment
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Always 0
 */

int _myenv(info_t *infor)
{
	print_list_str(infor->env);
	return (0);
}

/**
 * _getenv - It gets the value of an environ variable
 * @infor: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */

char *_getenv(info_t *infor, const char *name)
{
	list_t *node = info->env;
	char *w;

	while (node)
	{
		w = starts_with(node->str, name);
		if (w && *w)
			return (w);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - It initialize a new environment variable, or modify an existing one
 * @infor: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *infor)
{
	if (infor->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infor, infor->argv[1], infor->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable
 * @infor: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *infor)
{
	int i;

	if (infor->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= infor->argc; i++)
		_unsetenv(infor, infor->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @infor: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *infor)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

