/** ***********************************************************************************
  * it-edit the Integrated Terminal Editor: a text editor with severals               *
  * integrated functionnalities.                                                      *
  *                                                                                   *
  * Copyright (C) 2016 Brüggemann Eddie.                                              *
  *                                                                                   *
  * This file is part of it-edit.                                                     *
  * it-edit is free software: you can redistribute it and/or modify                   *
  * it under the terms of the GNU General Public License as published by              *
  * the Free Software Foundation, either version 3 of the License, or                 *
  * (at your option) any later version.                                               *
  *                                                                                   *
  * it-edit is distributed in the hope that it will be useful,                        *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                      *
  * GNU General Public License for more details.                                      *
  *                                                                                   *
  * You should have received a copy of the GNU General Public License                 *
  * along with it-edit. If not, see <http://www.gnu.org/licenses/>                    *
  *                                                                                   *
  ************************************************************************************/

#include "terminals_callbacks.h"

gboolean display_clipboard_menu(GtkWidget *widget, GdkEvent  *event, GtkWidget *clipboard_menu) {
  /** Display the clipbpoard menu from the terminals. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ((event->type == GDK_BUTTON_PRESS) && (((GdkEventButton*)event)->button == 3)) {

    gtk_menu_popup(GTK_MENU(clipboard_menu),
                   NULL,
                   NULL,
                   NULL,
                   NULL,
                   ((GdkEventButton*)event)->button,
                   gtk_get_current_event_time());



    return TRUE ;
  }

  return FALSE ;
}



void clipboard_copy(GtkMenuItem *menuitem, gpointer user_data) {
  /** Copy the selected text from an terminal to the clipboard. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  vte_terminal_copy_clipboard(VTE_TERMINAL(user_data) );

  return ;

}

void clipboard_paste(GtkMenuItem *menuitem, VteTerminal *user_data) {
  /** Paste the clipboard content into an terminal. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  vte_terminal_paste_clipboard(VTE_TERMINAL(user_data)) ;

  return ;
}

void terminal_size_allocate(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) {

  /** Callback by resizing terminals of any sort. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (! g_file_test(settings.image_filepath, G_FILE_TEST_EXISTS)) {

    return ;
  }

  if ((settings.use_bg_image) && (settings.use_image)) {

    resize_terminal_background_image(widget, settings.image_filepath, allocation->width, INT_MAX) ;
  }

  return ;

}


inline void resize_terminal_background_image(GtkWidget *widget, const char *filepath, const int width, const int height) {

  /** The terminal background image will always covers all the terminal surface. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GError *error = NULL ;

  image_size_t new_size_image = resizer(filepath, width, height, false) ;

  GdkPixbuf *pixbuf        ;
  GdkPixbuf *pixbuf_scaled ;

  pixbuf_scaled = gdk_pixbuf_new_from_file(filepath, &error) ;


  if (error == NULL) {

    pixbuf = gdk_pixbuf_scale_simple(pixbuf_scaled, new_size_image.width, gtk_widget_get_allocated_height(widget), GDK_INTERP_NEAREST) ;

    g_object_set(G_OBJECT(widget), "background-image-pixbuf", pixbuf, NULL) ;

    g_object_unref(pixbuf_scaled) ;

  }
  else {
    g_error_free(error) ;
  }

  return ;

}

