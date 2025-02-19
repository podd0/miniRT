#include <rt.h>

t_frame	f_to_world(t_frame f1, t_frame ref)
{
	t_frame	res;

	res.o = add(ref.o, f1.o);
	res.x = v_to_world(f1.x, ref);
	res.y = v_to_world(f1.y, ref);
	res.z = v_to_world(f1.z, ref);
	res.o = v_to_frame(res.o, ref);
	res.o = v_to_world(res.o, res);
	return (res);
}
