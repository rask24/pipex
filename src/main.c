/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 20:11:30 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utils.h"
#include "wrapper.h"
#include "process.h"

static void	_check_argument(int argc)
{
	return ;
	if (argc != 5)
		exit_with_message(__func__, "The number of arguments must be 4");
}

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	pid_t	pid;

	(void)argc;
	(void)argv;
	(void)envp;
	_check_argument(argc);
	xpipe(fds);
	pid = xfork();
	if (pid == CHILD)
	{
		ft_printf("This is child process.\n");
		ft_printf("%d\n", open_infile("sldkjflsdjf"));
		// execute_child_process();
	}
	else
	{
		ft_printf("This is parent process.\n");
		// execute_parent_process();
	}
	return (0);
}
