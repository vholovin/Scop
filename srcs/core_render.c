/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoreRender.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:36:00 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 16:36:02 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	reset_shader(t_scop *scop)
{
	glUniformMatrix4fv(scop->shader->mvp_matrix_location, 1, GL_TRUE,
													&scop->matrix->mvp[0]);
	glUniformMatrix4fv(scop->shader->model_matrix_location, 1, GL_TRUE,
													&scop->matrix->model[0]);
	glUniform3f(scop->shader->light_position_location, scop->light->position.x,
							scop->light->position.y, scop->light->position.z);
	glUniform3f(scop->shader->light_color_location, scop->light->color.x,
							scop->light->color.y, scop->light->color.z);
	glUniform3f(scop->shader->view_position_location, scop->camera->position.x,
							scop->camera->position.y, scop->camera->position.z);
	glUniform1i(scop->shader->mode_color_location, scop->control->mode_color);
	glUniform1i(scop->shader->switch_normal_location,
												scop->control->switch_normal);
	glUniform1i(scop->shader->switch_diffuse_location,
												scop->control->switch_diffuse);
	glUniform1i(scop->shader->switch_specular_location,
												scop->control->switch_specular);
	glUniform1f(scop->shader->index_specular_location,
												scop->control->index_specular);
	if (scop->control->mode_color == WIRE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (scop->control->mode_color != WIRE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void	draw_reset(t_scop *scop)
{
	SDL_GetWindowSize(scop->sdl->window, &scop->sdl->width, &scop->sdl->height);
	glViewport(0, 0, scop->sdl->width, scop->sdl->height);
	if (scop->control->background == true)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	else if (scop->control->background == false)
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void	draw_object(t_scop *scop)
{
	glDrawElements(GL_TRIANGLES, scop->buffer->face_number,
													GL_UNSIGNED_INT, NULL);
}

static void	draw_update(t_scop *scop)
{
	SDL_GL_SwapWindow(scop->sdl->window);
}

void		core_render(t_scop *scop)
{
	reset_shader(scop);
	draw_reset(scop);
	draw_object(scop);
	draw_update(scop);
}
