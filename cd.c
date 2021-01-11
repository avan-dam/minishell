/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 12:49:32 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/11 18:06:08 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/syslimits.h> // not sure if allowed?
#include <string.h>

/*
**	syntax: cd [directory]
**	cd: change directory
**	Implement for only a relative or absolute path
**	Change the current working directory to directory, 
**	if [directory] is not supplied, the value of HOME shell variable is used
**	any additional arguments following [directory] are ignored
*/

void	ft_cd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	int		i;
	char	*line;

	if (mini->cd == 0)
		setenv("OLDPWD", "NULL", 1);
	printf("VALUE OLDPWD: %s\n", getenv("OLDPWD"));
	mini->cd = 1;
	// set OLDPWD to PWD when cd is used once
	i = 0;
	if (mini->more == NULL)
	{
		chdir(getenv("HOME"));
		return ;
	}
	line = mini->more; // make sure to trim mini->more to only the first argument seeing the rest is ignored
	if (ft_strchr(line, '-') != NULL)
	{
		if (ft_strcmp(getenv("OLDPWD"), "NULL") == 0)
			chdir(getenv("OLDPWD"));
		else
			ft_putstr_fd("bash: cd: OLDPWD not set\n", mini->stdout);
		return ;
	}
	else if (chdir(mini->more) != 0)
	{
		while (line[i])
		{
			if (line[i] != ' ')
			{
				ft_putstr_fd("cd: ", mini->stdout);
				ft_putstr_fd(mini->more, mini->stdout);
				ft_putstr_fd(": No such file or directory\n", mini->stdout);
				return ;
			}
			i++;
		}
		// if mini->more consist of only withspace just return
		// ft_putstr("cd: ");
		// ft_putstr(mini->more);
		// ft_putstr(": No such file or directory\n");
	}
	printf("directory after cd : %s\n", getcwd(cwd, sizeof(cwd)));
	// input befor minimore: cd
	// printf("value of mini->more: %s\n", mini->more);
}
