/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:45:15 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"

static int	_open_new_tmpfile(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (fd);
}

static int	_open_tmpfile(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (fd);
}

static void	_write_heredoc_to_tmpfile(const char *delimiter)
{
	int		tmp_fd;
	char	*tmp;
	char	*del_nl;

	tmp_fd = _open_new_tmpfile(TMPFILE);
	del_nl = ft_strjoin(delimiter, "\n");
	while (true)
	{
		write(STDOUT_FILENO, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (tmp == NULL || !ft_strcmp(tmp, del_nl))
			break ;
		write(tmp_fd, tmp, strlen(tmp));
		free(tmp);
	}
	free(tmp);
	free(del_nl);
	xclose(tmp_fd);
}

pid_t	execute_heredoc_process(const char *delimiter, const char *cmd,
		int fds[2], char **envp)
{
	pid_t	pid;
	int		tmp_fd;

	pid = xfork();
	if (pid != CHILD)
		return (pid);
	_write_heredoc_to_tmpfile(delimiter);
	tmp_fd = _open_tmpfile(TMPFILE);
	xdup2(tmp_fd, STDIN_FILENO);
	xclose(fds[0]);
	xdup2(fds[1], STDOUT_FILENO);
	unlink(TMPFILE);
	execute_command(cmd, envp);
	return (0);
}
