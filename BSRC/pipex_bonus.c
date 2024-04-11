/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:18 by jlu               #+#    #+#             */
/*   Updated: 2024/04/11 17:23:21 by jlu              ###   ########.fr       */
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

	i = -1;
	while (++i <= pipex->pipe_n)
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
	pipex->pid = (int *)malloc(sizeof(int) * pipex->pipe_n);
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
	pipex.path = find_path(envp);
	pipex.path_cmds = ft_split(pipex.path, ':');
	pipes_creator(&pipex);
	the_piper(pipex, ag, envp);
	pipe_closer(&pipex);
	pipex.status = waiting(&pipex);
	if (pipex.here_doc == 1)
		unlink(".here_doc_temp");
	free_parent(&pipex);
	//getchar();
	return (pipex.status);
}

/*
	9.4 if unset the PATH and change permission file, my exit code is different. 
	5.4 here_doc completed. no memory leak with system(). god bless me tomorrow that it will stay like this. Tasks for tomorrow. Fix normi error
	
	5.4 adding here_doc but it is not working properly. It exits right away. Maybe I should use Elias method, just write into the terminal instead of creating a temp file.
	
	4.4 got it to work by fixing the right number of pipes. hard coded for filein exit code since filein isn't in waitpid so the waiting function doesn't matter. 5.4 need to add here_doc and understand what here_doc means also need to test with more cmds #
	3.4	using dprintf. Placed fork() at the wrong place, it was in the child process instead in the parent process. 
	2.4 updated the pipe situation instead of trying to make it like fd[i][2], it will be single fd[i], with odd number being write and even number being read end. not sure where it is seg faulting. updated my makefile, so it compiles bonus now
	
	1.4 added the pipe closer function that closes all the pipe at the end. I should probably also use that in the child process. The wait function, I should see if I can just wait for any child process or just the last one.
*/