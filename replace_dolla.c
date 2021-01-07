/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/07 16:16:59 by ambervandam   ########   odam.nl         */
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

static t_line *ft_find_dolla(char *line, int i, t_mini *mini, t_line *s)
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
	// if (end[0] == 39)
		// ft_memmove(&end[0], &end[1], ft_strlen(end) - 1);
	if(start[ft_len(start) - 1] == 39 && end[0] == 39 && ft_len(end) > 1)
	{
		if (end[1] == '"')
			ft_memmove(&end[1], &end[2], ft_strlen(end) - 1);
	}
    newvar = ft_check_var_tlist(mini, oldvar);
    printf("oldvar[%s] newvar[%s] start[%s] end[%s]\n", oldvar, newvar, start, end);
    s->line = line_replaced(start, newvar, end);
	s->k = ft_len(newvar) - 1;
	return(s);
}

static void		set_tline( t_line *s)
{
	s->line = NULL;
	s->k = 0;
}
char		*ft_check_dolla_quotes(char *line, t_mini *mini, int o, int t)
{
	int i;
	int k;
	int j;
	t_line s;
	
	j = 0;
	k = 1;
	i = 0;
	set_tline(&s);
    if (line == NULL)
        return (line);
	while (line[i] != '\0')
	{
		printf("char %c t is %d o is %d line is %s\n", line[i], t, o, line);
		if (line[i] == '\\') // ascii 92
		{
			ft_memmove(&line[i], &line[i+1], ft_strlen(line) - 1);
			i--;
		}	
		if ((line[i] == '\'') && (t % 2 == 0) && (ft_strrch_numb(line, '\'') == i))
		{
			printf("here single quoteline %s\n", line);
			o++;	
			ft_memmove(&line[i], &line[i+1], ft_strlen(line) - i);
			i--;
			while(line[i] != '\'')
				i++;
			ft_memmove(&line[i], &line[i+1], ft_strlen(line) - i);
			i--;
			if (line[i] == '"')
				i++;
		}
		else if (line[i] == '"')
		{
			printf("here in double quote part line %s\n", line);
			// into own function 
			t++;
			if (line[j - 1] != '\'')
			{	ft_memmove(&line[i], &line[i+1], ft_strlen(line) - 1);
				i--;}
			printf("here line %s\n", line);
			i--;
			j = i;
			while(line[j] != '\0' && line[j] != '\'')
			{
				if (line[j] == '"'&& line[j - 1] != '\'')
				{
					t++;
					ft_memmove(&line[j], &line[j+1], ft_strlen(line) - 1);
					i++;
					j--;
				}	
				j++;
			}
			if (line[i + 1] == '\\')
				i++;
			printf("line i is %c i is%d\n", line[i], i);
		}
		else if((line[i] == '$') && line[i - 1] != '"' && ((o % 2 == 0) || (line[i - 1] == 39)))
		{
			if ((line[i + 1] != '/') && (line[i + 1] != 92) && (line[i + 1] != '\0') && ft_find_dolla(line, i, mini, &s) != NULL)
			{
				ft_find_dolla(line, i, mini, &s);
				line = s.line;
				i = i + s.k;
			}
		}
				i++;
	}
	return (line);
}
