/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/04 11:04:41 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_builtin(t_base *tmp, t_mini *mini)
{
	if (ft_strcmp(tmp->av[0], "$?") == 0)
		ft_printf_exit_status(mini);
	else if (ft_strcmp(tmp->av[0], "env") == 0
		|| ft_strcmp(tmp->av[0], "/usr/bin/env") == 0)
		ft_lstprint(mini->env1, mini, 0);
	else if (ft_strcmp(tmp->av[0], "export") == 0)
		ft_export(tmp, mini);
	else if (ft_strcmp(tmp->av[0], "echo") == 0
		|| ft_strcmp(tmp->av[0], "/bin/echo") == 0)
		ft_echo(tmp, mini);
	else if ((ft_strcmp(tmp->av[0], "pwd") == 0)
		|| (ft_strcmp(tmp->av[0], "/bin/pwd") == 0))
		ft_pwd(mini);
	else if (ft_strcmp(tmp->av[0], "cd") == 0
		|| ft_strcmp(tmp->av[0], "/usr/bin/cd") == 0)
		ft_cd(tmp, mini);
	else if (ft_strcmp(tmp->av[0], "unset") == 0)
		ft_unset(mini, tmp->av[1]);
}

static void	parent_proces(pid_t pid, t_mini *mini, t_base *ptr, int piped)
{
	int			status;

	waitpid(pid, &status, 0);
	mini->exit = WEXITSTATUS(status);
	if (piped)
	{
		close(ptr->fd[1]);
		if (ptr->type != T_PIPE)
			close(ptr->fd[0]);
	}
	if (ptr->prev && ptr->prev->type == T_PIPE)
		close(ptr->prev->fd[0]);
}

static int	child_process(t_base *ptr, t_mini *mini, char **envp)
{
	if (ft_is_builtin(ptr->av[0]) == 0 && look_for_non_builtin(ptr, 1) == 2)
		unvalid_ident(ptr->av[0], mini, 127);
	if (ptr->type == T_PIPE && dup2(ptr->fd[1], STDOUT) < 0)
		return (1);
	if (ptr->prev && ptr->prev->type == T_PIPE
		&& dup2(ptr->prev->fd[0], STDIN) < 0)
		return (1);
	if (ft_strcmp(ptr->av[0], "exit") != 0
		&& ft_is_builtin(ptr->av[0]) == 1)
		exec_builtin(ptr, mini);
	else if (execve(ptr->av[0], ptr->av, envp) < 0 || !ptr->av[1])
		return (1);
	else
		unvalid_ident(ptr->av[0], mini, 127);
	return (0);
}

