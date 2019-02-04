#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    int width = x >= 0 ? (x < im.w ? x : im.w -1) : 0;
    int height = y >= 0 ? (y < im.h ? y : im.h -1) : 0;
    return im.data[im.w * height + width + im.w * im.h *c];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if (x >= 0 && x < im.w && y>=0 && y< im.w && c >=0 && c < im.c)
    {
        im.data[im.w * y + x + im.w * im.h * c] = v;
    }
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    memcpy(copy.data, im.data, sizeof(float) * im.w * im.h * im.c);
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);

    int currIndex = 0;

    for(int i = 0; i < im.h; ++i)
    {
        for(int j = 0; j < im.w; ++j)
        {
            currIndex = im.w * i + j;
            gray.data[currIndex] = 
                0.299 * im.data[currIndex] +
                0.587 * im.data[currIndex + im.h * im.w * 1]  +
                0.114 * im.data[currIndex + im.h * im.w * 2]; 
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    for(int i = 0; i < im.h; ++i)
    {
        for(int j = 0; j < im.w; ++j)
        {
            im.data[im.w * i + j + im.h * im.w * c] += v;
        }
    }
}

void clamp_image(image im)
{
    int currIndex = 0;
    for(int i = 0; i < im.h; ++i)
    {
        for(int j = 0; j < im.w; ++j)
        {
            for(int c = 0; c < im.c; ++c)
            {
                currIndex = im.w * i + j + im.h * im.w * c;
                if (im.data[currIndex] > 1)
                {
                    im.data[currIndex] = 1;
                }
                else if (im.data[currIndex] < 0)
                {
                    im.data[currIndex] = 0;
                }
            }
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
