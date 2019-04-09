/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.c.                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:35:41 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 16:35:42 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	tutorial(void)
{
	ft_putstr("\
CONTROLS:\n\
Move:\n\
	to axis X +:    Key: right\n	to axis X -:    Key: left\n\
	to axis Y +:    Key: up\n	to axis Y -:    Key: down\n\
	to axis Z +:    Key: <\n	to axis Z -:    Key: >\n\
Rotate local:\n\
	press key SHIFT and any keys:\n\
	to axis X +:    Key: right\n	to axis X -:    Key: left\n\
	to axis Y +:    Key: up\n	to axis Y -:    Key: down\n\
	to axis Z +:    Key: <\n	to axis Z -:    Key: >\n\
Transform scale:\n\
	Up index:       Key: +\n	Down index:     key: -\n\
Effects:\n\
	diffuse:        Key: d\n	normal:         Key: n\n\
	specular:       Key: s\n\
Specular index:\n\
	Up index:       Key: a\n	Down index:     key: z\n\
Color:\n\
	Choose mode:    Key: 1 - 5\n\
\n\
	Exit:           Key: esc\n\
\n\
");
}
