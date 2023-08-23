#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded with line numbers, starting at 0.
 * @infor: Structure containing potential arguments. Used to maintain constant function prototype.
 *  Return: Always 0
 */

int _myhistory(info_t *infor)
{
	print_list(infor->history);
	return (0);
}

/**
 * unset_alias - It sets alias to string
 * @infor: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *infor, char *str)
{
	char *w, c;
	int ret;

	w = _strchr(str, '=');
	if (!w)
		return (1);
	c = *w;
	*w = 0;
	ret = delete_node_at_index(&(infor->alias),
		get_node_index(infor->alias, node_starts_with(infor->alias, str, -1)));
	*w = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @infor: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *infor, char *str)
{
	char *w;

	w = _strchr(str, '=');
	if (!w)
		return (1);
	if (!*++w)
		return (unset_alias(infor, str));

	unset_alias(infor, str);
	return (add_node_end(&(infor->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *w = NULL, *a = NULL;

	if (node)
	{
		w = _strchr(node->str, '=');
		for (a = node->str; a <= w; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(w + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @infor: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *infor)
{
	int i = 0;
	char *w = NULL;
	list_t *node = NULL;

	if (infor->argc == 1)
	{
		node = infor->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; infor->argv[i]; i++)
	{
		w = _strchr(infor->argv[i], '=');
		if (w)
			set_alias(infor, infor->argv[i]);
		else
			print_alias(node_starts_with(infor->alias, infor->argv[i], '='));
	}

	return (0);
}

