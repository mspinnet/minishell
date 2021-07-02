/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:36:02 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/26 14:31:58 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**redir(t_command *ind_com)
{
	t_redir	re;

	re.i = -1;
	while (ind_com->args[++re.i] != NULL)
		re.i++;
	re.args2 = malloc(sizeof(char*) * re.i + 1);
	re.i = 0;
	re.j = 0;
	cikl_re(ind_com, &re);
	free_args(ind_com);
	return (re.args2);
}

void	cikl_re(t_command *ind_com, t_redir *re)
{
	while (ind_com->args[re->i] != NULL)
	{
		if (ft_strncmp(ind_com->args[re->i], ">", 2) == 0 && re->i != 0)
		{
			open_fd(ind_com, re);
			continue ;
		}
		if (ft_strncmp(ind_com->args[re->i], "<", 2) == 0 && re->i != 0)
		{
			open_fd(ind_com, re);
			continue ;
		}
		if (ft_strncmp(ind_com->args[re->i], ">>", 3) == 0 && re->i != 0)
		{
			open_fd(ind_com, re);
			continue ;
		}
		re->args2[re->j] = ft_strdup(ind_com->args[re->i]);
		re->i++;
		re->j++;
	}
	re->args2[re->j] = NULL;
}

void	close_redir(t_command *ind_com)
{
	if (ind_com->redir_fd[1] != 1)
		close(ind_com->redir_fd[1]);
}

void	open_fd(t_command *ind_com, t_redir *re)
{
	if (ft_strncmp(ind_com->args[re->i], ">", 2) == 0 && re->i != 0)
	{
		if_one_right(ind_com, re);
		return ;
	}
	if (ft_strncmp(ind_com->args[re->i], "<", 2) == 0 && re->i != 0)
	{
		if_one_left(ind_com, re->i);
		re->i += 2;
		return ;
	}
	if (ft_strncmp(ind_com->args[re->i], ">>", 3) == 0 && re->i != 0)
	{
		if_two_right(ind_com, re);
		return ;
	}
}

void	if_one_left(t_command *ind_com, int i)
{
	if (ind_com->redir_fd[0] != 0)
		close(ind_com->redir_fd[0]);
	ind_com->redir_fd[0] = open(ind_com->args[i + 1], O_RDONLY, 0666);
	if (ind_com->redir_fd[0] < 0)
	{
		write(1, "minishell: ", 11);
		write(1, ind_com->args[i + 1], ft_strlen(ind_com->args[i + 1]));
		write(1, ": No such file or directory\n", 28);
		g_var[0] = 1;
		ind_com->err_flag = 1;
	}
}
