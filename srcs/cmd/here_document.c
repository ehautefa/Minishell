/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:23:06 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/26 11:48:37 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_file(t_redir *red)
{
	char	*str;
	char	*file;

	str = malloc(1);
	file = malloc(1);
	if (file == NULL || str == NULL)
		return (NULL);
	file[0] = '\0';
	while (ft_strcmp(str, red->path))
	{
		free(str);
		str = readline("> ");
		if (!str)
			return (NULL);
		if (ft_strcmp(str, red->path))
		{
			if (file[0] != '\0')
				file = ft_strjoin(file, "\n");
			file = ft_strjoin(file, str);
		}
		signal(SIGINT, sig_int);
	}
	free(str);
	return (file);
}

// int	do_here_doc(t_redir *red)
// {
// 	int		file_fd;
// 	char	*file;
	
// 	file_fd = open("tmp_minishell", O_WRONLY | O_CREAT | O_TRUNC , 0766);
// 	file = init_file(red);
// 	write(file_fd, file, ft_strlen(file));
// 	close(file_fd);
// 	free(file);
	
// 	red->save_fd = dup(red->n);
// 	file_fd = open("tmp_minishell", O_RDONLY);
// 	dup2(file_fd, red->n);
// 	close(file_fd);
// 	return (0);
// }

int	do_here_doc(t_redir *red)
{
	int		fd[2];
	char	*file;
	
	pipe(fd);
	file = init_file(red);
	if (file == NULL)
		return (-1);
	write(fd[1], file, ft_strlen(file));
	close(fd[1]);
	free(file);
	
	red->save_fd = dup(red->n);
	dup2(fd[0], red->n);
	close(fd[0]);
	return (0);
}
