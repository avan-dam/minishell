/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:49:11 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/24 16:58:14 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_var_with_extra_backslash(char *tmpvar2, t_mini *mini)
{
	int	i;

	if (!tmpvar2)
		return ;
	i = 0;
	while (tmpvar2[i] && tmpvar2[i] != ' ')
	{
		if (tmpvar2[i] == '\\')
			ft_putchar_fd('\\', mini->stdout);
		ft_putchar_fd(tmpvar2[i], mini->stdout);
		i++;
	}
}

void	ft_lstprint(t_list *lst, t_mini *mini)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", mini->stdout);
		ft_putstr_fd(tmp->var1, mini->stdout);
		if (tmp->var2 != NULL)
			ft_putstr_fd("=", mini->stdout);
		if (tmp->var2 != NULL)
			ft_putstr_fd("\"", mini->stdout);
		if (tmp->var2 != NULL)
			ft_put_var_with_extra_backslash(tmp->var2, mini);
		if (tmp->var2 != NULL)
			ft_putstr_fd("\"", mini->stdout);
		ft_putstr_fd("\n", mini->stdout);
		tmp = tmp->next;
	}
}
