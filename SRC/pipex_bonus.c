/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:18 by jlu               #+#    #+#             */
/*   Updated: 2024/03/28 15:43:13 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x_bonus.h"

void	error_msg(char *err, char *ag)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == ERR_CMD)
	{
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(err, 2);
		exit (127);
	}
	if (ag != NULL)
	{
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": ", 2);
	}
	perror("");
	exit (EXIT_FAILURE);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	pipe_closer(t_pipex *pipex)
{
	// need to add it where it closes every other pipes
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

void	child_process1(char **ag, char **envp, t_pipex pipex, int i)
{
	dup2(pipex.fd[1], 1);
	close(pipex.fd[0]);
	dup2(pipex.filein, 0);
	close(pipex.filein);
	quotes_scan(ag[2 + i]);
	pipex.cmd_a = ft_split(ag[2 + i], 31);
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

void	get_filein(char **ag, t_pipex *pipex)
{
	pipex->filein = open (ag[1], O_RDONLY)
	if (pipex->filein < 0)
		error_msg(ERR, ag[1]),
}

void	get_fileout(char **ag, t_pipex *pipex, int ag_count)
{
	pipex->fileout = open(ag[ag_count - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.fileout < 0)
		error_msg(ERR, ag[ag_count - 1]);
}
int	main(int ac, char **ag, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	pipex.ag_count = ac - 2;
	pipex.status = 0;
	while (pipe(pipex.fd[i]) < 0)
		error_msg(ERR, NULL);
	pipex.path = find_path(envp);
	pipex.path_cmds = ft_split(pipex.path, ':');
	i = 0;
	while (i < ag_count)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] < 0)
			error_msg(ERR, NULL);
		if (pipex.pid[i] == 0)
			child_process1(ag, envp, pipex, i);
		i++;
	}
	
}