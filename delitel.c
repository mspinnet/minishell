/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delitel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:45:35 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 19:06:49 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_all	*delitel(char *str, t_all *all)
{
	t_del	del;

	del.i = 0;
	del.d = all->num_del;
	free(all);
	if (del.d == 0)
	{
		all = malloc(sizeof(t_all) * 1);
		all[0].num_del = 0;
		all[0].gnl = ft_strdup(str);
	}
	else
	{
		all = malloc(sizeof(t_all) * (del.d + 1));
		all->num_del = del.d;
		if (str[del.i] == ';' && str[del.i + 1] != ';')
		{
			while (del.i <= del.d)
				all[del.i++].gnl = ft_strdup("\0");
			prov_line(&all[0]);
		}
		else
			del_else(str, all, &del);
	}
	return (all);
}

void	del_else(char *str, t_all *all, t_del *del)
{
	del->k = 0;
	while (del->k <= del->d)
	{
		all[del->k].gnl = NULL;
		all[del->k].err_flag = 0;
		del->k++;
	}
	del->k = 0;
	while (str[del->k])
	{
		while_ne_del(str, del);
		if (str[del->k] == ';' && (str[del->k + 1] == '\0' ||
		str[del->k + 1] == ';'))
		{
			if_delitel(str, all, del);
			return ;
		}
		if_ne_term(str, all, del);
		if (del->err == 1)
			return ;
	}
}

void	if_ne_term(char *str, t_all *all, t_del *del)
{
	if (str[del->k] != '\0')
	{
		all[del->i++].gnl = ft_substr(str, del->c, del->k - del->c);
		if (prov_line(&all[0]) == 1)
		{
			while (del->d >= 0)
			{
				if (all[del->d].gnl != NULL)
					free(all[del->d].gnl);
				all[del->d].gnl = ft_strdup("\0");
				del->d--;
			}
			del->err = 1;
			return ;
		}
		del->k++;
	}
	else
		all[del->i++].gnl = ft_substr(str, del->c, del->k - del->c);
}

void	while_ne_del(char *str, t_del *del)
{
	del->c = del->k;
	while (str[del->k] != ';' && str[del->k] != '\0')
	{
		if (str[del->k] == 34 || str[del->k] == 39)
			del->k = if_cov(str, del->k);
		if (str[del->k] == 92 && (str[del->k + 1] == 34 ||
				str[del->k + 1] == 39))
			del->k += 2;
		if (str[del->k] == 92 && str[del->k + 1] == 32
			&& str[del->k - 1] != 92)
			del->k += 2;
		del->k++;
	}
}

void	if_delitel(char *str, t_all *all, t_del *del)
{
	if (str[del->k] == ';' && str[del->k + 1] == '\0')
	{
		all[del->i++].gnl = ft_substr(str, del->c, del->k - del->c);
		prov_line(&all[del->i - 1]);
		all[del->i++].gnl = ft_strdup("\0");
		return ;
	}
	else if (str[del->k] == ';' && str[del->k + 1] == ';')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `;;'\n", 52);
		all[del->i].err_flag = 1;
		while (del->d >= 0)
		{
			if (all[del->d].gnl != NULL)
				free(all[del->d].gnl);
			all[del->d].gnl = ft_strdup("\0");
			del->d--;
		}
		return ;
	}
}
