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

// static int  ft_check_spaces(char *line)
// {
//     int i;
//     int k;

//     k = 0;
//     i = 0;
//     while (line[i])
//     {
//         if (' ' == line[i])
//             k++;
//         i++;
//     }
//     if (i == k)
//         return (-1);
//     return (0);
// }

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
    // if (ft_check_spaces(mini->more) == -1)
    //     return (0);
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


// static int  ft_check_echo_n(t_mini *mini)
// {
//     int i;
//     i = 0;
//     if ((mini->more[0] != '-') || (mini->more[1] != 'n'))
//         return (-1)
//     while(mini->more[i + 1] != '\0' && )
//     {
//         if((mini->more[i] != '-') && (mini->more[i] != 'n' && mini->more[i] != ' ') && mini->more[i] != '\0')
//             return (-1);
//         if (mini->more[i] == '-' && mini->more != 'n')
//             return (-1);
//         if(mini->more[i])
//     }
// }

int    ft_echo(t_mini *mini)
{
    if (mini->more == NULL)
    {
        ft_putchar('\n');
        return (0);
    }
    if ((ft_check_empty(mini) == 1) && (mini->flag == 1))
        ft_putchar('\n');
    // if (ft_check_spaces(mini->more) == -1)
    //     return (0);
    if ((mini->more[0] == '-') && (mini->more[1] == 'n') && ((mini->more[2] == ' ') || (mini->more[2] == '\0')))
        ft_echo_n(mini);
    // if (ft_check_echo_n(mini) != -1)
    //     return(ft_echo_n(mini));
    mini->more = ft_strtrim(mini->more, " ");
    ft_putstr(mini->more);
    ft_putchar('\n');
    return (0);
}
