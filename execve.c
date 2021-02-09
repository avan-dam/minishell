/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/09 12:15:11 by salbregh      ########   odam.nl         */
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
		// printf("in with [%s]\n", ptr->argv[0]);
		dup2(mini->stdin, STDIN);
		dup2(mini->stdout, STDOUT);
		if (ft_is_builtin_command(ptr->argv[0]) == 0 && look_for_non_builtin(ptr) == 2)
			unvalid_identifier(ptr->argv[0], mini, 127);
		if (ptr->type == TYPE_PIPE && dup2(ptr->fd[1], STDOUT) < 0)
			exit (0); // change
		if (ptr->prev && ptr->prev->type == TYPE_PIPE && dup2(ptr->prev->fd[0], STDIN) < 0)
			exit (0);
		if ((ft_strcmp(ptr->argv[0], "echo")) == 0 || (ft_strcmp(ptr->argv[0], "/bin/echo") == 0) || (ft_strcmp(ptr->argv[0], "Echo") == 0))
			ft_echo(ptr, mini);
		else if ((ft_strcmp(ptr->argv[0], "pwd") == 0) || (ft_strcmp(ptr->argv[0], "/bin/pwd") == 0))
			ft_pwd(mini);
		else if ((ft_strcmp(ptr->argv[0], "cd") == 0) || (ft_strcmp(ptr->argv[0], "/usr/bin/cd") == 0))
			ft_cd(ptr, mini);
		else if (ft_strcmp(ptr->argv[0], "export") == 0)
			ft_export(ptr, mini);
		else if (ft_strcmp(ptr->argv[0], "unset") == 0)
			ft_unset(mini, ptr->argv[1]);
		else if (ft_strcmp(ptr->argv[0], "env") == 0 || ft_strcmp(ptr->argv[0], "/usr/bin/env") == 0)
			ft_lstprint(mini->env1, mini, 0);
		else if (execve(ptr->argv[0], ptr->argv, envp) < 0 || !ptr->argv[1])
			exit (1);
		else
			unvalid_identifier(ptr->argv[0], mini, 127);
		exit (EXIT_SUCCESS); // closes process with succes // change
	}
	else // parent process
	{
		waitpid(pid, &status, 0);
		mini->exit = WEXITSTATUS(status); // check this
		if (piped)
		{
			close(ptr->fd[1]); // COMMENTING THE BELOW OUT IS WHAT FIXED GRIFFINS TESTER
			// if (!ptr->next || ptr->next->type == TYPE_BREAK)
				// close(ptr->fd[0]);
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
		if ((tmp == NULL) || (tmp->size == 0))
			return (0) ;
		tmp = ft_redir(mini, tmp);
		if (tmp == NULL)
			return (0) ; // OR RETURN? // this is if error opening file										// should below be ptr or tmp?
		while (tmp->size == 0)
		{	
			tmp = tmp->next;
			if (tmp == NULL)
				return (0) ;
			tmp = ft_redir(mini, tmp);
		}
		if ((tmp->type == TYPE_PIPE  || (tmp->prev && tmp->prev->type == TYPE_PIPE)) && ft_is_builtin_command(tmp->argv[0]) == 1)
			execve_commands(tmp, envp, mini);
		else if (ft_strcmp(tmp->argv[0], "$?") == 0)
			ft_printf_exit_status(mini);
		else if (ft_strcmp(tmp->argv[0], "export") == 0)
			ft_export(tmp, mini);
		else if (ft_strcmp(tmp->argv[0], "echo") == 0 || ft_strcmp(tmp->argv[0], "/bin/echo") == 0)
			ft_echo(tmp, mini);
		else if ((ft_strcmp(tmp->argv[0], "pwd") == 0) || (ft_strcmp(tmp->argv[0], "/bin/pwd") == 0))
			ft_pwd(mini);
		else if (ft_strcmp(tmp->argv[0], "cd") == 0 || ft_strcmp(tmp->argv[0], "/usr/bin/cd") == 0)
			ft_cd(tmp, mini);
		else if (ft_strcmp(tmp->argv[0], "unset") == 0)
			ft_unset(mini, tmp->argv[1]);
		else if (ft_strcmp(tmp->argv[0], "exit") == 0)
		{
			if (tmp->argv[1] != NULL)
			{	
				mini->exit = ft_atoi(tmp->argv[1]);
				if (tmp->argv[2] != NULL)
					mini->exit = 1;
			}
			return (-1); // maybe tmp can also
		}
		else
		{	
			if (look_for_non_builtin(tmp) == 2) // RIGHT NOW DOES TO RECOGNISE CAT AND GREP
			{
				if (ft_strcmp("", tmp->argv[0]) == 0)
					break ;
				// printf("tmp->argv[0][%s]\n", tmp->argv[0]);
				unvalid_identifier(tmp->argv[0], mini, 127);
			}
			else
				execve_commands(tmp, envp, mini);
		}
		ft_reset_fds(mini);
		tmp = tmp->next;
	}
	return (0);
}

//UNVALID IDENTIFIER NOT WORKING properly

	// 	t_base *tmpp = ptr;
	// while(tmpp)
	// {
	// 	printf("AFTEr REDIR Argument HERE in list: tmpp->size%d\n", tmpp->size);
	// 	for (int k = 0; k < tmpp->size; k++)
	// 		printf("the argument: %s\n", tmpp->argv[k]);
	// 	printf("TYPE: %d\n", tmpp->type);
	// 	printf("SIZE: %d\n", tmpp->size);
	// 	printf("end of argument in list\n\n");
	// 	tmpp = tmpp->next;
	// }