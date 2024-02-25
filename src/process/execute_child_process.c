/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 22:40:58 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"
#include "libft.h"

void	execute_child_process(const char *infile_path, const char *cmd,
			int fds[2], char **envp)
{
	int	in_fd;

	in_fd = open_infile(infile_path);
	xdup2(in_fd, STDIN_FILENO);
	xdup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	execve("/bin/cat", ft_split(cmd, ' '), envp);
}
