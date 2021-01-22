

# include <libxml.h>

int    check_tag(char  *t_name)
{
    char    *str;

    str = t_name;
    // str = ft_strupcase(str);
    if (!ft_strncmp(str, "Camera", 6) && !ft_strncmp(str, "Object", 6)\
        && !ft_strncmp(str, "Light", 5) && !ft_strncmp(str, "Option", 6))
        return (0);
    return (1);
}