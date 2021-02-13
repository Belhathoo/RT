
# include <rt.h>

int				rt_mouse(int button, int x, int y, t_rt *rt)
{
  return (0);
}

t_vec	ft_rot_vec(t_vec a, t_vec b, double t)
{
	t_vec	res;

	res.x = (b.x * b.x + (1.0 - b.x * b.x) * cos(t)) * a.x + (b.x * b.y
			* (1.0 - cos(t)) - b.z * sin(t)) * a.y + (b.x * b.z
			* (1.0 - cos(t)) + b.y * sin(t)) * a.z;
	res.y = (b.x * b.y * (1.0 - cos(t)) + b.z * sin(t)) * a.x
		+ (b.y * b.y + (1.0 - b.y * b.y) * cos(t)) * a.y
		+ (b.y * b.z * (1.0 - cos(t)) - b.x * sin(t)) * a.z;
	res.z = (b.x * b.z * (1.0 - cos(t)) - b.y * sin(t)) * a.x
		+ (b.y * b.z * (1.0 - cos(t)) + b.x * sin(t)) * a.y
		+ (b.z * b.z + (1.0 - b.z * b.z) * cos(t)) * a.z;
	return (res);
}

int				rt_keys(int key, t_rt *rt)
{
  if (key == K_ESC)
		rt_close(rt);
    /*xyz 120 121 122 */
    if (key == K_X)
    {
      rt->scene->cam = rt_init_camera(ft_rot_vec(rt->scene->cam.lookfrom, vec(1, 0, 0), 5), rt->scene->cam.lookat, rt->scene->cam.fov);
      rt_draw(rt);
    }
    if (key == K_Y)
    {
      rt->scene->cam = rt_init_camera(ft_rot_vec(rt->scene->cam.lookfrom, vec(0, 1, 0), 5), rt->scene->cam.lookat, rt->scene->cam.fov);
      rt_draw(rt);
    }
    if (key == K_Z)
    {
      rt->scene->cam = rt_init_camera(ft_rot_vec(rt->scene->cam.lookfrom, vec(0, 0, 1), 5), rt->scene->cam.lookat, rt->scene->cam.fov);
      rt_draw(rt);
    }
  return (0);
}