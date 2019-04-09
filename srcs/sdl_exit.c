/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:27:15 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:27:17 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	sdl_exit(t_scop *scop)
{
	SDL_GL_DeleteContext(scop->sdl->gl_context);
	SDL_DestroyWindow(scop->sdl->window);
	SDL_Quit();
}
