#include "shell.h"

/**
 * is_chain - To test if current char in buffer is a chain delimeter
 * @infor: the parameter struct
 * @buf: the char buffer
 * @q: address of current position in buf.
 *
 * Return: 1 if chain delimeter, 0 otherwise.
 *
 */

int is_chain(info_t *infor, char *buf, size_t *q)
{
	size_t j = *q;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		infor->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		infor->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		infor->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = j;
	return (1);
}

/**
 * check_chain - It checks we should continue chaining based on last status
 * @infor: the parameter struct
 * @buf: the char buffer
 * @q: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void.
 *
 */

void check_chain(info_t *infor, char *buf, size_t *q, size_t i, size_t len)
{
	size_t j = *q;

	if (infor->cmd_buf_type == CMD_AND)
	{
		if (infor->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (infor->cmd_buf_type == CMD_OR)
	{
		if (!infor->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*q = j;
}

/**
 * replace_alias - It replaces an aliases in the tokenized string
 * @infor: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise.
 *
 */

int replace_alias(info_t *infor)
{
	int i;
	list_t *node;
	char *q;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(infor->alias, infor->argv[0], '=');
		if (!node)
			return (0);
		free(infor->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		infor->argv[0] = q;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @infor: the parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 *
 */

int replace_vars(info_t *infor)
{
	int i = 0;
	list_t *node;

	for (i = 0; infor->argv[i]; i++)
	{
		if (infor->argv[i][0] != '$' || !infor->argv[i][1])
			continue;

		if (!_strcmp(infor->argv[i], "$?"))
		{
			replace_string(&(infor->argv[i]),
					_strdup(convert_number(infor->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infor->argv[i], "$$"))
		{
			replace_string(&(infor->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(infor->env, &infor->argv[i][1], '=');
		if (node)
		{
			replace_string(&(infor->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&infor->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - It replaces string
 * @old: address of old string
 * @new: new string.
 *
 * Return: 1 if replaced, 0 otherwise.
 *
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

