/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:49 by jlu               #+#    #+#             */
/*   Updated: 2024/03/13 20:47:28 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_X_H
# define PIPE_X_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Error Handling
void	error_msg(char *msg);

// Utils

void	find_cmd(char *ag, char **envp);

//Processes
void	child_process(char **ag, char **envp, int *fd);
void	parent_process(char **ag, char **envp, int *fd);

#endif