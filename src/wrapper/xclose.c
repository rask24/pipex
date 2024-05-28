/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:33:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 02:39:30 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "utils.h"
#include "wrapper.h"

int	xclose(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == FAILURE)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
