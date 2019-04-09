/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_set_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:31:10 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:31:11 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	create_model_matrix(t_scop *scop)
{
	ft_bzero(&scop->matrix->model, 16 * sizeof(float));
}

static void	create_view_matrix(t_scop *scop)
{
	ft_bzero(&scop->matrix->view, 16 * sizeof(float));
	ft_memcpy(&scop->matrix->view[0 + 0 * 4], &scop->camera->right_axis,
													3 * sizeof(float));
	ft_memcpy(&scop->matrix->view[0 + 1 * 4], &scop->camera->up_axis,
													3 * sizeof(float));
	ft_memcpy(&scop->matrix->view[0 + 2 * 4], &scop->camera->forward_axis,
													3 * sizeof(float));
	scop->matrix->view[3 + 0 * 4] = -1.0f *
					vec_dot(scop->camera->right_axis, scop->camera->position);
	scop->matrix->view[3 + 1 * 4] = -1.0f *
					vec_dot(scop->camera->up_axis, scop->camera->position);
	scop->matrix->view[3 + 2 * 4] = -1.0f *
					vec_dot(scop->camera->forward_axis, scop->camera->position);
	scop->matrix->view[3 + 3 * 4] = 1.0f;
}

static void	create_projection_matrix(t_scop *scop)
{
	ft_bzero(&scop->matrix->projection, 16 * sizeof(float));
	scop->matrix->projection[0] =
		1.0f / ((float)WIDTH / HEIGHT * tanf(RAD(CAMERA_FOV) / 2.0f));
	scop->matrix->projection[1 + 1 * 4] =
		1.0f / (tanf(RAD(CAMERA_FOV) / 2.0f));
	scop->matrix->projection[2 + 2 * 4] =
		(CAMERA_NEAR + CAMERA_FAR) / (CAMERA_NEAR - CAMERA_FAR);
	scop->matrix->projection[3 + 2 * 4] =
		(2.0f * CAMERA_NEAR * CAMERA_FAR) / (CAMERA_NEAR - CAMERA_FAR);
	scop->matrix->projection[2 + 3 * 4] = -1.0;
}

void		scop_set_matrix(t_scop *scop)
{
	create_model_matrix(scop);
	create_view_matrix(scop);
	create_projection_matrix(scop);
}
