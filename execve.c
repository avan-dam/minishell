/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/04 14:45:25 by salbregh      ########   odam.nl         */
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
		// dup2(mini->stdin, STDIN);
		// dup2(mini->stdout, STDOUT);
		printf("GOES IN CHILD PROCESS, argv: %s\n", ptr->argv[0]);
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
		if ((ft_strcmp(ptr->argv[0], "echo")) == 0 || (ft_strcmp(ptr->argv[0], "/bin/echo") == 0))
			ft_echo(ptr, mini);
		// else if (ft_strcmp(ptr->argv[0], "cd") == 0)
		// 	ft_cd(ptr, mini);
		else if ((ft_strcmp(ptr->argv[0], "pwd") == 0) || (ft_strcmp(ptr->argv[0], "/bin/pwd") == 0))
			ft_pwd(mini);
		// else if (ft_strcmp(ptr->argv[0], "export") == 0)
		// 	ft_export(ptr, mini);
		// else if (ft_strcmp(ptr->argv[0], "unset") == 0)
		// 	ft_unset(mini, ptr->argv[1]);
		else if (ft_strcmp(ptr->argv[0], "env") == 0)
			ft_lstprint(mini->env1, mini);
		else if (look_for_non_builtin(ptr) == 0 && (execve(ptr->argv[0], ptr->argv, envp)) < 0)
		{
			printf("Execve failed.\n");
			printf("CASE 3\n");
			exit (0);
		}
		else
			unvalid_identifier(ptr->argv[0], mini, 127);
		exit (EXIT_SUCCESS); // closes process with succes // change
	}
	else // parent process
	{
		waitpid(pid, &status, 0);
		// mini->exit = WEXITSTATUS(status); // check this
		if (piped)
		{
			close(ptr->fd[1]);
			if (!ptr->next || ptr->next->type == TYPE_BREAK)
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
	while (tmp)
	{
		printf("Goes in with argv: %s\n", tmp->argv[0]);
		tmp = ft_redir(mini, tmp);
		if (tmp == NULL)
			break ;
		if (ft_strcmp(tmp->argv[0], "$?") == 0)
			ft_printf_exit_status(mini);
		else if (ft_strcmp(tmp->argv[0], "export") == 0)
			ft_export(ptr, mini);
		else if (ft_strcmp(ptr->argv[0], "cd") == 0)
			ft_cd(ptr, mini);
		else if (ft_strcmp(ptr->argv[0], "unset") == 0)
			ft_unset(mini, ptr->argv[1]);
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
		else
			execve_commands(tmp, envp, mini);
		
		ft_reset_fds(mini);
		// system("leaks minishell");
		tmp = tmp->next;
	}
	return (0);
}
