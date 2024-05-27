/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/27 22:48:15 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "wrapper.h"

pid_t	execute_infile_process(const char *infile_path, const char *cmd,
			int fds[2], char **envp)
{
	pid_t	pid;
	int		in_fd;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	in_fd = xopen(infile_path, O_RDONLY);
	xclose(fds[0]);
	xdup2(fds[1], STDOUT_FILENO);
	xdup2(in_fd, STDIN_FILENO);
	execute_command(cmd, envp);
	return (0);
}
