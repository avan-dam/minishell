/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/08 15:51:52 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *line_replaced(char *start, char *newvar, char *end)
{
    char *temp;
    char *newline;
    
    // printf("char *start[%s], char *newvar[%s], t_mini *end[%s]\n", start, newvar, end);
    temp = ft_strjoin(start, newvar);
    newline = ft_strjoin(temp, end);
    // printf("my newline is : [%s]", newline);
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
    return (ft_strdup(" "));
}

static char	*ft_find_dolla(char *line, int i, t_mini *mini)
{
	int		j;
    char    *start;
	char	*oldvar;
    char    *newvar;
    char    *end;

	j = i;
	while (line[i] != '\0' && line[i] != ' ')
		i++;
    oldvar = ft_substr(line, j + 1, i - j - 1);
    if (j == 0)
        start = ft_substr(line, 1, j);
    else
        start = ft_substr(line, 0, j - 1);
    end = ft_substr(line, i + 1, ft_strlen(line) - i);
    if (mini->tlist == NULL)
    {
        // printf("am i printing");
    	return (line_replaced(start, ft_strdup(" "), end));   
    }
    newvar = ft_check_var_tlist(mini, oldvar);
    if (ft_strcmp(end, "") != 0)
        newvar = ft_strjoin(newvar, " ");
    // printf("newvar[%s]\n", newvar);
    return (line_replaced(start, newvar, end));
}

char		*ft_check_dolla(char *line, t_mini *mini)
{
	int     i;
    char    *temp;

    i = 1;
    if (line == NULL)
        return (line);
    temp = ft_strdup(line);
	while (line[i] != '\0')
	{
        // printf("line[%s] line[i] %c\n", line, line[i]);
		if (line[i] == '$')
        {
			line = ft_find_dolla(temp, i, mini);
            temp = ft_strdup(line);
            if (line[i] != '\0')
                i++;
        }
        if (line[i] != '\0')
            i++;
	}
    return (line);
}
