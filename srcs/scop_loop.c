/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:30:48 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:30:49 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	recalculate_matrix(t_scop *scop)
{
	scop_set_transform(scop);
	scop_calculate_mvp(scop);
}

void		scop_loop(t_scop *scop)
{
	while (scop->control->play == true)
	{
		core_time(scop);
		core_keyboard(scop);
		recalculate_matrix(scop);
		if (scop->time->delta_time <= 1000 / FPS)
			core_render(scop);
	}
}
