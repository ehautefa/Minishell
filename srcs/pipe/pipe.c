/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:22:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 11:33:51 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipe(int *fd, int fd_std)
{;
	close(fd[!fd_std]);
	if (dup2(fd[fd_std], fd_std) == -1)
		return (print_error("FUCK OF THIS FUCKING SHIT !!!", -1));
	close(fd[fd_std]);
	return (0);
}

int	exe_pipe(t_mini *mini, t_cmd *cmd)
{
	int pid;
	int	ret;

	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		if (cmd->pipe_out)
		{
			close(cmd->pipe_out[0]);
			if (dup2(cmd->pipe_out[1], 1) == -1)
			{
				print_error("FUCK OF THIS FUCKING SHIT !!!", -1);
				exit (-1);
			}
			close(cmd->pipe_out[1]);
		}
		if (cmd->pipe_in)
		{
			close(cmd->pipe_in[1]);
			if (dup2(cmd->pipe_in[0], 0) == -1)
			{
				print_error("FUCK OF THIS FUCKING SHIT !!!", -1);
				exit (-1);
			}
			close(cmd->pipe_in[0]);
		}
		ret = redir(cmd->cmd, mini);
		if (ret == -1)
			exit (-1);
		exit(0);
	}
	else if (pid == -1)
	{
		print_error("FORK FUCKING FAILED !!!", -1);
		exit (-1);
	}
	return (0);
}
// int	exe_pipe(t_mini *mini, t_cmd *cmd)
// {
// 	int pid1;
// 	int pid2;
// 	int	ret;

// 	ret = 0;
// 	pid1 = 0;
// 	pid2 = 0;
// 	if (cmd->pipe_out)
// 	{
// 		pid1 = fork();
// 		if (pid1 == 0)
// 		{
// 			printf("SAlut c'est moi Lucette \n\n");
// 			exe_pipe(mini, cmd->next);
// 			exit(0);
// 		}
// 		if (!cmd->pipe_in)
// 		{
// 			pid2 = fork();
// 			if (pid2 == 0)
// 			{
// 				if (execute_pipe(cmd->pipe_out, 0, mini))
// 					return (-1);
// 				exit(0);
// 			}
// 		}
// 		// close(cmd->pipe_out[0]);
// 		// close(cmd->pipe_out[1]);
// 	}
// 	if (cmd->pipe_in)
// 		if (execute_pipe(cmd->pipe_in, 1, mini) == -1)
// 			return (-1);		
// 	ret = redir(cmd->cmd, mini);
// 	if (ret == -1)
// 		return (-1);
// 	printf("SAlut c'est moi Ginette \n");
// 	if (pid1)
// 		waitpid(pid1, NULL, 0);
// 	if (pid2)
// 		waitpid(pid2, NULL, 0);
// 	return (ret);