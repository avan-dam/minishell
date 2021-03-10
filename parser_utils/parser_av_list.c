/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_av_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 11:10:44 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/03/10 21:19:40 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static int	ft_begin(const char *s1, char c)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != c)
			return (i);
		i++;
	}
	return (i);
}

static int	fT_END(const char *s1, char c)
{
	int		i;
	int		inset;

	i = ft_strlen(s1) - 1;
	inset = 0;
	while (i >= 0)
	{
		if (s1[i] != c || i == 0 || s1[i - 1] == '\\')
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim_backslash(char const *s1, char c)
{
	int		i;
	int		begin;
	int		end;
	char	*newstr;

	if (s1 == NULL)
		return (NULL);
	begin = ft_begin(s1, c);
	end = fT_END(s1, c);
	if (begin > end)
		return (ft_strdup(""));
	newstr = (char *)malloc(sizeof(char) * (end - begin + 2));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (begin <= end)
	{
		newstr[i] = s1[begin];
		i++;
		begin++;
	}
	newstr[i] = '\0';
	return (newstr);
}
static int 	fill_av_more(t_mini *mini, int j, int k)
{
	char *result;
	// char *temp;

	// temp = mini->cmd_part;
	// mini->cmd_part = ft_strtrim_backslash(temp, ' ');
	// free(temp);
	// printf("mini->cmd_part is [%s]\n", mini->cmd_part);
	result = mem_check_tkns(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 4);
	while (mini->cmd_part[j] && 
		((mini->cmd_part[j] != ' ' ||  (mini->cmd_part[j] != ' ' && mini->cmd_part[j + 1] != '\\'))
		|| result == NULL))
		{
			printf("mini->cmd_part[j][%c]\n", mini->cmd_part[j]);
			free(result);
			result = mem_check_tkns(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 4);
			if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
			&& mini->cmd_part[j + 1] != '>'
			 && result != NULL)
		{
			printf("in break\n");
				break ;
		}
		if (result != NULL && (mini->cmd_part[j] == '\'' || mini->cmd_part[j] == '"'))
		{
			printf("in dis\n");
			j++;
			break ;
		}
		free(result);
		result = mem_check_tkns(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 4);
		j++;
	}
	printf("result is [%s]\n", result);
	while (mini->cmd_part[j] == ' ')
		j++;
	if ((mini->cmd_part[j] == '>') || (mini->cmd_part[j] == '<'))
		j--;
	if (result)
		free(result);
	// printf("returns values %d\n", j);
	return (j);
}

int	fill_av_list(t_base *new, t_mini *mini, int j, int l)
{
	int		k;

	k = 0;
	while (l != new->size)
	{
		if (mini->cmd_part[j] == '\0')
			new->av[l] = NULL;
		else
		{
			while (mini->cmd_part[j] == ' ')
				j++;
			k = j;
			j = fill_av_more(mini, j, k);
			if ((mini->cmd_part[j] == '>' || (mini->cmd_part[j] == '<'
				&& mini->cmd_part[j + 1] != '>')))
			{
				printf("in dis allocation\n");
				new->av[l] = ft_substr(mini->cmd_part, k, j - k + 1);
				j++;
			}
			else
				new->av[l] = ft_substr(mini->cmd_part, k, j - k);
			printf("new->size %d, new->av[l][%s] l is %d\n", new->size, new->av[l], l);
		}
		l++;
	}
	// printf("out fill_av_list\n");
	return (0);
}

static int	more_av_list(t_base *new, t_mini *mini, t_base **ptr, char *line)
{
	new->size = mini->numb_cmds;
	new->prev = NULL;
	new->next = NULL;
	new->av[mini->numb_cmds] = NULL;
	if (fill_av_list(new, mini, 0, 0) == -1)
	{
		free(line);
		return (-1);
	}
	new->type = mini->type_end;
	if (new->av[0][0] != '$')
	new->av[0] = ft_strtolower(new->av[0]);
	ft_lstadd_back_base(ptr, new);
	free(line);
	return (0);
}

int	create_av_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	t_base	*new;

	// printf("in create av list once with line [%s]\n", line);
	if (ft_strcmp(line, "") == 0)
		return (0);
	if (mini->cmd_part)
		free(mini->cmd_part);
	numb_characters = no_of_commands(line, mini, 0, 1);
	new = (t_base *)malloc(sizeof(t_base));
	if (new == NULL)
		return (-1);
	new->av = (char **)malloc(sizeof(char *) * (mini->numb_cmds + 1));
	if (new->av == NULL)
		return (-1);
	if (more_av_list(new, mini, ptr, line) == -1)
		return (-1);
	return (numb_characters);
}
