/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_keyboard_transform.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:33:06 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/03 17:33:07 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	key_transform_position(t_scop *scop)
{
	float speed;

	speed = (float)SPEED_TRANSFORM * (float)scop->time->delta_time / 1000;
	if (scop->sdl->keystate[SDL_SCANCODE_UP])
		scop->transform->position.y += speed;
	else if (scop->sdl->keystate[SDL_SCANCODE_DOWN])
		scop->transform->position.y -= speed;
	if (scop->sdl->keystate[SDL_SCANCODE_RIGHT])
		scop->transform->position.x += speed;
	else if (scop->sdl->keystate[SDL_SCANCODE_LEFT])
		scop->transform->position.x -= speed;
	if (scop->sdl->keystate[SDL_SCANCODE_PERIOD])
		scop->transform->position.z += speed;
	else if (scop->sdl->keystate[SDL_SCANCODE_COMMA])
		scop->transform->position.z -= speed;
}

static void	key_transform_rotation(t_scop *scop)
{
	float speed;

	speed = (float)SPEED_ROTATION * (float)scop->time->delta_time / 1000;
	if (scop->sdl->keystate[SDL_SCANCODE_UP])
		scop->transform->rotation.x += speed;
	else if (scop->sdl->keystate[SDL_SCANCODE_DOWN])
		scop->transform->rotation.x -= speed;
	if (scop->sdl->keystate[SDL_SCANCODE_LEFT])
		scop->transform->rotation.y += speed;
	else if (scop->sdl->keystate[SDL_SCANCODE_RIGHT])
		scop->transform->rotation.y -= speed;
	if (scop->sdl->keystate[SDL_SCANCODE_PERIOD])
		scop->transform->rotation.z -= speed;
	else if (scop->sdl->keystate[SDL_SCANCODE_COMMA])
		scop->transform->rotation.z += speed;
}

static void	key_transform_scale(t_scop *scop)
{
	if (scop->sdl->keystate[SDL_SCANCODE_EQUALS])
		scop->transform->scale =
				vec_mult(1 + SPEED_DELTA_SCALE, scop->transform->scale);
	else if (scop->sdl->keystate[SDL_SCANCODE_MINUS])
		scop->transform->scale =
				vec_mult(1 - SPEED_DELTA_SCALE, scop->transform->scale);
}

void		core_keyboard_transform(t_scop *scop)
{
	if (scop->sdl->keystate[SDL_SCANCODE_LSHIFT] ||
			scop->sdl->keystate[SDL_SCANCODE_RSHIFT])
		key_transform_rotation(scop);
	else
		key_transform_position(scop);
	key_transform_scale(scop);
}
