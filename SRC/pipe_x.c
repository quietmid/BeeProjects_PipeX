/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:54 by jlu               #+#    #+#             */
/*   Updated: 2024/03/20 18:16:44 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

/*
pipex should take in 3 to 5 arguments. 
store the first arg and read into the the arg[2] and [3] to determine what it should do. 
apply the cmd to file1 and file2 
output the final
*/


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
	dup2(pipex.fd[1], 1);
	close(pipex.fd[0]);
	dup2(pipex.filein, 0);
	pipex.cmd_a = ft_split(ag[2], ' ');
	if (pipex.cmd_a[0] == NULL)
		error_msg(ERR_SPT, NULL);
	pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd)
	{
		//free child memory
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	}
	execve(pipex.cmd, pipex.cmd_a, envp);
	//if (execve(pipex.cmd, pipex.cmd_a, envp) < 0)
	//	printf("execve failed");
}

void	child_process2(char **ag, char **envp, t_pipex pipex)
{
	dup2(pipex.fd[0], 0);
	close(pipex.fd[1]);
	dup2(pipex.fileout, 1);
	pipex.cmd_a = ft_split(ag[3], ' ');
	if (pipex.cmd_a[0] == NULL)
		error_msg(ERR_SPT, NULL);
	pipex.cmd = exe_cmd(pipex.cmd_a[0], pipex.path_cmds);
	if (!pipex.cmd)
	{
		//free child memory
		error_msg(ERR_CMD, pipex.cmd_a[0]);
	}
	execve(pipex.cmd, pipex.cmd_a, envp);
	//if (execve(pipex.cmd, pipex.cmd_a, envp) < 0)
	//	printf("execve failed");
}

int	main(int ac, char **ag, char **envp)
{
	t_pipex pipex;
	// int i; //test
	
	// i  = 0; //test
	if (ac != 5)
		error_msg(ERR_INPUT, NULL);
	pipex.filein = open(ag[1], O_RDONLY);
	if (pipex.filein < 0)
		error_msg(ERR_FILE, ag[1]);
	pipex.fileout = open(ag[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex.fileout < 0)
		error_msg(ERR_FILE, ag[4]);
	if (pipe(pipex.fd) < 0)
		error_msg(ERR_PIPE, NULL);
	pipex.path = find_path(envp);
	// printf("path: %s\n", pipex.path);
	pipex.path_cmds = ft_split(pipex.path, ':');
	// while (pipex.path_cmds[i] != NULL)
	// {
	// 	printf("cmd %d: %s\n", i, pipex.path_cmds[i]);
	// 	i++;
	// }
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error_msg(ERR_FORK, NULL);
	if (pipex.pid1 == 0) //child process
		child_process1(ag, envp, pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error_msg(ERR_FORK, NULL);
	if (pipex.pid2 == 0)
		child_process2(ag, envp, pipex);
	// if the pid1 is a parent process, then it waits then weprocess the parent
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	// free parents
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