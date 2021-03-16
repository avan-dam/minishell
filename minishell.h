/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 23:26:56 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/16 14:48:09 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h> // delete after
# include <stdlib.h>
# include <sys/syslimits.h>
# include <fcntl.h>
# include <signal.h>

# define R O_RDWR
# define C O_CREAT
# define A O_APPEND
# define T O_TRUNC

# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define T_END		3	
# define T_PIPE		4
# define T_BREAK	5

typedef struct s_base
{
	char			**av;
	int				size;
	int				type;
	int				fd[2];
	struct s_base	*prev;
	struct s_base	*next;
	int				redir;
}					t_base;

typedef struct s_line
{
	int				s;
	int				d;
	char			*str;
}					t_line;

typedef struct s_list
{
	char			*var1;
	char			*var2;
	struct s_list	*next;
}					t_list;

typedef struct s_mini
{
	t_list			*env1;
	int				stdout;
	int				stderr;
	int				numb_cmds;
	char			*cmd_part;
	int				type_end;
	int				stdin;
	int				exit;
}					t_mini;

/*
** fd[0] - read fd[1] - write made by pipe(fd);
*/

typedef struct s_piper
{
	int				check;
	char			*write_side;
	char			*read_side;
	int				fd[2];
}					t_piper;

void				ft_leaks(void); // DELETE

/*
**	LIST FUNCTION
*/
t_list				*ft_lstnew(void *var1, void *var2);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_back_base(t_base **ptr, t_base *new);
void				ft_lstprint(t_list *lst, t_mini *mini, int i);
void				ft_lstclear(t_list **lst);
int					ft_split_into_tlist(t_mini *mini, char *line);
void				ft_lstprintold(t_list *lst);
void				ft_baseclear(t_base **lst);
void				clear_leaks(t_base *ptr);
void				one_baseclear(t_base *store);
int					ft_lst_cmp(t_mini *mini, char *value);

/*
**	BUILTIN FUNCTION
*/
int					ft_echo(t_base *ptr, t_mini *mini);
int					ft_export(t_base *ptr, t_mini *mini);
int					ft_unset(t_mini *mini, char *unset);
void				ft_cd(t_base *ptr, t_mini *mini);
void				ft_pwd(t_mini *mini);
void				ft_exit(t_mini *mini, int exitstatus);
void				ft_print_exit_status(t_mini *mini);
void				ft_set_env(char **av, char **envp, t_mini *mini);
void				handle_sigint(int sig);
void				ft_signals(t_mini *mini, int i);
void				exec_builtin(t_base *tmp, t_mini *mini);
void				ft_lstprint_env(t_list *lst, t_mini *mini, t_base *ptr);
int					ft_unset_builtin(t_mini *mini, char *unset, t_base *ptr);

/*
**	PARSER FUNCTIONS
*/
int					parse_input(char *line, t_mini *mini, char **envp, int i);
char				*check_tokens(char *line, t_mini *mini, int i, int j);
int					ft_find_dolla(int i, int j, t_mini *mini, t_line *s);
int					ft_replace_quotes(t_line *s, int i, int j);
int					ft_correct_backslash(t_line *s, int i);
int					unvalid_ident(char *error, t_mini *mini, int exitstatus);
t_base				*ft_redir(t_mini *mini, t_base *ptr);
char				**ft_remove_redir_av(t_base *ptr, int i, int j);
int					add_new_into_list(int j, t_base *ptr, int i);
void				redir_change_backslash(t_base *ptr, int i);
int					ft_check_redir_in_quotes(t_base *ptr, t_mini *mini, int i);
int					check_file_toredir(t_base *ptr, int i, t_mini *mini);
int					error_opening(char *error, t_mini *mini);
int					fill_av_list(t_base *new, t_mini *mini, int j, int l);
int					create_av_list(t_base **ptr, char *line, t_mini *mini);
int					no_of_commands(char *line, t_mini *mini, int i, int numb);
void				ft_free_tmps(char *tmp, char *result);
char				*free_reset_tmp(char *tmp, char *result, char *line, int i);
char				*ft_strtrim_backslash(char const *s1, char c);
int					redir_error(t_mini *mini, int i);

/*
**	EXECVE FUNCTION
*/
int					exec_cmds(t_base *ptr, char **envp, t_mini *mini);
int					look_for_non_builtin(t_base *ptr, int i);
int					ft_is_builtin(char *str);
int					ft_execve(t_mini *mini, char **envp);

/*
**	UTILS
*/
int					ft_strchr_numb(char *line, char c, int i);
int					ft_strrchr_numb(char *line, char c, int i);
int					numb_char(char *line, char c);
int					ft_is_str_int(char *str);
void				clear_mini(t_mini *mini, int i);
void				ft_reset_fds(t_mini *mini);
char				*ft_strtolower(char *str);
char				*ft_trim_paths(char *line, char *set);
char				*mem_check_tkns(char *str, t_mini *mini, int i, int j);
char				*ft_string_insert(char *string, int i, char *middle);
char				*ft_strjoin_three(char *start, char *newvar, char *end);
int	ft_check_empty(char *string);

#endif
