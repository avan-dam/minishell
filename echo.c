/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 11:40:20 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/10 00:51:15 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_check_n(t_mini *mini)
{
    int i;
    int j;
    int l;

    i = 0;
    j = 0;
    l = 0;
    while (mini->more[i] != '\0')
    {
        l++;
        j = i;
        if (mini->more[i] != '-')
            return (-1);
        i++;
        while (mini->more[i] == 'n')
            i++;
		if (mini->more[i] == '\0')
			return (1);
        if (mini->more[i] != ' ')
        {
			printf("j = %i so mini->more[j] is %c and length is %lu\n", j, mini->more[j], ft_strlen(mini->more) - j);
            mini->more = ft_substr(mini->more, j, ft_strlen(mini->more) - j);
            return (2);
        }
        i++;
    }
    return (0);
}

int    ft_echo_n(t_mini *mini)
{
    int     i;
    int     j;

    if(mini->more == NULL)
        return (0);
	j = ft_check_n(mini);
    if (j == 1)
        return (j);
    mini->flag = 1;
	if (j != 2)
	{
	    i = ft_len(mini->more);
    	i = i - 3;
    	mini->more = ft_substrr(mini->more, 3, i);
	}
	j = 0;
    mini->more = ft_strtrim(mini->more, " ");
    ft_putstr(mini->more);
    return(0);
}

static int  ft_check_empty(t_mini *mini)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (ft_strcmp(mini->more, "") == 0)
        return (1);
    while (mini->more[i] != '\0')
    {
        if (mini->more[i] == ' ')
            j++;
        i++;
    }
    if (i == j)
        return (1);
    return (0);
}

int    ft_echo(t_mini *mini)
{
	// ft_lstprint(mini->tlist);
	// printf("mini->more = [%s]\n", mini->more);
    if (mini->more == NULL)
    {
        ft_putchar('\n');
        return (0);
    }
    if ((ft_check_empty(mini) == 1) && (mini->flag == 1))
        ft_putchar('\n');
    else if ((mini->more[0] == '-') && (mini->more[1] == 'n') && ((mini->more[2] == ' ') || (mini->more[2] == '\0') || (mini->more[2] == 'n')))
    {
        if (ft_echo_n(mini) == 2)
        {
            mini->more = ft_strtrim(mini->more, " ");
            ft_putstr(mini->more);
            ft_putchar('\n');
        }
    }
    else
    {
            mini->more = ft_strtrim(mini->more, " ");
            ft_putstr(mini->more);
            ft_putchar('\n');
    }
    return (0);
}
