/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:31:07 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/05 10:03:22 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_unset_var(t_env **env, char *unset_var_name)
{
    t_env   *tmp = NULL;
    t_env   *current_node;

    current_node = *env;
    if(!ft_strcmp((*env)->name, unset_var_name))
    {
        tmp = (*env)->next;
        ft_free_node(*env);
        *env = tmp;
        return (1);
    }
    while (current_node->next)
    {
        if (!ft_strcmp(current_node->next->name, unset_var_name))
        {
            tmp = current_node->next->next;
            ft_free_node(current_node->next);
            current_node->next = tmp;
            return (1);
        }
        current_node = current_node->next;
    }
    return (0);
}