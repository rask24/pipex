/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_outfile_append_process.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:54:05 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"

pid_t	execute_outfile_append_process(const char *outfile_path,
			const char *cmd, int fds[2], char **envp)
{
	pid_t	pid;
	int		out_fd;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	out_fd = xopen_with_permission(outfile_path, O_WRONLY | O_CREAT | O_APPEND,
			0664);
	xclose(fds[1]);
	xdup2(fds[0], STDIN_FILENO);
	xdup2(out_fd, STDOUT_FILENO);
	execute_command(cmd, envp);
	return (0);
}
