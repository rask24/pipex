/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:33:17 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/27 22:48:11 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "wrapper.h"

pid_t	execute_pipe_process(const char *cmd, int prev_fds[2], int next_fds[2],
			char **envp)
{
	pid_t	pid;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	xclose(prev_fds[1]);
	xdup2(prev_fds[0], STDIN_FILENO);
	xclose(next_fds[0]);
	xdup2(next_fds[1], STDOUT_FILENO);
	execute_command(cmd, envp);
	return (0);
}
