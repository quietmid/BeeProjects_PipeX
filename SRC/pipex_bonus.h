/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:42 by jlu               #+#    #+#             */
/*   Updated: 2024/03/28 15:43:00 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPE_X_BONUS_H
# define PIPE_X_BONUS_H

// other functions library
# include "../libft/libft.h"

// Library Headers
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>

//error definition

# define ERR_CMD "command not found"
# define ERR ""

typedef struct s_pipex
{
	pid_t	*pid;
	int		(*fd)[2];
	int		ag_count;
	int		filein;
	int		fileout;
	int		status;
	char	*path;
	char	*cmd;
	char	**path_cmds;
	char	**cmd_a;
}		t_pipex;

#endif