/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:31:07 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/12 10:55:25 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alpha_unset(char c)
{
	if (c == '_' || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c == '_' || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	check_unset_var(char *var_to_unset)
{
	int	i;

	i = 0;
	if ((var_to_unset[i] == '=' && var_to_unset[i + 1] == '\0')
		|| var_to_unset[i] == '\0' || is_alpha_unset(var_to_unset[i]) == 0)
	{
		printf("MINISHELL: unset: `%s': not a valid identifier\n", var_to_unset);
		return (1);
	}
	while (var_to_unset[i])
	{
		if (var_to_unset[i] == '=')
		{
			printf("MINISHELL: unset: `%s': not a valid identifier\n",
				var_to_unset);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_alpha_var(t_env *env, char *unset_alpha_var_name)
{
	t_env	*tmp_alpha;
	t_env	*current_alpha_node;

	tmp_alpha = NULL;
	current_alpha_node = find_first_alpha_node(env);
	if (!ft_strcmp(current_alpha_node->name, unset_alpha_var_name))
	{
		current_alpha_node->next_alpha->first_alpha_node = 1;
		return (0);
	}
	while (current_alpha_node->next)
	{
		if (!ft_strcmp(current_alpha_node->next_alpha->name,
				unset_alpha_var_name))
		{
			tmp_alpha = current_alpha_node->next_alpha->next_alpha;
			current_alpha_node->next_alpha = tmp_alpha;
			return (0);
		}
		current_alpha_node = current_alpha_node->next_alpha;
	}
	return (0);
}

int	unset_env_var(t_env *current_node, char *unset_var_name)
{
	t_env	*tmp;

	tmp = NULL;
	while (current_node->next)
	{
		if (!ft_strcmp(current_node->next->name, unset_var_name))
		{
			tmp = current_node->next->next;
			free_node(current_node->next);
			current_node->next = tmp;
			return (0);
		}
		current_node = current_node->next;
	}
	return (1);
}

int	unset_var(t_env **env, char *unset_var_name)
{
	t_env	*tmp;
	t_env	*current_node;

	tmp = NULL;
	current_node = *env;
	if (check_unset_var(unset_var_name) == 1)
		return (1);
	if (unset_alpha_var(*env, unset_var_name) == 1)
		return (1);
	if (!ft_strcmp((*env)->name, unset_var_name))
	{
		tmp = *env;
		*env = (*env)->next;
		free_node(tmp);
		return (0);
	}
	if (unset_env_var(current_node, unset_var_name) == 0)
		return (0);
	return (0);
}
