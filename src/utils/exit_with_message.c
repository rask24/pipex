/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:03:12 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 19:10:54 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_with_message(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s\n", msg);
	exit(1);
}
