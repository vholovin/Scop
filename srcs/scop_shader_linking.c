/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_linking_shader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:45:21 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 19:45:22 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		create_uniform_location_2(t_scop *scop)
{
	scop->shader->light_position_location =
		glGetUniformLocation(scop->shader->shader_program, "lightPosition");
	scop->shader->light_color_location =
		glGetUniformLocation(scop->shader->shader_program, "lightColor");
	scop->shader->view_position_location =
		glGetUniformLocation(scop->shader->shader_program, "viewPosition");
	scop->shader->switch_normal_location =
		glGetUniformLocation(scop->shader->shader_program, "switchNormal");
	scop->shader->switch_diffuse_location =
		glGetUniformLocation(scop->shader->shader_program, "switchDiffuse");
	scop->shader->switch_specular_location =
		glGetUniformLocation(scop->shader->shader_program, "switchSpecular");
	scop->shader->index_specular_location =
		glGetUniformLocation(scop->shader->shader_program, "indexSpecular");
}

static void		create_uniform_location_1(t_scop *scop)
{
	scop->shader->model_matrix_location =
		glGetUniformLocation(scop->shader->shader_program, "modelMatrix");
	scop->shader->mvp_matrix_location =
		glGetUniformLocation(scop->shader->shader_program, "mvpMatrix");
	scop->shader->mode_color_location =
		glGetUniformLocation(scop->shader->shader_program, "modeColor");
	scop->shader->diffuse_texture_location =
		glGetUniformLocation(scop->shader->shader_program, "diffuseTexture");
	scop->shader->normal_texture_location =
		glGetUniformLocation(scop->shader->shader_program, "normalTexture");
	scop->shader->mapping_diffuse_location =
		glGetUniformLocation(scop->shader->shader_program, "mappingDiffuse");
	scop->shader->mapping_normal_location =
		glGetUniformLocation(scop->shader->shader_program, "mappingNormal");
}

void			scop_shader_linking(t_scop *scop)
{
	GLint success;

	scop->shader->shader_program = glCreateProgram();
	glAttachShader(scop->shader->shader_program, scop->shader->vertex_shader);
	glAttachShader(scop->shader->shader_program, scop->shader->fragment_shader);
	glLinkProgram(scop->shader->shader_program);
	glGetProgramiv(scop->shader->shader_program, GL_LINK_STATUS, &success);
	if (!success)
		scop_error("shader program - linking failed");
	glUseProgram(scop->shader->shader_program);
	glDeleteShader(scop->shader->vertex_shader);
	glDeleteShader(scop->shader->fragment_shader);
	create_uniform_location_1(scop);
	create_uniform_location_2(scop);
}
