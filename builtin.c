/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 14:10:52 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/17 19:48:21 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_builtin(t_mini *mini, char *command, char *more, char **envp)
{
    (void)mini;
    int y;
    char *argv[] = { command , more, NULL };
	char *bincommand;
	if((command[0] == '/') && (command[1] == 'b') && (command[2] == 'i') && (command[3] == 'n') && (command[4] == '/'))
		bincommand = ft_strdup(command);
	else
		bincommand = ft_strjoin("/bin/", command);
	// SHOULD I USE envp as last parameter or null
	(void)envp;
    if ((y = execve(bincommand, argv , envp)) == -1)
	    return (-1); 
    return (0);
}