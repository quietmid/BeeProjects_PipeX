/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:18 by jlu               #+#    #+#             */
/*   Updated: 2024/04/01 22:54:30 by jlu              ###   ########.fr       */
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
	pipex->filein = open (ag[1], O_RDONLY);
	if (pipex->filein < 0)
		error_msg(ERR, ag[1]);
}

void	get_fileout(char **ag, t_pipex *pipex, int cmd_n)
{
	pipex->fileout = open(ag[cmd_n - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fileout < 0)
		error_msg(ERR, ag[cmd_n - 1]);
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

int	main(int ac, char **ag, char **envp)
{
	t_pipex	pipex;

	pipex.idx = -1;
	pipex.cmd_n = ac - 2;
	pipex.status = 0;
	get_filein(ag, &pipex);
	get_fileout(ag[ac - 1], &pipex, pipex.cmd_n);
	while (pipex.idx < pipex.cmd_n)
	{
		if (pipe(pipex.fd[pipex.idx++]) < 0)
			error_msg(ERR, NULL);
	}
	pipex.path = find_path(envp);
	pipex.path_cmds = ft_split(pipex.path, ':');
	if (!pipex.path_cmds)
		error_msg(ERR, NULL);
	pipex.idx = -1;
	while (pipex.idx < pipex.cmd_n)
		child_process(ag, envp, pipex);
	pipe_closer(&pipex);
	// waitpid
	// free
	return (pipex.status);
}

/*
	1.4 added the pipe closer function that closes all the pipe at the end. I should probably also use that in the child process. The wait function, I should see if I can just wait for any child process or just the last one.
*/