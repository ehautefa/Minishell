/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/22 15:36:57 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_list(t_cmd *tmp2)
{
	int		i;
	t_cmd	*tmp;

	tmp = tmp2;
	while (tmp)
	{
		i = -1;
		printf("CMD : \n");
		while (tmp->cmd && tmp->cmd[++i])
			printf("cmd : %s\n", tmp->cmd[i]);
		tmp = tmp->next;
		printf("\n");
	}
}

int	parser(char **token, t_mini *mini)
{
	int		i;
	int		begin;

	mini->cmd = NULL;
	i = -1;
	begin = 0;
	while (token[++i])
	{
		if (!ft_strcmp(token[i], ";"))
		{
			mini->cmd = parse_pipe(mini->cmd, token, &begin, i);
			if (mini->cmd == NULL)
				return (-2);
		}
	}
	if (begin != ft_strslen(token))
		mini->cmd = parse_end(mini->cmd, token, &begin, i);
	free_strs(token);
	ft_execute_cmd(mini);
	ft_cmd_clear(mini->cmd);
	return (0);
}

int	expand(char **token, int i, char *value)
{
	if (value == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	token[i] = ft_realloc(token[i], ft_strlen(value));
	if (token[i] == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	ft_strcpy(token[i], value);
	return (0);
}

char **expand_var_env(char **token, t_env **env_lst, int old_ret)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (token && token[i])
	{
		
		if (token[i][0] == '$' && token[i][1] && token[i][1] == '{')
			token[i][ft_strlen(token[i]) - 1] = '\0';
		if (token[i][0] == '$')
		{
			tmp = *env_lst;
			while (tmp)
			{
				if ((token[i][1] && token[i][1] == '{' && ft_strcmp(&token[i][2], tmp->name) == 0) || 
					ft_strcmp(&token[i][1], tmp->name) == 0)
				{
					if (expand(token, i, tmp->value) == -1)
						return (NULL);
					tmp = NULL;
				}
				else
					tmp = tmp->next;
			}
			if (token[i][0] == '$' && token[i][1] == '?' && expand(token, i, ft_itoa(old_ret)) == -1)
				return (NULL);
			else if (token[i][0] == '$')
				token[i][0] = '\0';
		}
		i++;
	}
	return (token);
}

int	lexer(char *str, t_mini *mini)
{
	char	**token;
	int		ret;

	token = ft_split_dollar(str);
	if (token == NULL)
		return (-1);
	token = expand_var_env(token, mini->env, mini->old_ret);
	if (token == NULL)
		return (-1);
	token = ft_split_quote(ft_reverse_split(token, ' '));
	if (token == NULL && errno == -1)
		return (print_error("ALLOCATION FAILED\n", -1));
	else if (token == NULL)
		return (-2);
	token = remove_quote(token);
	ret = parser(token, mini);
	if (ret == -1)
		return (ret);
	return (ret);
}
