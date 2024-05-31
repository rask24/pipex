/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/31 14:48:52 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>

#include "constants.h"
#include "libft.h"
#include "pipex.h"
#include "process.h"
#include "utils.h"
#include "wrapper.h"

static void	_check_arguments(int argc, char **argv)
{
	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
		usage_error_exit();
}

static int	**_create_pipe_fds(int num_pipes)
{
	int	**pipe_fds;
	int	i;

	pipe_fds = ft_xmalloc(sizeof(int *) * num_pipes);
	i = 0;
	while (i < num_pipes)
	{
		pipe_fds[i] = ft_xmalloc(sizeof(int) * 2);
		xpipe((pipe_fds)[i]);
		i++;
	}
	return (pipe_fds);
}

static void	_free_pipe_fds(int **pipe_fds, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
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
			.pipe_fds = _create_pipe_fds(argc - 5),
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
			.pipe_fds = _create_pipe_fds(argc - 4),
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

	_check_arguments(argc, argv);
	_init_ctx(&ctx, argc, argv);
	ch_pids = exec_all_processes(&ctx, envp);
	_free_pipe_fds(ctx.pipe_fds, ctx.num_cmds - 1);
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
