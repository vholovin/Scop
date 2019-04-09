/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:30:32 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:30:33 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	free_shader(t_scop *scop)
{
	glDeleteProgram(scop->shader->shader_program);
	free(scop->shader->vertex_path);
	free(scop->shader->fragment_path);
	free(scop->shader);
}

static void	free_obj(t_scop *scop)
{
	lst_free(scop->obj->vertex);
	lst_free(scop->obj->uv);
	lst_free(scop->obj->normal);
	lst_free(scop->obj->face);
	free(scop->obj);
}

static void	free_array(t_scop *scop)
{
	free(scop->array->vertex_array);
	free(scop->array->uv_array);
	free(scop->array->normal_array);
	free(scop->array->tangent_array);
	free(scop->array->bitangent_array);
	free(scop->array->face_array);
	free(scop->array);
}

static void	free_buffer(t_scop *scop)
{
	glDeleteVertexArrays(1, &scop->buffer->vao);
	glDeleteBuffers(1, &scop->buffer->vbo_vertex);
	glDeleteBuffers(1, &scop->buffer->vbo_uv);
	glDeleteBuffers(1, &scop->buffer->vbo_normal);
	glDeleteBuffers(1, &scop->buffer->vbo_tangent);
	glDeleteBuffers(1, &scop->buffer->vbo_bitangent);
	glDeleteBuffers(1, &scop->buffer->ibo);
	free(scop->buffer);
}

void		scop_free(t_scop *scop)
{
	free(scop->matrix);
	free(scop->camera);
	free(scop->transform);
	free_buffer(scop);
	free_array(scop);
	free_obj(scop);
	free_shader(scop);
	free(scop->light);
	free(scop->control);
	free(scop->texture);
	free(scop->time);
	free(scop->sdl);
	free(scop);
}
