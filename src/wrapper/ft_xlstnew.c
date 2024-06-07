/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:54:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/07 19:59:14 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>

#include "constants.h"
#include "libft.h"
#include "utils.h"

t_list	*ft_xlstnew(void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		error_exit(__func__, strerror(errno), FUNCTION_FAIL);
	return (new);
}
