/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 18:01:40 by ejolyn            #+#    #+#             */
/*   Updated: 2021/03/25 14:16:15 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec_exit_daughter(t_command *command)
{
	int i;

	i = -1;
	if (command->args[1] != NULL)
	{
		while (command->args[1][++i] != '\0')
			if (command->args[1][i] <= '0' || command->args[1][i] >= '9')
			{
				write(2, "minishell: exit: ", 17);
				write(2, command->args[1], ft_strlen(command->args[1]));
				write(2, ": numeric argument required \n", 30);
				exit(255);
			}
		if (command->args[2] != NULL)
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return ;
		}
		exit(ft_atoi(command->args[1]) % 256);
	}
	write(1, "exit\n", 5);
	exit(0);
}

void	exec_choice(t_all *command, int n, t_environment *gen_env, int tmpout)
{
	pipes_and_redir(command, n, tmpout);
	if (ft_strncmp(command->ind_com[n].args[0], "echo", 5) == 0)
		exec_echo(command, n);
	else if ((ft_strncmp(command->ind_com[n].args[0], "pwd", 4) == 0))
		exec_pwd(&command->ind_com[n], gen_env);
	else if ((ft_strncmp(command->ind_com[n].args[0], "env", 4) == 0))
		exec_env(&command->ind_com[n], gen_env);
	else if ((ft_strncmp(command->ind_com[n].args[0], "cd", 3) == 0))
		exit(0);
	else if ((ft_strncmp(command->ind_com[n].args[0], "export", 7) == 0)
								&& command->ind_com[n].args[1] == NULL)
		exec_export(&command->ind_com[n], gen_env);
	else if ((ft_strncmp(command->ind_com[n].args[0], "export", 7) == 0)
								&& command->ind_com[n].args[1] != NULL)
		exit(0);
	else if ((ft_strncmp(command->ind_com[n].args[0], "exit", 5) == 0))
		exit(0);
	else if ((ft_strncmp(command->ind_com[n].args[0], "unset", 6) == 0))
		exit(0);
	else
		exec_system_funct(&command->ind_com[n], gen_env);
	exit(0);
}

void	exec_choice_parents(t_all *command, int n, t_environment *gen_env)
{
	if (command->num_com == 0)
	{
		if ((ft_strncmp(command->ind_com[n].args[0], "export", 7) == 0)
								&& command->ind_com[n].args[1] != NULL)
			exec_export(&command->ind_com[n], gen_env);
		else if ((ft_strncmp(command->ind_com[n].args[0], "cd", 3) == 0))
			exec_cd(&command->ind_com[n], gen_env);
		else if ((ft_strncmp(command->ind_com[n].args[0], "unset", 6) == 0))
			exec_unset(&command->ind_com[n], gen_env);
		else if ((ft_strncmp(command->ind_com[n].args[0], "exit", 5) == 0))
			exec_exit_daughter(&command->ind_com[n]);
	}
}

void	exec_chain(t_all *command, t_environment *gen_env)
{
	int		n;
	int		tmpin;
	int		tmpout;
	int		status[command->num_com + 1];
	pid_t	ret[command->num_com + 1];

	n = -1;
	tmpin = dup(0);
	tmpout = dup(1);
	while (++n < command->num_com)
		pipe(command->ind_com[n].fd);
	n = -1;
	while (++n <= command->num_com)
	{
		g_var[0] = 0;
		dup2(command->ind_com[n].redir_fd[1], 1);
		ret[n] = fork();
		if (ret[n] > 0)
			close(command->ind_com[n].fd[1]);
		if (ret[n] == 0)
			exec_choice(command, n, gen_env, tmpout);
		exec_choice_parents(command, n, gen_env);
	}
	costyl_sps_norma(tmpin, tmpout);
	parents_and_sig(ret, status, n, command);
}

void	exec_all(t_all *command, t_environment *gen_env)
{
	int j;

	j = -1;
	while (++j <= command->num_com)
		if (command->ind_com[j].args[0] == NULL || command->err_flag == 1)
			return ;
	if (ft_strncmp(command->ind_com[command->num_com].args[0], "cat", 4) == 0
		&& command->ind_com[command->num_com].args[1] == NULL)
		g_var[2] = 1;
	if (ft_strncmp(command->ind_com[command->num_com].args[0], "grep", 4) == 0
		&& command->ind_com[command->num_com].args[1] != NULL &&
			command->ind_com[command->num_com].args[2] == NULL &&
				command->ind_com[command->num_com].redir_fd[0] == 0)
		g_var[2] = 1;
	exec_chain(command, gen_env);
}
