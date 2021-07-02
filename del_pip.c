/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_pip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:26:19 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 18:58:47 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_command	*delitel_pip(t_all *all)
{
	t_del	pip;

	pip.i = 0;
	pip.d = all->num_com;
	if (pip.d == 0)
	{
		all->ind_com = malloc(sizeof(t_command) * 1);
		all->num_com = 0;
		all->ind_com->str = ft_strdup(all->gnl);
	}
	else
	{
		all->ind_com = malloc(sizeof(t_command) * (pip.d + 1));
		all->num_com = pip.d;
		if (all->gnl[pip.i] == '|' && all->gnl[pip.i + 1] != '|')
		{
			while (pip.i <= pip.d)
				all->ind_com[pip.i++].str = ft_strdup("\0");
			prov_line2(all->ind_com[0].str, all);
		}
		else
			del_else_pip(all, &pip);
	}
	return (all->ind_com);
}

void		del_else_pip(t_all *all, t_del *pip)
{
	pip->k = 0;
	while (pip->k <= pip->d)
		all->ind_com[pip->k++].str = NULL;
	pip->k = 0;
	while (all->gnl[pip->k])
	{
		while_ne_pip(all, pip);
		if (all->gnl[pip->k] == '|' && (all->gnl[pip->k + 1] == '\0'
			|| all->gnl[pip->k + 1] == '|'))
		{
			if_pip(all, pip);
			return ;
		}
		if_ne_pip(all, pip);
		if (pip->err == 1)
			return ;
	}
	prov_line3(all, pip);
}

void		if_ne_pip(t_all *all, t_del *pip)
{
	if (all->gnl[pip->k] != '\0')
	{
		all->ind_com[pip->i++].str = ft_substr(all->gnl, pip->c,
			pip->k - pip->c);
		if (prov_line2(all->ind_com[0].str, all) == 1)
		{
			while (pip->d >= 0)
			{
				if (all->ind_com[pip->d].str != NULL)
					free(all->ind_com[pip->d].str);
				all->ind_com[pip->d].str = ft_strdup("\0");
				pip->d--;
			}
			pip->err = 1;
			return ;
		}
		pip->k++;
	}
	else
		all->ind_com[pip->i++].str = ft_substr(all->gnl, pip->c,
			pip->k - pip->c);
}

void		if_pip(t_all *all, t_del *pip)
{
	if (all->gnl[pip->k] == '|' && all->gnl[pip->k + 1] == '\0')
	{
		all->ind_com[pip->i].str = ft_substr(all->gnl, pip->c,
			pip->k - pip->c);
		pip->i++;
		all->ind_com[pip->i].str = ft_strdup("\0");
		prov_line2(all->ind_com[pip->i].str, all);
		return ;
	}
	else if (all->gnl[pip->k] == '|' && all->gnl[pip->k + 1] == '|')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `||'\n", 52);
		all->err_flag = 1;
		while (pip->d >= 0)
		{
			if (all->ind_com[pip->d].str != NULL)
				free(all->ind_com[pip->d].str);
			all->ind_com[pip->d].str = ft_strdup("\0");
			pip->d--;
		}
		return ;
	}
}

void		while_ne_pip(t_all *all, t_del *pip)
{
	pip->c = pip->k;
	while (all->gnl[pip->k] != '|' && all->gnl[pip->k])
	{
		if (all->gnl[pip->k] == 34 || all->gnl[pip->k] == 39)
			pip->k = if_cov(all->gnl, pip->k);
		if (all->gnl[pip->k] == 92 && (all->gnl[pip->k + 1] == 34 ||
				all->gnl[pip->k + 1] == 39))
			pip->k += 2;
		if (all->gnl[pip->k] == 92 && all->gnl[pip->k + 1] == 32)
			pip->k += 2;
		pip->k++;
	}
}
