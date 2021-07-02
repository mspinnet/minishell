/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:11:25 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 19:06:47 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (((unsigned char)s1[i] - (unsigned char)s2[i]) > 0)
			return (1);
		if (((unsigned char)s1[i] - (unsigned char)s2[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int		for_join(t_command *ind_com, char *str, int j)
{
	int		i;
	int		c;

	free(ind_com->str);
	c = j;
	i = 0;
	while (str[j] != 34 && str[j] != 39 && str[j] != 92 && str[j] != '$'
		&& str[j] != '\0' && str[j] != 32)
	{
		i++;
		j++;
	}
	ind_com->str = ft_substr(str, c, i);
	return (j - 1);
}

int		if_slesh(t_command *ind_com, char *str, int j)
{
	free(ind_com->str);
	j++;
	ind_com->str = malloc(sizeof(char) * 1 + 1);
	if (str[j] != '\0')
	{
		ind_com->str[0] = str[j];
		ind_com->str[1] = '\0';
	}
	else
	{
		write(1, "minishell: syntax error: miss simbol after ", 43);
		ft_putchar_fd(92, 1);
		write(1, " !!!\n", 5);
		ind_com->err_flag = 1;
		g_var[0] = 258;
	}
	return (j);
}

void	make_free(t_all *all, int del)
{
	int		i;
	int		j;
	int		c;

	i = -1;
	while (++i <= del)
	{
		free(all[i].gnl);
		j = -1;
		while (++j <= all[i].num_com)
		{
			if (all[i].ind_com[j].str != NULL)
				free(all[i].ind_com[j].str);
			c = -1;
			while (all[i].ind_com[j].args[++c])
				if (all[i].ind_com[j].args[c] != NULL)
					free(all[i].ind_com[j].args[c]);
			free(all[i].ind_com[j].args);
		}
		free(all[i].ind_com);
	}
}

void	free_args(t_command *ind_com)
{
	int		i;

	i = -1;
	while (ind_com->args[++i] != NULL)
		free(ind_com->args[i]);
	free(ind_com->args);
}
