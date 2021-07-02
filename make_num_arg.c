/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_num_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:37:16 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 19:08:56 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_struct(t_all *all)
{
	all->num_arg = 0;
	all->num_del = 0;
	all->num_com = 0;
	all->num_redir = 0;
}

void	make_num_arg(t_all *all, char *str)
{
	int		i;

	i = 0;
	init_struct(all);
	while (str[i])
	{
		i = is_space(str, i);
		while (str[i] != 32 && str[i])
		{
			if (str[i] == 34 || str[i] == 39)
				i = if_cov(str, i);
			i = if_pip_redir(all, str, i);
			i++;
		}
		if ((str[i] == 32 && str[i - 1] != 92) || str[i] == '\0')
		{
			i = is_space(str, i);
			all->num_arg++;
		}
	}
}

int		if_cov(char *str, int i)
{
	if (str[i] == 34)
	{
		i++;
		while (str[i] != 34 && str[i])
			i++;
	}
	if (str[i] == 39)
	{
		i++;
		while (str[i] != 39 && str[i])
			i++;
	}
	return (i);
}

int		if_pip_redir(t_all *all, char *s, int i)
{
	if (s[i] == 92 && (s[i + 1] == 34 || s[i + 1] == 39 ||
	s[i + 1] == 92 || s[i + 1] == ';'))
	{
		all->num_arg++;
		i += 2;
	}
	if (s[i] == ';')
		all->num_del++;
	if (s[i] == '|')
	{
		delitel_arg(all, s, i);
		all->num_com++;
	}
	if ((s[i] == '<' || (s[i] == '>' && s[i + 1] != '>' && s[i - 1] != '>')))
	{
		delitel_arg(all, s, i);
		all->num_redir++;
	}
	if ((s[i] == '>' && s[i + 1] == '>' && s[i + 2] != '>' && s[i - 1] != '>'))
	{
		delitel_arg(all, s, i);
		all->num_arg++;
		all->num_redir++;
	}
	return (i);
}

void	delitel_arg(t_all *all, char *s, int i)
{
	if ((s[i] == '<' || (s[i] == '>' && s[i + 1] != '>' && s[i - 1] != '>'))
		|| s[i] == '|')
	{
		if (s[i - 1] != 32)
			all->num_arg++;
		if (s[i + 1] != 32)
			all->num_arg++;
	}
	if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] != '>' && s[i - 1] != '>')
	{
		if (s[i - 1] != 32)
			all->num_arg++;
		if (s[i + 2] != 32)
			all->num_arg++;
	}
}
