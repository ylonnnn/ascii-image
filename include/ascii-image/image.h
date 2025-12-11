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

typedef enum
{
    SCALE_SUCCESS = 0,
    SCALE_FAIL,
    SCALE_UNSUPPORTED,
    SCALE_MINIMUM_BOUND,
} image_scale_status_t;

image_scale_status_t image_scale(dim_t *init_dim, dim_t *res, int new_width);

typedef enum
{
    LOAD_SUCCESS = 0,
    LOAD_FAIL
} image_load_status_t;

image_load_status_t image_load(const char *fpath, image_t *img, int req_comp);

/**
 * NOTE: If `width` is set to be less than `1`, the width will be based on the
 * original width of the image.
 */
void image_to_ascii(const char *fpath, int width);
void image_to_ascii_unscaled(const char *fpath);

#endif
