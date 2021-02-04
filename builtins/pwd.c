/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 17:59:29 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/03 22:17:40 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/syslimits.h>

/*
**	pwd : Print Working Directory
**	syntax: pwd [option]
**	prints the path of the current directory starting from the root
**	$PWD is an environment variable which stores the path of the
**	current directory
**
**	TO DO: check for > pwd ; cd..
*/

void		ft_pwd(t_mini *mini) // change to ptr?
{
	char	cwd[PATH_MAX];

	(void)mini;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putstr_fd(cwd, STDOUT);
	// ft_putstr_fd(cwd, STDOUT);
	// ft_putstr_fd(cwd, mini->stdout);
	ft_putchar('\n');
	mini->exit = 0;
}
