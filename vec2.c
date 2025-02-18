#include <rt.h>

t_vec3	cross(const t_vec3 a, const t_vec3 b)
{
	t_vec3 res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

float	vec_length(t_vec3 v)
{
	return sqrt(dot(v, v));
}

t_vec3	norm(t_vec3 v, float target_len)
{
	return scale(target_len/vec_length(v), v);
}

t_vec3	pairwise_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

t_vec3	pairwise_div(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x / b.x, a.y / b.y, a.z / b.z});
}
