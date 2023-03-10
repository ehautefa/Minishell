/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:20 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/12 10:55:25 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_cmd(t_mini *mini)
{
	if (mini->exe[1] && check_string(mini->exe[1]) == 0
		&& ft_strslen(mini->exe) > 2)
	{
		printf("MINISHELL: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	recover_cmd_part_2(t_mini *mini)
{
	if (!ft_strcmp(mini->exe[0], "exit"))
	{
		if (check_exit_cmd(mini) == 0)
			ft_exit(mini, 1);
	}
	else if (!ft_strcmp(mini->exe[0], "echo"))
		mini->old_ret = echo(mini->exe);
	else if (!ft_strcmp(mini->exe[0], "pwd"))
		mini->old_ret = print_pwd();
	else if (!ft_strncmp(mini->exe[0], "export", ft_strlen("export")))
		mini->old_ret = export_var(*mini->env, mini->exe);
	else if (!ft_strncmp(mini->exe[0], "cd", ft_strlen("cd")))
		mini->old_ret = change_directory(*mini->env, mini->exe[0],
				mini->exe[1]);
	else
		return (2);
	return (1);
}

int	recover_cmd(t_mini	*mini)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (mini->exe && mini->exe[0])
	{
		if (!ft_strcmp(mini->exe[0], "env"))
			mini->old_ret = print_env(*mini->env);
		else if (!ft_strncmp(mini->exe[0], "unset", ft_strlen("unset")))
		{
			while (mini->exe[++i])
			{
				flag = unset_var(mini->env, mini->exe[i]);
				if (flag == 1)
					mini->old_ret = 1;
			}
		}
		else
			return (recover_cmd_part_2(mini));
	}
	else
		return (2);
	return (1);
}
