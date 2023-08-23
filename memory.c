#include "shell.h"

/**
 * bfree - It frees a pointer and NULLs the address
 * @potr: address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */

int bfree(void **potr)
{
	if (potr && *potr)
	{
		free(*potr);
		*potr = NULL;
		return (1);
	}
	return (0);
}

