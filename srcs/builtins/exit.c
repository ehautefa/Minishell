/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/12 10:55:25 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_mini *mini, int ret, int flag_exec)
{
	if (mini->cmd)
		ft_cmd_clear(mini->cmd);
	if (mini->env)
		free_env(*mini->env);
	if (mini->exe)
		free_strs(mini->exe);
	if (mini->envp && mini->f_envp)
		free_strs(mini->envp);
	if (mini->red)
		free_red(mini->red, mini->nb_red);
	if (flag_exec == 0)
		return ;
	if (ret < -1)
		exit (ret);
	if (ret == -1 && mini->old_ret)
		exit(mini->old_ret);
	else if (ret != -1)
		exit(ret);
	else
		exit (0);
}

int	check_string(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free_node(env);
		env = tmp;
	}
	env = NULL;
}

void	ft_exit(t_mini *mini, int flag_exec)
{
	int	ret;
	int	flag_msg;

	ret = -1;
	flag_msg = 0;
	if (mini->nb_pipe == 0 && flag_exec != 0)
		write(2, "exit\n", 5);
	if (mini->exe && mini->exe[1])
		ret = ft_atoi(mini->exe[1]) % 256;
	if (mini->exe && mini->exe[1] && flag_exec != 0
		&& (check_string(mini->exe[1]) == 1 || ft_strlen(mini->exe[1]) > 19))
	{
		flag_msg = 1;
		ret = 2;
		write(2, "MINISHELL: exit: numeric argument required\n", 43);
	}
	if (mini->exe && flag_msg == 0 && ft_strslen(mini->exe) > 2
		&& flag_exec != 0)
	{
		write(2, "MINISHELL : exit: too many arguments\n", 37);
		ret = 1;
	}
	free_struct(mini, ret, flag_exec);
}
