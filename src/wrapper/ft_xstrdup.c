/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:55:55 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/07 19:59:24 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>

#include "constants.h"
#include "libft.h"
#include "utils.h"

char	*ft_xstrdup(const char *s)
{
	char	*ret;

	ret = ft_strdup(s);
	if (!ret)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
