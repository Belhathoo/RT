/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:59:05 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 14:29:31 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEFINE_H
# define RT_DEFINE_H

/*
 * Macros
 */

# define NBTHREAD 4
# define MAX_DEPTH 50

# define WIN_HEIGHT 800
# define WIN_WIDTH 1330
# define IMG_HEIGHT 600
# define IMG_WIDTH 1200
# define FRAME_UP 150
# define FRAME_DWN 50
# define FRAME_LFT 120
# define FRAME_RGHT 10

# define MAX 1e+9
# define MIN 1e-4
# define EPS 1e-9

# define PT_LIGHT 0
# define SP_LIGHT 1
# define PL_LIGHT 2

# define RS rt->scene
# define RCR rec->curr_obj

//  * MLX KEYS
# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include <key_linux.h>
# endif

// *   Noises

# define DAMIER 0
# define CIRCLES 1
# define VORONOI1 2
# define VORONOI2 3
# define VORONOI3 4
# define PERLIN 5

// BUTTONS

# define SAVE_BTN 0
# define MVT_BTN 1
# define CAM_BTN 2
# define LGHT_BTN 3
# define DAME_BTN 4
# define CIRC_BTN 5
# define V1_BTN 6
# define V2_BTN 7
# define V3_BTN 8

// *   Filters

# define NONE_FILTER 0
# define SEPIA 1
# define BNW 2 //
# define NEGATIVE 3
# define GRAY 4
# define MOTION_BLUR 5

#endif
