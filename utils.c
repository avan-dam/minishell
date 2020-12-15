/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 12:06:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/09 12:26:16 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int i;
	
	if (s == NULL)
		return ;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		// so that if you type \ once nothing happens only 
		// if twice in a row
		if (s[i] == 92)
			i++;
		write(1, &s[i], 1);
		i++;
	}
}

int		unvalid_identifier(char *error)
{
    ft_putstr("bash: export: '");
    ft_putstr(error);
    ft_putstr("': not a valid identifier\n");
	return (0);
}

int ft_strrch_numb(char *line, char c)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == c)
        {
            return (i);
        }
		i++;
    }
    return (-1);
}

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

int  ft_split_into_tlist(t_mini *mini, char *line, int j)
{
    t_list  *newnode;
    int     i;
    char	*var1;
    char	*var2;

    if ((i = ft_strrch_numb(line, '=')) == -1)
        return (0);
    if (line[i - 1] == ' ' || line[i + 1] == ' ')
        return (0);
    var1 = ft_substr(line, 0, i);
	var2 = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	if (j == 1)
	{
		if (ft_check_var1_already_in_list(var1, var2, mini) == 1)
    	    return (1);
	}
	newnode = ft_lstnew(var1, var2);
    ft_lstadd_back(&mini->tlist, newnode);
    return (1);
}
