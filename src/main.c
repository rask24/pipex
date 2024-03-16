/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/16 15:53:15 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utils.h"
#include "wrapper.h"
#include "process.h"

static void	_check_arguments(int argc)
{
	if (argc < 5)
		exit_with_message(__func__, MSG_INV_ARGS, INVALID_ARGUMENTS);
}

static void	_close_all_pipes(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	pid_t	pid;
	int		status;

	_check_arguments(argc);
	xpipe(fds);
	pid = execute_child_process(argv[1], argv[2], fds, envp);
	waitpid(pid, NULL, 0);
	pid = execute_parent_process(argv[4], argv[3], fds, envp);
	_close_all_pipes(fds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
