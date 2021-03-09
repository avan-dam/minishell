/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_quote_backslash.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 20:06:59 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/08 19:25:30 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_correct_backslash(t_line *s, int i)
{
	
	// if (i == 0 && s->str[1] == '$')
	// 	return (i + 2);
	// printf("in backy s->str is [%s]\n", s->str);
	if (s->str[i + 1] == '>' || s->str[i + 1] == '<')
		return (i+2);
	if (s->str[i + 1] != '>' && s->str[i + 1] != '<'
		&& ((s->str[i + 1] == '`') || (s->str[i + 1] == '"')
			|| ((s->str[i + 1] == '\'') && (s->d % 2 == 0))
			|| s->str[i + 1] == '$' || s->str[i + 1] == '\\'))
	{
		// printf("this\n");
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		if (s->str[i] != '\0' && ((s->str[i] == '$'
					&& ((i == 0) || ((i > 0) && (s->str[i - 1] != '\\'))))
				|| s->str[i] == '\'' || s->str[i] == '"'))
			i++;
	}
	else if ((s->s % 2 == 0) && (s->d % 2 == 0)
		&& (s->str[i + 1] != '>') && (s->str[i + 1] != '<'))
	{	
		// printf("that\n");
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	}
	return (i);
}

static int	ft_single_quotes(t_line *s, int i)
{
	if (s->d % 2 == 1)
	{
		if ((s->str[i + 1] == '\\') || ((s->str[i + 1] == '"')
				&& (s->d % 2 == 1)) || (i + 2 == (int)ft_strlen(s->str)))
			return (i);
		return (i + 2);
	}
	ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	if (i != 0)
		i--;
	s->s++;
	// if (s->str[i] == '\\' && s->d % 2 == 0 && s->str[i + 1] == '$')
	// {
	// 			printf("hhhh\n");

	// 	ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	// 	i++;
	// }
	while ((s->str[i] != '\'') && (s->str[i] != '\0'))
		i++;
	if (s->str[i] == '\'')
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		i--;
		s->s++;
	}
	return (i);
}

int	ft_replace_quotes(t_line *s, int i)
{
	// int k;
	if (numb_char(s->str, '>') != 0 || numb_char(s->str, '<') != 0)
		return (i);
	// printf("in replace quotes s->str is [%s]\n", s->str);
	if (s->str[i] == '\'')
		i = ft_single_quotes(s, i);
	else if (s->str[i] == '"')
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		// k = i;
		// while (s->str[i + 1] != '\0' && (s->str[i + 1] == '>' || s->str[i + 1] == '<' || s->str[i + 1] == '\\'))
		// 	i++;
		// if (s->str[i + 1] == '\0')
		// {
		// 	s->d++;
		// 	printf("outtta replace quotes s->str is [%s]\n", s->str);
		// 	return (i + 1);
		// }
		// if (i != 0)
			i--;
		if (s->s % 2 == 0)
			s->d++;
	}
	// printf("out replace quotes s->str is [%s]\n", s->str);
	return (i);
}
