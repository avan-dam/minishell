/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 12:49:32 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/11 12:45:43 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	syntax: cd [directory]
**	cd: change directory
**	Implement for only a relative or absolute path
**	Change the current working directory to directory,
**	if [directory] is not supplied, the value of HOME shell variable is used
**	any additional arguments following [directory] are ignored
**
** cd ~ 		~ is short for home directory
** cd .			. is short for current directory
** cd ..		.. is short for parent directory
** cd /			use to move to the root directory
*/

void			ft_add_env(char *env, char *path, t_mini *mini)
{
	t_list		*lst;

	lst = ft_lstnew(env, path);
	ft_lstadd_back(&mini->env1, lst);
}

char			*ft_get_env(char *env, t_mini *mini)
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

static void		ft_no_oldpwd(t_mini *mini)
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
		ft_putstr_fd("bash: cd: OLDPWD not set\n", STDOUT);
}

static void		ft_change_directory(t_mini *mini, char *path)
{
	char		cwd[PATH_MAX];

	if (chdir(path) == -1)
	{
		if (ft_strcmp(path, "") == 0)
			return ;
		ft_putstr_fd("bash: cd: ", STDOUT);
		ft_putstr_fd(path, STDOUT);
		ft_putstr_fd(": No such file or directory\n", STDOUT);
		mini->exit = 1;
		return ;
	}
	ft_unset(mini, "OLDPWD");
	ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
	ft_unset(mini, "PWD");
	ft_add_env("PWD", getcwd(cwd, sizeof(cwd)), mini);
}

void			ft_cd(t_base *ptr, t_mini *mini)
{
	if (ptr->argv[1] == NULL || ft_strcmp(ptr->argv[1], "~") == 0)
	{
		chdir(ft_get_env("HOME", mini));
		ft_unset(mini, "OLDPWD");
		ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
		ft_unset(mini, "PWD");
		ft_add_env("PWD", ft_get_env("HOME", mini), mini);
	}
	else if (ft_strcmp(ptr->argv[1], "-") == 0)
	{
		ft_no_oldpwd(mini);
		return ;
	}
	else if (ptr->argv[1] != NULL)
		ft_change_directory(mini, ptr->argv[1]);
	mini->exit = 0;
}
