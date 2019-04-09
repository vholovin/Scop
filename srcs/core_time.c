/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoreTime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:36:13 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 16:36:14 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	core_time(t_scop *scop)
{
	scop->time->delta_time = SDL_GetTicks() - scop->time->cur_time;
	scop->time->cur_time = SDL_GetTicks();
	if (scop->time->delta_time != 0)
		scop->time->cur_fps = 1000 / scop->time->delta_time;
}
