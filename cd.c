/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 12:49:32 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/06 13:47:51 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/syslimits.h> // not sure if allowed?
#include <string.h>

void	ft_cd(t_mini *mini)
{
	char	cwd[PATH_MAX];

	printf("current directory: %s\n", getcwd(cwd, sizeof(cwd)));
	// chdir("..");
	chdir(mini->more);
	printf("directory after cd : %s\n", getcwd(cwd, sizeof(cwd)));
	// input befor minimore: cd
	printf("GOES IN CD\n");
	printf("value of mini->more: %s\n", mini->more);
}
