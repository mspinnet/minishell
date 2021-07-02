/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:54:34 by ejolyn            #+#    #+#             */
/*   Updated: 2021/03/25 12:49:17 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec_env(t_command *command, t_environment *gen_env)
{
	int i;

	i = -1;
	if (command->args[1] != NULL)
	{
		write(2, "minishell: ", 11);
		write(2, command->args[1], ft_strlen(command->args[1]));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	while (gen_env->env[++i] != NULL)
	{
		write(1, gen_env->env[i], ft_strlen(gen_env->env[i]));
		write(1, "\n", 1);
	}
	exit(0);
}

void	resize_env(char *str, t_environment *gen_env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (gen_env->env[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (gen_env->env[++i] != NULL)
	{
		new_env[i] = ft_strdup(gen_env->env[i]);
		free(gen_env->env[i]);
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free(gen_env->env);
	gen_env->env = new_env;
}

void	rewrite_env_exp(char *arg, t_environment *gen_env, int l)
{
	int		i;
	char	*new_exp;

	i = -1;
	new_exp = (char *)malloc(ft_strlen(arg) + 2);
	while (gen_env->exp[l][++i] != '=' && gen_env->exp[l][i] != '\0')
		new_exp[i] = gen_env->exp[l][i];
	if (gen_env->exp[l][i] == '\0')
	{
		resize_env(arg, gen_env);
		new_exp[i] = '\0';
	}
	if (ft_strrchr(arg, '=') != NULL)
	{
		i--;
		while (arg[++i] != '\0')
			new_exp[i] = arg[i];
		new_exp[i] = '\0';
	}
	free(gen_env->exp[l]);
	gen_env->exp[l] = new_exp;
	l = ft_find_key(arg, gen_env->env);
	free(gen_env->env[l]);
	gen_env->env[l] = ft_strdup(new_exp);
}

int		checker_env(t_command *command, int i, int j)
{
	if ((command->args[i][0] < 65 || command->args[i][0] > 90) &&
		(command->args[i][0] < 96 || command->args[i][0] > 123)
			&& command->args[i][0] != 95)
	{
		write(2, "Not a valid identifier\n", 23);
		g_var[0] = 1;
		return (0);
	}
	while (command->args[i][++j] != '=' && command->args[i][j] != '\0')
		if ((command->args[i][j] < 65 || command->args[i][j] > 90)
			&& (command->args[i][j] < 96 || command->args[i][j] > 123)
				&& command->args[i][j] != 95 &&
					(command->args[i][j] < '0' || command->args[i][j] > '9'))
		{
			write(2, "Not a valid identifier\n", 23);
			g_var[0] = 1;
			return (0);
		}
	return (1);
}

void	add_arg_to_env(t_command *command, t_environment *gen_env)
{
	int i;
	int j;
	int l;
	int k;

	i = 0;
	j = 0;
	l = 0;
	k = 0;
	while (command->args[++i] != NULL)
	{
		k = checker_env(command, i, j);
		if (k == 1 && (l = ft_find_key(command->args[i], gen_env->exp)) == -1)
		{
			if (ft_strrchr(command->args[i], '=') != NULL)
				resize_env(command->args[i], gen_env);
			resize_exp(command->args[i], gen_env);
		}
		else if (k == 1 && l != -1)
			rewrite_env_exp(command->args[i], gen_env, l);
	}
}
