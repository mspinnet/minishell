/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sys_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:06:58 by ejolyn            #+#    #+#             */
/*   Updated: 2021/03/25 13:04:03 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*find_path_helper(t_environment *gen_env,
							char *find, int i, char *command)
{
	int j;
	int k;
	int l;

	k = 5;
	while (gen_env->env[i][k] != '\0')
	{
		j = 0;
		l = 0;
		while (gen_env->env[i][k] != '\0' && gen_env->env[i][k] != ':')
			find[j++] = gen_env->env[i][k++];
		find[j++] = '/';
		while (command[l] != '\0')
			find[j++] = command[l++];
		find[j] = '\0';
		if ((l = open(find, O_RDONLY)) > 0)
		{
			close(l);
			return (find);
		}
		if (gen_env->env[i][k] != '\0')
			k++;
	}
	return (NULL);
}

char	*find_path(char *command, t_environment *gen_env)
{
	char	*find;
	int		i;

	i = 0;
	while (gen_env->env[i] != NULL &&
		!(gen_env->env[i][0] == 'P' && gen_env->env[i][1] == 'A'
		&& gen_env->env[i][2] == 'T' && gen_env->env[i][3] == 'H'
			&& gen_env->env[i][4] == '='))
		i++;
	if (gen_env->env[i] == NULL)
		return (NULL);
	find = (char *)malloc(ft_strlen(gen_env->env[i]));
	find = find_path_helper(gen_env, find, i, command);
	return (find);
}

int		check_shlvl(t_environment *gen_env, int key)
{
	int i;
	int val;

	i = 0;
	val = 1;
	while (gen_env->env[key][i] != '=')
		i++;
	val = ft_atoi(gen_env->env[key] + 6);
	while (gen_env->env[key][++i] != '\0')
		if ((gen_env->env[key][i] < '0' || gen_env->env[key][i] > '9')
			&& gen_env->env[key][i] != '-')
			val = 1000;
	if (val >= 999)
	{
		write(2, "minishell: warning: shell ", 26);
		write(2, "level too high or is not number, resetting to 1\n", 48);
		free(gen_env->env[key]);
		gen_env->env[key] = ft_strdup("SHLVL=1");
	}
	else if (val < 0)
		gen_env->env[key] = ft_strdup("SHLVL=0");
	else
		return (1);
	return (0);
}

void	shlvl(t_environment *gen_env)
{
	int		key;
	int		lvl;
	char	*tmp;

	if ((key = ft_find_key("SHLVL", gen_env->env)) != -1)
	{
		if (check_shlvl(gen_env, key) == 0)
			return ;
		while (*gen_env->env[key] != '=')
			gen_env->env[key]++;
		gen_env->env[key]++;
		lvl = ft_atoi(gen_env->env[key]);
		lvl++;
		tmp = ft_strjoin("SHLVL=", ft_itoa(lvl));
		gen_env->env[key] = tmp;
	}
	else
	{
		tmp = ft_strdup("SHLVL=1");
		resize_env(tmp, gen_env);
		resize_exp(tmp, gen_env);
	}
}

void	exec_system_funct(t_command *command, t_environment *gen_env)
{
	char	*str;
	int		fd;

	if ((fd = open(command->args[0], O_RDONLY)) > 0)
	{
		close(fd);
		str = command->args[0];
		if (ft_strncmp(command->args[0], "./minishell", 13) == 0)
			shlvl(gen_env);
	}
	else
		str = find_path(command->args[0], gen_env);
	if (str == NULL)
	{
		write(2, "minishell: ", 11);
		write(2, command->args[0], ft_strlen(command->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	execve(str, command->args, gen_env->env);
}
