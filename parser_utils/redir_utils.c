/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 18:51:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/12 17:59:04 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tokens_open_argv(t_base *ptr, t_mini *mini, int i)
{
	char	*temp;

	temp = check_tokens(ptr->av[i + 1], mini, 0, 6);
	if (temp != NULL && ft_strcmp(temp, "") != 0)
	{
		free(ptr->av[i + 1]);
		ptr->av[i + 1] = temp;
	}
	else
	{
		free(temp);
		ft_putstr_fd("bash: ", STDERR);
		ft_putstr_fd(ptr->av[i + 1], STDERR);
		ft_putstr_fd(": ambiguous redirect\n", STDERR);
		mini->exit = 1;
		return (-1);
	}
	return (0);
}

int	redir_error(t_mini *mini, int i, t_base *ptr)
{
	if (i == 1)
	{
		if (ptr->av[i + 1] && (numb_char(ptr->av[i + 1], '>') > 0 || (numb_char(ptr->av[i + 1], '<') > 0)))
		{
			ft_putstr_fd("bash: syntax error near ", mini->stderr);
			ft_putstr_fd("unexpected token `", mini->stderr);
			ft_putstr_fd(ptr->av[i + 1], mini->stderr);
			ft_putstr_fd("'\n", mini->stderr);
		}
		else
		// printf("ptr->av[i][0]: %c\n", ptr->av[i + 1][0]);
		{// printf("ptr->av[i]: %s\n", ptr->av[i]);
			ft_putstr_fd("bash: syntax error near ", mini->stderr);
			ft_putstr_fd("unexpected token `newline'\n", mini->stderr);
			ft_reset_fds(mini);
		}
		mini->exit = 258;
	}
	if (i == 2)
	{
		ft_putstr_fd("bash: : No such file or directory\n", mini->stderr);
		mini->exit = 1;
	}
	// if (i == 3)
	// {
	// 	printf("ptr->av[i][0]: %c\n", ptr->av[i][0]);
	// 	printf("ptr->av[i]: %s\n", ptr->av[i]);
	// 	ft_putstr_fd("bash: syntax error near ", mini->stderr);
	// 	ft_putstr_fd("unexpected token `", mini->stderr);
	// 	ft_putstr_fd(" IN HERE ", 1);
	// 	ft_putstr_fd("'\n", mini->stderr);
	// 	ft_reset_fds(mini);
	// 	mini->exit = 258;	
	// }
	return (-1);
}
