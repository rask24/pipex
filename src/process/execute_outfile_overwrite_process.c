/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_outfile_overwrite_process.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:45:20 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"

static int	_open_outfile(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (fd);
}

pid_t	execute_outfile_overwrite_process(const char *outfile_path,
			const char *cmd, int fds[2], char **envp)
{
	pid_t	pid;
	int		out_fd;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	out_fd = _open_outfile(outfile_path);
	xclose(fds[1]);
	xdup2(fds[0], STDIN_FILENO);
	xdup2(out_fd, STDOUT_FILENO);
	execute_command(cmd, envp);
	return (0);
}
