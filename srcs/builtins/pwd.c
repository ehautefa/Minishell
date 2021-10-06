/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:37:41 by user42            #+#    #+#             */
/*   Updated: 2021/10/05 16:48:57 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_pwd(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "PWD"))
			env = env->next;
		else
		{
			printf("%s\n", env->value);
			return (1);
		}
	}
	return (0);
}
