/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/06 16:00:06 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *line_replaced(char *start, char *newvar, char *end)
{
    char *temp;
    char *newline;
    
    temp = ft_strjoin(start, newvar);
    newline = ft_strjoin(temp, end);
    return (newline);
}

static char *ft_check_var_tlist(t_mini *mini, char *oldvar)
{
    t_list  *tlist;

    // looking through environmental variables to see if needs to be replace
    // so only loop through env1 tlist not run tlist
    tlist = mini->env1;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, oldvar) == 0)
			return (tlist->var2);
        tlist = tlist->next;
	}
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
	// printf("in ft_finddoll with [%s]\n", line);
    while (line[i] != '\0' && line[i] != '#' && line[i] != '$' && line[i] != '-' && line[i] != '=' && line[i] != ' ' && line[i] != 39 && line[i] != '"')
        i++;
	if (i != 0)
	{
		if (line[i - 1] == '"')
			return (NULL);
	}
    oldvar = ft_substr(line, j, i - j);
    start = ft_substr(line, 0, j - 1);
    end = ft_substr(line, i, ft_strlen(line) - i);
	if (end[0] == '"')
		ft_memmove(&end[0], &end[1], ft_strlen(end));
		printf("end %s\n", end);
	newvar = ft_check_var_tlist(mini, oldvar);
    printf("oldvar[%s] newvar[%s] start[%s] end[%s]\n", oldvar, newvar, start, end);
    return (line_replaced(start, newvar, end));
}

char		*ft_check_dolla_quotes(char *line, t_mini *mini, int o, int t)
{
	int i;
	int k;
	int j;
	
	k = 1;
	i = 0;
    if (line == NULL)
        return (line);
	while (line[i + 1] != '\0')
	{
		i++;
		if ((line[i] == 92) && (line[i - 1] != '"'))
		{
			ft_memmove(&line[i], &line[i+1], ft_strlen(line) - 1);
			i--;
		}
		if ((line[i] == 39) && (t % 2 == 0))
		{
			o++;	
			ft_memmove(&line[i], &line[i+1], ft_strlen(line) - i);
			i--;
			if (line[i + 1] == 92)
				i++;
		}		
		else if ((line[i] == '"') && (o % 2 == 0))
		{
			// into own function 
			t++;
			j = i;
			ft_memmove(&line[i], &line[i+1], ft_strlen(line) - 1);
			i--;
			while(line[i] != '\0')
            {
                if (line[i] == '"' && ((line[i + 1] == '"') || (line[i + 1] == '$')))
				{
					t++;
					j++;
					k++;
					ft_memmove(&line[i], &line[i+1], ft_strlen(line) - 1);
            	}
				i++;
			}
			i = j - k;
			if (line[i + 1] == 92)
				i++;
		}
		else if((line[i] == '$') && ((o % 2 == 0) || (line[i - 1] == 39)))
		{
			if ((line[i + 1] != '/') && (line[i + 1] != 92) && (line[i + 1] != '\0') && ft_find_dolla(line, i, mini) != NULL)
				line = ft_find_dolla(line, i, mini);
		}
	}
	return (line);
}
