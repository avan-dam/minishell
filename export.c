/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/07 21:22:15 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_check_var1_already_in_list(char *var1, char *var2, t_mini *mini)
{
    t_list *tlist;

    tlist = mini->tlist;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, var1) == 0)
        {
            tlist->var2 = var2;
            mini->tlist = tlist;
    	    return (1);   
        }
        tlist = tlist->next;
	}
    return (0);
}

static int ft_check_equals(char *line)
{
    int i;
    int j;
	int k;

    j = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == '=')
        {
			if (k == 0)
				k = i;
		    j++;
		}
		i++;
    }
    if (j == 0 || j > 2 || k == 0)
        return (-1);
    return (k);
}

static int  ft_find_start_var(char *more, int i, int position)
{
    int j;
    int k;

    k = 0;
    j = 0;
    if (position == 0)
    {
    	while (j < i)
    	{
            if (more[j] == ' ')
                k = j;
            j++;
        }
        if (k != 0)
            k++;
		return (k);
    }
	if (position == 1)
	{
		while (more[i] != '\0')
		{
			if (more[i] == ' ')
				return (i);
			i++;
		}
		return (i);
	}
    return (-1);
}

int    ft_export(t_mini *mini)
{
    t_list  *adding;
    int     i;
    int     j;
    char	*var1;
    char	*var2;

    j = 0;
    if ((i = ft_check_equals(mini->more)) == -1)
        return (0);
    if (mini->more[i - 1] == ' ' || mini->more[i + 1] == ' ')
        return (0);
    j = ft_find_start_var(mini->more, i, 0);
    var1 = ft_substr(mini->more, j, i - j);
	j = ft_find_start_var(mini->more, i, 1);
	var2 = ft_substr(mini->more, i + 1, j - i - 1);
	if (ft_check_var1_already_in_list(var1, var2, mini) == 1)
    {
        ft_lstprint(mini->tlist);
        return (1);
    }
    adding = ft_lstnew(var1, var2);
    ft_lstadd_back(&mini->tlist, adding);
    ft_lstprint(mini->tlist);
    return (1);
}
