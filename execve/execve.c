/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/24 17:14:21 by ambervandam   ########   odam.nl         */
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
	if (ft_is_builtin(ptr->av[0]) == 0 && look_for_non_builtin(ptr) == 2)
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

int	exec_cmds(t_base *tmpstart, char **envp, t_mini *mini)
{
	t_base *tmp = tmpstart;
	while (tmp)
	{
		if ((tmp == NULL) || (tmp->size == 0))
			return (0);
		tmp = ft_redir(mini, tmp);
		if (tmp == NULL)
			return (0);
		while (tmp->size == 0)
		{
			tmp = tmp->next;
			if (tmp == NULL)
				return (0);
			tmp = ft_redir(mini, tmp);
		}
		if ((tmp->type == T_PIPE || (tmp->prev && tmp->prev->type == T_PIPE))
			&& ft_is_builtin(tmp->av[0]) == 1)
			execves(tmp, envp, mini);
		else if (ft_strcmp("", tmp->av[0]) == 0)
			break ;
		else if (ft_strcmp(tmp->av[0], "exit") != 0 && ft_is_builtin(tmp->av[0]))
			exec_builtin(tmp, mini);
		else if (ft_strcmp(tmp->av[0], "exit") == 0)
		{
			if (tmp->av[1] != NULL)
			{
				if (ft_is_str_int(tmp->av[1]) == 0)
					mini->exit = 255;
				else
				{
					mini->exit = ft_atoi(tmp->av[1]);
					if (tmp->av[2] != NULL)
						mini->exit = 1;
				}
			}
			return (-1);
		}
		else if (look_for_non_builtin(tmp) == 2)
			unvalid_ident(tmp->av[0], mini, 127);
		else
			execves(tmp, envp, mini);
		ft_reset_fds(mini);
		// int i = 0;
		// while (i < tmp->size)
		// {
		// 	// printf("i in\n");
		// 	free(tmp->av[i]);
		// 	i++;
		// }
		// free(tmp->av);
		tmpstart = tmp->next;
		// free(tmp);
		tmp = tmpstart;
		// tmp = tmp->next;

	}
	// ft_baseclear(&tmpstart);
	return (0);
}
