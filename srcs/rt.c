/* ************************************************************************** */
#include <rt.h>

static void rt_parse(t_rt *rt, char **argv)
{
  t_vec lookfrom = vec(-0, 20, -20.0);
  t_vec lookat = vec(0.0, 0.0, 0.0);
  float fov = 60.0;
  t_object *o;


  rt->scene->cam = rt_init_camera(lookfrom, lookat, fov);
/*
  rt->scene->object = (t_object *)malloc(sizeof(t_object));
  o = rt->scene->object;
  rt->scene->object->hit = rt_hit_sphere;
  rt->scene->object->pos = vec(-3.0, 0.0, 0.0);
  rt->scene->object->rot = vec(0, 0, 1);
  rt->scene->object->col = vec(0.2, 0.0, 1.0);
  rt->scene->object->size = 2.0;
  rt->scene->object->ka = 0.4;
  rt->scene->object->kd = 0.6;
  rt->scene->object->ks = 0.6;
  rt->scene->object->shininess = 90;
 */
  rt->scene->object = (t_object *)malloc(sizeof(t_object));
  o = rt->scene->object;
  rt->scene->object->name = ft_strdup("Cube");
  rt->scene->object->hit = rt_hit_cube;
  rt->scene->object->pos = vec(0.0, 0.0, 0.0);
  rt->scene->object->rot = vec_unit(vec(3.0, 2.0, 0.0));
  rt->scene->object->col = vec(1, 0, 0);
  rt->scene->object->size = 0.0;
  rt->scene->object->r = 1.2;
  rt->scene->object->ka = 0.4;
  rt->scene->object->kd = 0.6;
  rt->scene->object->ks = 0.6;
  rt->scene->object->shininess = 90;
  rt->scene->object->txt = NULL;  
  //add_(rt->scene->object);
  //  rt->scene->object = (t_object *)malloc(sizeof(t_object));
  //  o = rt->scene->object;
  //  rt->scene->object->hit = rt_hit_torus;
  //  rt->scene->object->pos = vec(0.0, 20.0, 0.0);
  //  rt->scene->object->rot = vec(0.0, -1.0, 2.0);
  //  rt->scene->object->col = vec(0.0, 1.0, 0.0);
  //  rt->scene->object->size = 9.0;
  //  rt->scene->object->ka = 0.4;
  //  rt->scene->object->kd = 0.6;
  //  rt->scene->object->ks = 0.6;
  //  rt->scene->object->shininess = 90;

//   rt->scene->object->next = (t_object *)malloc(sizeof(t_object));
//   rt->scene->object = rt->scene->object->next;
//   rt->scene->object->hit = rt_hit_sphere;
//   rt->scene->object->pos = vec(0.0, -50.5, -1.0);
//   rt->scene->object->rot = vec(0, 1, 0);
//   rt->scene->object->col = vec(0.0, 1.0, 1.0);
//   rt->scene->object->size = 50.0;
//   rt->scene->object->ka = 0.4;
//   rt->scene->object->kd = 0.6;
//   rt->scene->object->ks = 0.6;
//   rt->scene->object->shininess = 90;

  rt->scene->object->next = NULL;
  
  rt->scene->object = o;
   rt_get_repere(rt->scene);
   add_(rt->scene->object);
   
  // rt->scene->light = (t_light *)malloc(sizeof(struct s_l));
  // rt->scene->light->pos = vec(-5.0, 5.0, 5.0);
  // rt->scene->light->intensity = 0.8;
  // rt->scene->light->col = vec(1.0, 1.0, 1.0);
  // rt->scene->light->next = NULL;
  
}


void  add_(t_object *o)
{ 
   
    if (ft_strcmp(o->name, "Cube") == 0)
        get_cube_compos( o);
	
}

void background(t_rt *rt)
{
  int i;
  int j;

  i = -1;
  while (j = -1, ++i < WIN_WIDTH)
    while (++j < WIN_HEIGHT)
      mlx_pixel_put(rt->mlx, rt->win, i, j, 0x3E3E3d);
}

int main(int argc, char **argv)
{
  t_rt rt;

  
  rt_init(&rt);
  rt.scene = rt_init_scene();
  rt.mlx = mlx_init();
  if (argc == 2)
      rt_parser(&rt, argv);
  else
    rt_exit(&rt, ft_strdup("usage: ./rt scene_file"), EXIT_FAILURE);
  // rt.win = mlx_new_window(rt.mlx, WIN_WIDTH, WIN_HEIGHT, "RT");
  // rt.img = mlx_new_image(rt.mlx, IMG_WIDTH, IMG_HEIGHT);
  // rt.data = (int*)mlx_get_data_addr(rt.img, &rt.bpp, &rt.size, &rt.endian);
  // //background(&rt);
  // rt_draw(&rt);

  // mlx_hook(rt.win, 17, (1L << 17), rt_close, &rt);
  // mlx_hook(rt.win, 2, (1L << 0), rt_keys, &rt);
  // mlx_hook(rt.win, 4, (1L << 0), rt_mouse, &rt);
  // mlx_loop(rt.mlx);
  return (EXIT_SUCCESS);
}