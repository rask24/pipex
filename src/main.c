/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/17 15:08:28 by reasuke          ###   ########.fr       */
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

static void	_init_pipes(int **p_fds, int argc)
{
	int	n;
	int	i;

	n = argc - 4;
	*p_fds = ft_xmalloc(sizeof(int) * (2 * n));
	i = 0;
	while (i < n)
	{
		xpipe(*p_fds + (2 * i));
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		*fds;

	_check_arguments(argc);
	_init_pipes(&fds, argc);
	execute_processes(fds, argc, argv, envp);
	return (-1);
}
