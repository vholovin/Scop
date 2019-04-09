/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_calculate_mvp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:29:49 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:29:51 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	multiplication_matrix(float *left, float *right, float *result)
{
	uint i;
	uint j;
	uint k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[j + i * 4] = 0.0f;
			k = 0;
			while (k < 4)
			{
				result[j + i * 4] += left[k + i * 4] * right[j + k * 4];
				k++;
			}
			j++;
		}
		i++;
	}
}

void		scop_calculate_mvp(t_scop *scop)
{
	float matrix[16];

	ft_bzero(&matrix, 16 * sizeof(float));
	multiplication_matrix(scop->transform->position_matrix,
										scop->transform->scale_matrix, matrix);
	multiplication_matrix(matrix, scop->transform->rotation_matrix,
														scop->matrix->model);
	multiplication_matrix(scop->matrix->projection, scop->matrix->view, matrix);
	multiplication_matrix(matrix, scop->matrix->model, scop->matrix->mvp);
}
