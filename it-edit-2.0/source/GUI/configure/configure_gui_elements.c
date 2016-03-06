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

#include "./configure_gui_elements.h"

void setting_sourceview_settings(GtkSourceView *view) {
  /** Configure the GtkSourceView according to configuration. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gtk_source_view_set_auto_indent(view, settings.use_auto_indent) ;
  gtk_source_view_set_indent_on_tab(view, TRUE);
  gtk_source_view_set_indent_width(view, settings.indent_width) ;

  gtk_source_view_set_insert_spaces_instead_of_tabs(view, settings.use_spaces_as_tabs);
  gtk_source_view_set_smart_home_end(view, GTK_SOURCE_SMART_HOME_END_BEFORE) ;  /** ??? **/


  gtk_source_view_set_show_line_numbers(view, settings.display_line_numbers) ;

  gtk_source_view_set_tab_width(view, settings.tabs_width) ;

  if (settings.display_tabs_chars) {
    gtk_source_view_set_draw_spaces(view, GTK_SOURCE_DRAW_SPACES_TAB) ;
  }


  PangoFontDescription *font_desc = pango_font_description_from_string(settings.editor_font) ;
  gtk_widget_override_font(GTK_WIDGET(view), font_desc);

  return ;
}




void configure_terminal(GtkWidget *vteterminal, bool initialize) {
  /** Configure the VteTerminal according to the configuration. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Font settings: **/
  PangoFontDescription *font_desc = pango_font_description_from_string(settings.term_font) ;

  g_object_set(G_OBJECT(vteterminal), "font-desc", font_desc, NULL) ;

  /** Cursor shape settings: **/
  vte_terminal_set_cursor_shape(VTE_TERMINAL(vteterminal), (settings.cursor_shape == 0) ? VTE_CURSOR_SHAPE_BLOCK : (settings.cursor_shape == 1) ? VTE_CURSOR_SHAPE_IBEAM : VTE_CURSOR_SHAPE_UNDERLINE) ;



  /** Erasing keys binding. TODO: to remove maybe ??? **/
  g_object_set(G_OBJECT(vteterminal), "backspace-binding", (settings.backspace_binding == 0) ? VTE_ERASE_AUTO :
                                                           (settings.backspace_binding == 1) ? VTE_ERASE_ASCII_BACKSPACE :
                                                           (settings.backspace_binding == 2) ? VTE_ERASE_ASCII_DELETE :
                                                           (settings.backspace_binding == 3) ? VTE_ERASE_DELETE_SEQUENCE :
                                                                                               VTE_ERASE_TTY,
                                                           NULL) ;

  g_object_set(G_OBJECT(vteterminal), "delete-binding", (settings.delete_binding == 0) ? VTE_ERASE_AUTO :
                                                        (settings.delete_binding == 1) ? VTE_ERASE_ASCII_BACKSPACE :
                                                        (settings.delete_binding == 2) ? VTE_ERASE_ASCII_DELETE :
                                                        (settings.delete_binding == 3) ? VTE_ERASE_DELETE_SEQUENCE :
                                                                                         VTE_ERASE_TTY,
                                                         NULL) ;


  /** Background image settings: **/
  if (settings.use_bg_image) {

    // Must include the foreground color cause of the if statement.
    GdkRGBA fg_terminal ;
    gdk_rgba_parse(&fg_terminal, settings.term_fg) ;
    vte_terminal_set_default_colors(VTE_TERMINAL(vteterminal)) ;
    vte_terminal_set_color_foreground_rgba(VTE_TERMINAL(vteterminal), &fg_terminal) ;

    if (settings.use_texture) {

      if (g_file_test(settings.texture_filepath, G_FILE_TEST_EXISTS)) {

        g_object_set(G_OBJECT(vteterminal), "background-image-file", settings.texture_filepath, NULL) ;

        g_object_set(G_OBJECT(vteterminal), "scroll-background", settings.scroll_background, NULL)  ;  // default.

      }



    }
    else if (settings.use_image) {

      if (g_file_test(settings.image_filepath, G_FILE_TEST_EXISTS)) {

        if (initialize) {

          g_signal_connect(G_OBJECT(GTK_WIDGET(vteterminal)), "size-allocate", G_CALLBACK(terminal_size_allocate), NULL) ;
        }

        g_object_set(G_OBJECT(vteterminal), "scroll-background", FALSE, NULL)  ;  // default.

      }
    }
  }
  else {

    /** Colors settings: **/
    GdkRGBA bg_terminal ;
    gdk_rgba_parse(&bg_terminal, settings.term_bg) ;
    GdkRGBA fg_terminal ;
    gdk_rgba_parse(&fg_terminal, settings.term_fg) ;
 
    vte_terminal_set_default_colors(VTE_TERMINAL(vteterminal)) ;
 
    vte_terminal_set_color_foreground_rgba(VTE_TERMINAL(vteterminal), &fg_terminal) ;

    g_object_set(G_OBJECT(vteterminal), "background-image-file", NULL, NULL) ; // Must reset this setting otherwise background rgba is not settable.

    vte_terminal_set_color_background_rgba(VTE_TERMINAL(vteterminal), &bg_terminal) ;

    g_object_set(G_OBJECT(vteterminal), "scroll-background", settings.scroll_background, NULL)  ;

  }



  /** Usual default settings: **/
  vte_terminal_set_scrollback_lines(VTE_TERMINAL(vteterminal),    settings.scrollback_lines) ;

  vte_terminal_set_scroll_on_output(VTE_TERMINAL(vteterminal),    settings.scroll_on_output) ;

  vte_terminal_set_scroll_on_keystroke(VTE_TERMINAL(vteterminal), settings.scroll_on_keystroke) ;

  vte_terminal_set_emulation(VTE_TERMINAL(vteterminal),          NULL) ;  // default ; vte_terminal_get_emulation(VTE_TERMINAL(vteterminal))

  vte_terminal_set_encoding(VTE_TERMINAL(vteterminal),           vte_terminal_get_encoding(VTE_TERMINAL(vteterminal)))  ;  // default

  vte_terminal_set_cursor_blink_mode(VTE_TERMINAL(vteterminal),  VTE_CURSOR_BLINK_SYSTEM) ;

  /** Mouse left button double click word separators: The following characters are not register as word separators. **/
  vte_terminal_set_word_chars(VTE_TERMINAL(vteterminal), settings.regex_word_chars) ;



  return ;
}

