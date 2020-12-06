/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/04 19:17:14 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libgnl.h"

int    ft_export(t_mini *mini)
{
    t_list  *adding;
    int i;
    char *var1;
    char *var2;

    i = ft_strchr_numb(mini->more, '=');
    if (i == 0)
        return (0);
    var1 = ft_substrr(mini->more, 0, i);
    var2 = ft_substrr(mini->more, i + 1, ft_len(mini->more) - i - 1);
    adding = ft_lstnew(var1, var2);
    ft_lstadd_back(&mini->tlist, adding);
    ft_lstprint(mini->tlist);
    return (1);
}