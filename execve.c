/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/07 13:21:53 by ambervandam   ########   odam.nl         */
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
		// printf("value of argv: %s\n", ptr->argv[0]);
		dup2(mini->stdin, STDIN);
		dup2(mini->stdout, STDOUT);
		// printf("GOES IN CHILD PROCESS, argv: %s\n", ptr->argv[0]);
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
			ft_lstprint(mini->env1, mini);
		// add in exit?
		else if (execve(ptr->argv[0], ptr->argv, envp) < 0) // I THINK WE NEED A CALL TO LOOK FOR BUILTIN FUNCTION CALL OR 
		{													// SOMETHING OTHERWISE NEVER GOES INTO Unvalid_identifiers below
			// printf("GOES IN HERE execve\n");
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
				close(ptr->fd[0]);
		}
		if (ptr->prev && ptr->prev->type == TYPE_PIPE)
			close(ptr->prev->fd[0]);
	}
}

int			exec_cmds(t_base *ptr, char **envp, t_mini *mini)
{
	t_base	*tmp;

	tmp = ptr;
	// printf("in exc_smds\n");
	while (tmp)
	{
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
		// I COMMENTED OUT LOOK FOR NON_BUILTIN FUNCTIONS BECUASE WHEN IT IS NOT COMMENTED OUT GRIFFINS TESTER STOPS IN THE MIDDLE
		// look_for_non_builtin(tmp); // changes the execve commands i.e. ls to /bin/ls
		if ((tmp->type == TYPE_PIPE  || (tmp->prev && tmp->prev->type == TYPE_PIPE)) && ft_is_builtin_command(ptr->argv[0]) == 1)
		{
			// printf("goes in here ");
			execve_commands(tmp, envp, mini);
		}
		else if (ft_strcmp(tmp->argv[0], "$?") == 0)
		{
			// printf("GOES IN HERE\n");
			ft_printf_exit_status(mini);
		}
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
			// ft_t_baseclear(&ptr); // check this is only place needed 
			return (-1); // maybe tmp can also
		}
		else
		{	
			// printf("in here tmp->argv[0][%s]\n", tmp->argv[0]); // HERE value of tmp->argv[0] is wrong because of first call
			execve_commands(tmp, envp, mini);					// to execve_commands not sure why tho
		}
		ft_reset_fds(mini);
		tmp = tmp->next;
	}
	// printf("out of excves\n");
	// free(ptr);
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