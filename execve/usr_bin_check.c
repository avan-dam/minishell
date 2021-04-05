/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   usr_bin_check.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 21:29:11 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/05 14:48:23 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_usr_bin(t_base *ptr, struct dirent *dit, DIR *dirp, int i)
{
	char		*command;
	char		*tmp;
	char		*startcmd;

	command = ptr->av[0];
	tmp = command;
	startcmd = ft_substr(command, 0, 9);
	free(startcmd);
	if ((ft_strcmp(startcmd, "/usr/bin/")) == 0)
		tmp = ft_substr(command, 9, ft_strlen(command) - 9);
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

int	ft_check_in_bin(t_base *ptr, struct dirent *dit, DIR *dirp, int i)
{
	char		*command;
	char		*tmp;
	char		*startcmd;

	command = ptr->av[0];
	tmp = command;
	startcmd = ft_substr(command, 0, 5);
	if ((ft_strcmp(startcmd, "/bin/") == 0))
		tmp = ft_substr(command, 5, ft_strlen(command) - 5);
	free(startcmd);
	dit = readdir(dirp);
	while (dit)
	{
		if (ft_strcmp(dit->d_name, tmp) == 0)
		{
			ptr->av[0] = ft_strjoin("/bin/", tmp);
			if (tmp && i == 0)
				free(tmp);
			closedir(dirp);
			return (0);
		}
		dit = readdir(dirp);
	}
	return (1);
}

int	check_builtins_unset_path(t_base *ptr, t_mini *mini)
{
	if (ft_get_env("PATH", mini) == NULL
		&& ft_strncmp(ptr->av[0], "/bin/", 5) != 0
		&& ft_strncmp(ptr->av[0], "/usr/bin/", 9) != 0
		&& ft_strcmp(ptr->av[0], "export") != 0
		&& ft_strcmp(ptr->av[0], "unset") != 0
		&& ft_strcmp(ptr->av[0], "exit") != 0
		&& ft_strcmp(ptr->av[0], "cd") != 0
		&& ft_strcmp(ptr->av[0], "pwd") != 0
		&& ft_strcmp(ptr->av[0], "echo") != 0)
		return (1);
	return (0);
}
