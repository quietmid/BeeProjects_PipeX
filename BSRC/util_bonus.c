/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:13:04 by jlu               #+#    #+#             */
/*   Updated: 2024/04/17 17:29:02 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_msg(char *err, char *ag)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == ERR_INPUT)
		ft_putendl_fd(err, 2);
	if (err == ERR_CMD || err == ERR_NO)
	{
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(err, 2);
		exit (127);
	}
	if (err == ERR_EXE || err == ERR_DIR)
	{
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(err, 2);
		exit (126);
	}
	if (ag != NULL)
	{
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err)
		perror("");
	exit (EXIT_FAILURE);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->path_cmds)
	{
		while (pipex->path_cmds[i])
		{
			free(pipex->path_cmds[i]);
			i++;
		}
		free(pipex->path_cmds);
	}
	i = 0;
	if (pipex->fd)
	{
		while (i < pipex->pipe_n)
		{
			free(pipex->fd[i]);
			i++;
		}
		free(pipex->fd);
	}
	free(pipex->pid);
}

void	free_arr(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
			free(array[i++]);
		free(array);
	}
}

char	*find_path(char **envp)
{
	int	i;

	if (!envp || !*envp)
		*envp = "PATH=/bin:/usr/bin";
	i = 0;
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
		if (!*envp)
			return (NULL);
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
