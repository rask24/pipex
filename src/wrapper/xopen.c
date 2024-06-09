/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:39:02 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/10 00:49:42 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include "constants.h"
#include "utils.h"

int	xopen(const char *path, int oflag)
{
	int	ret;

	ret = open(path, oflag);
	if (ret == FAILURE)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
