/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:58:57 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 15:58:59 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define WIDTH				1280
# define HEIGHT				720
# define FPS 				30
# define FRAGMENT 			"shaders/fragmentShader.glsl"
# define VERTEX 			"shaders/vertexShader.glsl"
# define BUFFER_SIZE 		128
# define CAMERA_FOV			70
# define CAMERA_NEAR		0.001f
# define CAMERA_FAR			100.0f
# define PRECISION			0.000001f
# define RAD(x)				((M_PI * (x)) / 180.0)
# define TEXTURE_TILING		15.0f
# define SPEED_ROTATION		2
# define SPEED_TRANSFORM	1
# define SPEED_DELTA_SCALE 	0.05

# ifdef __APPLE__
#  include <OpenGL/gl3.h>
#  include <OpenGL/gl3ext.h>
# endif
# include <vec3.h>
# include <libft.h>
# include <SDL2/SDL.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef enum		e_mode
{
	WIRE, GRAY, FLAT_COLOR, SMOOTH_COLOR, TEXTURE
}					t_mode;

typedef enum		e_bool
{
	false, true
}					t_bool;

typedef struct		s_vetrex
{
	int				index;
	t_vec3			position;
	t_vec3			uv;
	t_vec3			normal;
	t_vec3			tangent;
	t_vec3			bitangent;
}					t_vertex;

typedef struct		s_matrix
{
	GLfloat			model[16];
	GLfloat			view[16];
	GLfloat			projection[16];
	GLfloat			mvp[16];
}					t_matrix;

typedef struct		s_camera
{
	t_vec3			position;
	t_vec3			target;
	t_vec3			forward_axis;
	t_vec3			right_axis;
	t_vec3			up_axis;
}					t_camera;

typedef struct		s_transform
{
	t_vec3			position;
	GLfloat			position_matrix[16];
	t_vec3			rotation;
	GLfloat			rotation_matrix[16];
	t_vec3			scale;
	GLfloat			scale_matrix[16];
}					t_transform;

typedef struct		s_buffer
{
	GLuint			vao;
	GLuint			vbo_vertex;
	GLuint			vbo_uv;
	GLuint			vbo_normal;
	GLuint			vbo_tangent;
	GLuint			vbo_bitangent;
	GLuint			ibo;
	uint			face_number;
}					t_buffer;

typedef struct		s_array
{
	float			*vertex_array;
	float			*uv_array;
	float			*normal_array;
	float			*tangent_array;
	float			*bitangent_array;
	uint			*face_array;
}					t_array;

typedef struct		s_lst
{
	t_vec3			vertex;
	int				face[3];
	struct s_lst	*next;
}					t_lst;

typedef struct		s_obj
{
	char			*obj_path;
	t_lst			*vertex;
	t_lst			*vertex_start;
	uint			vertex_length;
	t_lst			*uv;
	t_lst			*uv_start;
	uint			uv_length;
	t_lst			*normal;
	t_lst			*normal_start;
	uint			normal_length;
	t_lst			*face;
	t_lst			*face_start;
	uint			face_length;
	t_vec3			center_offset;
}					t_obj;

typedef struct		s_light
{
	t_vec3			position;
	t_vec3			color;
}					t_light;

typedef struct		s_texture
{
	char			*diffuse_texture_path;
	char			*normal_texture_path;
	GLuint			diffuse_texture_id;
	GLuint			normal_texture_id;
	GLuint			bump;
}					t_texture;

typedef struct		s_control
{
	t_bool			play;
	t_bool			background;
	t_mode			mode_color;
	t_bool			switch_normal;
	t_bool			switch_diffuse;
	t_bool			switch_specular;
	GLfloat			index_specular;
}					t_control;

typedef struct		s_shader
{
	char			*vertex_path;
	char			*fragment_path;
	GLuint			shader_program;
	GLuint			vertex_shader;
	GLuint			fragment_shader;
	GLuint			mvp_matrix_location;
	GLuint			mode_color_location;
	GLuint			model_matrix_location;
	GLuint			diffuse_texture_location;
	GLuint			normal_texture_location;
	GLuint			mapping_diffuse_location;
	GLuint			mapping_normal_location;
	GLuint			light_position_location;
	GLuint			light_color_location;
	GLuint			view_position_location;
	GLuint			switch_normal_location;
	GLuint			switch_diffuse_location;
	GLuint			switch_specular_location;
	GLuint			index_specular_location;
}					t_shader;

typedef	struct		s_time
{
	uint32_t		cur_time;
	uint			delta_time;
	uint			cur_fps;
}					t_time;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_GLContext	gl_context;
	int				width;
	int				height;
	SDL_Event		event;
	const Uint8		*keystate;
}					t_sdl;

typedef struct		s_scop
{
	int				ac;
	char			**av;
	t_sdl			*sdl;
	t_time			*time;
	t_shader		*shader;
	t_control		*control;
	t_texture		*texture;
	t_light			*light;
	t_obj			*obj;
	t_array			*array;
	t_buffer		*buffer;
	t_transform		*transform;
	t_camera		*camera;
	t_matrix		*matrix;
}					t_scop;

void				tutorial(void);
void				core_time(t_scop *scop);
void				core_keyboard(t_scop *scop);
void				core_keyboard_transform(t_scop *scop);
void				core_render(t_scop *scop);
t_scop				*scop_init(int ac, char **av);
void				scop_shader_upload(t_scop *scop);
void				scop_shader_linking(t_scop *scop);
void				scop_upload_texture(t_scop *scop);
void				scop_upload_obj(t_scop *scop);
void				scop_centered_obj(t_scop *scop);
void				scop_create_array(t_scop *scop);
void				scop_set_array(t_scop *scop);
void				scop_set_transform(t_scop *scop);
void				scop_set_matrix(t_scop *scop);
void				scop_calculate_mvp(t_scop *scop);
void				scop_loop(t_scop *scop);
void				scop_free(t_scop *scop);
void				scop_error(const char *message);
void				sdl_init(t_scop *scop);
void				sdl_exit(t_scop *scop);
void				sdl_error(const char *message);
void				gl_init_buffer(t_scop *scop);
void				gl_init_viewport(t_scop *scop);
t_lst				*lst_new(char *line, char *separator);
void				lst_push_back(t_lst **start, t_lst **end, t_lst *new);
void				lst_free(t_lst *lst);
void				face_new(t_scop *scop, char *line);
void				vertex_uv(t_vertex *v1, t_vertex *v2, t_vertex *v3);
void				vertex_normal(t_vertex *v1, t_vertex *v2, t_vertex *v3);
void				vertex_tangent(t_vertex *v1, t_vertex *v2, t_vertex *v3);

#endif
