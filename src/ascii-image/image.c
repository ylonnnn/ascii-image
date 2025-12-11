#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ascii-image/image.h"
#include "ascii-image/utils.h"

image_scale_status_t image_scale(dim_t *init_dim, dim_t *res, int32_t new_width)
{
    if (new_width < 1)
        return SCALE_MINIMUM_BOUND;

    int32_t width = init_dim->width, height = init_dim->height;
    if (width < new_width)
        return SCALE_UNSUPPORTED;

    double ratio = (double)height / width;

    res->height = new_width * ratio * 0.45;
    res->width = new_width;

    return SCALE_SUCCESS;
}

image_load_status_t image_load(const char *fpath, image_t *img,
                               int32_t req_comp)
{
    byte *data = stbi_load(fpath, &img->dim.width, &img->dim.height, &img->ch_n,
                           req_comp);
    if (data == NULL)
        return LOAD_FAIL;

    img->data = data;

    return LOAD_SUCCESS;
}

const char PIXEL_CHARS[] = ".,-~:;?*+SXsx%#@";
const size_t PC_COUNT =
    sizeof(PIXEL_CHARS) - 1; // Subtract 1 due to null terminator '\0'

void image_to_ascii(const char *fpath, int32_t width)
{
    image_t img;
    image_load_status_t load_st = image_load(fpath, &img, 1);
    if (load_st == LOAD_FAIL)
    {
        char message[256];
        sprintf(message, "failed to load '%s'", fpath);

        terminate(message, 0);
    }

    dim_t new;
    image_scale_status_t scale_st =
        image_scale(&img.dim, &new, width <= 0 ? img.dim.width : width);
    if (scale_st != SCALE_SUCCESS)
        terminate("failed to scale image", 0);

    double sc_h = (double)img.dim.height / new.height,
           sc_w = (double)img.dim.width / new.width;

    for (int32_t k = 0; k < new.height; ++k)
    {
        for (int32_t h = 0; h < new.width; ++h)
        {
            uint32_t average = 0;
            int32_t sy = k * sc_h, ey = (k + 1) * sc_h, sx = h * sc_w,
                    ex = (h + 1) * sc_w;

            for (int32_t y = sy; y < ey; ++y)
                for (int32_t x = sx; x < ex; ++x)
                {
                    int32_t idx = x + (y * img.dim.width);
                    average += (byte)img.data[idx];
                }

            average /= ((ey - sy)) * ((ex - sx));

            const char px =
                PIXEL_CHARS[(int32_t)((average / 255.0f) * (PC_COUNT - 1))];
            printf("%c", px);
        }

        printf("\n");
    }
}

void image_to_ascii_unscaled(const char *fpath) { image_to_ascii(fpath, -1); }