void apply_editor_change(void) {
  /** Apply changes to every noetbbok page. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gint number_of_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) ;

  int c ;
  for (c = 0 ; c < number_of_pages ; c++) {

    GtkWidget *notebook_child              = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), c) ;
    GtkWidget *current_textview            = gtk_bin_get_child(GTK_BIN(notebook_child)) ;

    setting_sourceview_settings(GTK_SOURCE_VIEW(current_textview)) ;
  }

  return ;

}

void apply_terminal_bg_change(void) {

  /** Apply and or update terminals background image. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ((settings.use_bg_image) && (settings.use_image) && (settings.image_filepath != NULL) ) {

    resize_terminal_background_image(gui->big_four_terminals->terminal_1->terminal, settings.image_filepath, gtk_widget_get_allocated_width(gui->big_four_terminals->terminal_1->terminal), INT_MAX) ;
    resize_terminal_background_image(gui->big_four_terminals->terminal_2->terminal, settings.image_filepath, gtk_widget_get_allocated_width(gui->big_four_terminals->terminal_2->terminal), INT_MAX) ;
    resize_terminal_background_image(gui->big_four_terminals->terminal_3->terminal, settings.image_filepath, gtk_widget_get_allocated_width(gui->big_four_terminals->terminal_3->terminal), INT_MAX) ;
    resize_terminal_background_image(gui->big_four_terminals->terminal_4->terminal, settings.image_filepath, gtk_widget_get_allocated_width(gui->big_four_terminals->terminal_4->terminal), INT_MAX) ;

    resize_terminal_background_image(gui->big_terminal->terminal, settings.image_filepath, gtk_widget_get_allocated_width(gui->big_terminal->terminal), INT_MAX) ;

  }

  configure_terminal(gui->big_four_terminals->terminal_1->terminal, false) ;
  configure_terminal(gui->big_four_terminals->terminal_2->terminal, false) ;
  configure_terminal(gui->big_four_terminals->terminal_3->terminal, false) ;
  configure_terminal(gui->big_four_terminals->terminal_4->terminal, false) ;

  configure_terminal(gui->big_terminal->terminal, false) ;

  gint page_nb = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->terminal_notebook)) ;

  int c ;

  for (c=0 ; c < page_nb ; c++) {

    Terminals *terminals = g_object_get_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->terminal_notebook),c)), "terminals") ;

    if ((settings.use_bg_image) && (settings.use_image) && (settings.image_filepath != NULL)) {

      resize_terminal_background_image(terminals->terminal_1->terminal, settings.image_filepath, gtk_widget_get_allocated_width(terminals->terminal_1->terminal), INT_MAX) ;
      resize_terminal_background_image(terminals->terminal_2->terminal, settings.image_filepath, gtk_widget_get_allocated_width(terminals->terminal_2->terminal), INT_MAX) ;

     }

     configure_terminal(terminals->terminal_1->terminal, false) ;
     configure_terminal(terminals->terminal_2->terminal, false) ;
  }

  return ;

}


