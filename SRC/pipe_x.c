/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:54 by jlu               #+#    #+#             */
/*   Updated: 2024/04/15 19:15:11 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

static char	*exe_cmd(char *ag, char **path)
{
	char	*tmp;
	char	*command;

	if (path)
	{
		while (*path)
		{
			tmp = ft_strjoin(*path, "/");
			command = ft_strjoin(tmp, ag);
			free(tmp);
			if (access(command, 0) == 0)
				return (command);
			free(command);
			path++;
		}
	}
	return (NULL);
}

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child_process1(char **ag, char **envp, t_pipex pipex)
{
	pipex.filein = open(ag[1], O_RDONLY);
	if (pipex.filein < 0)
		error_msg(ERR, ag[1]);
	sub_dup2(pipex.filein, pipex.fd[1]);
	close(pipex.fd[0]);
	close(pipex.filein);
	quotes_scan(ag[2]);
	pipex.cmd_a = ft_split(ag[2], 31);
	if (pipex.cmd_a[0] == NULL)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	if (pipex.cmd_a[0][0] == '/' || pipex.cmd_a[0][0] == '.')
		pipex.cmd = pipex.cmd_a[0];
	else
		pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	if (execve(pipex.cmd, pipex.cmd_a, envp) < 0)
	{
		error_msg(ERR, pipex.cmd);
		free_arr(pipex.path_cmds);
		free_arr(pipex.cmd_a);
	}
}

void	child_process2(char **ag, char **envp, t_pipex pipex)
{
	pipex.fileout = open(ag[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.fileout < 0)
		error_msg(ERR, ag[4]);
	sub_dup2(pipex.fd[0], pipex.fileout);
	close(pipex.fd[1]);
	close(pipex.fileout);
	quotes_scan(ag[3]);
	pipex.cmd_a = ft_split(ag[3], 31);
	if (pipex.cmd_a[0] == NULL)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	if (pipex.cmd_a[0][0] == '/' || pipex.cmd_a[0][0] == '.')
		pipex.cmd = pipex.cmd_a[0];
	else
		pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	if (execve(pipex.cmd, pipex.cmd_a, envp) < 0)
	{
		error_msg(ERR, pipex.cmd);
		free_arr(pipex.path_cmds);
		free_arr(pipex.cmd_a);
	}
}

int	main(int ac, char **ag, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		error_msg(ERR_INPUT, NULL);
	if (pipe(pipex.fd) < 0)
		error_msg(ERR, NULL);
	pipex.path = find_path(envp);
	pipex.path_cmds = ft_split(pipex.path, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error_msg(ERR, NULL);
	if (pipex.pid1 == 0)
		child_process1(ag, envp, pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error_msg(ERR, NULL);
	if (pipex.pid2 == 0)
		child_process2(ag, envp, pipex);
	waiting(&pipex);
	free_arr(pipex.path_cmds);
	return (pipex.status);
}
