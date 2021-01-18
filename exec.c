/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 14:10:52 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/18 19:51:59 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_bin_command(t_mini *mini)
{
	char *end;
	
	if (ft_strcmp("touch", mini->command) == 0)
	{
		mini->command = ft_strjoin("/usr/bin/touch", mini->command);
		return ;
	}
	end = ft_substr(mini->command, 0, 5);
	if (ft_strcmp("/bin/", end) != 0)
		mini->command = ft_strjoin("/bin/", mini->command);
	free(end);
}

int				ft_execve(t_mini *mini, char **envp, t_piper *piper)
{
    char *argv[] = {mini->command, mini->more, NULL}; // maybe have to add pipe to this
	pid_t	pid;

	printf("value of pipe: %i\n", piper->check);

	pid = fork();
	printf("Value of pid: %d\n", pid);
	ft_bin_command(mini);
	if ((pid = fork() == -1))
	{
		ft_putstr_fd("error in forking\n", mini->stdout);
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(mini->command, argv, envp) < 0) // executes the function
        	return (-1); 
		exit(0);
	}
	else
	{
			wait(NULL);
		return (0);
	}
    return 0;
}
