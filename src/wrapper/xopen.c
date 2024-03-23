/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:39:02 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:40:24 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xopen(const char *path, int oflag)
{
	int	ret;

	ret = open(path, oflag);
	if (ret == -1)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
