/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:27:08 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:27:10 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		sdl_error(const char *message)
{
	if (message)
	{
		ft_putstr("ERROR : ");
		ft_putstr(message);
		ft_putstr(" : ");
		ft_putendl(SDL_GetError());
		SDL_Quit();
		exit(1);
	}
}
