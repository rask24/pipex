/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:13:38 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/13 19:14:52 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	**create_pipe_fds(int num_pipes)
{
	int	**pipe_fds;
	int	i;

	pipe_fds = ft_xmalloc(sizeof(int *) * num_pipes);
	i = 0;
	while (i < num_pipes)
	{
		pipe_fds[i] = ft_xmalloc(sizeof(int) * 2);
		xpipe((pipe_fds)[i]);
		i++;
	}
	return (pipe_fds);
}
