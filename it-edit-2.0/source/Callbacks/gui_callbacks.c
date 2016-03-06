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

#include "gui_callbacks.h"



void toggle_display_terminals(GtkWidget *widget, gpointer user_data) {
  /** Toggle displaying terminals **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  /** The toggle echo is used for inhibit toggle from both the menu item and the button. **/
  static bool toggle_echo = false ;

  if (toggle_echo && user_data == NULL) {
    toggle_echo = false ;
    return ;
  }
  else {
    toggle_echo = false ;
  }

  if (! gtk_widget_get_visible(gui->terminal_notebook)) {
 
    /** Make the terminals side bar visible and give the focus to the terminal. **/
 
    gtk_widget_show(gui->terminal_notebook) ;

    Terminals *terminals  = g_object_get_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->terminal_notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->terminal_notebook)))), "terminals") ;

    gtk_widget_grab_focus(terminals->terminal_1->terminal) ;

    gtk_button_set_label(GTK_BUTTON(gui->buttons->terminals_show_button), "Hide") ;

  }
  else {
 
    /** Hide terminals sidebar and give the editor the focus. **/
 
    gtk_widget_hide(gui->terminal_notebook) ;

    if ( (gui->editor_notebook != NULL) && (gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) > 0) ) {

      if (gtk_widget_get_visible(gui->editor_notebook)) {

        GtkWidget *current_textview = gtk_bin_get_child(GTK_BIN(gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->editor_notebook))))) ;

        gtk_widget_grab_focus(current_textview) ;
      }

      gtk_button_set_label(GTK_BUTTON(gui->buttons->terminals_show_button), "Show") ;

    }

  }

  if (widget != NULL) {

    if ( ! gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->buttons->terminals_show_button)) &&  user_data != NULL ) {

      toggle_echo = true ;

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->terminals_show_button), TRUE) ;

    }
    else if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->buttons->terminals_show_button)) &&  user_data != NULL ) {

      toggle_echo = true ;

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->terminals_show_button), FALSE) ;
    }

  }


  return ;


}

void toggle_display_big_terminal_and_main_interface(GtkWidget *widget, gpointer user_data) {
  /** Toggle displaying big terminal and main interface **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  /** Keep track of the current Big term feature: **/
  static gint active_big_terminal = 2 ;

  /** The toggle echo is used for inhibit toggle from both the menu item and the button. **/
  static bool toggle_echo = false ;

  if (toggle_echo && user_data == NULL) {
    toggle_echo = false ;
    return ;
  }
  else {
    toggle_echo = false ;
  }


  active_big_terminal= (active_big_terminal == 1) ? 2 : 1 ;



  if (gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->main_notebook)) == 0) {
 
    /** Switch "Big term" on. **/
 
    gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), active_big_terminal) ;

    switch (active_big_terminal) {

      case 1 :
        gtk_widget_grab_focus(gui->big_terminal->terminal) ;
        break ;

      case 2 :
        gtk_widget_grab_focus(gui->big_four_terminals->terminal_1->terminal) ;
        break ;
    }
  }
  else {
 
    /** Switch "Big term" off and set focus to editor. **/
 
    gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), 0) ;

    if ( (gui->editor_notebook != NULL) && (gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) > 0) ) {

      GtkWidget *current_textview = gtk_bin_get_child(GTK_BIN(gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->editor_notebook))))) ;

      gtk_widget_grab_focus(current_textview) ;

    }
  }

  if (widget != NULL) {

    if ( ! gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->buttons->big_terminal_button)) &&  user_data != NULL ) {

      toggle_echo = true ;

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->big_terminal_button), TRUE) ;
    }
    else if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->buttons->big_terminal_button)) &&  user_data != NULL ) {

      toggle_echo = true ;

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->big_terminal_button), FALSE) ;
    }

  }

  return ;
}

void toogle_between_big_terminal_features(GtkWidget *widget, gpointer user_data) {

  /** Toggle between
   
      1. a big terminal occupying the full interface.
   
      2. a big terminal divided into  4 terminals.
   
  **/ 

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->main_notebook)) == 0)  {

    toggle_display_big_terminal_and_main_interface(NULL, NULL) ;

    return ;
  }
  else {

    if (gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->main_notebook)) == 1) {

      gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), 2) ;
    }
    else if (gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->main_notebook)) == 2) {
      gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), 1) ;
    }
  }

  return ;

}







