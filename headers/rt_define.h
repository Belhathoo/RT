/* ************************************************************************** */

#ifndef RT_DEFINE_H
# define RT_DEFINE_H

/*
 * Macros
 */

# define WIN_HEIGHT 720
# define WIN_WIDTH 1080
# define IMG_HEIGHT 500
# define IMG_WIDTH 1000

# define NBTHREAD 4
# define MAX_DEPTH 50
# define MAX  1e+9 // distance max de propagation
# define MIN 1e-4 
# define  EPS 1e-9    // dist min

# define S_LIGHT 0 //spot light; usual one
# define P_LIGHT 1 //parallele light; following one direction


/*
 * MLX KEYS
 */

# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include <key_linux.h>
# endif



# define DAMIER 0
# define CIRCLES 1
# define VORONOI1 2
# define VORONOI2 3
# define VORONOI3 4


/*
 * Filters
 */

# define NONE_FILTER 0
# define SEPIA 1
# define BNW 2 //black and white
# define MOTION_BLUR 4
# define NEGATIVE 8
# define CARTOON 16

#endif