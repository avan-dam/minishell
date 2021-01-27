/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:12:03 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/27 17:14:39 by salbregh      ########   odam.nl         */
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
	int 	status; 

	printf("value of pipe: %i\n", piper->check);

	ft_bin_command(mini);
	if ((pid = fork()) == -1)
	{
		ft_putstr_fd("error in forking\n", STDOUT);
	if (pid == -1)
	{
		ft_putstr_fd("error in forking\n", mini->stderr);
		return (-1);
	}
	printf("Value of pid: %d\n", pid);
	if (pid == 0) // this is the child process
	{
		printf("IN CHILD\n");
		printf("value of fd[0] - %i and fd[1] - %i\n", piper->fd[0], piper->fd[1]);
		close(piper->fd[0]); // close read side
		write(piper->fd[1], &piper->write_side, ft_strlen(piper->write_side));
		close(piper->fd[1]);
		if (piper->check == 0)
		{
			if (execve(mini->command, argv, envp) < 0) // executes the function
        		return (-1); 
			exit(0);
		}
	}
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
		printf("IN PARENT\n");
		printf("value of fd[0] - %i and fd[1] - %i\n", piper->fd[0], piper->fd[1]);
		close(piper->fd[1]); // close writing side
		printf("value of write_side: %s\nvalue of read_side: %s\n", piper->write_side, piper->read_side);
		read(piper->fd[0], &piper->read_side, ft_strlen(piper->read_side));
		printf("value of write_side: %s\nvalue of read_side: %s\n", piper->write_side, piper->read_side);
		execve(mini->command, argv, envp);
		wait(NULL);
		return (0);
	}
    return 0;
}
