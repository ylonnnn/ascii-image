#ifndef __ASCII_IMAGE_IMAGE_H__
#define __ASCII_IMAGE_IMAGE_H__

#include <stdint.h>
typedef unsigned char byte;

typedef struct
{
    int width, height;
} dim_t;

typedef struct
{
    dim_t dim;
    int ch_n; // Channel Count
    byte *data;
} image_t;

#define SCALE_SUCCESS 0
#define SCALE_FAIL 1
#define SCALE_UNSUPPORTED 2
#define SCALE_MINIMUM_BOUND 3

typedef int32_t image_scale_status;

image_scale_status image_scale(dim_t *init_dim, dim_t *res, int new_width);

#define LOAD_SUCCESS 0
#define LOAD_FAIL 1

typedef int32_t image_load_status;

image_load_status image_load(const char *fpath, image_t *img, int req_comp);

/**
 * NOTE: If `width` is set to be less than `1`, the width will be based on the
 * original width of the image.
 */
void image_to_ascii(const char *fpath, int width);
void image_to_ascii_unscaled(const char *fpath);

#endif
