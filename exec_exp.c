/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:56:49 by ejolyn            #+#    #+#             */
/*   Updated: 2021/03/20 20:15:03 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**ft_sort(char **env, int size)
{
	int		i;
	int		j;
	char	*swap;

	i = 0;
	j = 1;
	while (j <= size - 1)
	{
		while (i <= size - 1 - j)
		{
			if (ft_cmp(env[i], env[i + 1]) > 0)
			{
				swap = env[i];
				env[i] = env[i + 1];
				env[i + 1] = swap;
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (env);
}

char	**copy_exp(char **envp)
{
	int		i;
	char	**env_copy;

	i = -1;
	while (envp[++i] != NULL)
		;
	env_copy = (char **)malloc(sizeof(char*) * (i + 1));
	i = -1;
	while (envp[++i] != NULL)
		env_copy[i] = ft_strdup(envp[i]);
	env_copy[i] = NULL;
	env_copy = ft_sort(env_copy, i);
	return (env_copy);
}

void	resize_exp(char *str, t_environment *gen_env)
{
	char	**new_exp;
	int		i;

	i = 0;
	while (gen_env->exp[i] != NULL)
		i++;
	new_exp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (gen_env->exp[++i] != NULL)
	{
		new_exp[i] = ft_strdup(gen_env->exp[i]);
		free(gen_env->exp[i]);
	}
	new_exp[i] = ft_strdup(str);
	new_exp[i + 1] = NULL;
	new_exp = ft_sort(new_exp, i + 1);
	free(gen_env->exp);
	gen_env->exp = new_exp;
}

void	exec_export_norm(t_environment *gen_env, int i, int j)
{
	int c;

	c = 34;
	if (gen_env->exp[i][j] == '=')
	{
		write(1, "=", 1);
		write(1, &c, 1);
		while (gen_env->exp[i][++j] != '\0')
			write(1, &gen_env->exp[i][j], 1);
		write(1, &c, 1);
	}
}

void	exec_export(t_command *command, t_environment *gen_env)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (command->args[1] != NULL)
		add_arg_to_env(command, gen_env);
	else if (command->args[1] == NULL)
		while (gen_env->exp[++i] != NULL)
		{
			write(1, "declare -x ", 11);
			while (gen_env->exp[i][++j] != '=' && gen_env->exp[i][j] != '\0')
				write(1, &gen_env->exp[i][j], 1);
			exec_export_norm(gen_env, i, j);
			write(1, "\n", 1);
			j = -1;
		}
}
