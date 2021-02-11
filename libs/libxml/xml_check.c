

# include <libxml.h>

void    xml_check_tag(char  *t_name, t_xml *x)
{
    char    *str;

    str = t_name;
    // str = ft_strupcase(str);

    /*
        Check for cam numbers!!
    */
   if (!ft_strncmp(str, "Camera", 6) && x->cam_nbr > 1)
        xml_exit(x, ft_strdup("Only One Camera Allowed !"), 1);

    if (!(!ft_strncmp(str, "Camera", 6) || !ft_strncmp(str, "Object", 6)\
            || !ft_strncmp(str, "Light", 5) || !ft_strncmp(str, "Option", 6)))
        xml_exit(x, ft_strdup("Tag Unknown!"), 1); // check repeated tags !
    
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

int     xml_check_attr(char *t_name, char *a_name, t_xml *x)
{
    if (!ft_strcmp(t_name, "Object"))
    {
        if (!ft_strcmp(a_name, "name") || !ft_strcmp(a_name, "position")\
            || !ft_strcmp(a_name, "direction") ||!ft_strcmp(a_name, "translation")\
            || !ft_strcmp(a_name, "rotation") || !ft_strcmp(a_name, "radius")\
            || !ft_strcmp(a_name, "r") || !ft_strcmp(a_name, "color")\
            || !ft_strcmp(a_name, "texture") || !ft_strcmp(a_name, "noise")\
            || !ft_strcmp(a_name, "slice_vec") || !ft_strcmp(a_name, "slice_pnt")\
            || !ft_strcmp(a_name, "material"))
            return (1);
    }
    else if (!ft_strcmp(t_name, "Camera"))
    {
        if (!ft_strcmp(a_name, "lookfrom") || !ft_strcmp(a_name, "lookat")\
                || !ft_strcmp(a_name, "fov"))
            return (1);
    }
    else if (!ft_strcmp(t_name, "Option"))
    {
        if (!ft_strcmp(a_name, "anti-aliasing") || !ft_strcmp(a_name, "filter"))
            return (1);
    }
    else if (!ft_strcmp(t_name, "Light"))
    {
        if (!ft_strcmp(a_name, "type") || !ft_strcmp(a_name, "position")\
            || !ft_strcmp(a_name, "angle") || !ft_strcmp(a_name, "radius")\
            || !ft_strcmp(a_name, "intensity") || !ft_strcmp(a_name, "color")\
            || !ft_strcmp(a_name, "direction"))
            return (1);
    }
    return (0);
}