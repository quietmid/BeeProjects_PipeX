/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:37:47 by jlu               #+#    #+#             */
/*   Updated: 2024/05/29 16:39:19 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	arg_count(char *ag, t_pipex *pipex)
{
	if (ag && !ft_strncmp("here_doc", ag, 9))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

void	ft_here_doc(char *ag, t_pipex *pipex)
{
	int		file;
	char	*line;
	char	*end;

	file = open(".here_doc_temp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file < 0)
		error_msg(ERR_HD, NULL);
	write (1, "heredoc>", 9);
	line = get_next_line(STDIN_FILENO);
	end = ft_strjoin(ag, "\n");
	while (ft_strcmp(line, end) != 0)
	{
		write (1, "heredoc>", 9);
		ft_putstr_fd(line, file);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(end);
	pipex->filein = open(".here_doc_temp", O_RDONLY);
	if (pipex->filein < 0)
	{
		unlink(".here_doc_temp");
		error_msg(ERR_HD, NULL);
	}
}
