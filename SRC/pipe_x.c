/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:54 by jlu               #+#    #+#             */
/*   Updated: 2024/03/15 09:59:49 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

/*
pipex should take in 3 to 5 arguments. 
store the first arg and read into the the arg[2] and [3] to determine what it should do. 
apply the cmd to file1 and file2 
output the final
*/

void	child_process(char **ag, char **envp, t_pipex pipex)
{
	pipex.filein = open(ag[1], O_RDONLY, 0777);
	if (pipex.filein == -1)
		error_msg("Read Failed pid = 0");
	dup2(pipex.fd[1], 0);
	dup2(pipex.filein, 1);
	close(pipex.fd[0]);
	close(pipex.filein);
	exe_cmd(ag[2], envp);
}

void	parent_process(char **ag, char **envp, t_pipex pipex)
{
	pipex.fileout = open(ag[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.fileout == -1)
		error_msg("Open Fail");
	dup2(pipex.fd[0], 0);
	dup2(pipex.fileout, 1);
	close(pipex.fd[1]);
	close(pipex.fileout);
	exe_cmd(ag[3], envp);
}

int	main(int ac, char **ag, char **envp)
{
	t_pipex pipex;
	
	if (ac == 5)
	{
		if (pipe(pipex.fd) == -1)
			error_msg("Pipe Fail");
		pipex.pid1 = fork();
		if (pipex.pid1 == -1)
			error_msg("Fork Fail");
		if (pipex.pid1 == 0) //child process
			child_process(ag, envp, pipex);
			// child process func
		// if the pid1 is a parent process, then it waits then we process the parent
		;
	}
	else
		error_msg("Cmon man, I need FOUR arguments!");
	// ag = NULL;
	// envp = NULL;
	return (EXIT_SUCCESS);
}

//int	main(int ac, char **av)
//{
//	int id = fork();
//	int n;
//	if (id == 0)
//		n = 1;
//	else
//		n = 6;
//	if (id != 0)
//		wait();
//	int i;
//	for (i = n; i < n + 5; i++)
//		printf("%d ", i);
//		fflush(stdout);
//}

/*
if (pid < 0)
	fork failed
	printf Fork failed
	return 1 
*/