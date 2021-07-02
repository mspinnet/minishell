/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:55:59 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 17:56:18 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	if_one_right(t_command *ind_com, t_redir *re)
{
	close_redir(ind_com);
	ind_com->redir_fd[1] = open(ind_com->args[re->i + 1],
								O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (ind_com->redir_fd[1] == -1)
	{
		g_var[0] = 1;
		ind_com->err_flag = 1;
		write(1, "minishell: ", 11);
		perror(ind_com->args[re->i + 1]);
	}
	re->i += 2;
}

void	if_two_right(t_command *ind_com, t_redir *re)
{
	close_redir(ind_com);
	ind_com->redir_fd[1] = open(ind_com->args[re->i + 1],
								O_CREAT | O_APPEND | O_RDWR, 0666);
	if (ind_com->redir_fd[1] == -1)
	{
		g_var[0] = 1;
		ind_com->err_flag = 1;
		write(1, "minishell: ", 11);
		perror(ind_com->args[re->i + 1]);
	}
	re->i += 2;
}
