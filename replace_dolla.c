/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/10 00:34:43 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *line_replaced(char *start, char *newvar, char *end)
{
    char *temp;
    char *newline;
    
    temp = ft_strjoin(start, newvar);
    newline = ft_strjoin(temp, end);
    printf("newline is %s\n", newline);
    return (newline);
}

static char *ft_check_var_tlist(t_mini *mini, char *oldvar)
{
    char    *newvar;
    t_list  *tlist;
    
    tlist = mini->tlist;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, oldvar) == 0)
        {
            newvar = ft_strjoin(" ", tlist->var2);
    	    return (newvar);   
        }
        tlist = tlist->next;
	}
    mini->flag = 1;
    return (ft_strdup(""));
}

static char	*ft_find_dolla(char *line, int i, t_mini *mini)
{
	int		j;
    char    *start;
	char	*oldvar;
    char    *newvar;
    char    *end;

	i++;
    j = i;
    while (line[i] != '\0' && line[i] != '#' && line[i] != '$' && line[i] != '-' && line[i] != '=' && line[i] != ' ')
        i++;
    // printf("line is [%s] j is %d and i is %d \n", line, j, i);
    oldvar = ft_substr(line, j, i - j);
    start = ft_substr(line, 0, j - 2);
    end = ft_substr(line, i, ft_strlen(line) - i);
    newvar = ft_check_var_tlist(mini, oldvar);
    printf("oldvar[%s] newvar[%s] start[%s] end[%s]\n", oldvar, newvar, start, end);
    return (line_replaced(start, newvar, end));
}

char		*ft_check_dolla(char *line, t_mini *mini)
{
	int     i;

    i = 0;
    if (line == NULL)
        return (line);
	while (line[i + 1] != '\0')
	{
        if (line[i] == '$')
        {
            if ((line[i + 1] != '/') && (line[i + 1] != 92) && (line[i + 1] != '\0'))
                line = ft_find_dolla(line, i, mini);
            else
                i = i + 2;
        }
        if (line[i] != '\0' && line[i] != '$')
            i++;
	}
    return (line);
}
