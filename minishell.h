/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:50:50 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/01/11 18:55:53 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_line
{
	int				o;
	int				t;
	int				k;
	char			*line;
}					t_line;

typedef struct		s_list
{
	char			*var1;
	char			*var2;
	struct s_list	*next;
}					t_list;

typedef struct		s_mini
{
	char			*command;
	char			*more;
	t_list			*run2;
	char			*path;
	int				cd;
	t_list			*env1;
	// builtin and execve arrray need corresponding function array for this
	char			*builtin[8];
	char			*notbuiltin[13]; // ls mkdir touch cat
	int				stdout;
	int				stderr;
}					t_mini;

int					ft_echo(char *string, t_mini *mini);
void				ft_putstr(char *s);
int				    ft_export(t_mini *mini, char *more);
char				*ft_check_dolla_quotes(char *line, t_mini *mini, int i);
int 				ft_unset(t_mini *mini, char *unset);
int					unvalid_identifier(char *error, t_mini *mini);
int 				ft_strchr_numb(char *line, char c, int i);
int					ft_strrchr_numb(char *line, char c, int i);
int  				numb_char(char *line, char c);
int  				ft_split_into_tlist(t_mini *mini, char *line);
t_list				*ft_lstnew(void *var1, void *var2);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstprint(t_list *lst, t_mini *mini);
// int					ft_builtin(t_mini *mini, char *command, char *more, char **envp);
int					ft_execve(t_mini *mini, char **envp);
void				ft_lstclear(t_list **lst);

void				ft_cd(t_mini *mini);
void				ft_pwd(t_mini *mini);
void				ft_set_env(char **argv, char **envp, t_mini *mini);
void				ft_set_array(t_mini *mini);

#endif
