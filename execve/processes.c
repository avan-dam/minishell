/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 23:29:14 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/02 00:00:04 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_proces(pid_t pid, t_mini *mini, t_base *ptr, int piped)
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

static void	child_process_more(t_mini *mini, char **envp)
{
	mini->shell_level++;
	ft_unset(mini, "SHLVL");
	ft_add_env("SHLVL", ft_itoa(mini->shell_level), mini);
	handle_line(1, mini, envp);
}

int	child_process(t_base *ptr, t_mini *mini, char **envp)
{
	if (ft_strcmp(ptr->av[0], "./minishell") == 0)
		child_process_more(mini, envp);
	// if (ft_strcmp(ptr->av[0], "/usr/bin/gcc") != 0
	// 	&& ft_is_builtin(ptr->av[0]) == 0
	// 	&& look_for_non_builtin(ptr, 1, mini) == 2 && (ptr->av[0][0] != '.'
	// 		&& ptr->av[0][1] != '/'))
	// {
	// 	unvalid_ident(ptr->av[0], mini, 127);
	// }
	if (look_for_non_builtin(ptr, 1, mini) == -1
		&& execve(ptr->av[0], ptr->av, envp) < 0)
	{
		// unvalid_ident(ptr->av[0], mini, 127); // return statemtn?
		return (1);
	}
	if (look_for_non_builtin(ptr, 1, mini) == 2
		&& execve(ptr->av[0], ptr->av, envp) < 0)
	{
		// unvalid_ident(ptr->av[0], mini, 127);
		return (1);
	}
	if (ft_strcmp(ptr->av[0], "exit") == 0)
    {
	    sort_exit_statement(ptr, mini, 0);
		return (0);
	}
	if (ptr->type == T_PIPE && dup2(ptr->fd[1], STDOUT) < 0)
		return (1);
	if (ptr->prev && ptr->prev->type == T_PIPE
		&& dup2(ptr->prev->fd[0], STDIN) < 0)
		return (1);
	if (ft_strcmp(ptr->av[0], "exit") != 0 && ft_is_builtin(ptr->av[0]) == 1)
		exec_builtin(ptr, mini);
	else if (execve(ptr->av[0], ptr->av, envp) < 0 || !ptr->av[1])
	{
		printf("goes in\n");
		return (1);
	}
	else
		unvalid_ident(ptr->av[0], mini, 127);
	return (0);
}

// #include <stdio.h>


// 	if (ft_exit_check(ptr, mini) == 0)
// 		return (0);

// 	// else if (look_for_non_builtin(ptr, 1, mini) == -1
// 	// 	&& execve(ptr->av[0], ptr->av, envp) < 0)
// 	// 	unvalid_ident(ptr->av[0], mini, 127);
// 	// else if (look_for_non_builtin(ptr, 1, mini) == 2
// 	// 	&& execve(ptr->av[0], ptr->av, envp) < 0)
// 	// 	unvalid_ident(ptr->av[0], mini, 127);


