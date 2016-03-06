#include "Resizer.h"

image_size_t resizer(const char *filename, int frame_width, int frame_height, bool use_frame) {

  float factor_width  = 0.0f ;
  float factor_height = 0.0f ;

  float width  = 0.0f ;
  float height = 0.0f ;

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);

  float image_width  =  (float) gdk_pixbuf_get_width(pixbuf)  ;
  float image_height =  (float) gdk_pixbuf_get_height(pixbuf) ;


  float frame_image_width  = (float) frame_width  ;
  float frame_image_height = (float) frame_height ;

  float factor= (float) ( (float) frame_width / (float) frame_height)  ;

  if ((image_width >= frame_image_width) && (image_height > frame_image_height)) {

    factor_width  =  (float) image_width  / (float)  image_height  ;
    factor_height =  (float) image_height / (float)  image_width   ;

    width  = 0.0f  ;
    height = 0.0f  ;


    if ((factor_width == 1.0) || (factor_height == 1.0)) {

      if (frame_image_height > frame_image_width) {
        width  = frame_image_width ;
        height = frame_image_width ;
      }
      else if (frame_image_height < frame_image_width) {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
      else {
        width  = frame_image_height ;
        height = frame_image_height ;
      }

    }

    if (image_width > image_height) {

      if (factor_width < factor ) {

        while (height < frame_image_height) {

          if ((height + factor_height) >= frame_image_height) {
            width *= factor_height  ;
            break ;
          }

          width  += factor_width   ;
          height += factor_height  ;
        }
      }
      else if (factor_width > factor) {

        while (width < frame_image_width) {
          if ((width + factor_width) >= frame_image_width) {
            height *= factor_width ;
            break  ;
          }
          width  += factor_width   ;
          height += factor_height  ;
        }
      }

    }

    if (image_width < image_height) {

      if (factor_width < factor) {

        while (height < frame_image_height) {

          if ((height + factor_height) >= frame_image_height) {
            width *= factor_height ;
            break ;
          }
          width = width + factor_width    ;
          height =height+factor_height    ;
        }
      }
      else if (factor_width > factor) {

        while (width < frame_image_width) {

          if ((width + factor_width) >= frame_image_width) {
            height *= factor_width ;
            break  ;
          }
          width  += factor_width  ;
          height += factor_height ;
        }

      }
    }

  }

  else if ((image_width > frame_image_width) && (image_height <= frame_image_height)) {

    factor_width  = (float)(image_width)  / (float)(image_height) ;
    factor_height = (float)(image_height) / (float)(image_width)  ;
    width = 0.0f ;
    height =0.0f ;

    if (image_width == image_height) {
      if (frame_image_height > frame_image_width) {
        width  = frame_image_width ;
        height = frame_image_width ;
      }
      else if (height < frame_image_width) {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
      else {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
    }
    if (factor_width < factor) {
      while (height < frame_image_height) {
        if ((height + factor_height) >= height) {
          width *= factor_height ;
          break ;
        }

        width  += factor_width  ;
        height += factor_height ;
      }
    }
    else if (factor_width > factor) {

      while (width < frame_image_width) {

        if ((width + factor_width) >= frame_image_width) {
          height *= factor_width ;
          break  ;
        }
        width  += factor_width   ;
        height += factor_height  ;
      }
    }
  }

  else if ((image_width <= frame_image_width) && (image_height > frame_image_height)) {
    factor_width  = (float)(image_width) /  (float)(image_height) ;
    factor_height = (float)(image_height) / (float)(image_width) ;
    width  = 0.0f ;
    height = 0.0f ;


    if (image_width == image_height) {
      if (frame_image_height > frame_image_width) {
        width  = frame_image_width ;
        height = frame_image_width ;
      }
      else if (frame_image_height < frame_image_width) {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
      else {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
    }

    if (image_width > image_height) {

      if (factor_width < factor) {

        while (height < frame_image_height) {

          if ((height + factor_height) >= frame_image_height) {
            width *= factor_height ;
            break ;
          }

          width  += factor_width  ;
          height += factor_height ;
        }
      }
      else if (factor_width > factor) {

        while (width < frame_image_width) {

          if ((width + factor_width) >= width ) {
            height *= factor_width ;
            break  ;
          }
          width  += factor_width   ;
          height += factor_height  ;
        }
      }
    }
    if (image_width < image_height) {

      if (factor_width < factor) {        

        while (height < frame_image_height) {

          if ((height + factor_height) >= frame_image_height) {
            width *= factor_height ;
            break ;
          }
          width  += factor_width  ;
          height += factor_height ;
        }
      }
      else if (factor_width > factor) {

        while (width < frame_image_width) {
          if ((width + factor_width) >= width) {
            height *= factor_width ;
            break  ;
          }
          width  += factor_width  ;
          height += factor_height ;
       }

      }
    }

  }

  else if ((image_width <= frame_image_width) && (image_height <= frame_image_height)) {

    factor_width  = (float) image_width/image_height ;
    factor_height = (float) image_height/image_width ;

    width        = (float) image_width ;
    height       = (float) image_height ;
 
    if (! (use_frame) ) {

      if (frame_image_height == frame_image_width) {

        if (width > height) {

          while (width < frame_image_width) {
            width++  ;
            height += factor_height ;
          }
        }
        else if (width < height) {

          while (height < frame_image_height) {
            width += factor_width  ;
            height++ ;
          }
        }
        else {

          while (width < frame_image_width) {
           width++  ;
           height++ ;
          }
        }

      }
      else if (frame_image_height < frame_image_width && (frame_image_width > width) ) {

        while (width < frame_image_width) {
          width++ ;
          height += factor_height ;
        }
      }
      else if (frame_image_height < frame_image_width && (frame_image_height > height) ) {

        while (height < frame_image_height) {

          height++ ;
          width += factor_width ;
        }
      }
      else if (frame_image_height > frame_image_width && (frame_image_width > width) )  {

        while (width < frame_image_width) {
          width++ ;
          height += factor_height ;
        }
      }
      else if (frame_image_height > frame_image_width && (frame_image_height > height) )  {

        while (height < frame_image_height) {

          height++ ;
          width += factor_width ;
        }
      }

    }

  }

  image_size_t ret ;

  ret.width  = (uint16_t) roundf(width) ;
  ret.height = (uint16_t) roundf(height) ;

  ret.width_factor  = factor_width  ;
  ret.height_factor = factor_height ;
 

  return ret ;
}

