/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:03:54 by ejolyn            #+#    #+#             */
/*   Updated: 2021/03/20 23:21:17 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env_copy = (char **)malloc(sizeof(char*) * (i + 1));
	i = -1;
	while (envp[++i] != NULL)
		env_copy[i] = ft_strdup(envp[i]);
	env_copy[i] = NULL;
	return (env_copy);
}

int		ft_find_key(char *args, char **env)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (args[len] != '=' && args[len] != '\0')
		len++;
	while (env[i] != NULL)
	{
		if (ft_strncmp(args, env[i], len) == 0 &&
			(env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int		ft_cmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i])
		i++;
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

int		oldpwd_path(t_environment *gen_env)
{
	int key;
	int i;

	key = ft_find_key("OLDPWD", gen_env->env);
	i = chdir(gen_env->env[key] + 7);
	if (i != -1)
		return (1);
	return (-1);
}
