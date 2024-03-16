/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:03:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/16 15:38:21 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "constants.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>

int			open_infile(const char *file_path);
int			open_outfile(const char *file_path);
int			execute_child_process(const char *infile_path, const char *cmd,
				int fds[2], char **envp);
int			execute_parent_process(const char *outfile_path, const char *cmd,
				int fds[2], char **envp);
void		execute_command(const char *cmd, char **envp);
const char	*resolve_command_path(const char *cmd_name, char **envp);

#endif
