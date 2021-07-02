/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:47:25 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/25 16:11:50 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_termcap(char *his)
{
	struct termios	term;
	t_term			termc;

	necanon(&term);
	init_term(&termc, his);
	while (1)
	{
		termc.l = read(0, termc.str, 100);
		termc.str[termc.l] = 0;
		if (!strcmp(termc.str, "\e[A") || !strcmp(termc.str, "\e[B")
		|| !strcmp(termc.str, "\177") || !strcmp(termc.str, "\4"))
			if_4_cond(&termc, &term);
		else if (!strcmp(termc.str, "\e[C") || !strcmp(termc.str, "\e[D"))
			continue ;
		else if (!strcmp(termc.str, "\03") || !strcmp(termc.str, "\n"))
		{
			if_ctrl_c_n(&termc, &term, his);
			break ;
		}
		else
			if_notall(&termc);
	}
	return (termc.str2);
}
