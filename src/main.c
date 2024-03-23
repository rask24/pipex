/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:39:00 by reasuke          ###   ########.fr       */
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

static void	_init_pipes(int ***p_fds, int argc)
{
	int	n;
	int	i;

	n = argc - 4;
	*p_fds = ft_xmalloc(sizeof(int *) * n);
	i = 0;
	while (i < n)
	{
		(*p_fds)[i] = ft_xmalloc(sizeof(int) * 2);
		xpipe((*p_fds)[i]);
		i++;
	}
}

static void	_free_pipe_fds(int **fds, int argc)
{
	int	n;
	int	i;

	n = argc - 4;
	i = 0;
	while (i < n)
	{
		free(fds[i]);
		i++;
	}
	free(fds);
}

int	main(int argc, char **argv, char **envp)
{
	int		**fds;
	int		status;

	_check_arguments(argc);
	_init_pipes(&fds, argc);
	status = execute_processes(fds, argc, argv, envp);
	_free_pipe_fds(fds, argc);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (-1);
}
