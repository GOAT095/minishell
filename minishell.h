/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:53:07 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/21 18:27:10 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <termcap.h>
# include <fcntl.h>

# define BACKSPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define NEW_LINE 10
# define CTRLD 4

typedef struct s_command
{
	char		**tokens;
	int			n_tokens;
	int			input_file;
	int			output_file;
	int			pipe_pos;
	int			block;
	int			check_pos;
}				t_command;

typedef struct s_data
{
	t_list			*env_var;
	t_list			*history;
	t_list			*cmds;
	t_list			*n_pipe_cmd;
	t_list			*fd_close;
	t_command		*command;
	int				ret;
	int				fd[2];
	int				fdd;
	int				num_pipes;
	int				n_fork;
	char			*line;
	int				append;
	int				press;
	struct termios	term;
	struct termios	orig_term;
	t_list			*term_list;
	char			*ptr;
	int				sq;
	int				dq;
}				t_data;
t_data			g_data;

/*
** term_keys.c
*/

void				ft_new_line(void);
void				down_key(void);
void				up_key(void);
void				delete_end(int *col);
void				ft_ctrld(void);

/*
** term_utils.c
*/

void				ft_up_down(int c, int *col);
void				ft_add_line_to_his(void);

/*
** echo.c
*/

int					ft_echo(t_command *command, int i, int n);
int					check_n(char *args);

/*
** split.c
*/

char				**ft_split_pars(char *s, char c);
char				*get_other_variables(char *str);
char				*remove_all_quotes(char *str);
char				*ft_remove_slashes(char *str, int start, int end);

/*
** cd.c
*/

int					ft_cd(t_command *command);
int					ft_change_oldpwd(char *val);
int					ft_change_pwd(char *val);
char				*ft_get_home(void);
int					cd_error(int error, char *str);

/*
** pwd.c
*/

int					ft_pwd(void);

/*
** export.c
*/

int					ft_exist_var(
						char *export_var, char *token, int j, t_list *newlist);
void				ft_print_export(t_list *newlist);
void				ft_add_to_ex_list(char *token);
int					ft_export(t_command *command);

/*
** export_utils.c
*/

void				ft_print_export2(char *content, char *str_chr, char *var);
int					ft_valid_export_var(
						t_command *command, char *export_var, char *token,
						char *str);
char				*ft_get_export_var(char *exp_token);
int					ft_sort_exp_cmp(char *i_content, char *j_content);
void				ft_sort_export(void);

/*
** export_utils2.c
*/

void				ft_change(
						int j, char *token, char *old_var, t_list *newlist);
int					can_change(
						char *content, char *token, char *old_var,
						char *export_var);
char				*ft_get_oldvar(char *content);
void				ft_free_exist(char *str_free, char *str, char c);
int					ft_export_error(char *str, char *token);

/*
** env.c
*/

int					ft_env(t_command *command);
void				ft_stock_envp(char **envp);
char				**ft_get_envp(void);
void				ft_stock_ret(void);

/*
** unset.c
*/

int					ft_unset(t_command *command);
int					ft_chr_var(char *unset_var);
int					ft_del_list(
						t_list **head, int position, t_list *curr,
						t_list *prev);

/*
** bin.c
*/

void				ft_exec_check2(char **tokens, struct stat ps);
void				ft_exec_check1(char **token, struct stat path_stat);
void				ft_exec_bin2(
						char **bins, char *path, struct stat ps, char **token);
int					ft_exec_bin(t_command *command);
void				ft_bin(t_command *command);

/*
** bin_utils.c
*/

void				ft_exec_error(int error, char *token);
void				ft_dup_in_out(int dup, int in, int out);
char				*ft_get_path(void);

/*
** main.c
*/

void				ft_parse(char *line, int j, int i);
int					ft_prompt(int argc, char **argv);
void				ft_stock_envp(char **envp);

/*
** utils1.c
*/

int					ft_strchr_set(char *str, char *set, char *token);
void				ft_free_d_p(char **str);
void				ft_free_list(void);
void				ft_close_fd(void);
int					ft_strcmp(const char *s1, const char *s2);

/*
** utils2.c
*/

void				ft_putstrs_fd(char *s1, char *s2, char *s3, char *s4);
void				ft_putstrs_er(char *s1, char *s2, char *s3, char *s4);
int					ft_check_syntax_last(char *line);
int					ft_check_syntax2(char *line);
int					ft_check_syntax(char *line);

