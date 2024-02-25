/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:03:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 22:41:58 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>

# define FAIL -1

int		open_infile(const char *file_path);
int		open_outfile(const char *file_path);
void	execute_child_process(const char *infile_path, const char *cmd,
			int fds[2], char **envp);
void	execute_parent_process(const char *outfile_path, const char *cmd,
			int fds[2], char **envp);

#endif
