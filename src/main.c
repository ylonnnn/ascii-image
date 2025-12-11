#include "ascii-image/image.h"

int main()
{
    const char *fpath = "sample/liege-1.jpg";
    image_to_ascii(fpath, -1);

    return 0;
}
