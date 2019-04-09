/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:27:26 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:27:28 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		sdl_init(t_scop *scop)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		sdl_error("Failed to init SDL");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
												SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	scop->sdl->window = SDL_CreateWindow("scop", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (scop->sdl->window == NULL)
		sdl_error("Failed to create window");
	scop->sdl->gl_context = SDL_GL_CreateContext(scop->sdl->window);
	scop->sdl->keystate = SDL_GetKeyboardState(NULL);
	SDL_SetWindowResizable(scop->sdl->window, SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_FALSE);
}
