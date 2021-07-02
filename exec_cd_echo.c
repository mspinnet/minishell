/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:43:11 by ejolyn            #+#    #+#             */
/*   Updated: 2021/03/26 12:35:57 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*find_home(t_environment *gen_env)
{
	int		i;
	int		j;
	char	*find;

	i = 0;
	j = 4;
	while (gen_env->env[i] != NULL && !(gen_env->env[i][0] == 'H'
				&& gen_env->env[i][1] == 'O' && gen_env->env[i][2] == 'M'
					&& gen_env->env[i][3] == 'E' && gen_env->env[i][4] == '='))
		i++;
	if (gen_env->env[i] == NULL)
		return (NULL);
	find = (char *)malloc(ft_strlen(gen_env->env[i]));
	while (gen_env->env[i][++j] != '\0')
		find[j - 5] = gen_env->env[i][j];
	return (find);
}

void	pwd_oldpwd(t_environment *gen_env, char *oldpwd)
{
	int		key;
	char	*pwd;

	pwd = ft_strjoin("OLDPWD=", oldpwd);
	if ((key = ft_find_key(pwd, gen_env->exp)) != -1)
		rewrite_env_exp(pwd, gen_env, key);
	oldpwd = getcwd(NULL, 1000);
	free(pwd);
	pwd = ft_strjoin("PWD=", oldpwd);
	if ((key = ft_find_key(pwd, gen_env->exp)) != -1)
		rewrite_env_exp(pwd, gen_env, key);
	free(pwd);
	free(oldpwd);
}

void	exec_cd(t_command *command, t_environment *gen_env)
{
	int		i;
	char	*home;

	i = -1;
	home = getcwd(NULL, 1000);
	free(home);
	if (command->args[1] == NULL && (home = find_home(gen_env)) != NULL)
	{
		i = chdir((const char *)home);
		pwd_oldpwd(gen_env, home);
		free(home);
	}
	else if ((i = chdir(command->args[1])) == 0)
		pwd_oldpwd(gen_env, home);
	home = NULL;
	if (i == -1 && (home = find_home(gen_env)) == NULL)
	{
		write(2, "minishell: ", 11);
		if (command->args[1] == NULL)
			write(2, "cd: HOME not set\n", 17);
		else
			perror(command->args[1]);
		g_var[0] = 1;
	}
	home != NULL ? free(home) : 0;
}

void	exec_echo(t_all *command, int n)
{
	int i;

	i = 0;
	while (command->ind_com[n].args[++i] != NULL)
	{
		write(1, command->ind_com[n].args[i],
			ft_strlen(command->ind_com[n].args[i]));
		if (command->ind_com[n].args[i + 1] != NULL
			&& command->ind_com[n].args[i][0] != '\0')
			write(1, " ", 1);
	}
	if (command->ind_com[n].key == 0)
		write(1, "\n", 1);
}

void	exec_pwd(t_command *command, t_environment *gen_env)
{
	char *pwd;

	(void)gen_env;
	(void)command;
	pwd = getcwd(NULL, 1000);
	if (pwd == NULL)
	{
		perror("pwd: ");
		exit(1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	exit(0);
}
