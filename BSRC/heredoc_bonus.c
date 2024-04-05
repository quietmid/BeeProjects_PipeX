/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:37:47 by jlu               #+#    #+#             */
/*   Updated: 2024/04/05 16:06:43 by jlu              ###   ########.fr       */
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
	char	*buff;

	file = open(".here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file < 0)
		error_msg(ERR_HD, NULL);
	buff = NULL;
	while (1)
	{
		write (1, "heredoc>", 9);
		if (!ft_strncmp(ag, buff, ft_strlen(ag) + 1))
			break ;
		write (file, buff, ft_strlen(buff));
		write (file, "\n", 1);
		free (buff);
	}
	free(buff);
	close(file);
	pipex->filein = open(".here_doc", O_RDONLY);
	if (pipex->filein < 0)
	{
		unlink(".here_doc");
		error_msg(ERR_HD, NULL);
	}
}