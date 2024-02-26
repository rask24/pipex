/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:14:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/26 14:32:37 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "wrapper.h"
#include "libft.h"

void	execute_parent_process(const char *outfile_path, const char *cmd,
			int fds[2], char **envp)
{
	int	out_fd;

	out_fd = open_outfile(outfile_path);
	xdup2(fds[0], STDIN_FILENO);
	xdup2(out_fd, STDOUT_FILENO);
	close(fds[1]);
	execute_command(cmd, envp);
}
