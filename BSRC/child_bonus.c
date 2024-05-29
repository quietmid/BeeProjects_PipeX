/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:31:43 by jlu               #+#    #+#             */
/*   Updated: 2024/04/17 17:30:00 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*exe_cmd(char *ag, char **path)
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

static void	exe_support(char *cmd, char **ag, char **envp, t_pipex *pipex)
{
	if (cmd[0] == '.')
	{
		if (access(cmd, X_OK) != 0)
		{
			error_msg(ERR_EXE, cmd);
			free_arr(ag);
			free_parent(pipex);
		}
		if (open(cmd, O_RDONLY | O_DIRECTORY) > 0)
		{
			error_msg(ERR_DIR, cmd);
			free_arr(ag);
			free_parent(pipex);
		}
	}
	if (execve(cmd, ag, envp) < 0)
	{
		error_msg(ERR, cmd);
		free_arr(ag);
		free_parent(pipex);
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
	pipex.cmd = find_cmd(pipex.cmd_a, pipex.path_cmds);
	if (!pipex.cmd && !pipex.path_cmds)
		error_msg(ERR_NO, pipex.cmd_a[0]);
	if (!pipex.cmd)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	exe_support(pipex.cmd, pipex.cmd_a, envp, &pipex);
}
