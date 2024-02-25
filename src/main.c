/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 19:01:48 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	*cmd[3];
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_printf("I am Child Process: %d\n", pid);
		cmd[0] = ft_strdup("ls");
		cmd[1] = ft_strdup("-l");
		cmd[2] = NULL;
		execve("/bin/ls", cmd, env);
		exit(0);
	}
	ft_printf("I am Parent Process: %d\n", pid);
	(void)argc;
	(void)argv;
	return (0);
}
