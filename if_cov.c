/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_cov.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 22:21:56 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/24 20:18:39 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		if_cov2(t_command *ind_com, char *s, int j, t_environment *env)
{
	ind_com->str2 = ft_strdup("\0");
	j++;
	j = if_cov2_cikl(ind_com, s, j, env);
	if (s[j] == '\0')
	{
		write(1, "minishell: syntax error: don't close ", 37);
		ft_putchar_fd(34, 1);
		write(1, " !!!\n", 5);
		ind_com->err_flag = 1;
		g_var[0] = 258;
	}
	free(ind_com->str);
	free(ind_com->str2);
	ind_com->str = ft_strdup(ind_com->str2);
	return (j);
}

int		if_slesh_cov(t_command *ind_com, char *s, int j)
{
	if (s[j] == 92 && (s[j + 1] == 34 || s[j + 1] == 92 || s[j + 1] == '$'))
	{
		j = if_slesh(ind_com, s, j);
		free(ind_com->str2);
		ind_com->str2 = ft_strjoin(ind_com->str2, ind_com->str);
		j++;
	}
	if (s[j] == 92 && s[j + 1] != 34 && s[j + 1] != 92 && s[j + 1] != '$')
	{
		free(ind_com->str);
		ind_com->str = ft_substr(s, j, 1);
		free(ind_com->str2);
		ind_com->str2 = ft_strjoin(ind_com->str2, ind_com->str);
		j++;
	}
	return (j);
}

int		if_cov2_dol(t_command *ind_com, char *s, int j)
{
	if (s[j] == '$' && s[j + 1] == 34)
	{
		free(ind_com->str2);
		ind_com->str2 = ft_strjoin(ind_com->str2, "$");
		j++;
	}
	return (j);
}

int		if_cov2_cikl2(t_command *ind_com, char *s, int j, t_environment *env)
{
	if (s[j] == 39)
	{
		free(ind_com->str2);
		ind_com->str2 = ft_strjoin(ind_com->str2, "'");
		j++;
	}
	if (s[j] == '$' && s[j + 1] != 34)
	{
		j = if_dollar(ind_com, s, j, env);
		free(ind_com->str2);
		ind_com->str2 = ft_strjoin(ind_com->str2, ind_com->str);
		j++;
	}
	return (j);
}

int		if_cov2_cikl(t_command *ind_com, char *s, int j, t_environment *env)
{
	while (s[j] != 34 && s[j] != '\0')
	{
		j = if_slesh_cov(ind_com, s, j);
		j = if_cov2_cikl2(ind_com, s, j, env);
		if (s[j] == '$' && s[j + 1] == 34)
			j = if_cov2_dol(ind_com, s, j);
		while (s[j] != '$' && s[j] != 92 && s[j] != 34)
		{
			free(ind_com->str);
			ind_com->str = ft_substr(s, j, 1);
			free(ind_com->str2);
			ind_com->str2 = ft_strjoin(ind_com->str2, ind_com->str);
			j++;
		}
	}
	return (j);
}
