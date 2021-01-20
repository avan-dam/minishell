/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 14:10:52 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/19 10:11:20 by salbregh      ########   odam.nl         */
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

	ft_bin_command(mini);
	if ((pid = fork()) == -1)
	{
		ft_putstr("error in forking\n");
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
