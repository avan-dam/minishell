/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 23:26:56 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/05 14:22:23 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>

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
	char			*part;
	int				type_end;
	int				stdin;
	int				exit;
	int				shell_level;
}					t_mini;

typedef struct s_piper
{
	int				check;
	char			*write_side;
	char			*read_side;
	int				fd[2];
}					t_piper;

/*
**	LIST FUNCTIONS
*/

t_list				*ft_lstnew(void *var1, void *var2);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_back_base(t_base **ptr, t_base *new);
void				ft_lstprint(t_list *lst, t_mini *mini);
void				ft_lstclear(t_list **lst);
int					ft_split_into_tlist(t_mini *mini, char *line);
void				clear_leaks(t_base *ptr);
void				one_baseclear(t_base *store);
void				delete_node(t_list *lst, t_list *target, t_mini *mini);

/*
**	BUILTIN FUNCTIONS
*/

void				handle_line(int lineret, t_mini *mini, char **envp);
int					ft_echo(t_base *ptr, t_mini *mini);
void				check_last_arg(t_base *ptr, int i);
int					ft_echo_n(char *str, t_mini *mini);
int					free_return(char *str);
int					check_empty(char *str);
int					ft_export(t_base *ptr, t_mini *mini);
int					ft_unset(t_mini *mini, char *unset);
void				ft_cd(t_base *ptr, t_mini *mini);
void				ft_add_env(char *env, char *path, t_mini *mini);
char				*ft_get_env(char *env, t_mini *mini);
void				up_shell_level(t_mini *mini);
void				ft_pwd(t_mini *mini);
void				ft_exit(t_mini *mini, int exitstatus);
int					sort_exit_statement(t_base *ptr, t_mini *mini, int i);
int					ft_exit_check(t_base *ptr, t_mini *mini);
void				ft_set_env(char **av, char **envp, t_mini *mini);
void				handle_sigint(int sig);
void				ft_signals(t_mini *mini, int i);
void				exec_builtin(t_base *tmp, t_mini *mini, char **envp);
void				ft_lstprint_env(t_list *lst, t_mini *mini, t_base *ptr);
int					ft_unset_builtin(t_mini *mini, t_base *ptr);

/*
**	PARSER FUNCTIONS
*/

int					parse_input(char *line, t_mini *mini, char **envp, int i);
char				*check_tokens(char *line, t_mini *mini, int i, int j);
int					ft_find_dolla(int i, int j, t_mini *mini, t_line *s);
int					ft_replace_quotes(t_line *s, int i, int j);
int					ft_replace_tilda(t_line *s, int i, t_mini *mini);
int					ft_correct_backslash(t_line *s, int i);
int					ft_extra_check_dolla(t_line *s, int i, int j);
int					unvalid_ident(char *error, t_mini *mini, int exitstatus);
t_base				*ft_redir(t_mini *mini, t_base *ptr);
char				**ft_remove_redir_av(t_base *ptr, int i, int j);
int					add_new_into_list(int j, t_base *ptr, int i);
void				redir_change_backslash(t_base *ptr, int i);
int					direction_list(t_base *ptr, int i, int j, int k);
int					ft_check_redir_in_quotes(t_base *ptr, t_mini *mini, int i);
int					check_file_toredir(t_base *ptr, int i, t_mini *mini);
int					error_opening(char *error, t_mini *mini);
int					fill_av_list(t_base *new, t_mini *mini, int j, int l);
int					create_av_list(t_base **ptr, char *line, t_mini *mini);
int					no_of_commands(char *line, t_mini *mini, int i);
int					mini_vals(t_mini *mini, int i, char *line, int check);
void				ft_free_tmps(char *tmp, char *result);
char				*free_reset_tmp(char *tmp, char *result, char *line, int i);
char				*ft_strtrim_backslash(char const *s1, char c);
int					redir_error(t_mini *mini, int i);
int					div_str(char *line, int i, char *result, char *tmp);
int					no_commands_line(char *line, int i, t_mini *mini);
int					ft_print_error(t_mini *mini);
void				fix_redir_space_echo(t_base *ptr, int i);

/*
**	EXECVE FUNCTION
*/

int					exec_cmds(t_base *ptr, char **envp, t_mini *mini);
int					look_for_non_builtin(t_base *ptr, int i, t_mini *mini,
						char **envp);
int					ft_is_builtin(char *str);
int					ft_execve(t_mini *mini, char **envp);
int					sort_struct_before_redir(t_base *ptr, t_mini *mini);
void				sort_struct_after_redir(t_base *ptr);
int					ft_check_usr_bin(t_base *ptr, struct dirent *dit,
						DIR *dirp, int i);
int					ft_check_in_bin(t_base *ptr, struct dirent *dit,
						DIR *dirp, int i);
int					child_process(t_base *ptr, t_mini *mini, char **envp,
						int k);
void				parent_proces(pid_t pid, t_mini *mini, t_base *ptr,
						int piped);

/*
**	UTILS
*/

int					ft_strchr_numb(char *line, char c, int i);
int					numb_char(char *line, char c);
int					ft_is_str_int(char *str);
void				clear_mini(t_mini *mini, int i);
void				ft_reset_fds(t_mini *mini);
char				*ft_strtolower(char *str);
char				*mem_check_tkns(char *str, t_mini *mini, int i, int j);
char				*ft_string_insert(char *string, int i, char *middle);
char				*ft_strjoin_three(char *start, char *newvar, char *end);
int					ft_check_empty(char *string);
int					send_to_unvalid(t_mini *mini, int j);
int					send_to_unvalid_one(int j, char *s, int k, t_mini *mini);
void				free_all(char *tmp2, char *tmp);
int					dolla_while_checker(char *s, int i);

#endif
