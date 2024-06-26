/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:51 by jlu               #+#    #+#             */
/*   Updated: 2024/04/17 16:27:41 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

void	error_msg(char *err, char *ag)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == ERR_INPUT)
		ft_putendl_fd(err, 2);
	if (err == ERR_CMD)
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
	if (err == ERR)
		perror("");
	exit (EXIT_FAILURE);
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

void	waiting(t_pipex *pipex)
{
	int	status;

	status = 0;
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &status, 0);
	if (WIFEXITED(status))
		pipex->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		pipex->status = WTERMSIG(status);
}

void	quotes_scan(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') \
		&& (count == 0 || count == 2))
			str[i] = 31;
		if (str[i] == c)
		{
			count += 1;
			str[i] = 31;
		}
		if ((str[i] == 39 || str[i] == 34) && count == 0)
		{
			c = str[i];
			count += 1;
			str[i] = 31;
		}
		i++;
	}
}
