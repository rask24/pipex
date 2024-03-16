/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:33:17 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/16 16:35:46 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"

int	execute_pipe_process(const char *cmd, int prev_fds[2], int next_fds[2],
		char **envp)
{
	pid_t	pid;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	close(prev_fds[1]);
	xdup2(prev_fds[0], STDIN_FILENO);
	close(next_fds[0]);
	xdup2(next_fds[1], STDOUT_FILENO);
	execute_command(cmd, envp);
	return (0);
}
