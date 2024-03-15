/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:20:08 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/15 16:35:51 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xfork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (pid);
}
