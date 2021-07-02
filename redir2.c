/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 22:02:13 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 17:56:26 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		redir_error(char *str)
{
	int		i;
	int		c;

	i = 0;
	while (str[i])
	{
		c = 0;
		i = while_ne_redir(str, i);
		while ((str[i] == '>' || str[i] == '<') && str[i])
		{
			i++;
			c++;
		}
		if (c <= 2 && str[i] >= '0' && str[i] <= '9')
			if (min_2(str, i, c) == 1)
				return (1);
		if (c > 2)
			if (max_2(str, i) == 1)
				return (1);
		i++;
	}
	return (0);
}

int		while_ne_redir(char *str, int i)
{
	while (str[i] != '>' && str[i] != '<' && str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = if_cov(str, i);
		if (str[i] == 92)
			i++;
		i++;
	}
	return (i);
}

int		max_2(char *str, int i)
{
	if (str[i - 1] == '>' && str[i - 2] != '>')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `>'\n", 50);
		return (1);
	}
	else if (str[i - 1] == '>' && str[i - 2] == '>')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `>>'\n", 51);
		return (1);
	}
	if (str[i - 1] == '<')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `<'\n", 50);
		return (1);
	}
	return (0);
}

int		min_2(char *str, int i, int c)
{
	int		res;
	char	*str2;

	if (c == 2 && str[i - 1] == '<')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `<'\n", 50);
		return (1);
	}
	res = ft_atoi(&str[i]);
	str2 = ft_itoa(res);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '>' || str[i] == '<')
	{
		g_var[0] = 258;
		write(1, "minishell: syntax error near unexpected token `", 47);
		ft_putstr_fd(str2, 1);
		write(1, "'\n", 2);
		free(str2);
		return (1);
	}
	if (str2 != NULL)
		free(str2);
	return (0);
}
