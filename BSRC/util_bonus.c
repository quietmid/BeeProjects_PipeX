/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:13:04 by jlu               #+#    #+#             */
/*   Updated: 2024/04/09 17:30:35 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_msg(char *err, char *ag)
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

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->filein);
	close(pipex->fileout);
	while (pipex->path_cmds[i])
	{
		free(pipex->path_cmds[i]);
		i++;
	}
	free(pipex->path_cmds);
	//i = 0;
	//while (pipex->fd[i])
	//{
	//	free(pipex->fd[i]);
	//	i++;
	//}
	//free(pipex->fd);
}

void	free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

char	*find_path(char **envp, char *ag)
{
	while (ft_strncmp("PATH", *envp, 4))
	{	
		envp++;
		if (!*envp)
			error_msg(ERR_CMD, ag);
	}
	return (*envp + 5);
}

void	pipe_closer(t_pipex *pipex)
{
	int	i;
	int	pipe_n;

	pipe_n = pipex->cmd_n - 1;
	i = 0;
	while (i < pipe_n)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
}
