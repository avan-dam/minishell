/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/07 10:14:29 by ambervandam   ########   odam.nl         */
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

static void ft_replace_env(char *var1, char *var2)
{
    printf("I am now in my replace function wanting to replace [%s] with [%s]\n", var1, var2);
    (void)var1;
    (void)var2;
}

static char	*ft_find_env(char *replace, int i, t_mini *mini)
{
    printf("in ft_find_env\n");
	int		j;
	char	*envvar;
    t_list  *lst;

    lst = mini->tlist;
	j = i;
	while (replace[i] != '\0' && replace[i] != ' ')
		i++;
    envvar = ft_substrr(replace, j, i - j);
    printf("envvar:%s", envvar);
	if (lst == NULL)
		return (envvar);
	while (lst != NULL)
	{
        if (lst->var1 == envvar)
        {
            ft_replace_env(envvar, lst->var2);
            return (envvar);
        }
        lst = lst->next;
	}
    return (envvar);
        
}

int		ft_check_env(t_mini *mini)
{
	int i;

    i = 0;
    printf("in ft_check_env\n");
	if (mini->command[0] == '$')
		mini->command = ft_find_env(mini->command, 0, mini);
	while (mini->command[i] != '\0')
	{
		if (mini->command[i] == '$')
			mini->command = ft_find_env(mini->command, i, mini);
	}
	if (mini->more[0] == '$')
		mini->more = ft_find_env(mini->more, 0, mini);
	while (mini->more[i] != '\0')
	{
		if (mini->more[i] == '$')
			mini->more = ft_find_env(mini->more, i, mini);
	}
    return (0);
}
