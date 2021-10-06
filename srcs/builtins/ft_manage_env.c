/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:25:52 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/05 09:54:27 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Retours d'erreurs : -1, arret du programme.
**					   -2, erreur, mais le process continue. 
*/

void	ft_print_env(t_env *env)
{
	while (env)
	{
		if (env->name)
			printf("%s=", env->name);
		if (env->value)
			printf("%s", env->value);
		else
			printf("''");
		printf("\n");
		env = env->next;
	}
}

int	ft_fill_env_lst_value(char *str, t_env *env, int i)
{
	int	j;
	int	k;

	j = 1;
	k = i + 1;
	while (str[++i])
		j++;
	env->value = malloc(sizeof(char) * j + 1);
	if (!env->value)
		return (-1);
	j = 0;
	while (str[k])
		env->value[j++] = str[k++];
	env->value[j] = '\0';
	return (1);
}

int	ft_fill_env_lst_name(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	env->name = malloc(sizeof(char) * i + 1);
	if (!env->name)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		env->name[i] = str[i];
		i++;
	}
	env->name[i] = '\0';
	if (!ft_fill_env_lst_value(str, env, i))
		return (-1);
	return (1);
}

t_env	*create_env_lst(char **env)
{
	t_env	*env_lst;
	t_env	*current_node;
	int		i;

	i = 0;
	env_lst = NULL;
	current_node = NULL;
	while (env[i])
	{
		current_node = malloc(sizeof(t_env));
		ft_lstadd_back_env(&env_lst, current_node);
		if (!ft_fill_env_lst_name(env[i], current_node))
			return (NULL);
		i++;
	}
	return (env_lst);
}

// int	main(int argc, char **argv, char **env)
// {
	
// 	(void)argv;
// 	(void)argc;
// 	t_env	*env_lst = create_env_lst(env);
// 	ft_recover_cmd()
// 	return (0);
// }