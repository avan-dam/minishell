/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 14:10:52 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/21 20:40:02 by ambervandam   ########   odam.nl         */
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

int				ft_execve(t_mini *mini, char **envp)
{
    char *argv[] = {mini->command, mini->more, NULL};
	// char *argv[] ={ "touch", "/tmp/file", NULL };
	pid_t	pid;

	pid = fork();
	printf("Value of pid: %d\n", pid);
	ft_bin_command(mini);
	if (pid == -1)
	{
		ft_putstr("error in forking\n");
		return (-1);
	}
	else if (pid == 0)
	{
		// if (execve("/usr/bin/touch", argv, NULL) < 0)
		if (execve(mini->command, argv, envp) < 0)
        	return (-1); 
		exit(0);
	}
	else
	{
		wait(NULL);
		return (0);
	}
	(void)envp;
    return 0;
}
