/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/13 19:46:05 by reasuke          ###   ########.fr       */
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

static void	_init_ctx(t_ctx *ctx, int argc, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		*ctx = (t_ctx)
		{
			.infile = NULL,
			.outfile = argv[argc - 1],
			.pipe_fds = create_pipe_fds(argc - 5),
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
			.pipe_fds = create_pipe_fds(argc - 4),
			.cmds = argv + 2,
			.is_here_doc = false,
			.delimiter = NULL,
			.num_cmds = argc - 3,
		};
}

static void	_wait_for_children(pid_t *ch_pids, int num_cmds, int *stat)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(ch_pids[i], stat, 0);
		i++;
	}
}

static void	_handle_exit_status(int stat)
{
	if (WIFEXITED(stat))
		exit(WEXITSTATUS(stat));
	else
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	int		stat;
	pid_t	*ch_pids;

	_check_arguments(argc, argv);
	_init_ctx(&ctx, argc, argv);
	ch_pids = exec_all_processes(&ctx, envp);
	free_pipe_fds(ctx.pipe_fds, ctx.num_cmds - 1);
	_wait_for_children(ch_pids, ctx.num_cmds, &stat);
	free(ch_pids);
	_handle_exit_status(stat);
}
