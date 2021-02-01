
#include <rt.h>

t_object	*x_zero(t_object *compos, t_object *obj)
{
	compos->vec1 = obj->vec1;
	compos->vec2 = obj->vec2;
	compos->rot = obj->rot;
	compos->size = obj->size;
	//compos->height = obj->height;
	//compos->weight = obj->weight;
	return (compos);
}

t_object	*x_un(t_object *compos, t_object *obj)
{
	compos->vec1 = obj->vec1;
	compos->vec2 = obj->rot;
	compos->rot = obj->vec2;
	compos->size = obj->size;
	//compos->height = 4;
	return (compos);
}

t_object	*x_deux(t_object *compos, t_object *obj)
{
	compos->vec1 = obj->vec2;
	compos->vec2 = obj->rot;
	compos->rot = obj->vec1;
	compos->size = 4;
	//compos->height = 4;
	return (compos);
}

t_object	*x_trois(t_object *compos, t_object *obj)
{
	compos->vec1 = obj->rot;
	compos->vec2 = obj->vec1;
	compos->rot = obj->vec2;
	compos->size = 4;
	//compos->height = obj->size;
	return (compos);
}

t_object	*x_quatre(t_object *compos, t_object *obj)
{
	compos->vec1 = obj->rot;
	compos->vec2 = obj->vec2;
	compos->rot = obj->vec1;
	compos->size = 4;
	//compos->height = obj->size;
	return (compos);
}