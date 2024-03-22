/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:51 by jlu               #+#    #+#             */
/*   Updated: 2024/03/22 18:06:26 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

// when the file can't be found
// zsh: no such file or directiory: `input`
// 0: stdinput 1: stdoutput 2:stderror 

void	error_msg(char *err, char *ag)
{
	ft_putstr_fd("pipex: ", 2);
	write(2, err, ft_strlen(err));
	if (err == ERR_CMD)
	{
		ft_putendl_fd(ag, 2);
		exit (errno);
	}
	if (err == ERR_FILE)
	{
		ft_putendl_fd(ag, 2);
		exit (errno);
	}
	if (err == ERR_FILE)
	{
		if (ag == NULL)
			ag = "\n";
		ft_putendl_fd(ag, 2);
		exit (errno);
	}
	exit (EXIT_FAILURE);
}

// go through the envp and search for PATH then get that string after the PATH 
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return(*envp + 5); // the 5 to get pass the PATH
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
