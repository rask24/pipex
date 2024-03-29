/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:03:12 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/02 15:07:04 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_with_message(const char *func, const char *msg, int status)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", func, msg);
	exit(status);
}
