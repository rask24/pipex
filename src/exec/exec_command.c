/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:29:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/10 00:48:04 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "exec.h"
#include "libft.h"
#include "parse_command.h"
#include "utils.h"
#include "wrapper.h"

#include "exec_internal.h"

static const char	*_fetch_exec_path(char **cmd_list, char **envp)
{
	const char	*exec_path;

	if (ft_strchr(cmd_list[0], '/'))
		return (cmd_list[0]);
	if (!extract_path_from_env(envp))
		error_exit(cmd_list[0], strerror(ENOENT), NOT_FOUND);
	exec_path = resolve_command_path(cmd_list[0], envp);
	if (!exec_path)
		error_exit(cmd_list[0], NOT_FOUND_MSG, NOT_FOUND);
	return (exec_path);
}

static void	_exec_command_internal(char **cmd_list, char **envp,
									const char *exec_path)
{
	if (access(exec_path, X_OK) == FAILURE)
	{
		if (errno == EACCES)
			error_exit(cmd_list[0], strerror(errno), NOT_EXECUTABLE);
		else if (errno == ENOENT)
			error_exit(cmd_list[0], strerror(errno), NOT_FOUND);
	}
	xexecve(exec_path, cmd_list, envp);
}

void	exec_command(const char *cmd, char **envp)
{
	char		**cmd_list;
	const char	*exec_path;

	cmd_list = parse_command(cmd);
	exec_path = _fetch_exec_path(cmd_list, envp);
	_exec_command_internal(cmd_list, envp, exec_path);
}
