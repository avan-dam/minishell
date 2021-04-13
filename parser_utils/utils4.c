/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 16:00:38 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/13 11:08:00 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_error(t_mini *mini)
{
	ft_putstr_fd("minishell does not ", mini->stderr);
	ft_putstr_fd("support multiline quotes\n", mini->stderr);
	mini->exit = 2;
	return (-1);
}

int	send_to_unvalid(t_mini *mini, int j, char *s)
{
	if (j == 2)
	{	
		if (s && ft_strcmp(s, "<<") == 0)
		{
			ft_putstr_fd("bash: syntax error near ", mini->stderr);
			ft_putstr_fd("unexpected token `newline'\n", mini->stderr);
			mini->exit = 258;
			return (-1);
		}
		return (ft_print_error(mini));
	}
	if (j > 3)
		return (unvalid_ident("<", mini, 258));
	return (0);
}

int	send_to_unvalid_one(int j, char *s, int k, t_mini *mini)
{
	if (j > 1 && s[k] == '<')
		return (unvalid_ident("<", mini, 258));
	if (j > 2)
		return (unvalid_ident(">", mini, 258));
	return (0);
}

void	free_all(char *tmp2, char *tmp)
{
	free(tmp2);
	free(tmp);
}

int	dolla_while_checker(char *s, int i)
{
	if (s[i] != '\0' && s[i] != '$' && s[i] != '-' && s[i] != '=' && s[i]
		!= ' ' && s[i] != '\'' && s[i] != '"' && s[i] != '\\' && s[i] != '/'
		&& s[i] != '%' && s[i] != '*')
		return (1);
	return (0);
}
