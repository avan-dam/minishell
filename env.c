/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 22:27:08 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/08 14:30:34 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// rewrite getenv() setenv()

// gcc -o env env.c

int		main(int argc, char **argv, char **envp)
{
	for (int i = 0; envp[i] != NULL; i++)
	{
		printf("%d: %s\n", i, envp[i]);
	}
}