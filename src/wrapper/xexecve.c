/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xexecve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:43:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/10 00:47:20 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "constants.h"
#include "utils.h"

void	xexecve(const char *path, char * const *argv, char * const *envp)
{
	if (execve(path, argv, envp) == FAILURE)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
}
