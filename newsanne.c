/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newsanne.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 17:59:29 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/05 19:14:53 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/syslimits.h> // not sure if allowed?
#include <unistd.h>
#include <string.h>

void	ft_cd(t_mini *mini)
{
	// input befor minimore: cd
	printf("GOES IN CD\n");
	printf("value of mini->more: %s\n", mini->more);
}

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

void	ft_pwd(t_mini *mini)
{
	char				buf[PATH_MAX];// check is use of limits includes is allowed
	unsigned long int	i;

	i = 0;
	if (strcmp("", mini->more) != 0) // what is mini->more initialized too?
	{
		while (i < strlen(mini->more))
		{
			if (mini->more[i] != ' ')
			{
				ft_putstr("pwd: too many arguments\n");
				return ;
			}
			i++;
		}
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_putstr(buf);
	ft_putchar('\n');
}
