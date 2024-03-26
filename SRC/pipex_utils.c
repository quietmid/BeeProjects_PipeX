/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:51 by jlu               #+#    #+#             */
/*   Updated: 2024/03/26 15:23:32 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

// when the file can't be found
// zsh: no such file or directiory: `input`
// 0: stdinput 1: stdoutput 2:stderror 

void	error_msg(char *err, char *ag, t_pipex *pipex)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == ERR_INPUT)
	{
		ft_putendl_fd(err, 2);
		exit (EXIT_FAILURE);
	}
	if (err == ERR_CMD)
	{
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(err, 2);
		free_child(pipex);
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

// go through the envp and search for PATH then get that string after the PATH 
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_a[i] != NULL)
		free(pipex->cmd_a[i++]);
	if (pipex->cmd_a)
		free(pipex->cmd_a);
	free(pipex->cmd);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	close(pipex->filein);
	close(pipex->fileout);
	i = 0;
	while (pipex->path_cmds[i] != NULL)
		free(pipex->path_cmds[i++]);
	free(pipex->path_cmds);
}

void	pipe_closer(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}
