/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:24:02 by ejolyn            #+#    #+#             */
/*   Updated: 2021/03/20 20:08:47 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	delete_str_from_env(t_environment *gen_env, int numb)
{
	char	**new_env;
	int		i;

	i = 0;
	while (gen_env->env[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i));
	i = -1;
	while (++i < numb)
	{
		new_env[i] = ft_strdup(gen_env->env[i]);
		free(gen_env->env[i]);
	}
	free(gen_env->env[i]);
	while (gen_env->env[++i] != NULL)
	{
		new_env[i - 1] = ft_strdup(gen_env->env[i]);
		free(gen_env->env[i]);
	}
	new_env[i - 1] = NULL;
	free(gen_env->env[i]);
	free(gen_env->env);
	gen_env->env = new_env;
}

void	delete_str_from_exp(t_environment *gen_env, int numb)
{
	char	**new_exp;
	int		i;

	i = 0;
	while (gen_env->exp[i] != NULL)
		i++;
	new_exp = (char **)malloc(sizeof(char *) * (i));
	i = -1;
	while (++i < numb)
	{
		new_exp[i] = ft_strdup(gen_env->exp[i]);
		free(gen_env->exp[i]);
	}
	free(gen_env->exp[i]);
	while (gen_env->exp[++i] != NULL)
	{
		new_exp[i - 1] = ft_strdup(gen_env->exp[i]);
		free(gen_env->exp[i]);
	}
	new_exp[i - 1] = NULL;
	free(gen_env->exp[i]);
	free(gen_env->exp);
	gen_env->exp = new_exp;
}

void	unset_env(t_environment *gen_env, char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (gen_env->env[i] != NULL)
	{
		while (gen_env->env[i][len] != '=')
			len++;
		if (ft_strncmp(gen_env->env[i], str, len) == 0 &&
			(ft_strncmp(str, "_", 1) != 0))
		{
			delete_str_from_env(gen_env, i);
			delete_str_from_exp(gen_env, i);
			break ;
		}
		i++;
		len = 0;
	}
}

void	unset_exp(t_environment *gen_env, char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (gen_env->exp[i] != NULL)
	{
		while (gen_env->exp[i][len] != '=')
			len++;
		if (ft_strncmp(gen_env->exp[i], str, len) == 0 &&
			(ft_strncmp(str, "_", 1) != 0))
		{
			delete_str_from_exp(gen_env, i);
			break ;
		}
		i++;
		len = 0;
	}
}

void	exec_unset(t_command *command, t_environment *gen_env)
{
	int k;

	k = 0;
	while (command->args[++k] != NULL)
	{
		unset_env(gen_env, command->args[k]);
		unset_exp(gen_env, command->args[k]);
	}
}
