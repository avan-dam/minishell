/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:50:50 by avan-dam      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/12/17 19:48:14 by ambervandam   ########   odam.nl         */
=======
/*   Updated: 2020/12/19 17:55:55 by salbregh      ########   odam.nl         */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

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
	char			*notbuiltin[5]; // ls mkdir touch cat
}					t_mini;

int					ft_echo(char *string);
void				ft_putstr(char *s);
int	    			ft_strchr_numb(const char *s, int c);
int				    ft_export(t_mini *mini, char *more);
char				*ft_check_dolla(char *line, t_mini *mini);
int 				ft_unset(t_mini *mini, char *unset);
int					unvalid_identifier(char *error);
int 				ft_strrch_numb(char *line, char c);
int  				ft_split_into_tlist(t_mini *mini, char *line);
t_list				*ft_lstnew(void *var1, void *var2);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstprint(t_list *lst);
// int					ft_builtin(t_mini *mini, char *command, char *more, char **envp);
int					ft_execve(t_mini *mini);

void				ft_cd(t_mini *mini);
void				ft_pwd(t_mini *mini);
void				ft_set_env(char **argv, char **envp, t_mini *mini);
void				ft_set_array(t_mini *mini);

#endif
