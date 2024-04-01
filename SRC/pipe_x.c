/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:54 by jlu               #+#    #+#             */
/*   Updated: 2024/04/01 22:29:09 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

void	waiting(t_pipex *pipex)
{
	int	status;

	status = 0;
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &status, 0);
	if (WIFEXITED(status))
		pipex->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		pipex->status = WTERMSIG(status);
}

//join the command with the path and use access to find the command
static char	*exe_cmd(char *ag, char **path)
{
	char	*tmp;
	char	*command;

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
	return (NULL);
}

void	child_process1(char **ag, char **envp, t_pipex pipex)
{
	pipex.filein = open(ag[1], O_RDONLY);
	if (pipex.filein < 0)
		error_msg(ERR, ag[1]);
	dup2(pipex.fd[1], 1);
	close(pipex.fd[0]);
	dup2(pipex.filein, 0);
	close(pipex.filein);
	quotes_scan(ag[2]);
	pipex.cmd_a = ft_split(ag[2], 31);
	if (pipex.cmd_a[0] == NULL)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	if (pipex.cmd_a[0][0] == '/')
		pipex.cmd = pipex.cmd_a[0];
	else
		pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	if (execve(pipex.cmd, pipex.cmd_a, envp) < 0)
	{
		free_arr(pipex.cmd_a);
		error_msg(ERR, NULL);
	}
}

void	child_process2(char **ag, char **envp, t_pipex pipex)
{
	pipex.fileout = open(ag[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.fileout < 0)
		error_msg(ERR, ag[4]);
	dup2(pipex.fd[0], 0);
	close(pipex.fd[1]);
	dup2(pipex.fileout, 1);
	close(pipex.fileout);
	quotes_scan(ag[3]);
	pipex.cmd_a = ft_split(ag[3], 31);
	if (pipex.cmd_a[0] == NULL)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	if (pipex.cmd_a[0][0] == '/')
		pipex.cmd = pipex.cmd_a[0];
	else
		pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd)
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	if (execve(pipex.cmd, pipex.cmd_a, envp) < 0)
	{
		free_arr(pipex.cmd_a);
		error_msg(ERR, NULL);
	}
}

int	main(int ac, char **ag, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		error_msg(ERR_INPUT, NULL);
	pipex.status = 0;
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
	pipe_closer(&pipex);
	waiting(&pipex);
	free_arr(pipex.path_cmds);
	return (pipex.status);
}

/*
	27.3 updates: scan the agc first and replace sp(32) with 31 unless you encounter a ' or " then you ignore the space until another ' or " to close the argument. can't do "awk '{print "Hello"}'" as an argument. I get awk & {print Hello} instead of {print "Hello"}
	
	26.3 updates 2: fix the error code, its now giving the correct error code. The tester is still not passing. Especially if the commands itself has "" marks.
	
	26.3 updates: need to return the wexitstatus in waitpid to make sure that I return the right exit code. I am piping correctly and currently no memory leaks. 

	22.3 updates: used tester failed a lot of cases on STDERR, im not exiting correctly or printing out the correct exit code. I also need to check for ag[1] permission, if it doesn't allow us, I need to return errors too, permission denied.
*/