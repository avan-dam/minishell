/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 11:40:20 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/04 16:14:05 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libgnl.h"

int    ft_echo_n(t_mini *mini)
{
    int     i;
    int     j;
    char    *temp;

    j = 0;
    temp = ft_strdupp("mini->more");
    mini->flag = 1;
    i = ft_len(mini->more);
    i = i - 3;
    mini->more = ft_substrr(mini->more, 3, i);
    ft_putstr(mini->more);
    return(0);
}

int    ft_echo(t_mini *mini)
{
    if ((mini->more[0] == '-') && (mini->more[1] == 'n') && (mini->more[2] == ' '))
        ft_echo_n(mini);
    else
    {
        ft_putstr(mini->more);
        ft_putchar('\n');
    }
    return (0);
}
