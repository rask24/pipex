/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:44:57 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/09 22:06:55 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "exec.h"
#include "constants.h"
#include "libft.h"
#include "wrapper.h"

#include "process_internal.h"

static void	_write_heredoc_to_tmpfile(const char *delimiter)
{
	int		tmp_fd;
	char	*tmp;
	char	*del_nl;

	tmp_fd = xopen_with_permission(TMPFILE, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	del_nl = ft_xstrjoin(delimiter, "\n");
	while (true)
	{
		write(STDOUT_FILENO, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (tmp == NULL)
		{
			ft_printf("\n%s: warning: %s (wanted `%s')\n",
				PROG_NAME, HEREDOC_WARN, delimiter);
			break ;
		}
		if (tmp == NULL || !ft_strcmp(tmp, del_nl))
			break ;
		write(tmp_fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	free(tmp);
	free(del_nl);
	xclose(tmp_fd);
}

static int	_fetch_file_fd(t_process *pr)
{
	int	fd;

	if (pr->mode == MODE_HEREDOC)
	{
		_write_heredoc_to_tmpfile(pr->delimiter);
		fd = xopen(TMPFILE, O_RDONLY);
		xunlink(TMPFILE);
		return (fd);
	}
	else if (pr->mode == MODE_INFILE)
		return (xopen(pr->file_path, O_RDONLY));
	else if (pr->mode == MODE_OUTFILE_APPEND)
		return (xopen_with_permission(pr->file_path,
				O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	else if (pr->mode == MODE_OUTFILE_OVERWRITE)
		return (xopen_with_permission(pr->file_path,
				O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	else
		return (-1);
}

static void	_manage_redirection(t_process *pr, int file_fd)
{
	if (pr->mode == MODE_INFILE || pr->mode == MODE_HEREDOC)
	{
		xclose(pr->pipe_fd[0]);
		xdup2(file_fd, STDIN_FILENO);
		xdup2(pr->pipe_fd[1], STDOUT_FILENO);
	}
	else if (pr->mode == MODE_PIPE)
	{
		xclose(pr->pipe_fd[1]);
		xdup2(pr->pipe_fd[0], STDIN_FILENO);
		xclose(pr->next_pipe_fd[0]);
		xdup2(pr->next_pipe_fd[1], STDOUT_FILENO);
	}
	else
	{
		xclose(pr->pipe_fd[1]);
		xdup2(pr->pipe_fd[0], STDIN_FILENO);
		xdup2(file_fd, STDOUT_FILENO);
	}
}

pid_t	exec_single_process(t_process *pr, char **envp)
{
	pid_t	pid;
	int		file_fd;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	file_fd = _fetch_file_fd(pr);
	_manage_redirection(pr, file_fd);
	exec_command(pr->cmd, envp);
	return (0);
}
