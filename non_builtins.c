/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   non_builtins.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 15:06:53 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/07 12:19:54 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int		ft_check_in_usr_bin(t_base *ptr, struct dirent *dit, DIR *dirp)
{
	char		*command;

	command = ptr->argv[0];
	if (ft_strcmp(ft_substr(command, 0, 9), "/usr/bin/") == 0)
		command = ft_substr(command, 9, ft_strlen(command));
	while ((dit = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dit->d_name, command) == 0)
		{
			ptr->argv[0] = ft_strjoin("/usr/bin/", ptr->argv[0]);
			closedir(dirp);
			return (0);
		}
	}
	// free(command);
	return (1);
}

static int		ft_check_in_bin(t_base *ptr, struct dirent *dit, DIR *dirp)
{
	char		*command;

	command = ptr->argv[0];
	char*	tmp = command;
	if (ft_strcmp(ft_substr(tmp, 0, 5), "/bin/") == 0)
		tmp = ft_substr(command, 5, ft_strlen(command));
	// free(tmp);
	while ((dit = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dit->d_name, command) == 0)
		{
			ptr->argv[0] = ft_strjoin("/bin/", ptr->argv[0]);
			closedir(dirp);
			return (0);
		}
	}
	// system("leaks minishell");
	return (1);
}

int         ft_is_builtin_command(char *str)
{
    if ((ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "/bin/echo") == 0 || ft_strcmp(str, "Echo") == 0 ||
		ft_strcmp(str, "cd") == 0) || ft_strcmp(str, "/usr/bin/cd") == 0 ||
		ft_strcmp(str, "env") == 0 || ft_strcmp(str, "/usr/bin/env") == 0 ||
		ft_strcmp(str, "exit") == 0 ||
		ft_strcmp(str, "export") == 0 || 
		ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "/bin/pwd") == 0 ||
		ft_strcmp(str, "unset") == 0 ||
		ft_strcmp(str, "$?") == 0)
		return (1);
	return (0);
}

/*
**	dir is the directory pointer
** 	opendir() opes the directory and point to the first entry in the directory
*/

int				look_for_non_builtin(t_base *ptr)
{
	t_base			*tmp;
	DIR				*dirp; // dir pointer
	struct dirent	*dit;

	tmp = ptr; // so < notworking.txt can work
	if (ft_is_builtin_command(tmp->argv[0]) == 1)
	// if (ft_is_builtin_command(ptr->argv[0]) == 1)
		return (1);
	dit = NULL;
	if ((dirp = opendir("/bin")) == NULL)
		exit(0);
	if (ft_check_in_bin(tmp, dit, dirp) == 0)
	// if (ft_check_in_bin(ptr, dit, dirp) == 0)
	{
		// system("leaks minishell");
		return (0);
	}
	closedir(dirp);
	if ((dirp = opendir("/usr/bin")) == NULL)
		exit (0);
	if (ft_check_in_usr_bin(tmp, dit, dirp) == 0)
	// if (ft_check_in_usr_bin(ptr, dit, dirp) == 0)
		return (0);
	if (closedir(dirp) == -1)
		exit (0);
	return (1);
}
