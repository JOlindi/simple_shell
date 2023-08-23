#include "shell.h"

/**
 * _memset - It fills memory with a constant byte
 * @q: the pointer to the memory area
 * @e: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (q) a pointer to the memory area q
 */
char *_memset(char *q, char e, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		q[i] = e;
	return (q);
}

/**
 * ffree - frees a string of strings
 * @ww: string of strings.
 *
 */

void ffree(char **ww)
{
	char **a = ww;

	if (!ww)
		return;
	while (*ww)
		free(*ww++);
	free(a);
}

/**
 * _realloc - It reallocates a block of memory
 * @ptr: A pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

