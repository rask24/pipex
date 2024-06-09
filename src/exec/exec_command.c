/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:29:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/09 20:06:55 by reasuke          ###   ########.fr       */
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

#include "exec_internal.h"

static void	_execute_file_path(char **cmd_list, char **envp)
{
	if (access(cmd_list[0], X_OK) == SUCCESS)
		execve(cmd_list[0], cmd_list, envp);
	error_exit(cmd_list[0], strerror(errno), NOT_EXECUTABLE);
}

static void	_execute_env_path(char **cmd_list, char **envp)
{
	const char	*exec_path;

	if (!extract_path_from_env(envp))
		error_exit(cmd_list[0], strerror(ENOENT), NOT_FOUND);
	exec_path = resolve_command_path(cmd_list[0], envp);
	if (!exec_path)
		not_found_exit(cmd_list[0]);
	if (access(exec_path, X_OK) == SUCCESS)
		execve(exec_path, cmd_list, envp);
	error_exit(cmd_list[0], strerror(errno), NOT_EXECUTABLE);
}

void	execute_command(const char *cmd, char **envp)
{
	char		**cmd_list;

	cmd_list = parse_command(cmd);
	if (ft_strchr(cmd_list[0], '/'))
		_execute_file_path(cmd_list, envp);
	else
		_execute_env_path(cmd_list, envp);
}
