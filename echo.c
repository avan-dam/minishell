/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 11:40:20 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/07 18:21:20 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_check_spaces(char *line)
{
    int i;
    int k;

    k = 0;
    i = 0;
    while (line[i])
    {
        if (' ' == line[i])
            k++;
        i++;
    }
    if (i == k)
        return (-1);
    return (0);
}

int    ft_echo_n(t_mini *mini)
{
    int     i;
    int     j;
    char    *temp;

    j = 0;
    if(mini->more == NULL)
        return (0);
    temp = ft_strdupp("mini->more");
    mini->flag = 1;
    i = ft_len(mini->more);
    i = i - 3;
    mini->more = ft_substrr(mini->more, 3, i);
    if (ft_check_spaces(mini->more) == -1)
        return (0);
    ft_putstr(mini->more);
    return(0);
}

int    ft_echo(t_mini *mini)
{
    // printf("mini->more[%s], mini->command [%s]\n", mini->more, mini->command);
    if (mini->more == NULL)
        return (0);
    if (ft_check_spaces(mini->more) == -1)
        return (0);
    if ((mini->more[0] == '-') && (mini->more[1] == 'n') && ((mini->more[2] == ' ') || (mini->more[2] == '\0')))
        ft_echo_n(mini);
    else
    {   
        ft_putstr(mini->more);
        ft_putchar('\n');
    }
    return (0);
}