static void	execves(t_base *ptr, char **envp, t_mini *mini)
{
	pid_t		pid;
	int			piped;

	piped = 0;
	if (ptr->type == T_PIPE || (ptr->prev && ptr->prev->type == T_PIPE))
	{
		piped = 1;
		if (pipe(ptr->fd))
			exit(0);
	}
	pid = fork();
	if (pid < 0)
		exit(0);
	if (pid == 0)
	{
		dup2(mini->stdin, STDIN);
		dup2(mini->stdout, STDOUT);
		if (child_process(ptr, mini, envp) == 1)
			exit (EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		parent_proces(pid, mini, ptr, piped);
}

// int	exec_cmds(t_base *ptr, char **envp, t_mini *mini)
// {
// 	// t_base	*tmp;
// 	int		i;

// 	while (ptr)
// 	{
// 		if ((ptr == NULL) || (ptr->size == 0))
// 			return (0);
// 		ptr = ft_redir(mini, ptr);
// 		if (ptr == NULL)
// 			return (0);
// 		while (ptr->size == 0)
// 		{
// 			ptr = ptr->next;
// 			if (ptr == NULL)
// 				return (0);
// 			ptr = ft_redir(mini, ptr);
// 		}
// 		if ((ptr->type == T_PIPE || (ptr->prev && ptr->prev->type == T_PIPE))
// 			&& ft_is_builtin(ptr->av[0]) == 1)
// 			execves(ptr, envp, mini);
// 		else if (ft_strcmp("", ptr->av[0]) == 0)
// 			break ;
// 		else if (ft_strcmp(ptr->av[0], "exit") != 0 && ft_is_builtin(ptr->av[0]))
// 			exec_builtin(ptr, mini);
// 		else if (ft_strcmp(ptr->av[0], "exit") == 0)
// 		{
// 			if (ptr->av[1] != NULL)
// 			{
// 				if (ft_is_str_int(ptr->av[1]) == 0)
// 					mini->exit = 255;
// 				else
// 				{
// 					mini->exit = ft_atoi(ptr->av[1]);
// 					if (ptr->av[2] != NULL)
// 						mini->exit = 1;
// 				}
// 			}
// 			return (-1);
// 		}
// 		else if (look_for_non_builtin(ptr) == 2)
// 			unvalid_ident(ptr->av[0], mini, 127);
// 		else
// 			execves(ptr, envp, mini);
// 		ft_reset_fds(mini);
// 		i = 0;
// 		while (i <= ptr->size)
// 		{
// 			free(ptr->av[i]);
// 			i++;
// 		}
// 		free(ptr->av);
// 		ptr = ptr->next;
// 	}
// 	return (0);
// }
int	exec_cmds(t_base *ptr, char **envp, t_mini *mini)
{
	if ((ptr == NULL) || (ptr->size == 0))
		return (0);
	ptr = ft_redir(mini, ptr);
	if (ptr == NULL)
		return (0);
	while (ptr->size == 0)
	{
<<<<<<< HEAD
		tmp = ptr->next;
		ptr = ft_redir(mini, ptr);
		if (ptr == NULL || ptr->size == 0)
			return (0);
		while (ptr->size == 0)
		{
			ptr = ptr->next;
			if (ptr == NULL)
				return (0);
			ptr = ft_redir(mini, ptr);
		}
		if ((ptr->type == T_PIPE || (ptr->prev && ptr->prev->type == T_PIPE)))
			// && ft_is_builtin(ptr->av[0]) == 1)
		{
			// printf("GOES IN PIPES\n");
			execves(ptr, envp, mini);
			// printf("COMES OUTs PIPES\n");
		}
		// else if (ft_strcmp("", ptr->av[0]) == 0)
		// 	break ;
		else if (ft_strcmp(ptr->av[0], "exit") != 0 && ft_is_builtin(ptr->av[0]) == 1)
			exec_builtin(ptr, mini);
		else if (ft_strcmp(ptr->av[0], "exit") == 0)
=======
		ptr = ptr->next;
		if (ptr == NULL)
			return (0);
		ptr = ft_redir(mini, ptr);
	}
	if ((ptr->type == T_PIPE || (ptr->prev && ptr->prev->type == T_PIPE))
		&& ft_is_builtin(ptr->av[0]) == 1)
		execves(ptr, envp, mini);
	else if (ft_strcmp("", ptr->av[0]) == 0)
		return (0) ;
	else if (ft_strcmp(ptr->av[0], "exit") != 0 && ft_is_builtin(ptr->av[0]))
		exec_builtin(ptr, mini);
	else if (ft_strcmp(ptr->av[0], "exit") == 0)
	{
		if (ptr->av[1] != NULL)
>>>>>>> amberbranch
		{
			if (ft_is_str_int(ptr->av[1]) == 0)
				mini->exit = 255;
			else
			{
				mini->exit = ft_atoi(ptr->av[1]);
				if (ptr->av[2] != NULL)
					mini->exit = 1;
			}
		}
<<<<<<< HEAD
		else if (look_for_non_builtin(ptr) == 2)
			unvalid_ident(ptr->av[0], mini, 127);
		else
			execves(ptr, envp, mini);
		ft_reset_fds(mini);
		i = 0;
		while (i <= ptr->size)
		{
			// printf("value of ptr->av[i]: %s\n", ptr->av[i]);
			free(ptr->av[i]);
			i++;
		}
		free(ptr->av);
		free(ptr);
		ptr = tmp;
=======
		return (-1);
>>>>>>> amberbranch
	}
	else if (look_for_non_builtin(ptr, 0) == 2)
		unvalid_ident(ptr->av[0], mini, 127);
	else
		execves(ptr, envp, mini);
	ft_reset_fds(mini);
	return (0);
}
