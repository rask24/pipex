/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:38:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/09 21:41:04 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "exec.h"
#include "libft.h"
#include "pipex.h"
#include "wrapper.h"

#include "process_internal.h"

static void	_close_pipe_end(int fds[2])
{
	xclose(fds[0]);
	xclose(fds[1]);
}

pid_t	*exec_all_processes(t_ctx *ctx, char **envp)
{
	int			i;
	t_process	*prs;
	pid_t		*ch_pids;

	prs = init_processes(ctx);
	ch_pids = ft_xmalloc(sizeof(pid_t) * ctx->num_cmds);
	i = 0;
	while (i < ctx->num_cmds)
	{
		ch_pids[i] = exec_single_process(&prs[i], envp);
		if (i > 0)
			_close_pipe_end(ctx->pipe_fds[i - 1]);
		if (ctx->is_here_doc && i == 0)
			waitpid(ch_pids[i], NULL, 0);
		i++;
	}
	free(prs);
	return (ch_pids);
}
