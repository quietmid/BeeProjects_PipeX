/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:18 by jlu               #+#    #+#             */
/*   Updated: 2024/03/29 17:13:20 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


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

void	get_filein(char **ag, t_pipex *pipex)
{
	pipex->filein = open (ag[1], O_RDONLY);
	if (pipex->filein < 0)
		error_msg(ERR, ag[1]),
}

void	get_fileout(char **ag, t_pipex *pipex, int cmd_n)
{
	pipex->fileout = open(ag[cmd_n - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fileout < 0)
		error_msg(ERR, ag[cmd_n - 1]);
}

int	main(int ac, char **ag, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	pipex.cmd_n = ac - 2;
	pipex.status = 0;
	get_filein(ag, &pipex);
	get_fileout(ag[ac - 1], &pipex, pipex.cmd_n);
	while (i <= pipex.cmd_n)
	{
		if (pipe(pipex.fd[i++]) < 0)
			error_msg(ERR, NULL);
	}
	pipex.path = find_path(envp);
	pipex.path_cmds = ft_split(pipex.path, ':');
	
}

/**/