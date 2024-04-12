/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:31:43 by jlu               #+#    #+#             */
/*   Updated: 2024/04/12 17:31:33 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*exe_cmd(char *ag, char **path)
{
	char	*tmp;
	char	*command;

	if (path && ag)
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

void	the_piper(t_pipex pipex, char **ag, char **envp)
{
	int	i;

	i = -1;
	while (++i < pipex.pid_n)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] < 0)
			error_msg(ERR, NULL);
		if (pipex.pid[i] == 0)
			child_process(ag, envp, pipex, i);
	}
}

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

static void	exe_support(const char *cmd, char **ag, char **envp)
{
	if (execve(cmd, ag, envp) < 0)
	{
		free_arr(ag);
		error_msg(ERR, NULL);
	}
}

void	child_process(char **ag, char **envp, t_pipex pipex, int i)
{
	if (i == 0)
	{
		if (pipex.here_doc == 0)
			get_filein(ag, &pipex);
		sub_dup2(pipex.filein, pipex.fd[0][1]);
	}
	else if (i == (pipex.pipe_n))
	{
		get_fileout(ag[pipex.last_ag], &pipex);
		sub_dup2(pipex.fd[i - 1][0], pipex.fileout);
	}
	else
		sub_dup2(pipex.fd[i - 1][0], pipex.fd[i][1]);
	pipe_closer(&pipex);
	pipex.cmd_a = cmd_split(ag[2 + i + pipex.here_doc]);
	if (pipex.cmd_a[0][0] == '/')
		pipex.cmd = pipex.cmd_a[0];
	else
		pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd && !pipex.path_cmds)
		error_msg(ERR_NO, pipex.cmd_a[0]);
	if (!pipex.cmd)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	exe_support(pipex.cmd, pipex.cmd_a, envp);
}
