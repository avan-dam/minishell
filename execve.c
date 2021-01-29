/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/29 22:57:31 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void		execve_commands(t_base *ptr, char **envp)
{
	pid_t		pid;
	int			status;
	int			piped;

	piped = 0;
	if (ptr->type == TYPE_PIPE || (ptr->prev && ptr->prev->type == TYPE_PIPE))
	{
		piped = 1;
		if (pipe(ptr->fd))
		{
			printf("Error in piping\n");
			exit (0); // change
		}
	}
	if ((pid = fork()) < 0)
	{
		printf("Error in forking\n");
		exit (0); // change
	}
	if (pid == 0) // child process
	{
		if (ptr->type == TYPE_PIPE && dup2(ptr->fd[1], STDOUT) < 0)
		{
			printf("Type is pipe, and dup 2 failed.\n");
			exit (0); // change
		}
		if (ptr->prev && ptr->prev->type == TYPE_PIPE && dup2(ptr->prev->fd[0], STDIN) < 0)
		{
			printf("Type of previous is pipe, and dup 2 failed.\n");
			exit (0);
		}
		if ((execve(ptr->argv[0], ptr->argv, envp)) < 0)
		{
			printf("Execve failed.\n");
			exit (0);
		}
		exit (EXIT_SUCCESS); // closes process with succes // change
	}
	else // parent process
	{
		waitpid(pid, &status, 0);
		// mini->exit = WEXITSTATUS(status); // check this
		if (piped)
		{
			close(ptr->fd[1]);
			if (!ptr->next || ptr->next->type == TYPE_BREAK) // end proces if no next or type is break
				close(ptr->fd[1]);
		}
		if (ptr->prev && ptr->prev->type == TYPE_PIPE)
			close(ptr->prev->fd[0]);
	}
}

void		exec_cmds(t_base *ptr, char **envp, t_mini *mini)
{
	t_base	*tmp;

	tmp = ptr;
	while (tmp)
	{
		if ((ft_strcmp(tmp->argv[0], "echo")) == 0 || (ft_strcmp(tmp->argv[0], "/bin/echo") == 0))
			ft_echo(tmp, mini);
		else if (ft_strcmp(tmp->argv[0], "cd") == 0)
			ft_cd(tmp, mini);
		else if ((ft_strcmp(tmp->argv[0], "pwd") == 0) || (ft_strcmp(tmp->argv[0], "/bin/pwd") == 0))
			ft_pwd(mini);
		else if (ft_strcmp(tmp->argv[0], "export") == 0)
			ft_export(tmp, mini);
		else if (ft_strcmp(tmp->argv[0],"unset") == 0)
			ft_unset(mini, tmp->argv[1]);
		else if (ft_strcmp(tmp->argv[0], "env") == 0)
			ft_lstprint(mini->env1, mini);
		else if (look_for_non_builtin(tmp) == 0)
		{
			printf("goes in non builtin\n");
			execve_commands(tmp, envp);
		}
		else
			unvalid_identifier(tmp->argv[0], mini);
		tmp = tmp->next;
	}
}
