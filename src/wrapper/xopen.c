/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:39:02 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:48:22 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xopen(const char *path, int oflag)
{
	int	ret;

	ret = open(path, oflag);
	if (ret == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
