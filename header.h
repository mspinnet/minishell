/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:21:41 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 19:12:57 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <term.h>

extern int			g_var[3];

typedef struct		s_command
{
	char			**args;
	char			*str;
	char			*str2;
	int				fd[2];
	int				redir_fd[2];
	int				key;
	int				err_flag;
}					t_command;

typedef struct		s_environment
{
	char			**env;
	char			**exp;
}					t_environment;

typedef struct		s_term
{
	char			**hist;
	char			str[2048];
	char			*str2;
	char			buf;
	int				fd;
	int				l;
	int				i;
	int				j;
	int				c;
}					t_term;

typedef struct		s_all
{
	t_command		*ind_com;
	char			*gnl;
	int				num_arg;
	int				num_del;
	int				num_com;
	int				num_redir;
	int				err_flag;
}					t_all;

typedef struct		s_dolllar
{
	int		l;
	int		c;
	int		f;
	int		j;
	char	*res;
	char	*copy;
}					t_dollar;

typedef struct		s_del
{
	int		i;
	int		k;
	int		c;
	int		d;
	int		err;
}					t_del;

typedef struct		s_redir
{
	char	**args2;
	int		i;
	int		j;
}					t_redir;

int					is_space(char *str, int i);
char				*tab_space(char *str);
int					ft_strcmp(const char *s1, const char *s2);
void				make_num_arg(t_all *all, char *str);
void				init_struct(t_all *all);
int					if_pip_redir(t_all *all, char *str, int i);
int					if_cov(char *str, int i);
void				delitel_arg(t_all *all, char *str, int i);
char				**make_arguments(int	num_arg,
					t_command *ind_com, char *str);
int					*while_str(t_command *ind_com, char *str, int *i);
int					*while_not_space(t_command *ind_com, char *str, int *i);
int					*if_redirect1(t_command *ind_com, char *str, int *i);
int					*if_redirect2(t_command *ind_com, char *str, int *i);
int					*minus_n(t_command *ind_com, char *str, int *i);
char				**make_clear_str(t_command *ind_com, t_environment *env);
void				while_str2(t_command *ind_com,
					t_environment *env, t_redir *res);
void				if_simbol(t_command *ind_com,
					t_environment *env, t_redir *res);
t_all				*delitel(char *str, t_all *all);
void				del_else(char *str, t_all *all, t_del *del);
int					prov_line(t_all *all);
void				if_delitel(char *str, t_all *all, t_del *del);
void				while_ne_del(char *str, t_del *del);
void				if_ne_term(char *str, t_all *all, t_del *del);
t_command			*delitel_pip(t_all *all);
void				del_else_pip(t_all *all, t_del *pip);
int					prov_line2(char *str, t_all *all);
void				while_ne_pip(t_all *all, t_del *pip);
void				if_pip(t_all *all, t_del *pip);
void				if_ne_pip(t_all *all, t_del *pip);
void				prov_line3(t_all *all, t_del *pip);
int					if_cov1(t_command *ind_com, char *str, int j);
int					if_cov2(t_command *ind_com, char *str, int j,
					t_environment *env);
int					if_cov2_cikl(t_command *ind_com, char *s, int j,
					t_environment *env);
int					if_cov2_cikl2(t_command *ind_com,
					char *s, int j, t_environment *env);
int					if_slesh_cov(t_command *ind_com, char *s, int j);
int					if_cov2_dol(t_command *ind_com, char *s, int j);
int					if_slesh(t_command *ind_com, char *str, int j);
int					for_join(t_command *ind_com, char *str, int j);
int					if_dollar(t_command *ind_com, char *str, int j,
					t_environment *env);
void				vopr_or_slesh(t_command *ind_com, t_dollar *dol, char c);
void				cikl_dol(char *str, t_dollar *dol, t_environment *env);
void				search_env(t_dollar *dol, t_environment *env, char *str);
void				exec_export(t_command *command, t_environment *gen_env);
void				resize_exp(char *str, t_environment *gen_env);
char				**copy_exp(char **envp);
char				**ft_sort(char **env, int size);
char				**copy_envp(char **envp);
void				exec_env(t_command *command, t_environment *gen_env);
void				resize_env(char *str, t_environment *gen_env);
void				add_arg_to_env(t_command *command, t_environment *gen_env);
int					ft_cmp(char *s1, char *s2);
void				exec_all(t_all *command, t_environment *gen_env);
void				delete_str_from_env(t_environment *gen_env, int numb);
void				exec_unset(t_command *command, t_environment *gen_env);
int					ft_find_key(char *args, char **env);
void				rewrite_env_exp(char *arg, t_environment *gen_env, int l);
void				make_free(t_all *all, int del);
void				init_redir(t_command *command);
char				**redir(t_command *ind_com);
void				if_one_left(t_command *ind_com, int i);
void				if_two_right(t_command *ind_com, t_redir *re);
void				if_one_right(t_command *ind_com, t_redir *re);
void				free_args(t_command *ind_com);
void				cikl_re(t_command *ind_com, t_redir *re);
void				open_fd(t_command *ind_com, t_redir *re);
void				close_redir(t_command *ind_com);
int					redir_error(char *str);
int					min_2(char *str, int i, int c);
int					max_2(char *str, int i);
int					main(int argc, char **argv, char **envp);
void				while_get_line(t_all *all, t_environment *env, char *his);
void				make_struct(int del, t_all *all,
					t_environment *env, int err);
void				my_signal(int signal);
void				my_signal2(int signal);
void				exec_echo(t_all *command, int n);
void				exec_cd(t_command *command, t_environment *gen_env);
void				exec_pwd(t_command *command, t_environment *gen_env);
char				*find_home(t_environment *gen_env);
void				pwd_oldpwd(t_environment *gen_env, char *oldpwd);
void				exec_chain(t_all *command, t_environment *gen_env);
char				*find_path(char *command, t_environment *gen_env);
void				exec_system_funct(t_command *command,
					t_environment *gen_env);
void				shlvl(t_environment *gen_env);
int					ft_cmp(char *s1, char *s2);
void				pipes_and_redir(t_all *command,
					int n, int tmpout);
void				parents_and_sig(pid_t *ret,
					int *status, int n, t_all *command);
void				costyl_sps_norma(int tmpin, int tmpout);
int					oldpwd_path(t_environment *gen_env);

int					ft_putchar(int c);
char				*ft_termcap(char *his);
void				necanon(struct termios *term);
void				init_term(t_term *termc, char *his);
void				if_up(t_term *termc);
void				if_down(t_term *termc);
void				if_backspace(t_term *termc);
void				if_ctrl_d(t_term *termc, struct termios *term);
void				if_ctrl_c_n(t_term *termc, struct termios *term, char *his);
void				if_notall(t_term *termc);
void				if_4_cond(t_term *termc, struct termios *term);
int					while_ne_redir(char *str, int i);

#endif
