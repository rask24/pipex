/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_infile_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:45:34 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"

static int	_open_infile(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (fd);
}

pid_t	execute_infile_process(const char *infile_path, const char *cmd,
			int fds[2], char **envp)
{
	pid_t	pid;
	int		in_fd;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	in_fd = _open_infile(infile_path);
	xclose(fds[0]);
	xdup2(fds[1], STDOUT_FILENO);
	xdup2(in_fd, STDIN_FILENO);
	execute_command(cmd, envp);
	return (0);
}
