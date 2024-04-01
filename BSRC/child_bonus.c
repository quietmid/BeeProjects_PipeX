/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:31:43 by jlu               #+#    #+#             */
/*   Updated: 2024/03/30 13:39:21 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static void		sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child_process(char **ag, char **envp, t_pipex pipex)
{
	pipex.pid = fork();
	if (pipex.pid < 0)
		error_msg(ERR, NULL);
	if (pipex.idx == 0)
		sub_dup2(pipex.filein, pipex.fd[0][1]);
	else if (pipex.idx == (pipex.cmd_n - 1))
		sub_dup2(pipex.fd[pipex.idx][0], pipex.fileout);
	else
		sub_dup2(pipex.fd[pipex.idx][0], pipex.fd[pipex.idx + 1][1]);
	pipe_closer(&pipex);
	quotes_scan(ag[2 + pipex.idx]);
	pipex.cmd_a = ft_split(ag[2 + pipex.idx], 31);
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
