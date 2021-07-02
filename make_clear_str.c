/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_clear_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:59:54 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/24 20:19:22 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**make_clear_str(t_command *ind_com, t_environment *env)
{
	t_redir		res;

	res.i = 0;
	ind_com->err_flag = 0;
	while (ind_com->args[res.i])
		res.i++;
	res.args2 = malloc(sizeof(char*) * (res.i + 1));
	res.i = 0;
	while (ind_com->args[res.i] != NULL)
	{
		res.j = 0;
		res.args2[res.i] = ft_strdup("\0");
		while_str2(ind_com, env, &res);
		res.i++;
	}
	res.args2[res.i] = NULL;
	free_args(ind_com);
	return (res.args2);
}

void	while_str2(t_command *ind_com, t_environment *env, t_redir *res)
{
	while (ind_com->args[res->i][res->j])
	{
		if (ind_com->args[res->i][res->j] == 32)
			res->j = is_space(ind_com->args[res->i], res->j);
		if (ind_com->args[res->i][res->j] != 34 &&
		ind_com->args[res->i][res->j] != 39 &&
		ind_com->args[res->i][res->j] != 92 &&
		ind_com->args[res->i][res->j] != '$' &&
		ind_com->args[res->i][res->j] != '\0')
		{
			res->j = for_join(ind_com, ind_com->args[res->i], res->j);
			free(res->args2[res->i]);
			res->args2[res->i] = ft_strjoin(res->args2[res->i], ind_com->str);
		}
		if_simbol(ind_com, env, res);
		res->j++;
	}
}

void	if_simbol(t_command *ind_com, t_environment *env, t_redir *res)
{
	if (ind_com->args[res->i][res->j] == '$')
	{
		res->j = if_dollar(ind_com, ind_com->args[res->i], res->j, env);
		free(res->args2[res->i]);
		res->args2[res->i] = ft_strjoin(res->args2[res->i], ind_com->str);
	}
	if (ind_com->args[res->i][res->j] == 92)
	{
		res->j = if_slesh(ind_com, ind_com->args[res->i], res->j);
		free(res->args2[res->i]);
		res->args2[res->i] = ft_strjoin(res->args2[res->i], ind_com->str);
	}
	else if (ind_com->args[res->i][res->j] == 39)
	{
		res->j = if_cov1(ind_com, ind_com->args[res->i], res->j);
		free(res->args2[res->i]);
		res->args2[res->i] = ft_strjoin(res->args2[res->i], ind_com->str);
	}
	else if (ind_com->args[res->i][res->j] == 34)
	{
		res->j = if_cov2(ind_com, ind_com->args[res->i], res->j, env);
		free(res->args2[res->i]);
		res->args2[res->i] = ft_strjoin(res->args2[res->i], ind_com->str);
	}
}

int		if_cov1(t_command *ind_com, char *str, int j)
{
	int		i;

	ind_com->str2 = ft_strdup("\0");
	i = 0;
	j++;
	while (str[j] != 39 && str[j] != '\0')
	{
		i++;
		j++;
	}
	if (str[j] == '\0')
	{
		write(1, "minishell: syntax error: don't close ", 37);
		ft_putchar_fd(39, 1);
		write(1, " !!!\n", 5);
		ind_com->err_flag = 1;
		g_var[0] = 258;
	}
	free(ind_com->str);
	free(ind_com->str2);
	ind_com->str2 = ft_substr(str, j - i, i);
	free(ind_com->str2);
	ind_com->str = ft_strdup(ind_com->str2);
	return (j);
}

int		*minus_n(t_command *ind_com, char *str, int *i)
{
	int		*j;
	int		c;

	j = i;
	c = j[0];
	if (str[c] == '-' && str[c - 1] == 32 && str[c + 1] == 'n')
	{
		c++;
		while (str[c] == 'n' && str[c])
			c++;
		if (str[c] == 32 || str[c] == '\0')
		{
			ind_com->key = 1;
			j[0] = c;
			return (j);
		}
		else
		{
			i[3] = 1;
			return (i);
		}
	}
	else
		i[3] = 1;
	return (i);
}
