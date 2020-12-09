/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/08 17:15:57 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_check_var1_already_in_list(char *var1, char *var2, t_mini *mini)
{
    t_list *tlist;

    tlist = mini->tlist;
    while (tlist != NULL)
	{
        if(tlist->var1)
        {
            if (ft_strcmp(tlist->var1, var1) == 0)
            {
                tlist->var2 = var2;
                mini->tlist = tlist;
    	        return (1);   
            }
        }
        tlist = tlist->next;
	}
    return (0);
}

static int ft_strrch_equal(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '=')
        {
            return (i);
        }
		i++;
    }
    return (-1);
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


static int  ft_export_more(t_mini *mini, char *line)
{
    t_list  *adding;
    int     i;
    int     j;
    char	*var1;
    char	*var2;

    j = 0;
    if ((i = ft_strrch_equal(line)) == -1)
        return (0);
    if (line[i - 1] == ' ' || line[i + 1] == ' ')
        return (0);
    j = ft_find_start_var(line, i, 0);
    var1 = ft_substr(line, j, i - j);
	j = ft_find_start_var(line, i, 1);
	var2 = ft_substr(line, i + 1, j - i - 1);
	if (ft_check_var1_already_in_list(var1, var2, mini) == 1)
    {
        ft_lstprint(mini->tlist);
        return (1);
    }
    adding = ft_lstnew(var1, var2);
    ft_lstadd_back(&mini->tlist, adding);
    return (1);
}
int    ft_export(t_mini *mini)
{
    int     i;
    int     j;
    char    *word;

    i = 0;
    // printf("in unset fucntion mini->more%s\n", mini->more);
    if (mini->more == NULL)
		return (0);
	while(mini->more[i] != '\0')
    {
        j = i;
        while(mini->more[i] != ' ' && mini->more[i] != '\0')
			i++;
		if (mini->more[i] != '\0')
		    i++;
		if (i == (int)ft_strlen(mini->more))
	        word = ft_substr(mini->more, j, i - j);
		else
	        word = ft_substr(mini->more, j, i - j - 1);
        // printf("word:%s\n", word);
		ft_export_more(mini, word);
    }
    ft_lstprint(mini->tlist);
    return (0);
}


// int    ft_export(t_mini *mini)
// {
//     t_list  *adding;
//     int     i;
//     int     j;
//     char	*var1;
//     char	*var2;

//     j = 0;
//     if ((i = ft_strrch_equal(mini->more)) == -1)
//         return (0);
//     if (mini->more[i - 1] == ' ' || mini->more[i + 1] == ' ')
//         return (0);
//     j = ft_find_start_var(mini->more, i, 0);
//     var1 = ft_substr(mini->more, j, i - j);
// 	j = ft_find_start_var(mini->more, i, 1);
// 	var2 = ft_substr(mini->more, i + 1, j - i - 1);
// 	if (ft_check_var1_already_in_list(var1, var2, mini) == 1)
//     {
//         ft_lstprint(mini->tlist);
//         return (1);
//     }
//     adding = ft_lstnew(var1, var2);
//     ft_lstadd_back(&mini->tlist, adding);
//     ft_lstprint(mini->tlist);
//     return (1);
// }
