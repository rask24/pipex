/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:48:29 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 02:36:42 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>

#include "constants.h"
#include "libft.h"
#include "utils.h"
#include "wrapper.h"

char	**ft_xsplit(const char *s, char c)
{
	char	**ret;

	ret = ft_split(s, c);
	if (!ret)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
