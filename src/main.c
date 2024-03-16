/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/16 16:47:02 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utils.h"
#include "wrapper.h"
#include "process.h"

static void	_check_arguments(int argc)
{
	if (argc < 5)
		exit_with_message(__func__, MSG_INV_ARGS, INVALID_ARGUMENTS);
}

static void	_close_all_pipes(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

static void	_prep_pipe_fds(int *fds, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		xpipe(fds + (2 * i));
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		*fds;
	pid_t	ch_pid;
	int		status;
	int		i;

	_check_arguments(argc);
	fds = ft_xmalloc(sizeof(int) * (2 * argc - 8));
	_prep_pipe_fds(fds, argc - 4);
	ch_pid = execute_infile_process(argv[1], argv[2], fds, envp);
	waitpid(ch_pid, NULL, 0);
	i = 0;
	while (i < argc - 5)
	{
		ch_pid = execute_pipe_process(argv[3 + i], fds + (2 * i), fds + (2 * i + 2), envp);
		_close_all_pipes(fds + (2 * i));
		waitpid(ch_pid, NULL, 0);
		i++;
	}
	ch_pid = execute_outfile_process(argv[argc - 1], argv[argc - 2], fds + (2 * i), envp);
	_close_all_pipes(fds + (2 * i));
	waitpid(ch_pid, &status, 0);
	free(fds);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
