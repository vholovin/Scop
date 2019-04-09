/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:30:39 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:30:41 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	init_3(t_scop *scop_tmp)
{
	scop_tmp->transform = malloc(sizeof(*(scop_tmp->transform)));
	if (scop_tmp->transform == NULL)
		scop_error("malloc error");
	scop_tmp->transform->position = vec_new(0.0f, 0.0f, 0.0f);
	scop_tmp->transform->rotation = vec_new(0.0f, 0.0f, 0.0f);
	scop_tmp->transform->scale = vec_new(1.0f, 1.0f, 1.0f);
	scop_tmp->camera = malloc(sizeof(*(scop_tmp->camera)));
	if (scop_tmp->camera == NULL)
		scop_error("malloc error");
	scop_tmp->camera->position = vec_new(0.0f, 0.0f, 5.0f);
	scop_tmp->camera->target = vec_new(0.0f, 0.0f, 0.0f);
	scop_tmp->camera->forward_axis =
		vec_norm(vec_sub(scop_tmp->camera->position, scop_tmp->camera->target));
	scop_tmp->camera->right_axis =
		vec_norm(vec_cross(vec_new(0, 1, 0), scop_tmp->camera->forward_axis));
	scop_tmp->camera->up_axis =
		vec_norm(vec_cross(scop_tmp->camera->forward_axis,
												scop_tmp->camera->right_axis));
	scop_tmp->matrix = malloc(sizeof(*(scop_tmp->matrix)));
	if (scop_tmp->matrix == NULL)
		scop_error("malloc error");
}

static void	init_2(t_scop *scop_tmp)
{
	scop_tmp->obj = malloc(sizeof(*(scop_tmp->obj)));
	if (scop_tmp->obj == NULL)
		scop_error("malloc error");
	scop_tmp->obj->obj_path = scop_tmp->av[1];
	scop_tmp->obj->vertex = NULL;
	scop_tmp->obj->uv = NULL;
	scop_tmp->obj->normal = NULL;
	scop_tmp->obj->face = NULL;
	scop_tmp->obj->vertex_start = NULL;
	scop_tmp->obj->uv_start = NULL;
	scop_tmp->obj->normal_start = NULL;
	scop_tmp->obj->face_start = NULL;
	scop_tmp->obj->vertex_length = 0;
	scop_tmp->obj->uv_length = 0;
	scop_tmp->obj->normal_length = 0;
	scop_tmp->obj->face_length = 0;
	scop_tmp->array = malloc(sizeof(*(scop_tmp->array)));
	if (scop_tmp->array == NULL)
		scop_error("malloc error");
	scop_tmp->buffer = malloc(sizeof(*(scop_tmp->buffer)));
	if (scop_tmp->buffer == NULL)
		scop_error("malloc error");
	scop_tmp->buffer->face_number = 0;
}

static void	init_1(t_scop *scop_tmp)
{
	scop_tmp->control = malloc(sizeof(*(scop_tmp->control)));
	if (scop_tmp->control == NULL)
		scop_error("malloc error");
	scop_tmp->control->play = true;
	scop_tmp->control->background = true;
	scop_tmp->control->mode_color = SMOOTH_COLOR;
	scop_tmp->control->switch_normal = true;
	scop_tmp->control->switch_diffuse = true;
	scop_tmp->control->switch_specular = true;
	scop_tmp->control->index_specular = 0.05f;
	scop_tmp->texture = malloc(sizeof(*(scop_tmp->texture)));
	if (scop_tmp->texture == NULL)
		scop_error("malloc error");
	scop_tmp->texture->diffuse_texture_path = NULL;
	scop_tmp->texture->normal_texture_path = NULL;
	if (scop_tmp->ac >= 2)
		scop_tmp->texture->diffuse_texture_path = scop_tmp->av[2];
	if (scop_tmp->ac >= 3)
		scop_tmp->texture->normal_texture_path = scop_tmp->av[3];
	scop_tmp->light = malloc(sizeof(*(scop_tmp->light)));
	if (scop_tmp->light == NULL)
		scop_error("malloc error");
	scop_tmp->light->position = (t_vec3){0.0f, 0.0f, 5.0f};
	scop_tmp->light->color = (t_vec3){0.8f, 0.8f, 0.8f};
}

static void	init_0(t_scop *scop_tmp)
{
	scop_tmp->sdl = malloc(sizeof(*(scop_tmp->sdl)));
	if (scop_tmp->sdl == NULL)
		scop_error("malloc error");
	scop_tmp->sdl->width = WIDTH;
	scop_tmp->sdl->height = HEIGHT;
	scop_tmp->time = malloc(sizeof(*(scop_tmp->time)));
	if (scop_tmp->time == NULL)
		scop_error("malloc error");
	scop_tmp->time->cur_time = 0;
	scop_tmp->time->delta_time = 0;
	scop_tmp->time->cur_fps = 0;
	scop_tmp->shader = malloc(sizeof(*(scop_tmp->shader)));
	if (scop_tmp->shader == NULL)
		scop_error("malloc error");
	scop_tmp->shader->vertex_path = NULL;
	scop_tmp->shader->fragment_path = NULL;
}

t_scop		*scop_init(int ac, char **av)
{
	t_scop	*scop_tmp;

	scop_tmp = malloc(sizeof(*(scop_tmp)));
	if (scop_tmp == NULL)
		scop_error("malloc error");
	scop_tmp->ac = ac;
	scop_tmp->av = av;
	init_0(scop_tmp);
	init_1(scop_tmp);
	init_2(scop_tmp);
	init_3(scop_tmp);
	return (scop_tmp);
}
