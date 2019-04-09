/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_init_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:04 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:15:05 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		create_ibo(t_scop *scop)
{
	scop->buffer->face_number = scop->obj->face_length * 3;
	glGenBuffers(1, &scop->buffer->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scop->buffer->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					sizeof(uint) * scop->buffer->face_number,
					scop->array->face_array, GL_DYNAMIC_DRAW);
}

static void		add_vbo_to_vao(GLuint *vbo_id, GLuint pos, uint layout,
																uint stride)
{
	glEnableVertexAttribArray(pos);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_id);
	glVertexAttribPointer(pos, layout, GL_FLOAT, GL_FALSE, stride, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		create_vbo(GLuint *vbo_id, void *array, uint size)
{
	glGenBuffers(1, vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_id);
	glBufferData(GL_ARRAY_BUFFER, size, array, GL_DYNAMIC_DRAW);
}

static void		create_vao(t_scop *scop)
{
	glGenVertexArrays(1, &scop->buffer->vao);
	glBindVertexArray(scop->buffer->vao);
	glGenVertexArrays(1, &scop->buffer->vao);
	glBindVertexArray(scop->buffer->vao);
}

void			gl_init_buffer(t_scop *scop)
{
	create_vao(scop);
	create_vbo(&scop->buffer->vbo_vertex, scop->array->vertex_array,
						sizeof(float) * 3 * scop->obj->vertex_length);
	add_vbo_to_vao(&scop->buffer->vbo_vertex, 0, 3, 0);
	create_vbo(&scop->buffer->vbo_uv, scop->array->uv_array,
						sizeof(float) * 2 * scop->obj->vertex_length);
	add_vbo_to_vao(&scop->buffer->vbo_uv, 1, 2, 0);
	create_vbo(&scop->buffer->vbo_normal, scop->array->normal_array,
						sizeof(float) * 3 * scop->obj->vertex_length);
	add_vbo_to_vao(&scop->buffer->vbo_normal, 2, 3, 0);
	create_vbo(&scop->buffer->vbo_tangent, scop->array->tangent_array,
						sizeof(float) * 3 * scop->obj->vertex_length);
	add_vbo_to_vao(&scop->buffer->vbo_tangent, 3, 3, 0);
	create_vbo(&scop->buffer->vbo_bitangent, scop->array->bitangent_array,
						sizeof(float) * 3 * scop->obj->vertex_length);
	add_vbo_to_vao(&scop->buffer->vbo_bitangent, 4, 3, 0);
	create_ibo(scop);
}
