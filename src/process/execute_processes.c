/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:38:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:46:27 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "libft.h"
#include "wrapper.h"

static void	_close_pipe_end(int fds[2])
{
	xclose(fds[0]);
	xclose(fds[1]);
}

int	_execute_infile_outfile_processes(int **fds, int argc, char **argv,
	char **envp)
{
	pid_t	ch_pid;
	int		status;
	int		i;

	ch_pid = execute_infile_process(argv[1], argv[2], fds[0], envp);
	waitpid(ch_pid, &status, 0);
	i = 0;
	while (i < argc - 5)
	{
		ch_pid = execute_pipe_process(argv[3 + i], fds[i], fds[i + 1], envp);
		_close_pipe_end(fds[i]);
		waitpid(ch_pid, &status, 0);
		i++;
	}
	ch_pid = execute_outfile_overwrite_process(argv[argc - 1], argv[argc - 2],
			fds[i], envp);
	_close_pipe_end(fds[i]);
	waitpid(ch_pid, &status, 0);
	return (status);
}

int	_execute_heredoc_append_processes(int **fds, int argc, char **argv,
	char **envp)
{
	pid_t	ch_pid;
	int		status;
	int		i;

	ch_pid = execute_heredoc_process(argv[2], argv[3], fds[0], envp);
	waitpid(ch_pid, &status, 0);
	i = 0;
	while (i < argc - 6)
	{
		ch_pid = execute_pipe_process(argv[4 + i], fds[i], fds[i + 1], envp);
		_close_pipe_end(fds[i]);
		waitpid(ch_pid, &status, 0);
		i++;
	}
	ch_pid = execute_outfile_append_process(argv[argc - 1], argv[argc - 2],
			fds[i], envp);
	_close_pipe_end(fds[i]);
	waitpid(ch_pid, &status, 0);
	return (status);
}

int	execute_processes(int **fds, int argc, char **argv, char **envp)
{
	int	status;

	if (!ft_strcmp(argv[1], "here_doc"))
		status = _execute_heredoc_append_processes(fds, argc, argv, envp);
	else
		status = _execute_infile_outfile_processes(fds, argc, argv, envp);
	return (status);
}
