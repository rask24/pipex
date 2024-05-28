/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:38:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/28 20:49:13 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "exec.h"
#include "wrapper.h"

#include "process_internal.h"

static void	_close_pipe_end(int fds[2])
{
	xclose(fds[0]);
	xclose(fds[1]);
}

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
	ft_dprintf(STDERR_FILENO, "envp: %p\n", pr->envp);
	ft_dprintf(STDERR_FILENO, "delimiter: %s\n", pr->delimiter);
}

static t_process	*_init_processes(int **fds, int argc, char **argv,
						char **envp)
{
	int			i;
	t_process	*prs;

	prs = ft_xmalloc(sizeof(t_process) * (argc - 3));
	prs[0] = (t_process){MODE_INFILE, argv[1], argv[2], fds[0], NULL,
		envp, NULL};
	i = 0;
	while (i < argc - 5)
	{
		prs[i + 1] = (t_process){MODE_PIPE, NULL, argv[3 + i], fds[i],
			fds[i + 1], envp, NULL};
		i++;
	}
	prs[i + 1] = (t_process){MODE_OUTFILE_OVERWRITE, argv[argc - 1],
		argv[argc - 2], fds[i], NULL, envp, NULL};
	return (prs);
}

int	exec_all_processes(int **fds, int argc, char **argv, char **envp)
{
	pid_t		ch_pid;
	int			status;
	int			i;
	t_process	*prs;

	prs = _init_processes(fds, argc, argv, envp);
	i = 0;
	while (i < argc - 3)
	{
		ch_pid = exec_single_process(&prs[i]);
		if (i > 0)
			_close_pipe_end(fds[i - 1]);
		waitpid(ch_pid, &status, 0);
		i++;
	}
	free(prs);
	return (status);
}

// int	_execute_heredoc_append_processes(int **fds, int argc, char **argv,
// 	char **envp)
// {
// 	pid_t	ch_pid;
// 	int		status;
// 	int		i;

// 	ch_pid = execute_heredoc_process(argv[2], argv[3], fds[0], envp);;
// 	waitpid(ch_pid, &status, 0);
// 	i = 0;
// 	while (i < argc - 6)
// 	{
// 		ch_pid = execute_pipe_process(argv[4 + i], fds[i], fds[i + 1], envp);
// 		_close_pipe_end(fds[i]);
// 		waitpid(ch_pid, &status, 0);
// 		i++;
// 	}
// 	ch_pid = execute_outfile_append_process(argv[argc - 1], argv[argc - 2],
// 			fds[i], envp);
// 	_close_pipe_end(fds[i]);
// 	waitpid(ch_pid, &status, 0);
// 	return (status);
// }

// int	execute_processes(int **fds, int argc, char **argv, char **envp)
// {
// 	int	status;

// 	if (!ft_strcmp(argv[1], "here_doc"))
// 		status = _execute_heredoc_append_processes(fds, argc, argv, envp);
// 	else
// 		status = _execute_infile_outfile_processes(fds, argc, argv, envp);
// 	return (status);
// }
