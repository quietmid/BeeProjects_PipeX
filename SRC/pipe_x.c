/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:54 by jlu               #+#    #+#             */
/*   Updated: 2024/03/22 18:24:13 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

void	waiting(t_pipex *pipex)
{
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}
//join the command with the path and use access to find the command
static char	*exe_cmd(char *ag, char **path)
{
	char	*tmp;
	char	*command;

	if (!ag)
		perror("Error");
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
	return NULL;
}

void	child_process1(char **ag, char **envp, t_pipex pipex)
{	
	pipex.filein = open(ag[1], O_RDONLY);
	if (pipex.filein < 0)
		error_msg(ERR_FILE, ag[1]);
	dup2(pipex.fd[1], 1);
	close(pipex.fd[0]);
	dup2(pipex.filein, 0);
	pipex.cmd_a = ft_split(ag[2], ' ');
	if (pipex.cmd_a[0] == NULL)
		error_msg(ERR_SPT, NULL);
	pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd)
	{
		free_child(&pipex);
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	}
	if (execve(pipex.cmd, pipex.cmd_a, envp) < 0)
	{
		free_child(&pipex);
		error_msg(ERROR, NULL);
	}
}

void	child_process2(char **ag, char **envp, t_pipex pipex)
{
	pipex.fileout = open(ag[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex.fileout < 0)
		error_msg(ERR_FILE, ag[4]);
	dup2(pipex.fd[0], 0);
	close(pipex.fd[1]);
	dup2(pipex.fileout, 1);
	pipex.cmd_a = ft_split(ag[3], ' ');
	if (pipex.cmd_a[0] == NULL)
		error_msg(ERR_SPT, NULL);
	pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd)
	{
		free_child(&pipex);
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	}
	if (execve(pipex.cmd, pipex.cmd_a, envp) < 0)
		error_msg(ERROR, NULL);
}

int	main(int ac, char **ag, char **envp)
{
	t_pipex pipex;

	if (ac != 5)
		error_msg(ERR_INPUT, NULL);
	if (pipe(pipex.fd) < 0)
		error_msg(ERR_PIPE, NULL);
	pipex.path = find_path(envp);
	pipex.path_cmds = ft_split(pipex.path, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error_msg(ERR_FORK, NULL);
	if (pipex.pid1 == 0)
		child_process1(ag, envp, pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error_msg(ERR_FORK, NULL);
	if (pipex.pid2 == 0)
		child_process2(ag, envp, pipex);
	pipe_closer(&pipex);
	waiting(&pipex);
	free_parent(&pipex);
	return (EXIT_SUCCESS);
}

/*
	22.3 updates: used tester failed a lot of cases on STDERR, apparently im not exiting correctly or printing out the correct exit code. I also need to check for ag[1] permission, if it doesn't allow us, I need to return errors too, permission denied.
*/