/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   non_builtins.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 15:06:53 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/04 11:46:53 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

static int	ft_check_in_usr_bin(t_base *ptr, struct dirent *dit, DIR *dirp, int i)
{
	char		*command;
	char		*tmp;
	int			usrbin;
	char		*startcmd;

	command = ptr->av[0];
	tmp = command;
	startcmd = ft_substr(command, 0, 9);
	usrbin = ft_strcmp(startcmd, "/usr/bin/");
	free(startcmd);
	if (usrbin == 0)
		tmp = ft_substr(command, 9, ft_strlen(command) - 9);
	// free(command);
	dit = readdir(dirp);
	while (dit)
	{
		if (ft_strcmp(dit->d_name, tmp) == 0)
		{
			ptr->av[0] = ft_strjoin("/usr/bin/", tmp);
			if (tmp && i == 0)
				free(tmp);
			closedir(dirp);
			return (0);
		}
		dit = readdir(dirp);
	}
	return (1);
}

static int	ft_check_in_bin(t_base *ptr, struct dirent *dit, DIR *dirp, int i)
{
	char		*command;
	char		*tmp;
	int			bin;
	char		*startcmd;

	// printf("GOES IN WITH: %s\n", ptr->av[0]);
	command = ptr->av[0];
	tmp = command;
	startcmd = ft_substr(command, 0, 5);
	bin = ft_strcmp(startcmd, "/bin/");
	free(startcmd);
	if (bin == 0)
		tmp = ft_substr(command, 5, ft_strlen(command) - 5);
	// free(command);
	dit = readdir(dirp);
	while (dit)
	{
		if (ft_strcmp(dit->d_name, tmp) == 0)
		{
			ptr->av[0] = ft_strjoin("/bin/", tmp);
			if (tmp && i == 0)
				free(tmp);
			closedir(dirp);
			// printf("COMES OUT\n");
			return (0);
		}
		dit = readdir(dirp);
	}
	return (1);
}

int	ft_is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "/bin/echo") == 0
		|| ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "/usr/bin/cd") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "/usr/bin/env") == 0
		|| ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "/bin/pwd") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "$?") == 0)
		return (1);
	return (0);
}

/*
**	dir is the directory pointer
** 	opendir() opes the directory and point to the first entry in the directory
*/

int	look_for_non_builtin(t_base *ptr, int i)
{
	t_base			*tmp;
	DIR				*dirp;
	struct dirent	*dit;

	tmp = ptr;
	if (ft_is_builtin(tmp->av[0]) == 1)
		return (1);
	dit = NULL;
	dirp = opendir("/bin");
	if (dirp == NULL)
		exit(0);
	if (ft_check_in_bin(tmp, dit, dirp, i) == 0)
		return (0);
	closedir(dirp);
	dirp = opendir("/usr/bin");
	if (dirp == NULL)
		exit(0);
	if (ft_check_in_usr_bin(ptr, dit, dirp, i) == 0)
		return (0);
	if (closedir(dirp) == -1)
		exit(0);
<<<<<<< HEAD
	free(tmp->av[0]);
=======
>>>>>>> amberbranch
	return (2);
}
