/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_set_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:31:22 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:31:24 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	set_identity_matrix(GLfloat *matrix)
{
	uint i;

	i = 0;
	while (i < 4)
	{
		matrix[i + i * 4] = 1.0f;
		i++;
	}
}

static void	set_position_matrix(t_scop *scop)
{
	t_vec3 v;

	v = scop->transform->position;
	ft_bzero(&scop->transform->position_matrix[0], 16 * sizeof(float));
	set_identity_matrix(&scop->transform->position_matrix[0]);
	scop->transform->position_matrix[3 + 0 * 4] = v.x;
	scop->transform->position_matrix[3 + 1 * 4] = v.y;
	scop->transform->position_matrix[3 + 2 * 4] = v.z;
	scop->transform->position_matrix[3 + 3 * 4] = 1.0f;
}

static void	set_rotation_matrix(t_scop *scop)
{
	t_vec3 v;

	v = scop->transform->rotation;
	ft_bzero(&scop->transform->rotation_matrix[0], 16 * sizeof(float));
	scop->transform->rotation_matrix[0 + 0 * 4] = cosf(v.y) * cosf(v.z);
	scop->transform->rotation_matrix[1 + 0 * 4] =
		cosf(v.x) * sinf(v.z) + sinf(v.x) * sinf(v.y) * cosf(v.z);
	scop->transform->rotation_matrix[2 + 0 * 4] =
		sinf(v.x) * sinf(v.z) - cosf(v.x) * sinf(v.y) * cosf(v.z);
	scop->transform->rotation_matrix[0 + 1 * 4] = -cosf(v.y) * sinf(v.z);
	scop->transform->rotation_matrix[1 + 1 * 4] =
		cosf(v.x) * cosf(v.z) - sinf(v.x) * sinf(v.y) * sinf(v.z);
	scop->transform->rotation_matrix[2 + 1 * 4] =
		sinf(v.x) * cosf(v.z) + cosf(v.x) * sinf(v.y) * sinf(v.z);
	scop->transform->rotation_matrix[0 + 2 * 4] = sinf(v.y);
	scop->transform->rotation_matrix[1 + 2 * 4] = -sinf(v.x) * cosf(v.y);
	scop->transform->rotation_matrix[2 + 2 * 4] = cosf(v.x) * cosf(v.y);
	scop->transform->rotation_matrix[3 + 3 * 4] = 1.0;
}

static void	set_scale_matrix(t_scop *scop)
{
	t_vec3 v;

	v = scop->transform->scale;
	ft_bzero(&scop->transform->scale_matrix[0], 16 * sizeof(float));
	scop->transform->scale_matrix[0 + 0 * 4] = v.x;
	scop->transform->scale_matrix[1 + 1 * 4] = v.y;
	scop->transform->scale_matrix[2 + 2 * 4] = v.z;
	scop->transform->scale_matrix[3 + 3 * 4] = 1.0;
}

void		scop_set_transform(t_scop *scop)
{
	set_position_matrix(scop);
	set_rotation_matrix(scop);
	set_scale_matrix(scop);
}
