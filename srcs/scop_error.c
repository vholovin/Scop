/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:30:15 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:30:26 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	scop_error(const char *message)
{
	if (message)
	{
		ft_putstr("ERROR : ");
		ft_putendl(message);
		exit(1);
	}
}
