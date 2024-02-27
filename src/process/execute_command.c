/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:29:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/26 22:14:05 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "process.h"
#include "utils.h"

static void	_not_found_exit(const char *cmd_name)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", cmd_name);
	exit(NOT_FOUND);
}

static void	_permission_denied_exit(const char *cmd_name)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: Permission denied\n", cmd_name);
	exit(PERMISSION_DENIED);
}

static void	_execute_direct_path(char **cmd_list, char **envp)
{
	if (access(cmd_list[0], X_OK) == SUCCESS)
		execve(cmd_list[0], cmd_list, envp);
	if (errno == EACCES)
		_permission_denied_exit(cmd_list[0]);
	exit_with_message(cmd_list[0], strerror(errno));
}

void	execute_command(const char *cmd, char **envp)
{
	char		**cmd_list;
	const char	*exec_path;

	cmd_list = ft_split(cmd, ' ');
	if (access(cmd_list[0], F_OK) == SUCCESS)
		_execute_direct_path(cmd_list, envp);
	exec_path = resolve_command_path(cmd_list[0], envp);
	if (!exec_path)
		_not_found_exit(cmd_list[0]);
	execve(exec_path, cmd_list, envp);
}
