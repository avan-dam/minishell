/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 12:49:32 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/24 22:41:13 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_env(char *env, char *path, t_mini *mini)
{
	t_list		*lst;

	lst = ft_lstnew(env, path);
	ft_lstadd_back(&mini->env1, lst);
}

static char	*ft_get_env(char *env, t_mini *mini)
{
	t_list		*lst;
	char		*pathname;

	pathname = NULL;
	lst = mini->env1;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->var1, env) == 0)
		{
			pathname = lst->var2;
			return (pathname);
		}
		lst = lst->next;
	}
	ft_lstclear(&lst);
	return (NULL);
}

static void	ft_no_oldpwd(t_mini *mini)
{
	char		cwd[PATH_MAX];

	if (ft_get_env("OLDPWD", mini) != NULL)
	{
		chdir(ft_get_env("OLDPWD", mini));
		ft_putstr_fd(ft_get_env("OLDPWD", mini), STDOUT);
		ft_putstr_fd("\n", STDOUT);
		ft_unset(mini, "OLDPWD");
		ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
		ft_unset(mini, "PWD");
		ft_add_env("PWD", getcwd(cwd, sizeof(cwd)), mini);
	}
	else
		ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR);
}

static void	ft_change_directory(t_mini *mini, char *path)
{
	char		cwd[PATH_MAX];

	if (chdir(path) == -1)
	{
		if (ft_strcmp(path, "") == 0)
			return ;
		ft_putstr_fd("bash: cd: ", STDERR);
		ft_putstr_fd(path, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->exit = 1;
		return ;
	}
	ft_unset(mini, "OLDPWD");
	ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
	ft_unset(mini, "PWD");
	ft_add_env("PWD", getcwd(cwd, sizeof(cwd)), mini);
}

void	ft_cd(t_base *ptr, t_mini *mini)
{
	char		cwd[PATH_MAX];

	mini->exit = 0;
	if (ptr->av[1] == NULL || ptr->av[1][0] == '~')
	{
		chdir(ft_get_env("HOME", mini));
		if (ptr->av[1][1] == '/' && ft_strcmp(ptr->av[1], "~/") != 0)
		{
			if (chdir(&ptr->av[1][2]))
			{
				ft_putstr_fd("bash: cd: ", STDERR);
				ft_putstr_fd(ft_get_env("HOME", mini), STDERR);
				ft_putstr_fd(&ptr->av[1][1], STDERR);
				ft_putstr_fd(": No such file or directory\n", STDERR);
			}
			ft_unset(mini, "OLDPWD");
			ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
			ft_unset(mini, "PWD");
			ft_add_env("PWD", getcwd(cwd, sizeof(cwd)), mini);
			return ;
		}
		ft_unset(mini, "OLDPWD");
		ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
		ft_unset(mini, "PWD");
		ft_add_env("PWD", ft_get_env("HOME", mini), mini);
	}
	else if (ft_strcmp(ptr->av[1], "-") == 0)
		return (ft_no_oldpwd(mini));
	else if (ptr->av[1] != NULL)
		ft_change_directory(mini, ptr->av[1]);
}
