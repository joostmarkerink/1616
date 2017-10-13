//
//  1616.c
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

#include "1616.h"

int canvas1616_sort(const void *a,const void *b){
    int aa=*(unsigned char *)a;
    int bb=*(unsigned char *)b;
    return aa-bb;
}

int driver1616_sendPixel(driver1616 *d,unsigned char offset,unsigned char clr){
    if(d->should_send_address==0 && d->previous_offset==(offset-1)){
        //just send the 4bit color;
    }else{
        //send offset and 4bit color;
    }
    return 1; 
}


void display1616_update(display1616 *d){
    if(d->change_counter==0) return;
    
    qsort(d->change, d->change_counter, sizeof(unsigned char),canvas1616_sort);

    unsigned char i;

    for(i=0;i<d->change_counter;i++){
        unsigned char clr=d->next_pixel[d->change[i]];
        unsigned char offset=d->change[i];
        if(d->driver->sendPixel(d->driver,offset,clr)){
            d->driver->previous_offset=offset;
            d->pixel[offset]=clr;
        }
    }
    d->change_counter=0;
}

pixelcanvas *display1616_as_canvas(display1616 *d){ return &d->canvas; }


void display1616_set_pixel_wo(display1616 *d,unsigned char o,char color){
    if(d->pixel[o]!=color && d->next_pixel[o]!=color){
        d->next_pixel[o]=color;
        int i;
        for(i=0;i<256;i++) if(d->change[i]==o) return;
        d->change[d->change_counter++]=o;
    }
}


void display1616_set_pixel(abstractpixelcanvas *d,int x,int y,unsigned int color){
    display1616_set_pixel_wo(d,(y*16)+x,color);
}

void display1616_initialize(display1616 *d,driver1616 *driver){
    d->driver=driver;
    d->canvas.width=16;
    d->canvas.height=16;
    d->canvas.set_pixel=display1616_set_pixel;
}
/*
void display1616_set_all_pixels(display1616 *d,const unsigned char *c){
    int i;
    for(i=0;i<(16*16);i++)
        display1616_set_pixel_wo(d,i,c[i]);
}

*/
