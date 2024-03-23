/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen_with_permission.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:41:27 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:43:46 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xopen_with_permission(const char *path, int oflag, int permission)
{
	int	ret;

	ret = open(path, oflag, permission);
	if (ret == -1)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
