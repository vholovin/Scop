/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoreKeyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:35:41 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 16:35:42 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	key_exit(t_scop *scop)
{
	if (scop->sdl->event.type == SDL_QUIT)
		scop->control->play = false;
	if (scop->sdl->event.type == SDL_KEYDOWN &&
							scop->sdl->keystate[SDL_SCANCODE_ESCAPE])
		scop->control->play = false;
}

static void	key_switch(t_scop *scop)
{
	if (scop->sdl->keystate[SDL_SCANCODE_B] &&
							scop->control->background == true)
		scop->control->background = false;
	else if (scop->sdl->keystate[SDL_SCANCODE_B] &&
							scop->control->background == false)
		scop->control->background = true;
	if (scop->sdl->keystate[SDL_SCANCODE_N] &&
							scop->control->switch_normal == true)
		scop->control->switch_normal = false;
	else if (scop->sdl->keystate[SDL_SCANCODE_N] &&
							scop->control->switch_normal == false)
		scop->control->switch_normal = true;
	if (scop->sdl->keystate[SDL_SCANCODE_D] &&
							scop->control->switch_diffuse == true)
		scop->control->switch_diffuse = false;
	else if (scop->sdl->keystate[SDL_SCANCODE_D] &&
							scop->control->switch_diffuse == false)
		scop->control->switch_diffuse = true;
	if (scop->sdl->keystate[SDL_SCANCODE_S] &&
							scop->control->switch_specular == true)
		scop->control->switch_specular = false;
	else if (scop->sdl->keystate[SDL_SCANCODE_S] &&
							scop->control->switch_specular == false)
		scop->control->switch_specular = true;
}

static void	key_index_specular(t_scop *scop)
{
	if (scop->sdl->keystate[SDL_SCANCODE_A] &&
							scop->control->index_specular < 1.0f)
		scop->control->index_specular += 0.05f;
	else if (scop->sdl->keystate[SDL_SCANCODE_Z] &&
							scop->control->index_specular > 0.0f)
		scop->control->index_specular -= 0.05f;
}

static void	key_color(t_scop *scop)
{
	if (scop->sdl->keystate[SDL_SCANCODE_1])
		scop->control->mode_color = WIRE;
	else if (scop->sdl->keystate[SDL_SCANCODE_2])
		scop->control->mode_color = GRAY;
	else if (scop->sdl->keystate[SDL_SCANCODE_3])
		scop->control->mode_color = FLAT_COLOR;
	else if (scop->sdl->keystate[SDL_SCANCODE_4])
		scop->control->mode_color = SMOOTH_COLOR;
	else if (scop->sdl->keystate[SDL_SCANCODE_5])
		scop->control->mode_color = TEXTURE;
}

void		core_keyboard(t_scop *scop)
{
	if (SDL_PollEvent(&scop->sdl->event))
	{
		key_exit(scop);
		if (scop->sdl->event.type == SDL_KEYDOWN)
		{
			key_switch(scop);
			key_index_specular(scop);
			key_color(scop);
			core_keyboard_transform(scop);
		}
	}
}
