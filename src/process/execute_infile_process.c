/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/16 16:04:39 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"

int	execute_infile_process(const char *infile_path, const char *cmd,
		int fds[2], char **envp)
{
	pid_t	pid;
	int		in_fd;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	in_fd = open_infile(infile_path);
	xdup2(in_fd, STDIN_FILENO);
	xdup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	execute_command(cmd, envp);
	return (0);
}
