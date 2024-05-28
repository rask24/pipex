/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:35:38 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 02:01:20 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "pipex.h"
#include "wrapper.h"

#include "process_internal.h"

static t_process	_create_first_process(t_ctx *ctx)
{
	t_process	pr;

	if (ctx->is_here_doc)
		pr = (t_process)
		{
			.mode = MODE_HEREDOC,
			.file_path = TMPFILE,
			.cmd = ctx->cmds[0],
			.pipe_fd = ctx->pipe_fds[0],
			.delimiter = ctx->delimiter
		};
	else
		pr = (t_process)
		{
			.mode = MODE_INFILE,
			.file_path = ctx->infile,
			.cmd = ctx->cmds[0],
			.pipe_fd = ctx->pipe_fds[0]
		};
	return (pr);
}

static t_process	_create_pipe_process(t_ctx *ctx, int i)
{
	t_process	pr;

	pr = (t_process)
	{
		.mode = MODE_PIPE,
		.cmd = ctx->cmds[i],
		.pipe_fd = ctx->pipe_fds[i - 1],
		.next_pipe_fd = ctx->pipe_fds[i],
	};
	return (pr);
}

static t_process	_create_last_process(t_ctx *ctx)
{
	t_process	pr;

	if (ctx->is_here_doc)
		pr = (t_process)
		{
			.mode = MODE_OUTFILE_APPEND,
			.file_path = ctx->outfile,
			.cmd = ctx->cmds[ctx->num_cmds - 1],
			.pipe_fd = ctx->pipe_fds[ctx->num_cmds - 2],
		};
	else
		pr = (t_process)
		{
			.mode = MODE_OUTFILE_OVERWRITE,
			.file_path = ctx->outfile,
			.cmd = ctx->cmds[ctx->num_cmds - 1],
			.pipe_fd = ctx->pipe_fds[ctx->num_cmds - 2]
		};
	return (pr);
}

t_process	*init_processes(t_ctx *ctx)
{
	int			i;
	t_process	*prs;

	prs = ft_xmalloc(sizeof(t_process) * ctx->num_cmds);
	prs[0] = _create_first_process(ctx);
	i = 1;
	while (i < ctx->num_cmds - 1)
	{
		prs[i] = _create_pipe_process(ctx, i);
		i++;
	}
	prs[i] = _create_last_process(ctx);
	return (prs);
}
