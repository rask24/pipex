/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen_with_permission.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:41:27 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/23 19:48:15 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	xopen_with_permission(const char *path, int oflag, int permission)
{
	int	ret;

	ret = open(path, oflag, permission);
	if (ret == FAILURE)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
