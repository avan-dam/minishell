/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 15:06:53 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/06 21:45:36 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "/bin/echo") == 0
		|| ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "/usr/bin/cd") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "/usr/bin/env") == 0
		|| ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "/bin/pwd") == 0
		|| ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}

static int	ft_check_unset(t_mini *mini, t_base *tmp, int j, char **envp)
{
	if (ft_get_env("PATH", mini) == NULL
		&& ft_strncmp(tmp->av[0], "/bin/", 5) != 0
		&& ft_strncmp(tmp->av[0], "/usr/bin/", 9) != 0
		&& ft_strcmp(tmp->av[0], "export") != 0
		&& ft_strcmp(tmp->av[0], "unset") != 0
		&& ft_strcmp(tmp->av[0], "exit") != 0
		&& ft_strcmp(tmp->av[0], "cd") != 0
		&& ft_strcmp(tmp->av[0], "pwd") != 0
		&& ft_strcmp(tmp->av[0], "echo") != 0)
	{
		if (j == 0 && ft_is_builtin(tmp->av[0]) == 0)
			return (-1);
		if (execve(tmp->av[0], tmp->av, envp) < 0)
		{
			mini->exit = 127;
			ft_putstr_fd("bash: ", STDERR);
			ft_putstr_fd(tmp->av[0], STDERR);
			ft_putstr_fd(": No such file or directory\n", STDERR);
			return (-1);
		}
		return (-1);
	}
	return (0);
}

int	look_for_non_builtin(t_base *ptr, int i, t_mini *mini, char **envp)
{
	t_base			*tmp;
	DIR				*dirp;
	struct dirent	*dit;

	tmp = ptr;
	if (ft_check_unset(mini, tmp, i, envp) == -1)
		return (-1);
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
	if (ft_check_usr_bin(ptr, dit, dirp, i) == 0)
		return (0);
	if (closedir(dirp) == -1)
		exit(0);
	return (2);
}

void	exec_builtin(t_base *tmp, t_mini *mini, char **envp)
{
	if (ft_check_unset(mini, tmp, 0, envp) == -1)
		return ;
	else if (ft_strcmp(tmp->av[0], "env") == 0
		|| ft_strcmp(tmp->av[0], "/usr/bin/env") == 0)
		ft_lstprint_env(mini->env1, mini, tmp);
	else if (ft_strcmp(tmp->av[0], "export") == 0)
		ft_export(tmp, mini);
	else if (ft_strcmp(tmp->av[0], "echo") == 0
		|| ft_strcmp(tmp->av[0], "/bin/echo") == 0)
		ft_echo(tmp, mini);
	else if ((ft_strcmp(tmp->av[0], "pwd") == 0)
		|| (ft_strcmp(tmp->av[0], "/bin/pwd") == 0))
		ft_pwd(mini);
	else if (ft_strcmp(tmp->av[0], "cd") == 0
		|| ft_strcmp(tmp->av[0], "/usr/bin/cd") == 0)
		ft_cd(tmp, mini);
	else if (ft_strcmp(tmp->av[0], "unset") == 0)
		ft_unset_builtin(mini, tmp);
}
