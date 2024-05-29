/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:18 by jlu               #+#    #+#             */
/*   Updated: 2024/04/19 13:03:13 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_filein(char **ag, t_pipex *pipex)
{
	pipex->filein = open(ag[1], O_RDONLY);
	if (pipex->filein < 0)
		error_msg(ERR, ag[1]);
}

void	get_fileout(char *ag, t_pipex *pipex)
{
	if (pipex->here_doc == 0)
	{
		pipex->fileout = open(ag, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fileout < 0)
			error_msg(ERR, ag);
	}
	else
	{
		pipex->fileout = open(ag, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->fileout < 0)
			error_msg(ERR, ag);
	}
}

static int	waiting(t_pipex *pipex)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	while (++i < pipex->pid_n)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = WTERMSIG(status);
	}
	return (status);
}

static void	pipes_creator(t_pipex *pipex)
{
	int	i;
	int	j;

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
	pipex->pid = (int *)malloc(sizeof(int) * pipex->pid_n);
	if (!pipex->pid)
		error_msg(ERR, NULL);
}

int	main(int ac, char **ag, char **envp)
{
	t_pipex	pipex;

	if (ac < arg_count(ag[1], &pipex))
		error_msg(ERR_INPUT, NULL);
	if (pipex.here_doc == 1)
		ft_here_doc(ag[2], &pipex);
	pipex.last_ag = ac - 1;
	pipex.cmd_n = ac - 3 - pipex.here_doc;
	pipex.pipe_n = pipex.cmd_n - 1;
	pipex.pid_n = pipex.pipe_n + 1;
	pipex.path = find_path(envp);
	pipex.path_cmds = ft_split(pipex.path, ':');
	pipes_creator(&pipex);
	the_piper(pipex, ag, envp);
	pipe_closer(&pipex);
	pipex.status = waiting(&pipex);
	if (pipex.here_doc == 1)
		unlink(".here_doc_temp");
	free_parent(&pipex);
	getchar();
	return (pipex.status);
}
