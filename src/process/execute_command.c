/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:29:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/26 15:52:42 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "process.h"

static void	not_found_exit(const char *cmd_name)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", cmd_name);
	exit(NOT_FOUND);
}

void	execute_command(const char *cmd, char **envp)
{
	char		**cmd_list;
	const char	*exec_path;

	cmd_list = ft_split(cmd, ' ');
	exec_path = resolve_command_path(cmd_list[0], envp);
	if (!exec_path)
		not_found_exit(cmd_list[0]);
	execve(exec_path, cmd_list, envp);
}
