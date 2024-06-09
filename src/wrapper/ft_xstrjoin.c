/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:40:28 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/10 00:49:23 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>

#include "constants.h"
#include "libft.h"
#include "utils.h"

char	*ft_xstrjoin(const char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
