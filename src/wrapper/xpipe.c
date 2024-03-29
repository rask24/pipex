/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:14:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/15 16:35:51 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xpipe(int fds[2])
{
	int	ret;

	ret = pipe(fds);
	if (ret == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
