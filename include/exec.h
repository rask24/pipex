/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:03:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/28 19:46:25 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "constants.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

pid_t		execute_infile_process(const char *infile_path, const char *cmd,
				int fds[2], char **envp);
pid_t		execute_heredoc_process(const char *delimiter, const char *cmd,
				int fds[2], char **envp);
pid_t		execute_pipe_process(const char *cmd, int prev_fds[2],
				int next_fds[2], char **envp);
pid_t		execute_outfile_overwrite_process(const char *outfile_path,
				const char *cmd, int fds[2], char **envp);
pid_t		execute_outfile_append_process(const char *outfile_path,
				const char *cmd, int fds[2], char **envp);
void		execute_command(const char *cmd, char **envp);
const char	*resolve_command_path(const char *cmd_name, char **envp);

#endif
