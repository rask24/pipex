/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:03:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/17 16:19:01 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "constants.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void		execute_processes(int **fds, int argc, char **argv, char **envp);
pid_t		execute_infile_process(const char *infile_path, const char *cmd,
				int fds[2], char **envp);
pid_t		execute_pipe_process(const char *cmd, int prev_fds[2],
				int next_fds[2], char **envp);
pid_t		execute_outfile_process(const char *outfile_path, const char *cmd,
				int fds[2], char **envp);
void		execute_command(const char *cmd, char **envp);
const char	*resolve_command_path(const char *cmd_name, char **envp);

#endif
