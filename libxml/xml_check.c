

# include <libxml.h>

int    check_tag(char  *t_name)
{
    char    *str;

    // printf("--%s--\n", t_name);
    str = t_name;
    // str = ft_strupcase(str);
    if (!ft_strncmp(str, "Camera", 6) || !ft_strncmp(str, "Object", 6)\
        || !ft_strncmp(str, "Light", 5) || !ft_strncmp(str, "Option", 6))
        return (1);
    return (0);
    
    /*
        check for repeated tags too!!
    */
}

/*
    attr depends on tag's name
    attributes for each Object depend on the value of the Name's atrr_Value
    atrribute for lights depends on the value of the Type's attr_Value
*/

/*
    only one of the 3 (col || txt || noise)
*/

int     check_attr(char *t_name, char *a_name)
{

// printf("---%s---\n", t_name);
// printf("\t-%s-\n", a_name);
    if (!ft_strcmp(t_name, "Object"))
       { if (!ft_strcmp(a_name, "name") || !ft_strcmp(a_name, "position")\
            || !ft_strcmp(a_name, "direction") ||!ft_strcmp(a_name, "translation")\
            || !ft_strcmp(a_name, "rotation") || !ft_strcmp(a_name, "radius")\
            || !ft_strcmp(a_name, "color") || !ft_strcmp(a_name, "texture")
            || !ft_strcmp(a_name, "noise") || !ft_strcmp(a_name, "material"))
            return (1);}
    else if (!ft_strcmp(t_name, "Camera"))
       { if (!ft_strcmp(a_name, "lookfrom") || !ft_strcmp(a_name, "lookat")\
                || !ft_strcmp(a_name, "fov"))
            return (1);}
    else if (!ft_strcmp(t_name, "Option"))
        {if (!ft_strcmp(a_name, "anti-aliasing") || !ft_strcmp(a_name, "filtre"))
            return (1);}
    else if (!ft_strcmp(t_name, "Light"))
        {if (!ft_strcmp(a_name, "type") || !ft_strcmp(a_name, "position")\
            || !ft_strcmp(a_name, "angle") || !ft_strcmp(a_name, "radius")\
            || !ft_strcmp(a_name, "intensity") || !ft_strcmp(a_name, "color"))
            return (1);}
    return (0);
}