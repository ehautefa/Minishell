/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:28:50 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/12 10:55:25 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_value_exp(char *cmd, char **value, int i)
{
	int	k;

	k = 0;
	while (cmd[i] && (cmd[i] == '=' || cmd[i] == '\"' || cmd[i] == '\''))
		i++;
	while (cmd[i])
	{
		if (cmd[i] != '\"' && cmd[i] != '\'')
			(*value)[k++] = cmd[i];
		i++;
	}
	(*value)[k] = '\0';
}

int	recover_value_exp(char *cmd, char **value, int i)
{
	int	counter_l;
	int	tmp_index;

	counter_l = 0;
	tmp_index = i;
	while (cmd[i])
	{
		if (cmd[i] != '\"' || cmd[i] != '=' || cmd[i] != '\'')
			counter_l++;
		i++;
	}
	*value = malloc(sizeof(char) * counter_l + 1);
	if (!value)
		return (-1);
	fill_value_exp(cmd, value, tmp_index);
	return (0);
}

int	recover_name_exp(char *cmd, char **name, char **value)
{
	int	i;
	int	k;
	int	counter_l;

	i = -1;
	k = 0;
	counter_l = 0;
	while (cmd[++i] && cmd[i] != '=')
		counter_l++;
	*name = malloc(sizeof(char) * counter_l + 1);
	if (!name)
		return (-1);
	i = -1;
	while (cmd[++i] && cmd[i] != '=')
		(*name)[k++] = cmd[i];
	(*name)[k] = '\0';
	recover_value_exp(cmd, value, i);
	return (0);
}

int	export(t_env *env, char *var_export, int ret)
{
	char	*name_exp;
	char	*value_exp;	
	int		flag;

	value_exp = NULL;
	name_exp = NULL;
	flag = 0;
	ret = recover_name_exp(var_export, &name_exp, &value_exp);
	if (ret == -1)
		return (-1);
	if (!is_in_env(env, name_exp))
	{
		flag = set_valid_flag(var_export);
		ret = create_export_node(env, flag, name_exp, value_exp);
		if (ret == -1)
			return (-1);
	}
	else
	{
		ret = change_exp_value(env, name_exp, value_exp);
		if (ret == 0 && name_exp)
			free(name_exp);
	}
	return (ret);
}

int	export_var(t_env *env, char **var_export)
{
	int	ret;
	int	i;
	int	flag_msg;

	i = 1;
	flag_msg = 0;
	ret = 0;
	if (var_export && !var_export[1])
	{
		udpate_alpha_road(env);
		return (0);
	}
	while (var_export[i])
	{
		ret = check_export_value(var_export[i]);
		if (ret == 1 && flag_msg == 0)
		{
			printf("MINISHELL : export : not a valid identifier\n");
			flag_msg = 1;
		}
		if (ret == 0 && export(env, var_export[i], ret) == -1)
			return (print_error("ALLOCATION FAILED\n", -1, errno));
		i++;
	}
	return (ret);
}
