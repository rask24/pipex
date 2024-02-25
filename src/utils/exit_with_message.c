/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:03:12 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 19:45:31 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_with_message(const char *func, const char *msg)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", func, msg);
	exit(1);
}
