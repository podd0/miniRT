/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:13:52 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/06 00:36:28 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H 1

struct					s_vi
{
	int					*arr;
	int					size;
	int					buf_size;
};

typedef struct s_vi		t_vi;

void					vi_push_back(t_vi *vec, int elem);
int						vi_pop_back(t_vi *vec);
void					vi_assign(t_vi *vec, int n, int value);
void					vi_resize(t_vi *vec, int n);
t_vi					*vi_init(int n, int value);
t_vi					*vi_uninit(int n);
void					vi_free(t_vi *vec);
t_vi					*vi_copy(t_vi *vec);
void					vi_map(t_vi *vec, void (*f)(int));
void					vi_map_sub(t_vi *vec, int (*f)(int));
int						vi_back(t_vi *vec);

struct					s_vl
{
	long				*arr;
	int					size;
	int					buf_size;
};

typedef struct s_vl		t_vl;

void					vl_push_back(t_vl *vec, long elem);
long					vl_pop_back(t_vl *vec);
void					vl_assign(t_vl *vec, int n, long value);
void					vl_resize(t_vl *vec, int n);
t_vl					*vl_init(int n, long value);
t_vl					*vl_uninit(int n);
void					vl_free(t_vl *vec);
t_vl					*vl_copy(t_vl *vec);
void					vl_map(t_vl *vec, void (*f)(long));
void					vl_map_sub(t_vl *vec, long (*f)(long));
long					vl_back(t_vl *vec);

struct					s_vlu
{
	long unsigned int	*arr;
	int					size;
	int					buf_size;
};

typedef struct s_vlu	t_vlu;

void					vlu_push_back(t_vlu *vec, long unsigned int elem);
long unsigned int		vlu_pop_back(t_vlu *vec);
void					vlu_assign(t_vlu *vec, int n, long unsigned int value);
void					vlu_resize(t_vlu *vec, int n);
t_vlu					*vlu_init(int n, long unsigned int value);
t_vlu					*vlu_uninit(int n);
void					vlu_free(t_vlu *vec);
t_vlu					*vlu_copy(t_vlu *vec);
void					vlu_map(t_vlu *vec, void (*f)(long unsigned int));
void					vlu_map_sub(t_vlu *vec,
							long unsigned int (*f)(long unsigned int));
long unsigned int		vlu_back(t_vlu *vec);

struct					s_vstr
{
	char				**arr;
	int					size;
	int					buf_size;
};

typedef struct s_vstr	t_vstr;

void					vstr_push_back(t_vstr *vec, char *elem);
char					*vstr_pop_back(t_vstr *vec);
void					vstr_assign(t_vstr *vec, int n, char *value);
void					vstr_resize(t_vstr *vec, int n);
t_vstr					*vstr_init(int n, char *value);
t_vstr					*vstr_uninit(int n);
void					vstr_free(t_vstr *vec);
t_vstr					*vstr_copy(t_vstr *vec);
void					vstr_map(t_vstr *vec, void (*f)(char *));
void					vstr_map_sub(t_vstr *vec, char *(*f)(char *));
char					*vstr_back(t_vstr *vec);

struct					s_vec
{
	void				**arr;
	int					size;
	int					buf_size;
};

typedef struct s_vec	t_vector;

void					vec_push_back(t_vector *vec, void *elem);
void					*vec_pop_back(t_vector *vec);
void					vec_assign(t_vector *vec, int n, void *value);
void					vec_resize(t_vector *vec, int n);
t_vector				*vec_init(int n, void *value);
t_vector				*vec_uninit(int n);
void					vec_free(t_vector *vec);
t_vector				*vec_copy(t_vector *vec);
void					vec_map(t_vector *vec, void (*f)(void *));
void					vec_map_sub(t_vector *vec, void *(*f)(void *));
void					*vec_back(t_vector *vec);

struct					s_vch
{
	char				*arr;
	int					size;
	int					buf_size;
};

typedef struct s_vch	t_vch;

void					vch_push_back(t_vch *vec, char elem);
char					vch_pop_back(t_vch *vec);
void					vch_assign(t_vch *vec, int n, char value);
void					vch_resize(t_vch *vec, int n);
t_vch					*vch_init(int n, char value);
t_vch					*vch_uninit(int n);
void					vch_free(t_vch *vec);
t_vch					*vch_copy(t_vch *vec);
void					vch_map(t_vch *vec, void (*f)(char));
void					vch_map_sub(t_vch *vec, char (*f)(char));
char					vch_back(t_vch *vec);

#endif
