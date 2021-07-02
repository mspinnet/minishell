/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:11:24 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/24 20:18:57 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		if_dollar(t_command *ind_com, char *str, int j, t_environment *env)
{
	t_dollar	dol;

	if (ind_com->str != NULL)
		free(ind_com->str);
	dol.res = ft_strdup("\0");
	j++;
	if (str[j] == '\0')
	{
		free(dol.res);
		ind_com->str = ft_strdup("$");
		return (j);
	}
	if (str[j] == 92 || str[j] == '?')
	{
		vopr_or_slesh(ind_com, &dol, str[j]);
		return (j);
	}
	if (str[j] >= '1' && str[j] <= '9')
		return (j);
	dol.j = j;
	cikl_dol(str, &dol, env);
	ind_com->str = ft_strdup(dol.res);
	free(dol.res);
	return (dol.j);
}

void	vopr_or_slesh(t_command *ind_com, t_dollar *dol, char c)
{
	if (c == 92)
	{
		free(dol->res);
		dol->res = ft_strjoin(dol->res, "$");
		ind_com->str = ft_strdup(dol->res);
		free(dol->res);
	}
	if (c == '?')
	{
		dol->copy = ft_itoa(g_var[0]);
		free(dol->res);
		dol->res = ft_strjoin(dol->res, dol->copy);
		free(dol->copy);
	}
}

void	cikl_dol(char *str, t_dollar *dol, t_environment *env)
{
	while ((ft_isalnum(str[dol->j]) == 1 || str[dol->j] == '_'))
	{
		if (str[dol->j] == '0')
		{
			free(dol->res);
			dol->res = ft_strjoin(dol->res, "minishell");
		}
		if (ft_isalpha(str[dol->j]) == 1 || str[dol->j] == '_')
		{
			dol->l = dol->j;
			dol->f = 0;
			dol->c = 0;
			while ((ft_isalnum(str[dol->j]) == 1 || str[dol->j] == '_')
				&& str[dol->j] != '\0')
			{
				dol->c++;
				dol->j++;
			}
			search_env(dol, env, str);
		}
		break ;
	}
}

void	search_env(t_dollar *dol, t_environment *env, char *str)
{
	dol->j = dol->j - 1;
	dol->copy = ft_substr(str, dol->l, dol->c);
	dol->c = ft_strlen(dol->copy);
	while (env->env[dol->f] != NULL)
		if (ft_strncmp(env->env[dol->f], dol->copy, dol->c) == 0)
			if (env->env[dol->f][dol->c] == '=')
			{
				dol->l = ft_strlen(env->env[dol->f]);
				ft_bzero(dol->copy, ft_strlen(dol->copy));
				free(dol->copy);
				dol->copy = ft_substr(env->env[dol->f], dol->c + 1,
					dol->l - (dol->c + 1));
				break ;
			}
			else
				dol->f++;
		else
			dol->f++;
	if (env->env[dol->f] != NULL)
	{
		free(dol->res);
		dol->res = ft_strjoin(dol->res, dol->copy);
	}
	free(dol->copy);
}

void	init_redir(t_command *command)
{
	command->redir_fd[0] = 0;
	command->redir_fd[1] = 1;
	command->err_flag = 0;
}
