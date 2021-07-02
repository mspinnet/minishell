/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:04:19 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 11:08:27 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	if_backspace(t_term *termc)
{
	if (termc->j > 1)
	{
		termc->j--;
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		free(termc->str2);
		termc->str2 = ft_substr(termc->str2, 0, termc->j);
		return ;
	}
	else if (termc->j == 1)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		free(termc->str2);
		termc->str2 = ft_strdup("\0");
		termc->j = 0;
		return ;
	}
}

void	if_ctrl_d(t_term *termc, struct termios *term)
{
	if (termc->j == 0)
	{
		term->c_lflag |= ECHO;
		term->c_lflag |= ICANON;
		term->c_lflag |= ISIG;
		tcsetattr(0, TCSANOW, term);
		termc->i = -1;
		while (termc->hist[++termc->i])
			free(termc->hist[termc->i]);
		free(termc->hist);
		free(termc->str2);
		exit(write(1, "exit\n", 5));
	}
	else
		return ;
}

void	if_ctrl_c_n(t_term *termc, struct termios *term, char *his)
{
	term->c_lflag |= ECHO;
	term->c_lflag |= ICANON;
	term->c_lflag |= ISIG;
	tcsetattr(0, TCSANOW, term);
	if (!strcmp(termc->str, "\03"))
	{
		free(termc->str2);
		termc->str2 = ft_strdup("\0");
		write(1, "\n", 1);
	}
	else if ((!strcmp(termc->str, "\n")))
	{
		termc->fd = open(his, O_CREAT | O_APPEND | O_RDWR, 0666);
		write(termc->fd, termc->str2, ft_strlen(termc->str2));
		write(termc->fd, "\n", 1);
		close(termc->fd);
		write(1, "\n", 1);
	}
	termc->i = -1;
	while (termc->hist[++termc->i])
		free(termc->hist[termc->i]);
	free(termc->hist);
}

void	if_notall(t_term *termc)
{
	write(0, termc->str, termc->l);
	free(termc->str2);
	termc->str2 = ft_strjoin(termc->str2, termc->str);
	termc->j++;
}

void	if_4_cond(t_term *termc, struct termios *term)
{
	if (!strcmp(termc->str, "\e[A"))
		if_up(termc);
	else if (!strcmp(termc->str, "\e[B"))
		if_down(termc);
	else if (!strcmp(termc->str, "\177"))
		if_backspace(termc);
	else if (!strcmp(termc->str, "\4"))
		if_ctrl_d(termc, term);
}
