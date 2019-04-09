/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_create_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:30:06 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:30:08 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	write_lst_to_array(float *array, t_lst *lst, uint count, uint size)
{
	uint	i;

	i = 0;
	while (i < count * size)
	{
		array[i++] = lst->vertex.x;
		array[i++] = lst->vertex.y;
		if (count > 2)
			array[i++] = lst->vertex.z;
		lst = lst->next;
	}
}

static void	create_uv_normal_array(t_scop *scop)
{
	uint i;

	i = 0;
	while (i < (2 * scop->obj->vertex_length))
	{
		scop->array->uv_array[i] = INFINITY;
		i++;
	}
	if (scop->obj->uv_start)
		write_lst_to_array(scop->array->uv_array, scop->obj->uv_start, 2,
													scop->obj->uv_length);
	if (!(scop->array->normal_array = (float *)malloc(sizeof(float) * 3 *
													scop->obj->vertex_length)))
		return ;
	i = 0;
	while (i < (3 * scop->obj->vertex_length))
	{
		scop->array->normal_array[i] = INFINITY;
		i++;
	}
	if (scop->obj->normal_start)
		write_lst_to_array(scop->array->normal_array,
			scop->obj->normal_start, 3, scop->obj->normal_length);
}

void		scop_create_array(t_scop *scop)
{
	if (!(scop->array->vertex_array = (float *)malloc(sizeof(float) * 3 *
													scop->obj->vertex_length)))
		return ;
	write_lst_to_array(scop->array->vertex_array, scop->obj->vertex_start, 3,
													scop->obj->vertex_length);
	if (!(scop->array->tangent_array = (float *)malloc(sizeof(float) * 3 *
													scop->obj->vertex_length)))
		return ;
	if (!(scop->array->bitangent_array = (float *)malloc(sizeof(float) * 3 *
													scop->obj->vertex_length)))
		return ;
	if (!(scop->array->face_array = (uint *)malloc(sizeof(uint) * 3 *
													scop->obj->face_length)))
		return ;
	if (!(scop->array->uv_array = (float *)malloc(sizeof(float) * 2 *
													scop->obj->vertex_length)))
		return ;
	create_uv_normal_array(scop);
}
