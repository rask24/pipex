/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:29:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/27 23:05:43 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "exec.h"
#include "split_word.h"
#include "utils.h"

static void	_not_found_exit(const char *cmd_name)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: command not found\n", PROG_NAME,
		cmd_name);
	exit(NOT_FOUND);
}

static void	_execute_file_path(char **cmd_list, char **envp)
{
	if (access(cmd_list[0], X_OK) == SUCCESS)
		execve(cmd_list[0], cmd_list, envp);
	error_exit(cmd_list[0], strerror(errno), NOT_EXECUTABLE);
}

static void	_execute_env_path(char **cmd_list, char **envp)
{
	const char	*exec_path;

	exec_path = resolve_command_path(cmd_list[0], envp);
	if (!exec_path)
		_not_found_exit(cmd_list[0]);
	execve(exec_path, cmd_list, envp);
}

void	execute_command(const char *cmd, char **envp)
{
	char		**cmd_list;

	cmd_list = split_word(cmd);
	if (ft_strchr(cmd_list[0], '/') && access(cmd_list[0], F_OK) == SUCCESS)
		_execute_file_path(cmd_list, envp);
	else
		_execute_env_path(cmd_list, envp);
}
