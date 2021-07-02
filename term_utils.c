/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:02:25 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 11:08:33 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	necanon(struct termios *term)
{
	tcgetattr(0, term);
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, term);
	tgetent(0, "xterm-256color");
	tputs(save_cursor, 1, ft_putchar);
}

void	init_term(t_term *termc, char *his)
{
	termc->str2 = NULL;
	termc->fd = open(his, O_RDONLY);
	termc->i = 0;
	termc->l = 0;
	while (read(termc->fd, &termc->buf, 1))
		termc->l++;
	close(termc->fd);
	termc->str2 = malloc(sizeof(char) * termc->l + 1);
	termc->fd = open(his, O_RDONLY);
	while (read(termc->fd, &termc->buf, 1))
		termc->str2[termc->i++] = termc->buf;
	termc->str2[termc->i] = '\0';
	close(termc->fd);
	termc->hist = ft_split(termc->str2, '\n');
	termc->c = 0;
	termc->i = -1;
	while (termc->hist[++termc->i])
		termc->c++;
	termc->i = termc->c;
	termc->j = 0;
	free(termc->str2);
	termc->str2 = ft_strdup("\0");
}

void	if_up(t_term *termc)
{
	if (termc->c == 0)
		return ;
	termc->i--;
	if (termc->i <= 0)
		termc->i = 0;
	if (termc->i >= termc->c)
		termc->i = termc->c - 1;
	tputs(restore_cursor, 0, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	write(0, termc->hist[termc->i], ft_strlen(termc->hist[termc->i]));
	free(termc->str2);
	termc->str2 = ft_strdup(termc->hist[termc->i]);
	termc->j = ft_strlen(termc->str2);
}

void	if_down(t_term *termc)
{
	termc->i++;
	if (termc->i <= 0)
		termc->i = 0;
	if (termc->i <= termc->c - 1)
	{
		tputs(restore_cursor, 0, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(0, termc->hist[termc->i], ft_strlen(termc->hist[termc->i]));
		free(termc->str2);
		termc->str2 = ft_strdup(termc->hist[termc->i]);
		termc->j = ft_strlen(termc->str2);
	}
	if (termc->i >= termc->c)
	{
		tputs(restore_cursor, 0, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		free(termc->str2);
		termc->str2 = ft_strdup("\0");
		termc->j = 0;
	}
}
