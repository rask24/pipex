/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:33:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/10 00:49:27 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "utils.h"

int	xclose(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == FAILURE)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
