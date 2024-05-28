/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunlink.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:20:08 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 02:41:07 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "utils.h"
#include "wrapper.h"

int	xunlink(const char *path)
{
	int	ret;

	ret = unlink(path);
	if (ret == FAILURE)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
