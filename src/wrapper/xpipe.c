/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:14:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 19:23:55 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xpipe(int fds[2])
{
	int	ret;

	ret = pipe(fds);
	if (ret == FAIL)
		exit_with_message(strerror(errno));
	return (ret);
}
