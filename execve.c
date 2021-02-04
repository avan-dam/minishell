/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/04 12:50:25 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execve_commands(t_base *ptr, char **envp, t_mini *mini)
{
	pid_t		pid;
	int			status;
	int			piped;

	piped = 0;
	if (ptr->type == TYPE_PIPE || (ptr->prev && ptr->prev->type == TYPE_PIPE))
	{
		piped = 1;
		if (pipe(ptr->fd))
			exit (0); // change
	}
	if ((pid = fork()) < 0)
		exit (0); // change
	if (pid == 0) // child process
	{
		dup2(mini->stdin, STDIN);
		dup2(mini->stdout, STDOUT);
		if (ptr->type == TYPE_PIPE && dup2(ptr->fd[1], STDOUT) < 0)
		{
			// printf("Type is pipe, and dup 2 failed.\n");
			exit (0); // change
		}
		if (ptr->prev && ptr->prev->type == TYPE_PIPE && dup2(ptr->prev->fd[0], STDIN) < 0)
		{
			// printf("Type of previous is pipe, and dup 2 failed.\n");
			exit (0);
		}
		// in here check commands;
		if ((ft_strcmp(ptr->argv[0], "echo")) == 0) // || (ft_strcmp(ptr->argv[0], "/bin/echo") == 0))
		{
			// printf("goes in echo with ptr->argv[1]: %s\n", ptr->argv[1]);
			ft_echo(ptr, mini);
		}
		else if (ft_strcmp(ptr->argv[0], "cd") == 0)
			ft_cd(ptr, mini);
		else if ((ft_strcmp(ptr->argv[0], "pwd") == 0) || (ft_strcmp(ptr->argv[0], "/bin/pwd") == 0))
			ft_pwd(mini);
		else if (ft_strcmp(ptr->argv[0], "export") == 0)
			ft_export(ptr, mini);
		else if (ft_strcmp(ptr->argv[0],"unset") == 0)
			ft_unset(mini, ptr->argv[1]);
		else if (ft_strcmp(ptr->argv[0], "env") == 0)
			ft_lstprint(mini->env1, mini);
		else if ((execve(ptr->argv[0], ptr->argv, envp)) < 0)
		{
			printf("Execve failed.\n");
			printf("CASE 3\n");
			exit (0);
			(void)envp;
		}
		// else
		// 	unvalid_identifier(ptr->argv[0], mini, 127);
		// exit (EXIT_SUCCESS); // closes process with succes // change // REMOVED THIS THIS MAKES ENV AND EXPORT AND UNSET WORK
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

int			exec_cmds(t_base *ptr, char **envp, t_mini *mini)
{
	t_base	*tmp;

	tmp = ptr;
	(void)envp;
	while (tmp)
	{
		ft_redir(mini, tmp);
		if (tmp == NULL)
			break ;
		// if ((ft_strcmp(tmp->argv[0], "echo")) == 0) //|| (ft_strcmp(tmp->argv[0], "/bin/echo") == 0))
		// 	ft_echo(tmp, mini);
		// else if (ft_strcmp(tmp->argv[0], "cd") == 0)
		// 	ft_cd(tmp, mini);
		// else if ((ft_strcmp(tmp->argv[0], "pwd") == 0) || (ft_strcmp(tmp->argv[0], "/bin/pwd") == 0))
		// 	ft_pwd(mini);
		// else if (ft_strcmp(tmp->argv[0], "export") == 0)
		// 	ft_export(tmp, mini);
		// else if (ft_strcmp(tmp->argv[0],"unset") == 0)
		// 	ft_unset(mini, tmp->argv[1]);
		// else if (ft_strcmp(tmp->argv[0], "env") == 0)
		// 	ft_lstprint(mini->env1, mini);
		// else if (look_for_non_builtin(tmp) == 0)
		execve_commands(tmp, envp, mini);
		if (ft_strcmp(tmp->argv[0], "$?") == 0)
			ft_printf_exit_status(mini);
		else if (ft_strcmp(tmp->argv[0], "") == 0)
		{
			ft_putstr_fd(tmp->argv[0], mini->stdout);
			mini->exit = 0;
		}
		else if (ft_strcmp(tmp->argv[0], "exit") == 0)
		{	
			if (tmp->argv[1] != NULL)
			{	
				mini->exit = ft_atoi(tmp->argv[1]);
				if (tmp->argv[2] != NULL)
					mini->exit = 1;
			}
			return (-1);
		}
		else if (look_for_non_builtin(tmp) == 0) // change obvs
			execve_commands(tmp, envp, mini);
		else 		
			unvalid_identifier(tmp->argv[0], mini, 127);
		ft_reset_fds(mini);
		tmp = tmp->next;
	}
	return (0);
}
