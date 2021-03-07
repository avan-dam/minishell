/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 17:59:29 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/21 20:31:49 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	pwd : Print Working Directory
**	syntax: pwd [option]
**	prints the path of the current directory starting from the root
**	$PWD is an environment variable which stores the path of the
**	current directory
*/

void	ft_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];

	(void)mini;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putstr_fd(cwd, STDOUT);
	ft_putchar('\n');
	mini->exit = 0;
}
