/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:32:59 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 17:50:19 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

int		g_var[3];

void	my_signal2(int signal)
{
	(void)signal;
	if (g_var[1] == 1 && g_var[2] == 0)
		write(1, "\b\b  \b\b", 6);
	if (g_var[2] == 1)
	{
		write(1, "Quit: 3\n", 8);
		g_var[0] = 131;
		g_var[2] = 0;
	}
}

void	my_signal(int signal)
{
	if (signal == SIGINT)
	{
		if (g_var[2] == 1)
		{
			write(1, "\n", 1);
			g_var[2] = 0;
			g_var[0] = 130;
		}
		if (g_var[1] == 1 && g_var[2] == 0)
		{
			write(1, "\b\b  \b\b\n", 7);
			write(1, "minishell$ ", 11);
			g_var[0] = 1;
		}
	}
	if (signal == SIGQUIT)
		my_signal2(signal);
}

void	make_struct(int del, t_all *all, t_environment *env, int err)
{
	int i;
	int j;

	i = -1;
	while (++i <= del)
	{
		j = 0;
		make_num_arg(&all[i], all[i].gnl);
		all[i].ind_com = delitel_pip(&all[i]);
		all[i].err_flag = 0;
		while (j <= all[i].num_com)
		{
			init_redir(&all[i].ind_com[j]);
			all[i].ind_com[j].args = make_arguments(all[i].num_arg,
						&all[i].ind_com[j], all[i].ind_com[j].str);
			all[i].ind_com[j].args = make_clear_str(&all[i].ind_com[j], env);
			if (all[i].num_redir != 0 && all[i].ind_com[j].err_flag == 0)
				all[i].ind_com[j].args = redir(&all[i].ind_com[j]);
			if (all[i].ind_com[j].err_flag == 1)
				err++;
			j++;
		}
		if (all[i].err_flag == 0 && err == 0)
			exec_all(&all[i], env);
	}
}

void	while_get_line(t_all *all, t_environment *env, char *his)
{
	char			*str;
	int				del;

	while (1)
	{
		write(1, "minishell$ ", 11);
		g_var[1] = 0;
		str = ft_termcap(his);
		str = tab_space(str);
		if (redir_error(str) == 1)
			free(str);
		else
		{
			make_num_arg(all, str);
			all = delitel(str, all);
			del = all->num_del;
			make_struct(all->num_del, all, env, 0);
			free(str);
			make_free(all, del);
		}
		g_var[1] = 1;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_all			*all;
	t_environment	env;
	int				fd;
	char			*his;

	(void)argc;
	(void)argv;
	g_var[0] = 0;
	g_var[1] = 1;
	g_var[2] = 0;
	all = malloc(sizeof(t_all) * 1);
	env.env = copy_envp(envp);
	env.exp = copy_exp(envp);
	his = getcwd(NULL, 1000);
	free(his);
	his = ft_strjoin(his, "/history");
	fd = open(his, O_CREAT | O_RDWR, 0666);
	close(fd);
	signal(SIGINT, my_signal);
	signal(SIGQUIT, my_signal);
	signal(SIGTERM, SIG_IGN);
	while_get_line(all, &env, his);
	return (0);
}
