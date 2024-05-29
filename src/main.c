/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 19:53:13 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "constants.h"
#include "libft.h"
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

static void	_init_ctx(t_ctx *ctx, int argc, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		*ctx = (t_ctx)
		{
			.infile = NULL,
			.outfile = argv[argc - 1],
			.pipe_fds = _create_pipe_fds(argc),
			.cmds = argv + 3,
			.is_here_doc = true,
			.delimiter = argv[2],
			.num_cmds = argc - 4,
		};
	else
		*ctx = (t_ctx)
		{
			.infile = argv[1],
			.outfile = argv[argc - 1],
			.pipe_fds = _create_pipe_fds(argc),
			.cmds = argv + 2,
			.is_here_doc = false,
			.delimiter = NULL,
			.num_cmds = argc - 3,
		};
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	int		stat;
	pid_t	*ch_pids;
	int		i;

	_check_arguments(argc);
	_init_ctx(&ctx, argc, argv);
	ch_pids = exec_all_processes(&ctx, envp);
	_free_pipe_fds(ctx.pipe_fds, argc);
	i = 0;
	while (i < ctx.num_cmds)
	{
		waitpid(ch_pids[i], &stat, 0);
		i++;
	}
	free(ch_pids);
	if (WIFEXITED(stat))
		exit(WEXITSTATUS(stat));
	else
		exit(FAILURE);
}
