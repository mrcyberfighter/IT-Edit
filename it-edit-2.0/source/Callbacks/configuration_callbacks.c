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

#include "configuration_callbacks.h"


void view_buttonbar(GtkWidget *widget, GtkWidget *to_show) {
  /** Show | hidden the buttonbar. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ( gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)) ) {

    gtk_widget_show_all(to_show) ;

  }
  else {

    gtk_widget_hide(to_show) ;
  }

  return ;
}

void toggle_fullscreen(GtkWidget *widget, GtkWidget *window) {
  /** Toggle into fullscreen mode. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ( gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)) )  {

    gtk_window_fullscreen(GTK_WINDOW(window)) ;
  }
  else {

    gtk_window_unfullscreen(GTK_WINDOW(window)) ;
  }

  return ;

}

void change_texture(GtkButton *button, char *user_data) {
  /** Store the selected texture file in the configuration file. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  if (settings.texture_filepath != NULL) {
    g_free(settings.texture_filepath) ;
  }

  if (g_strcmp0(user_data, "folder-image.png") == 0) {
    GtkWidget *file_chooser = g_object_get_data(G_OBJECT(button), "file_chooser") ;
    gtk_widget_set_sensitive(file_chooser, TRUE) ;
    settings.texture_filepath = g_strdup_printf("%s", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser))) ;
  }
  else {
    GtkWidget *file_chooser = g_object_get_data(G_OBJECT(button), "file_chooser") ;
    gtk_widget_set_sensitive(file_chooser, FALSE) ;
    settings.texture_filepath = g_strdup_printf("%s%s", PATH_TO_TEXTURE, user_data) ;
  }

  return ;

}


inline void apply_configuration_change(GKeyFile *conf_file) {

  g_key_file_set_boolean(conf_file, "Editor", "backup",                  settings.backup_file);
  g_key_file_set_value(conf_file,  "Editor", "font",                    settings.editor_font);
  g_key_file_set_value(conf_file,  "Editor", "scheme",                  settings.scheme_default);
  g_key_file_set_boolean(conf_file, "Editor", "display_line_numbers",    settings.display_line_numbers);
  g_key_file_set_boolean(conf_file, "Editor", "display_tabs_chars",      settings.display_tabs_chars);
  g_key_file_set_boolean(conf_file, "Editor", "use_auto_indent",         settings.use_auto_indent);
  g_key_file_set_integer(conf_file, "Editor", "indent_width",            settings.indent_width);
  g_key_file_set_boolean(conf_file, "Editor", "use_spaces_as_tabs",      settings.use_spaces_as_tabs);
  g_key_file_set_boolean(conf_file, "Editor", "rm_trailing_spaces",      settings.rm_trailing_spaces);
  g_key_file_set_integer(conf_file, "Editor", "tabs_width",              settings.tabs_width);


  g_key_file_set_value(conf_file,   "Terminal", "font",                   settings.term_font);
  g_key_file_set_integer(conf_file, "Terminal", "cursor_shape",          settings.cursor_shape);
  g_key_file_set_value(conf_file,   "Terminal", "background",             settings.term_bg) ;
  g_key_file_set_value(conf_file,   "Terminal", "foreground",             settings.term_fg) ;
  g_key_file_set_boolean(conf_file, "Terminal", "use_background_image",  settings.use_bg_image);
  g_key_file_set_boolean(conf_file, "Terminal", "use_texture",           settings.use_texture);
  g_key_file_set_boolean(conf_file, "Terminal", "use_image",             settings.use_image);
  g_key_file_set_value(conf_file,   "Terminal", "texture_filepath",       settings.texture_filepath);
  g_key_file_set_value(conf_file,   "Terminal", "image_filepath",         settings.image_filepath);
  g_key_file_set_value(conf_file,   "Terminal", "user_shell",             settings.user_shell)  ;
  g_key_file_set_value(conf_file,   "Terminal", "start_dir",              settings.start_dir)  ;
  g_key_file_set_value(conf_file,   "Terminal", "regex_word_chars",       settings.regex_word_chars)  ;
  g_key_file_set_integer(conf_file, "Terminal", "cursor_blink",          settings.blink_mode) ;
  g_key_file_set_integer(conf_file, "Terminal", "scrollback_lines",      settings.scrollback_lines) ;
  g_key_file_set_boolean(conf_file, "Terminal", "scroll_on_output",      settings.scroll_on_output) ;
  g_key_file_set_boolean(conf_file, "Terminal", "scroll_on_keystroke",   settings.scroll_on_keystroke) ;
  g_key_file_set_integer(conf_file, "Terminal", "backspace_binding",     settings.backspace_binding) ;
  g_key_file_set_integer(conf_file, "Terminal", "delete_binding",        settings.delete_binding) ;
  g_key_file_set_string(conf_file,  "Terminal", "command",               settings.command) ;


  g_key_file_set_double(conf_file,  "GUI",      "side_terms_factor",     settings.side_terms_factor) ;
  g_key_file_set_boolean(conf_file, "GUI",      "side_terms_on",         settings.side_terms_on) ;
  g_key_file_set_boolean(conf_file, "GUI",      "buttonbar_on",          settings.buttonbar_on) ;
  g_key_file_set_boolean(conf_file, "GUI",      "big_term_on",           settings.big_term_on) ;
  g_key_file_set_boolean(conf_file, "GUI",      "big_term_div",          settings.big_term_div) ;
  g_key_file_set_boolean(conf_file, "GUI",      "fullscreen",            settings.fullscreen) ;

  return ;

}


void write_changes_to_conf_file(void) {
  /** Write all settings to configuration file. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  GKeyFile *conf_file = g_key_file_new() ;

  GError *error = NULL ;

  g_key_file_load_from_file(conf_file, PATH_TO_CONF_FILE, G_KEY_FILE_NONE, &error) ;

  if (error != NULL) {

    char *msg = g_strdup_printf("Configuration file error:\n%s\n%s", g_path_get_basename(PATH_TO_CONF_FILE), error->message) ;

    display_message_dialog("Error configuration !", msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    free(msg) ;

    g_error_free(error) ;

    return ;

  }

  error= NULL ;


  apply_configuration_change(conf_file) ;

  g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, &error);

  if (error != NULL) {

    char *msg = g_strdup_printf("Cannot save conf file:\n%s\n",error->message) ;

    display_message_dialog("Error configuration !", msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    free(msg) ;

    g_error_free(error) ;
  }

  error= NULL ;

  g_key_file_unref(conf_file) ;

  return ;

}

inline void apply_applications_change(GKeyFile *conf_file) {

  g_key_file_set_value(conf_file, "Programming",  "diff",            gui_app.diff)  ;
  g_key_file_set_value(conf_file, "Programming",  "debugger",        gui_app.debugger)  ;
  g_key_file_set_value(conf_file, "Programming",  "python",          gui_app.python)  ;
  g_key_file_set_value(conf_file, "Programming",  "gui_designer",    gui_app.gui_designer)  ;
  g_key_file_set_value(conf_file, "Programming",  "devhelp",         gui_app.devhelp)  ;

  g_key_file_set_value(conf_file, "Utils",        "calculator",      gui_app.calculator)  ;
  g_key_file_set_value(conf_file, "Utils",        "color_picker",    gui_app.color_picker)  ;
  g_key_file_set_value(conf_file, "Utils",        "dictionary",      gui_app.dictionary)  ;
  g_key_file_set_value(conf_file, "Utils",        "file_manager",    gui_app.file_manager)  ;
  g_key_file_set_value(conf_file, "Utils",        "notes",           gui_app.notes)  ;
  g_key_file_set_value(conf_file, "Utils",        "browser",         gui_app.browser)  ;

  //g_key_file_set_string_list(conf_file, "Others",  "others",  (const gchar **) gui_app.others, gui_app.nb_of_others)  ;

}

void write_changes_to_app_file(void) {

  /** Write all settings to the applications configuration file. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  GKeyFile *conf_file = g_key_file_new() ;

  GError *error = NULL ;

  g_key_file_load_from_file(conf_file, PATH_TO_APP_FILE, G_KEY_FILE_NONE, &error) ;

  if (error != NULL) {

    char *msg = g_strdup_printf("Configuration file error:\n%s\n%s", g_path_get_basename(PATH_TO_APP_FILE), error->message) ;

    display_message_dialog("Error configuration !", msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    free(msg) ;

    g_error_free(error) ;

    return ;

  }


  apply_applications_change(conf_file) ;

  g_key_file_save_to_file(conf_file, PATH_TO_APP_FILE, &error);

  if (error != NULL) {

    fprintf(stderr,"Cannot save conf file:\n%s\n",error->message) ;

    g_error_free(error) ;
  }

  g_key_file_unref(conf_file) ;

  return ;



}

void remove_selected_items_from_files_manager(GtkWidget *widget, GtkWidget *files_manager_vbox) {
  /** Remove all selected items from the "File Handler" functionnality configuration file,
    * We store all not selected (to not remove) items in an GSlist using as a file content buffer
    * to overwrite the file content.
    *********************************************************************************************/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  /** Get the checkbuttons which contains the data. **/
  GList *check_buttons_list = gtk_container_get_children(GTK_CONTAINER(files_manager_vbox)) ;

  FILE *fp = fopen(PATH_TO_LINKS_FILE, "w");

  while (check_buttons_list != NULL) {

    if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_buttons_list->data)) ) {
      /** The checkbutton is selected so we remove it from the GSList and freeing the data. **/

      files_manager_list=g_slist_remove(files_manager_list, g_object_get_data(G_OBJECT(check_buttons_list->data), "item") ) ;

      Files_Manager *file_item = (Files_Manager *) g_object_get_data(G_OBJECT(check_buttons_list->data), "item") ;

      /** Freeing the file_item members. **/
      free(file_item->label) ;
      free(file_item->uri)   ;

      /** Freeing the structure. **/
      free(file_item) ;

      /** Update the GUI. **/
      gtk_widget_destroy(GTK_WIDGET(check_buttons_list->data));
    }
    else {

      /** Append data to GSList and write it to file. **/
      files_manager_list = g_slist_append(files_manager_list, g_object_get_data(G_OBJECT(check_buttons_list->data), "item") ) ;

      Files_Manager *file_item = (Files_Manager *) g_object_get_data(G_OBJECT(check_buttons_list->data), "item") ;

      /** Write the data to file. **/
      fputs(file_item->label, fp) ;
      fputc('\n', fp) ;
      fputs(file_item->uri, fp) ;
      fputc('\n', fp) ;

    }

    if (check_buttons_list->next == NULL) {
      break ;
    }
    else {
      check_buttons_list = check_buttons_list->next ;
    }

  }

  fclose(fp) ;

  return ;

}

