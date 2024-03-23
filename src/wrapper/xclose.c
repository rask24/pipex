/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:33:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:48:02 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xclose(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
