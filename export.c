/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/06 15:46:19 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_export(t_mini *mini)
{
    t_list  *adding;
    int     i;
    char	*var1;
    char	*var2;

    i = ft_strchr_numb(mini->more, '=');
    if (i == 0)
        return (0);
    if (mini->more[i - 1] == ' ' || mini->more[i + 1] == ' ')
        return (0);
    var1 = ft_substrr(mini->more, 0, i);
    var2 = ft_substrr(mini->more, i + 1, ft_len(mini->more) - i - 1);
    // check if var1 already in tlist and change var2 accordingly then
    adding = ft_lstnew(var1, var2);
    ft_lstadd_back(&mini->tlist, adding);
    ft_lstprint(mini->tlist);
    return (1);
}

static char *ft_replace_env(t_mini *mini, char *envvar)
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
        if (lst->var1 == envvar)
            return (lst->var2);
        lst = lst->next;
	}
    return (NULL);
}

static void	ft_find_env(t_mini *mini, int i)
{
	int		j;
	char	*envvar

	j = i;
	while (mini->more[i] != '\0' && ' ')
		i++;
    envvar = ft_substrr(mini->more, j, i - j);
	if (ft_replace_env(mini, envvar) != NULL)
        
}

int		ft_check_env(t_mini *mini)
{
	int i;

	if mini->more[0] == '$'
		ft_find_env(mini, 0);
	while (mini->more[i] != '\0')
	{
		if (mini->more[i] == '$')
			ft_find_env(mini, i);
	}
}
