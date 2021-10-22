/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:10:50 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/22 10:51:34 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_substrs(char **s, size_t len)
{
	char		**str;
	size_t		i;
	size_t		size;

	i = -1;
	str = malloc((len + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (++i < len && s[i])
	{
		size = ft_strlen(s[i]);
		str[i] = malloc((size + 1) * sizeof(char));
		if (str[i] == NULL)
			return (NULL);
		ft_strlcpy(str[i], s[i], size + 1);
	}
	str[i] = NULL;
	return (str);
}

t_cmd	*find_cmd_struct(t_cmd *cmd, char **tmp, int in, int out)
{
	t_cmd	*last;
	t_cmd	*new;

	last = ft_cmd_last(cmd);
	if (cmd && last->cmd == NULL)
	{
		last->cmd = tmp;
		last->pipe_out = out;
	}
	else if (!cmd)
	{
		cmd = ft_cmd_new(tmp, in, out);
		if (cmd == NULL)
			return (NULL);
	}
	else
	{
		new = ft_cmd_new(tmp, in, out);
		if (new == NULL)
			return (NULL);
		ft_cmd_add_back(&cmd, new);
	}
	return (cmd);
}

t_cmd	*parse_pipe(t_cmd *cmd, char **token, int *begin, int i)
{
	char	**tmp;
	t_cmd	*new;

	tmp = ft_substrs(&token[*begin], i - *begin);
	if (tmp == NULL)
		return (NULL);
	cmd = find_cmd_struct(cmd, tmp, 0, 1);
	if (cmd == NULL)
		return (NULL);
	new = ft_cmd_new(NULL, 1, 0);
	if (new == NULL)
		return (NULL);
	ft_cmd_add_back(&cmd, new);
	*begin = i + 1;
	return (cmd);
}

t_cmd	*parse_end(t_cmd *cmd, char **token, int *begin, int i)
{
	char	**tmp;
	t_cmd	*last;

	tmp = ft_substrs(&token[*begin], i - *begin);
	if (tmp == NULL)
		return (NULL);
	last = ft_cmd_last(cmd);
	cmd = find_cmd_struct(cmd, tmp, 0, 0);
	if (cmd == NULL)
		return (NULL);
	*begin = i + 1;
	return (cmd);
}

char	*erase_copy(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src && dest && src[i] && dest[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**remove_quote(char **token)
{
	int	i;
	int	j;

	j = 0;
	while (token[j])
	{
		i = 0;
		while (token[j][i])
		{
			if (token[j][i] == '\"' || token[j][i] == '\'')
			{
				erase_copy(&token[j][i + 1], &token[j][i]);
			}
			else
				i++;
		}
		j++;
	}
	return (token);
}