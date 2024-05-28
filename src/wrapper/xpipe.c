/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:14:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 02:40:07 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "utils.h"
#include "wrapper.h"

int	xpipe(int fds[2])
{
	int	ret;

	ret = pipe(fds);
	if (ret == FAILURE)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
