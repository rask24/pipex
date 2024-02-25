/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:20:08 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 19:21:05 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xfork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAIL)
		exit_with_message(strerror(errno));
	return (pid);
}
