/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 12:49:32 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/14 21:56:18 by salbregh      ########   odam.nl         */
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
** cd /			use to move to the root directory?

** everytime you change directory, change OLDPWD and PWD
*/

void		ft_add_env(char *env, char *path, t_mini *mini)
{
	t_list	*lst;

	lst = ft_lstnew(env, path);
	ft_lstprint(lst);
	ft_lstadd_back(&mini->env1, lst); // mistake in add back maybe
	// ft_lstprint(mini->env1);
}

void		*ft_get_env(char *env, t_mini *mini)
{
	t_list	*lst;
	
	lst = mini->env1;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->var1, env) == 0)
		{
			printf("%s\n", lst->var2); // waarde klopt
			return (lst->var2);
		}
		lst = lst->next;
	}
	free(lst);
	return (NULL);
}

void		ft_cd(t_mini *mini)
{
	char	cwd[PATH_MAX];

	mini->oldpwd = getcwd(cwd, sizeof(cwd));
	if (mini->more == NULL || ft_strcmp(mini->more, "~") == 0)
	{
		chdir(ft_get_env("HOME", mini));
		ft_unset(mini, "OLDPWD");
		ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
		ft_unset(mini, "PWD");
		ft_add_env("PWD", ft_get_env("HOME", mini), mini);
	}
	else if (ft_strcmp(mini->more, "-") == 0)
	{
		if (ft_get_env("OLDPWD", mini) != NULL)
		{
			chdir(ft_get_env("OLDPWD", mini));
			ft_putstr(ft_get_env("OLDPWD", mini));
			ft_putstr("\n");
			ft_unset(mini, "OLDPWD");
			ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
			ft_unset(mini, "PWD");
			ft_add_env("PWD", getcwd(cwd, sizeof(cwd)), mini);
		}
		else
			ft_putstr("bash: cd: OLDPWD not set\n");
		return ;
	}
	else if (mini->more != NULL)
	{
		if (chdir(mini->more) == -1) // when directory change fails
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putstr(mini->more);
			ft_putstr("\n");
			return ;
		}
		ft_unset(mini, "OLDPWD");
		ft_add_env("OLDPWD", ft_get_env("PWD", mini), mini);
		ft_unset(mini, "PWD");
		ft_add_env("PWD", getcwd(cwd, sizeof(cwd)), mini);
	}
}
