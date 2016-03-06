#ifndef GTK_RESIZER_UTILITY_HH
#define GTK_RESIZER_UTILITY_HH

#include <math.h>
#include <stdbool.h>
#include <inttypes.h> //stdint.h

#include <gdk/gdk.h>

typedef struct {

  uint16_t width ;
  uint16_t height ;

  float width_factor  ;
  float height_factor ;

} image_size_t ;

image_size_t resizer(const char *filename, int frame_width, int frame_height, bool use_frame) ;

#endif
