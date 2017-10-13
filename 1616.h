//
//  1616.h
//  1616
//
/*
 MIT License
 
 Copyright (c) 2017 Joost Markerink
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef _1616_h
#define _1616_h

#include "pixelcanvas.h"


typedef struct _display1616 display1616;
typedef struct _driver1616 driver1616;

struct _driver1616{
    unsigned char previous_offset;
    char should_send_address;
    int(*sendPixel)(driver1616 *,unsigned char offset,unsigned char color);
};

typedef unsigned char canvas1616[16*16];

struct _display1616{
    pixelcanvas canvas;
    unsigned char pixel[16*16], next_pixel[16*16], change[16*16];
    unsigned char change_counter;
    driver1616 *driver;
};

void            display1616_initialize         (display1616 *,driver1616 *);
void            display1616_update             (display1616 *);
pixelcanvas *   display1616_as_canvas          (display1616 *);


#endif /* _ x4_h */
