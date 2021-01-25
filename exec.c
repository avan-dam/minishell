/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 14:10:52 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/25 18:05:37 by ambervandam   ########   odam.nl         */
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
    // char *argv[] = {mini->command, "cat", "test"};
    char 	*argv[] = {mini->command, mini->more, NULL};
	pid_t	pid;
	int 	status; 

	pid = fork();
	printf("Value of pid: %d\n", pid);
	ft_bin_command(mini);
    waitpid(pid, &status, 0);
	if (pid == -1)
	{
		ft_putstr_fd("error in forking\n", mini->stderr);
		return (-1);
	}
	else if (pid == 0)
	{
		printf("Argv[0][%s] argv[1][%s]\n", argv[0], argv[1]);
		dup2(mini->stdin, 0);
		dup2(mini->stdout, 1);
		// dup2(mini->stdin, 0);
		if (execve(mini->command, argv, envp) < 0)
		{	
			mini->exit = 1; //check if exit status can also be other
			return (-1); 
		}
		// exit(0);
	}      
    else if (WIFEXITED(status)) 
    { 
        mini->exit = WEXITSTATUS(status);
    }
	else
	{
		wait(NULL);
		return (0);
	}
    return 0;
}
