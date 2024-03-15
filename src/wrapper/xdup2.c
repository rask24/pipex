/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:21:06 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/15 16:35:51 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xdup2(int fd1, int fd2)
{
	int	ret;

	ret = dup2(fd1, fd2);
	if (ret == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