void toggle_display_search_and_replace_bar(GtkToggleButton *togglebutton, gpointer user_data) {
  /** Toggle displaying search and replace bar. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  if (gtk_toggle_button_get_active(togglebutton)) {

    gtk_widget_show(gui->search_and_replace->search_and_replace_main_vbox) ;

    gtk_widget_grab_focus(gui->search_and_replace->search_entry) ;

  }
  else {


    gtk_widget_hide(gui->search_and_replace->search_and_replace_main_vbox) ;

    reset_search() ;

    if ( (gui->editor_notebook != NULL) && (gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) > 0) ) {
      GtkWidget *current_textview = gtk_bin_get_child(GTK_BIN(gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->editor_notebook))))) ;

      gtk_widget_grab_focus(current_textview) ;
    }
  }

  return ;

}

void close_search_and_replace_bar(GtkWidget *button, gpointer user_data) {
  /** Close search and replace bar. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  if ( gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) <= 0)  {

    return ;
  }

  destroy_highlight_selection() ;

  if ( searching.source_search_highlight_context != NULL) {

    gtk_source_search_context_set_highlight(searching.source_search_highlight_context, FALSE) ;

  }



  gtk_widget_hide(gui->search_and_replace->search_and_replace_main_vbox) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->search_and_replace_button), FALSE);

  reset_search() ;



  if ( (gui->editor_notebook != NULL) && (gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) > 0) ) {

    GtkWidget *current_textview = gtk_bin_get_child(GTK_BIN(gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->editor_notebook))))) ;

    gtk_widget_grab_focus(current_textview) ;
  }

  return ;

}

void toggle_use_space_instead_of_tabs(GtkWidget *widget, gpointer user_data) {

  /** Toggle between use tabs or spaces callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (settings.use_spaces_as_tabs) {
    settings.use_spaces_as_tabs = FALSE ;
  }
  else {
    settings.use_spaces_as_tabs = TRUE ;
  }


  gtk_image_clear(GTK_IMAGE(gui->buttons->tabs_image)) ;

  gtk_image_clear(GTK_IMAGE(gui->menu->switch_tabs->image)) ;

  switch (settings.use_spaces_as_tabs) {

    case 1 :

      gtk_image_set_from_file(GTK_IMAGE(gui->buttons->tabs_image), PATH_TO_BUTTON_ICON "tabs-off.png") ;

      gtk_image_set_from_file(GTK_IMAGE(gui->menu->switch_tabs->image), PATH_TO_MENU_ICON "tabs-off.png") ;

      break ;

    case 0 :

     gtk_image_set_from_file(GTK_IMAGE(gui->buttons->tabs_image), PATH_TO_BUTTON_ICON "tabs-on.png") ;

     gtk_image_set_from_file(GTK_IMAGE(gui->menu->switch_tabs->image), PATH_TO_MENU_ICON "tabs-on.png") ;

     break ;
  }

  switch_spaces_tabs(gui->editor_notebook, &settings.use_spaces_as_tabs) ;

  return ;

}

void add_new_terminals(GtkWidget *widget, gpointer user_data) {

  /** Add new terminals to sidebar callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  set_new_terminals(gui->terminal_notebook) ;

  return ;
}

void set_syntax_highlight_radio(const char *id) {
  /** Called to set the syntax highlight menu radiobutton according to the current editor content mimetype. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  GList *menu_syntax_items = gtk_container_get_children(GTK_CONTAINER(gui->menu->menu_syntax)) ;


  while (menu_syntax_items->data != NULL) {

    if (g_strcmp0(id, (char *) g_object_get_data(G_OBJECT(menu_syntax_items->data), "lang_id")) == 0 ) {
      gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_syntax_items->data), TRUE);
      break ;
    }

    if (menu_syntax_items->next == NULL) {
      break ;
    }

    menu_syntax_items = menu_syntax_items->next ;

  }


  return ;

}

gboolean set_syntax_highlight(GtkMenuItem *menuitem, GdkEvent  *event, const char *lang_id) {
  /** Radiobuttons syntax highlight setting callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  if ( g_strcmp0(lang_id, "text") != 0 && lang_id != NULL && gui->editor_notebook ) {

    GtkWidget *notebook_child                = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->editor_notebook))) ;

    if (notebook_child) {

      GtkWidget *current_textview            = gtk_bin_get_child(GTK_BIN(notebook_child)) ;
      GtkTextBuffer *current_textview_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(current_textview)) ;

      GtkSourceLanguageManager *source_language_manager = gtk_source_language_manager_get_default();

      GtkSourceLanguage *source_language = gtk_source_language_manager_get_language(source_language_manager, lang_id) ;

      gtk_source_buffer_set_language(GTK_SOURCE_BUFFER(current_textview_buffer), source_language) ;

    }
  }

  return FALSE ;

}

void set_scheme_highlight(GtkMenuItem *menuitem, char *scheme_id) {
  /** Save the selected schame to configuration file. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  if ( scheme_id != NULL && gui->editor_notebook != NULL ) {

    gint number_of_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) ;

    GtkSourceStyleSchemeManager *style_scheme_manager = gtk_source_style_scheme_manager_get_default() ;

    free(settings.scheme_default) ;
    settings.scheme_default = g_strdup_printf("%s", scheme_id) ;



    GKeyFile *conf_file = g_key_file_new() ;

    GError *error = NULL ;

    g_key_file_load_from_file(conf_file, PATH_TO_CONF_FILE, G_KEY_FILE_NONE, &error) ;

    if (error) {

      g_warning("Error open configuration file.\n%s\nCannot store the scheme id %s", error->message, settings.scheme_default) ;
      g_error_free(error)  ;
    }

    g_key_file_set_string(conf_file, "Editor", "scheme", settings.scheme_default);

    error = NULL ;

    g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, &error);

    if (error != NULL) {
      g_warning("Error save to configuration file.\n%s\nCannot store the scheme id %s", error->message, settings.scheme_default) ;
      g_error_free(error)  ;
    }

    g_key_file_unref(conf_file) ;


    int c ;

    for (c = 0 ; c < number_of_pages ; c++) {

      GtkWidget *notebook_child              = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), c) ;
      GtkWidget *current_textview            = gtk_bin_get_child(GTK_BIN(notebook_child)) ;
      GtkTextBuffer *current_textview_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(current_textview)) ;



      GtkSourceStyleScheme *style_scheme = gtk_source_style_scheme_manager_get_scheme(style_scheme_manager, scheme_id)  ;

      gtk_source_buffer_set_style_scheme(GTK_SOURCE_BUFFER(current_textview_buffer), style_scheme) ;

    }
  }

  return ;

}

void launch_application(GtkWidget *widget, const char *cmdline) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GError *error = NULL ;

  GAppInfo *app = g_app_info_create_from_commandline(cmdline, cmdline, G_APP_INFO_CREATE_NONE, &error) ;

  if (error != NULL) {

    gchar *msg_fmt = g_strdup_printf("Cannot launch application: %s\n%s\n", g_path_get_basename(cmdline), error->message) ;

    display_message_dialog("Error application launching !", msg_fmt , GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_free(msg_fmt) ;

    g_error_free(error) ;

    return ;
  }

  g_app_info_launch(app, NULL, NULL , &error) ;

  return ;
}

void launch_readme_html(GtkWidget *widget, gpointer user_data) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  char *readme_realpath = realpath(PATH_TO_README, NULL) ;

  gchar *readme_uri = g_filename_to_uri(readme_realpath, NULL, NULL);

  gtk_show_uri(NULL, readme_uri, GDK_CURRENT_TIME, NULL);

  g_free(readme_uri) ;
  free(readme_realpath) ;

  return ;

}

void launch_license_html(GtkWidget *widget, gpointer user_data) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  char *html_license_realpath = realpath(PATH_TO_GPL_HTML, NULL) ;

  gchar *html_license_uri = g_filename_to_uri(html_license_realpath, NULL, NULL);

  gtk_show_uri(NULL, html_license_uri, GDK_CURRENT_TIME, NULL);

  g_free(html_license_uri) ;
  free(html_license_realpath) ;

  return ;

}

void quit_application(GtkWidget *widget, gpointer user_data) {

  /** Quit application callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (files_not_saved_check() > 0) {
    /** Any file is not saved by exiting the application. **/

    if (! display_unsaved_files_dialog()) {

      gtk_main_quit() ;

      exit(EXIT_SUCCESS) ;
    }

  }
  else {

    gtk_main_quit() ;

    exit(EXIT_SUCCESS) ;

  }


  return ;
}


