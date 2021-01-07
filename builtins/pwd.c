/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 17:59:29 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/07 14:44:51 by salbregh      ########   odam.nl         */
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

void		ft_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putstr(cwd);
	mini->path = cwd;
	ft_putchar('\n');
}