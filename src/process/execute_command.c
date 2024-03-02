/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:29:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/02 15:31:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "process.h"
#include "utils.h"

static void	_not_found_exit(const char *cmd_name)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: command not found\n", PROG_NAME,
		cmd_name);
	exit(NOT_FOUND);
}

static void	_execute_direct_path(char **cmd_list, char **envp)
{
	if (access(cmd_list[0], X_OK) == SUCCESS)
		execve(cmd_list[0], cmd_list, envp);
	exit_with_message(PROG_NAME, strerror(errno), NOT_EXECUTABLE);
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
