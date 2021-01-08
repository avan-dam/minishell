/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 12:49:32 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/08 19:50:50 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/syslimits.h> // not sure if allowed?
#include <string.h>

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

static void	ft_add_env(char *env, char *path, t_mini *mini)
{
	t_list	*lst;

	lst = ft_lstnew(env, path);
	ft_lstadd_back(&mini->env1, lst);
}

static char	*ft_get_env(char *env, t_mini *mini)
{
	t_list	*lst;
	
	lst = mini->env1;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->var1, env) == 0)
			return (lst->var2);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_cd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*currentpwd;

	currentpwd = ft_get_env("PWD", mini);
	if (mini->more == NULL || ft_strcmp(mini->more, "~") == 0)
	{
		chdir(ft_get_env("HOME", mini));
		ft_unset(mini, "PWD");
		ft_add_env("PWD", ft_get_env("HOME", mini), mini);
		ft_add_env("OLDPWD", currentpwd, mini);
		return ;
	}
	else if (ft_strcmp(mini->more, "-") == 0) // also prints where it goes back to?
	{
		if (ft_get_env("OLDPWD", mini) != NULL)
		{
			chdir(ft_get_env("OLDPWD", mini));
			ft_unset(mini, "OLDPWD"); // delete the existing oldpwd
			ft_add_env("OLDPWD", currentpwd, mini); // add oldpwd
			ft_unset(mini, "PWD");
			ft_add_env("PWD", "find previous", mini);
		}
		else
			ft_putstr("bash: cd: OLDPWD not set\n");
		return ;
	}
	else
	{
		if (chdir(mini->more) < 0) // if chdir did not succeed fix this
		{
			ft_putstr("cd: ");
			ft_putstr(mini->more);
			ft_putstr(": No such file or directory\n");
			return ;
		}
		getcwd(cwd, sizeof(cwd));
		// printf("CWD: %s\n", cwd);
		ft_unset(mini, "PWD");
		ft_add_env("PWD", cwd, mini);
		ft_unset(mini, "OLDPWD");
		ft_add_env("OLDPWD", currentpwd, mini);
	}
	
	// if (ft_strcmp(mini->more, "..") == 0) // go to parent class (one level up from current directory)
	// if (ft_strcmp(mini->more, "../..")) // go to the parents parents class (two levels up from current directory)
	// if (ft_strcmp(mini->more, ".") == 0) // change into current directory, do nothing, do you change/set oldpwd?
	// cd ../filename (put in chdir?)
	// if ((ft_strcmp(mini->more, ~) == 0 )) // go into home directory set by $HOME


	// ft_set_env("OLDPWD", currentpwd, mini);
	// printf("directory after cd : %s\n", getcwd(cwd, sizeof(cwd)));
}
