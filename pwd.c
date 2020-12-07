/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 17:59:29 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/07 08:15:31 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/syslimits.h> // not sure if allowed?

/*
**	pwd : Print Working Directory
**	syntax: pwd [option]
**	prints the path of the current directory starting from the root
**	$PWD is an environment variable which stores the path of the
**	current directory
**
**	if there are characters behind pwd that are not whitespace, pwd
**	will print: pwd: too many arguments
*/

void		ft_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];// check is use of limits includes is allowed

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putstr(cwd);
	mini->path = cwd;
	ft_putchar('\n');
}