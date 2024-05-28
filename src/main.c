/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 00:06:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "process.h"
#include "utils.h"
#include "wrapper.h"

static void	_check_arguments(int argc)
{
	if (argc < 5)
		error_exit(__func__, MSG_INV_ARGS, INVALID_ARGUMENTS);
}

static int	**_create_pipe_fds(int argc)
{
	int	num_fds;
	int	i;
	int	**pipe_fds;

	num_fds = argc - 4;
	pipe_fds = ft_xmalloc(sizeof(int *) * num_fds);
	i = 0;
	while (i < num_fds)
	{
		pipe_fds[i] = ft_xmalloc(sizeof(int) * 2);
		xpipe((pipe_fds)[i]);
		i++;
	}
	return (pipe_fds);
}

static void	_free_pipe_fds(int **pipe_fds, int argc)
{
	int	n;
	int	i;

	n = argc - 4;
	i = 0;
	while (i < n)
	{
		free(pipe_fds[i]);
		i++;
	}
	free(pipe_fds);
}

int	main(int argc, char **argv, char **envp)
{
	int		**pipe_fds;
	int		status;

	_check_arguments(argc);
	pipe_fds = _create_pipe_fds(argc);
	status = exec_all_processes(pipe_fds, argc, argv, envp);
	_free_pipe_fds(pipe_fds, argc);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (-1);
}
