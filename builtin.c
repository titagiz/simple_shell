#include "shell.h"

/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = str_toi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_putss(info->argv[1]);
			_putchars('\n');
			return (1);
		}
		info->err_num = str_toi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}


/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_putss("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_putss(s);
			_putchars('\n');
			return (1);
		}
		_putss(get_env(info, "OLDPWD=")), _putchars('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_putss(info->argv[1]), _putchars('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * my_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_putss("help call works. Function not yet implemented \n");
	if (0)
		_putss(*arg_array); /* temp att_unused workaround */
	return (0);
}
