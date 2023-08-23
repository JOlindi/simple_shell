#include "shell.h"

/**
 * _myexit - It exits the shell
 * @infor: A structure containing  potential arguments. Used to maintain the constant function prototype.
 * Return: Exits with a given exit status.
 * (0) if info.argv[0] != "exit"
 */

int _myexit(info_t *infor)
{
int exitcheck;

	if (infor->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(infor->argv[1]);
		if (exitcheck == -1)
		{
			infor->status = 2;
			print_error(infor, "Illegal number: ");
			_eputs(infor->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infor->err_num = _erratoi(infor->argv[1]);
		return (-2);
	}
	infor->err_num = -1;
	return (-2);
}

/**
 * _mycd -It changes the current directory of the process
 * @infor: A structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Always 0
 */

int _mycd(info_t *infor)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infor->argv[1])
	{
		dir = _getenv(infor, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: What should this be? */
				chdir((dir = _getenv(infor, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(infor->argv[1], "-") == 0)
	{
		if (!_getenv(infor, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infor, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: What should this be? */
			chdir((dir = _getenv(infor, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(infor->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(infor, "can't cd to ");
		_eputs(infor->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infor, "OLDPWD", _getenv(infor, "PWD="));
		_setenv(infor, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @infor: A structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *infor)
{
	char **arg_array;

	arg_array = infor->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

