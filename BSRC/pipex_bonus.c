/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:18 by jlu               #+#    #+#             */
/*   Updated: 2024/04/03 16:53:15 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	pipe_closer(t_pipex *pipex)
{
	int i;
	int pipe_n;
	
	pipe_n = pipex->cmd_n - 1;
	i = 0;
	while (i < pipe_n)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
}

void	get_filein(char **ag, t_pipex *pipex)
{
	pipex->filein = open(ag[1], O_RDONLY);
	if (pipex->filein < 0)
		error_msg(ERR, ag[1]);
}

void	get_fileout(char *ag, t_pipex *pipex)
{
	pipex->fileout = open(ag, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fileout < 0)
		error_msg(ERR, ag);
}

void	waiting(t_pipex *pipex)
{
	int	status;

	status = 0;
	waitpid(pipex->pid, &status, 0);
	if (WIFEXITED(status))
		pipex->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		pipex->status = WTERMSIG(status);
}

static void	pipes_creator(t_pipex *pipex)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	pipex->fd = (int **)malloc(pipex->pipe_n * sizeof(int *));
	if (!pipex->fd)
		error_msg(ERR, NULL);
	while (j < pipex->pipe_n)
	{
		pipex->fd[j] = (int *)malloc(2 * sizeof(int));
		if (!pipex->fd[j])
			error_msg(ERR, NULL);
		j++;
	}
	while (i < pipex->cmd_n - 1)
	{
		if (pipe(pipex->fd[i]) < 0)
			error_msg(ERR, NULL);
		i++;
	}
	pipex->pid = (int *)malloc(sizeof(int) + pipex->pipe_n);
	if (!pipex->pid)
		error_msg(ERR, NULL);
}

static int	the_piper(t_pipex *pipex, char **ag, char **envp)
{
	int status;
	int	i;

	

	return (status);
}

int	main(int ac, char **ag, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
		error_msg(ERR_INPUT, NULL);
	get_filein(ag, &pipex);
	get_fileout(ag[ac - 1], &pipex);
	pipex.cmd_n = ac - 3; // - heredoc
	pipex.pipe_n = (pipex.cmd_n - 1) * 2; // for both ends
	pipex.status = 0;
	pipex.path = find_path(envp);
	pipex.path_cmds = ft_split(pipex.path, ':');
	if (!pipex.path_cmds)
		error_msg(ERR, NULL);
	pipes_creator(&pipex);
	pipex.idx = 0;

	// pid should be *pid and run the while loop and whild pid[i] == 0, its when I run the child process
	//dprintf(2, "pipex.cmd_n:%d\n", pipex.cmd_n);
	while (pipex.idx < pipex.cmd_n)
	{
		dprintf(2, "pipex.idx--%d\n", pipex.idx);
		ft_putstr_fd("debug2\n", 2);
		child_process(ag, envp, pipex);
		ft_putstr_fd("debug3\n", 2);
		pipex.idx++;
	}
	pipe_closer(&pipex);
	waitpid(-1, NULL, 0);
	//waiting(&pipex);
	// free
	return (0);
}

/*
	3.4	using dprintf
	2.4 updated the pipe situation instead of trying to make it like fd[i][2], it will be single fd[i], with odd number being write and even number being read end. not sure where it is seg faulting. updated my makefile, so it compiles bonus now
	
	1.4 added the pipe closer function that closes all the pipe at the end. I should probably also use that in the child process. The wait function, I should see if I can just wait for any child process or just the last one.
*/