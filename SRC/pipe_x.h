/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:49 by jlu               #+#    #+#             */
/*   Updated: 2024/03/12 16:11:05 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_X_H
# define PIPE_X_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

//error types
typedef enum s_error
{
		WRONG_ARGCOUNT,
		CMD_MISSING, // commond not found
		PIPE_FAIL,
		NO_PATH,
		FAIL_EXCU,
} t_error;

// Error Handling
void	error_msg_params(t_error error, char *msg);

#endif