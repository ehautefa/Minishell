/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:44:56 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/07 03:24:14 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	int				first_alpha_node;
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*next_alpha;
}					t_env;



t_env	*find_first_alpha_node(t_env *env);
void    ft_exit(t_env *env);
void	udpate_alpha_road(t_env *env);
void 	free_node(t_env *node);
t_env	*create_env_lst(char **env);
int		fill_env_lst(char *str, t_env *env);
void	lstadd_back_env(t_env **alst, t_env *new);
t_env	*lstlast_env(t_env *lst);
int		fill_env_lst_value(char *str, t_env *env, int i);
int		check_env(t_env *env, char *var_export);
int		export_var(t_env *env, char *var_export);
int		create_export_node(t_env *env, char *name, char *value);
int		fill_env_lst_name(char *str, t_env *env);
int		unset_var(t_env **env, char *unset_var_name);
int		recover_cmd(char **cmd, t_env **env);

int		print_pwd(t_env *env);

/****************************/
/*			PRINT			*/
/****************************/

void	print_env(t_env *env);
void	print_env_alpha(t_env *env);

#endif
