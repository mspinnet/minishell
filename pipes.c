/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:31:02 by ejolyn            #+#    #+#             */
/*   Updated: 2021/03/25 11:44:58 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parents_and_sig(pid_t *ret, int *status, int n, t_all *command)
{
	int f;

	while (n-- > 0)
	{
		if (command->ind_com[n].fd[0] != 0)
			close(command->ind_com[n].fd[0]);
		waitpid(ret[n], &status[n], 0);
		f = WSTOPSIG(status[n]);
		if (f != 0)
			g_var[0] = f;
	}
}

void	costyl_sps_norma(int tmpin, int tmpout)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}

void	pipes_and_redir_2(t_all *command, int n, int tmpout)
{
	dup2(command->ind_com[n].redir_fd[0], 0);
	if (command->ind_com[n].redir_fd[0] == 0)
	{
		dup2(command->ind_com[n - 1].fd[0], 0);
		close(command->ind_com[n - 1].fd[0]);
	}
	if (command->ind_com[n].redir_fd[1] == 1)
		dup2(tmpout, 1);
}

void	pipes_and_redir(t_all *command, int n, int tmpout)
{
	if (n == 0 && n != command->num_com)
	{
		dup2(command->ind_com[n].redir_fd[0], 0);
		if (command->ind_com[n].redir_fd[1] == 1)
			dup2(command->ind_com[n].fd[1], 1);
		close(command->ind_com[n].fd[1]);
	}
	else if (n == 0 && n == command->num_com)
		dup2(command->ind_com[n].redir_fd[0], 0);
	else if (n < command->num_com)
	{
		dup2(command->ind_com[n].redir_fd[0], 0);
		if (command->ind_com[n].redir_fd[0] == 0)
		{
			dup2(command->ind_com[n - 1].fd[0], 0);
			close(command->ind_com[n - 1].fd[0]);
		}
		if (command->ind_com[n].redir_fd[1] == 1)
			dup2(command->ind_com[n].fd[1], 1);
	}
	else if (n == command->num_com)
		pipes_and_redir_2(command, n, tmpout);
}
