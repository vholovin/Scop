/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:23:58 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:24:01 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		main(int ac, char **av)
{
	t_scop *scop;

	if (ac >= 2 && ac <= 5)
	{
		tutorial();
		scop = scop_init(ac, av);
		sdl_init(scop);
		scop_shader_upload(scop);
		scop_shader_linking(scop);
		scop_upload_texture(scop);
		scop_upload_obj(scop);
		scop_centered_obj(scop);
		scop_create_array(scop);
		scop_set_array(scop);
		scop_set_transform(scop);
		scop_set_matrix(scop);
		gl_init_buffer(scop);
		gl_init_viewport(scop);
		scop_loop(scop);
		sdl_exit(scop);
		scop_free(scop);
	}
	else
		scop_error("./scop [filename].obj [diffuse texture] [normal texture]");
	return (0);
}
