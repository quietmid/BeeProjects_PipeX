/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:51 by jlu               #+#    #+#             */
/*   Updated: 2024/03/28 13:34:20 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

// when the file can't be found
// zsh: no such file or directiory: `input`
// 0: stdinput 1: stdoutput 2:stderror 

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

// go through the envp and search for PATH then get that string after the PATH 
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

void	pipe_closer(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
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
		if ((str[i] == ' ' || str[i] == '	') && (count == 0 || count == 2))
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
