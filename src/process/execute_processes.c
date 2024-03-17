/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:38:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/17 12:50:08 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void	_close_pipe_end(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

void	execute_processes(int *fds, int argc, char **argv, char **envp)
{
	pid_t	ch_pid;
	int		status;
	int		i;

	ch_pid = execute_infile_process(argv[1], argv[2], fds, envp);
	waitpid(ch_pid, &status, 0);
	i = 0;
	while (i < argc - 5)
	{
		ch_pid = execute_pipe_process(argv[3 + i], fds + (2 * i),
				fds + (2 * i + 2), envp);
		_close_pipe_end(fds + (2 * i));
		waitpid(ch_pid, &status, 0);
		i++;
	}
	ch_pid = execute_outfile_process(argv[argc - 1], argv[argc - 2],
			fds + (2 * i), envp);
	_close_pipe_end(fds + (2 * i));
	waitpid(ch_pid, &status, 0);
	free(fds);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}
