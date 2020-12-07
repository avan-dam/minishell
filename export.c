/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/06 16:14:23 by ambervandam   ########   odam.nl         */
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

static void ft_replace_env(t_mini *mini, char *var1, char *var2)
{
    printf("I am now in my replace function wanting to replace [%s] with [%s]\n", var1, var2);
    (void)mini;
    (void)var1;
    (void)var2;
}

static void	ft_find_env(t_mini *mini, int i)
{
    printf("in ft_find_env\n");
	int		j;
	char	*envvar;
    t_list  *lst;

    lst = mini->tlist;
	j = i;
	while (mini->more[i] != '\0' && mini->more[i] != ' ')
		i++;
    envvar = ft_substrr(mini->more, j, i - j);
	ft_replace_env(mini, envvar, lst->var2);
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
        if (lst->var1 == envvar)
        {
            ft_replace_env(mini, envvar, lst->var2);
            return ;
        }
        lst = lst->next;
	}
    return ;
        
}

int		ft_check_env(t_mini *mini)
{
	int i;

    i = 0;
    printf("in ft_check_env\n");
	if (mini->more[0] == '$')
		ft_find_env(mini, 0);
	while (mini->more[i] != '\0')
	{
		if (mini->more[i] == '$')
			ft_find_env(mini, i);
	}
    return (0);
}
