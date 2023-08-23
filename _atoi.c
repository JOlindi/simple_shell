#include "shell.h"

/**
 * interactive - It returns true if shell is interactive mode
 * @info: A struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 *
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - It checks if character is a delimeter
 * @b: The character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */

int is_delim(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 * isAlpha -It checks for alphabetic character
 * @b: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int isAlpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - It converts a string to an integer
 * @q: String to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *q)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; q[i] != '\0' && flag != 2; i++)
	{
		if (q[i] == '-')
			sign *= -1;

		if (q[i] >= '0' && q[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (q[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

