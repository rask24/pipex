/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 22:43:07 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utils.h"
#include "wrapper.h"
#include "process.h"

static void	_check_argument(int argc)
{
	if (argc != 5)
		exit_with_message(__func__, "The number of arguments must be 4");
}

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	pid_t	pid;

	_check_argument(argc);
	xpipe(fds);
	pid = xfork();
	if (pid == CHILD)
		execute_child_process(argv[1], argv[2], fds, envp);
	else
		execute_parent_process(argv[4], argv[3], fds, envp);
	return (0);
}