/*
** utils2.c
*/

void				init2(int *num_pipe);
void				ft_close_and_ret(int *j, t_list **pipe_list);
void				init1(
						char **argv, t_list **newlist, t_list **pipe_list,
						int *j);
int					check_input(t_list *newlist, int j);
void				ft_parse2(int i, int j, char *pipe_cmd);

/*
** exit.c
*/

int					ft_exit(t_command *command, int i);
int					ft_just_numbers(char *str);
int					ft_exit_error(int error, char *str);

/*
** redirections.c
*/

char				*ft_check_redirections(
						char *pipe_cmds, int i, char *new_pipe);
void				ft_check_redirections2(char **new_pipe, int *i, char *str);
void				ft_in_red_file(char **new_pipe, char **tmp_in, int j);
char				*ft_check_in(
						char *pipe_cmds, char *new_pipe, char *tmp_free, int i);
void				ft_out_red_file(char *tmp_out, char **new_pipe);

/*
** redirections_utils.c
*/

int					ft_check_in2(char *tmp_in);
int					ft_check_out(char **tmp_out);
void				ft_out_red_file2(char *file, char c, int out, int priority);
void				ft_close_get_out(int out);

/*
** builtin_utils.c
*/

int					ft_check_builtin(t_command *command);
int					ft_exec_builtin(t_command *command);
void				ft_builtin(t_command *command);

/*
** tockens.c
*/

void				ft_prepare_tokens(t_command *command, int k, int len);
void				ft_new_tokens(
						t_command *command, int len, int k, char **tmp_double2);

/*
** split_utils.c
*/

char				*get_other_variables(char *str);
char				*ft_remove_slashes(char *str, int start, int end);
char				*remove_all_quotes(char *str);
char				**split_parse2(char *s, char **str, char c, int splited);
char				**ft_split_pars(char *s, char c);

/*
** split_utils1.c
*/

int					is_escaped(char *s, int j);
int					chec_before(char *s, int i, char c);
int					countt(char *s, char c);
char				**ft_free(char **s, int j);
int					ft_count(const char *s, int l);

/*
** split_util2.c
*/

int					check_char(char c);
int					check_cots(char *s, int d_quote, int s_quote);
int					remove_tabs_check(char *s, char c);
char				*ft_stock(char *line, char *buff, int i);
char				*ft_put_variable(char *str, int k, int j);

/*
** split_util3.c
*/

int					ft_ch_do(int i, int c, char *s);
int					ft_rep_var_2(int value_len, char *value, char *ptr, int *i);
char				*ft_replace_variable(char *str, char *value, int k, int j);
void				ft_get_var3(int *s_quote, int *d_quote, int *j, char *str);
int					ft_get_var2(int j, char *str, int *k, int i);

/*
** split_util4.c
*/

int					ft_remove_slashes3(int i, char *str, int end);
void				ft_remove_slashes4(char *str, char **back, int end, int i);
void				ft_remove_slashes_7(int count, int *j, char **back);
char				*ft_remove_slashes_6(char *str, int i, int end, int len);
char				*ft_remove_slashes_2(char *str, int start, int end);

/*
** split_util5.c
*/

void				init_3params(int *i, int *j, int *d);
int					my_ternary(int *splited, int i, int d);
void				ft_remove_all1(char *str, int *i, int *start);
void				ft_remove_all2(char *str, int *i, int *start);
int					ft_remove_slashes_5(char *str, int i, int end);

/*
** split_util6.c
*/

int					get_other_var2(char *str, int i, int d_quote, int s_quote);
void				fill_with(char *s, int start, int len, char c);
char				*ft_variable_value(char *var);
char				*ft_check_dollar_slash(char	*s, int i, int c);
char				*ft_get_variables(char *str, int start, int i);

/*
** term_keys.c
*/

void				ft_new_line(void);
void				down_key(void);
void				up_key(void);
void				delete_end(int *col);
void				ft_ctrld(void);

/*
** term_utils.c
*/

void				ft_up_down(int c, int *col);
void				ft_add_line_to_his(void);

/*
** term.c
*/

int					get_line(void);
void				ft_init_get_line(int *col);
void				ft_get_char(int c, int *col);
void				ft_init_term(void);

/*
** main.c
*/

void				sighandler(int dummy);
void				ft_exec(t_command *command);
int					ft_prompt(int argc, char **argv);
void				ft_parse(char *line, int j, int i);

#endif
