/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:30:14 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 19:10:51 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**make_arguments(int num_arg, t_command *ind_com, char *str)
{
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	ind_com->args = malloc(sizeof(char*) * num_arg + 1);
	ind_com->key = 0;
	while_str(ind_com, str, i);
	ind_com->args[i[2]] = NULL;
	return (ind_com->args);
}

int		*while_str(t_command *ind_com, char *str, int *i)
{
	while (str[i[0]])
	{
		i[0] = is_space(str, i[0]);
		if (i[3] == 0 && i[2] > 0)
			i = minus_n(ind_com, str, i);
		i[1] = i[0];
		i = while_not_space(ind_com, str, i);
		if (i[1] != i[0])
			ind_com->args[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
		if (str[i[0]] == 32)
			i[0] = is_space(str, i[0]);
	}
	return (i);
}

int		*while_not_space(t_command *ind_com, char *str, int *i)
{
	while (str[i[0]] != 32 && str[i[0]])
	{
		if (str[i[0]] == 34 || str[i[0]] == 39)
			i[0] = if_cov(str, i[0]);
		if ((str[i[0]] == '|' && str[i[0] - 1] != 32 && str[i[0] + 1] != 32) ||
			(str[i[0]] == '|' && str[i[0] - 1] != 32 && str[i[0] + 1] == 32))
		{
			ind_com->args[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
			i[1] = i[0] + 1;
		}
		if (str[i[0]] == '|' && str[i[0] - 1] == 32 && str[i[0] + 1] != 32)
		{
			ind_com->args[i[2]++] = ft_substr(str, i[0], 1);
			i[1] = i[0] + 1;
		}
		i = if_redirect1(ind_com, str, i);
		i = if_redirect2(ind_com, str, i);
		if (str[i[0]] == 92 && (str[i[0] + 1] == 34 || str[i[0] + 1] == 39 ||
		str[i[0] + 1] == 92 || str[i[0] + 1] == '>' || str[i[0] + 1] == '<'))
			i[0] += 1;
		if (str[i[0]] == 92 && str[i[0] + 1] == 32 && str[i[0] - 1] != 92)
			i[0] += 1;
		i[0]++;
	}
	return (i);
}

int		*if_redirect1(t_command *ind_com, char *str, int *i)
{
	if (((str[i[0]] == '<' || (str[i[0]] == '>' && str[i[0] + 1] != '>' &&
	str[i[0] - 1] != '>')) && str[i[0] - 1] != 32 && str[i[0] + 1] != 32) ||
	((str[i[0]] == '<' || (str[i[0]] == '>' && str[i[0] + 1] != '>' &&
	str[i[0] - 1] != '>')) && str[i[0] - 1] != 32 && str[i[0] + 1] == 32))
	{
		ind_com->args[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
		ind_com->args[i[2]++] = ft_substr(str, i[0], 1);
		i[1] = i[0] + 1;
	}
	if ((str[i[0]] == '<' || (str[i[0]] == '>' && str[i[0] + 1] != '>' &&
	str[i[0] - 1] != '>')) && str[i[0] - 1] == 32 && str[i[0] + 1] != 32)
	{
		ind_com->args[i[2]++] = ft_substr(str, i[0], 1);
		i[1] = i[0] + 1;
	}
	return (i);
}

int		*if_redirect2(t_command *ind_com, char *str, int *i)
{
	if (((str[i[0]] == '>' && str[i[0] + 1] == '>') && str[i[0] - 1] != 32
	&& str[i[0] + 2] != 32) || ((str[i[0]] == '>' && str[i[0] + 1] == '>')
	&& str[i[0] - 1] != 32 && str[i[0] + 2] == 32))
	{
		ind_com->args[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
		ind_com->args[i[2]++] = ft_substr(str, i[0], 2);
		i[1] = i[0] + 2;
	}
	if ((str[i[0]] == '>' && str[i[0] + 1] == '>') && str[i[0] - 1] == 32
	&& str[i[0] + 2] != 32)
	{
		ind_com->args[i[2]++] = ft_substr(str, i[0], 2);
		i[1] = i[0] + 2;
	}
	return (i);
}
