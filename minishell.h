/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:50:50 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/12/05 18:34:35 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h> 

typedef struct		s_mini
{
	char	*command;
	char	*more;
	int		flag;
}					t_mini;

int		ft_echo(t_mini *mini);
int		ft_strcmp(const char *s1, const char *s2);
int		check_liney(char **liney, t_mini *mini);
void	ft_first_word(char *liney, t_mini *mini);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar(char c);
void	ft_putstr(char *s);

void	ft_cd(t_mini *mini);
void	ft_pwd(t_mini *mini);

#endif
