/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prov_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:42:35 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/24 20:20:16 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_space(char *str, int i)
{
	if (str[i] == 32)
		while (str[i] == 32)
			i++;
	return (i);
}

char	*tab_space(char *str)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == 9)
			str2[i] = 32;
		else
			str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	free(str);
	return (str2);
}

int		prov_line(t_all *all)
{
	int		i;

	i = 0;
	i = is_space(all->gnl, i);
	if (all->gnl[i] == '\0')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `;'\n", 51);
		all->err_flag = 1;
		return (1);
	}
	return (0);
}

int		prov_line2(char *str, t_all *all)
{
	int		i;

	i = 0;
	i = is_space(str, i);
	if (str[i] == '\0')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `|'\n", 51);
		all->err_flag = 1;
		return (1);
	}
	return (0);
}

void	prov_line3(t_all *all, t_del *pip)
{
	if (prov_line2(all->ind_com[pip->d].str, all))
	{
		while (pip->d >= 0)
		{
			if (all->ind_com[pip->d].str != NULL)
				free(all->ind_com[pip->d].str);
			all->ind_com[pip->d].str = ft_strdup("\0");
			pip->d--;
		}
		pip->err = 1;
	}
}
