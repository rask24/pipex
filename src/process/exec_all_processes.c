/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:38:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 02:10:50 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "exec.h"
#include "pipex.h"
#include "wrapper.h"

#include "process_internal.h"

static void	_close_pipe_end(int fds[2])
{
	xclose(fds[0]);
	xclose(fds[1]);
}

// TODO: delete
__attribute__((unused)) static void	_dev_display_pr(t_process *pr)
{
	ft_dprintf(STDERR_FILENO, "mode: %d\n", pr->mode);
	ft_dprintf(STDERR_FILENO, "file_path: %s\n", pr->file_path);
	ft_dprintf(STDERR_FILENO, "cmd: %s\n", pr->cmd);
	ft_dprintf(STDERR_FILENO, "pipe_fd: %d, %d\n", pr->pipe_fd[0],
		pr->pipe_fd[1]);
	if (pr->next_pipe_fd)
		ft_dprintf(STDERR_FILENO, "next_pipe_fd: %d, %d\n", pr->next_pipe_fd[0],
			pr->next_pipe_fd[1]);
	ft_dprintf(STDERR_FILENO, "delimiter: %s\n", pr->delimiter);
}

int	exec_all_processes(t_ctx *ctx, char **envp)
{
	pid_t		ch_pid;
	int			status;
	int			i;
	t_process	*prs;

	prs = init_processes(ctx);
	i = 0;
	while (i < ctx->num_cmds)
	{
		ch_pid = exec_single_process(&prs[i], envp);
		if (i > 0)
			_close_pipe_end(ctx->pipe_fds[i - 1]);
		waitpid(ch_pid, &status, 0);
		i++;
	}
	free(prs);
	return (status);
}
