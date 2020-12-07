/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/07 11:51:50 by ambervandam   ########   odam.nl         */
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

int    ft_export(t_mini *mini)
{
    t_list  *adding;
    int     i;
    char	*var1;
    char	*var2;

    i = ft_strchr_numb(mini->more, '=');
    if (i == 0)
        return (0);
    if (mini->more[i - 1] == ' ' || mini->more[i + 1] == ' ')
        return (0);
    var1 = ft_substrr(mini->more, 0, i);
    var2 = ft_substrr(mini->more, i + 1, ft_len(mini->more) - i - 1);
    if (ft_check_var1_already_in_list(var1, var2, mini) == 1)
    {
        printf("here\n");
        ft_lstprint(mini->tlist);
        return (1);
    }
    printf("there\n");
    adding = ft_lstnew(var1, var2);
    ft_lstadd_back(&mini->tlist, adding);
    ft_lstprint(mini->tlist);
    return (1);
}

static char *line_replaced(char *start, char *newvar, char *end)
{
    char *temp;
    char *newline;
    
    printf("char *start[%s], char *newvar[%s], t_mini *end[%s]\n", start, newvar, end);
    temp = ft_strjoin(start, newvar);
    newline = ft_strjoin(temp, end);
    printf("my newline is : [%s]", newline);
    return (newline);
}

static char	*ft_find_env(char *line, int i, t_mini *mini)
{
    printf("in ft_find_env\n");
	int		j;
    char    *start;
	char	*oldvar;
    char    *newvar;
    char    *end;

	j = i;
    printf("line: %s, int i %d", line, i);
	while (line[i] != '\0' && line[i] != ' ')
		i++;
    oldvar = ft_substr(line, j + 1, i - j - 1);
    if (j == 0)
        start = ft_substr(line, 1, j);
    else
        start = ft_substr(line, 0, j - 1);
    end = ft_substr(line, i + 1, ft_strlen(line) - i);
    printf("oldvar:[%s] start:[%s] end: [%s]", oldvar, start, end);
	if (mini->tlist == NULL)
	{
        newvar = ft_strdup(" ");
        printf("1new var: [%s]", newvar);
    	return (line_replaced(start, newvar, end));   
    }
	while (mini->tlist != NULL)
	{
        if (ft_strcmp(mini->tlist->var1, oldvar) == 0)
        {
            newvar = ft_strjoin(" ", mini->tlist->var2);
            newvar = ft_strjoin(newvar, " ");
            printf("2new var: [%s]", newvar);
    	    return (line_replaced(start, newvar, end));   
        }
        mini->tlist = mini->tlist->next;
	}
    return (line_replaced(start, " ", end));
}

char		*ft_check_env(char *line, t_mini *mini)
{
	int i;

    i = 0;
    if (line == NULL)
        return (line);
	while (line[i] != '\0')
	{ 
		if (line[i] == '$')
			line = ft_find_env(line, i, mini);
        i++;
	}
    return (line);
}
