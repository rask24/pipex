/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_outfile_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/16 16:49:34 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"

pid_t	execute_outfile_process(const char *outfile_path, const char *cmd,
			int fds[2], char **envp)
{
	pid_t	pid;
	int		out_fd;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	out_fd = open_outfile(outfile_path);
	xdup2(fds[0], STDIN_FILENO);
	xdup2(out_fd, STDOUT_FILENO);
	close(fds[1]);
	execute_command(cmd, envp);
	return (0);
}
