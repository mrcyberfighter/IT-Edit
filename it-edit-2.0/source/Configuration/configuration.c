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

#include "configuration.h"

char *have_app_application(const char *default_list[]) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gchar *path_env_variable = (gchar *) g_environ_getenv(g_get_environ(), "PATH")  ;

  int c = 0 ;

  while ( default_list[c] != NULL) {

    char *dir = NULL ;

    while ((dir=strtok(path_env_variable, ":")) != NULL) {

      gchar *filepath = g_strdup_printf("%s/%s",dir,default_list[c]) ;

      if (g_file_test(filepath, G_FILE_TEST_EXISTS)) {

        return filepath ;
      }

      g_free(filepath) ;

      path_env_variable = NULL ;

    }

    ++c ;

  }

  return g_strdup_printf("%s","") ;

}


void set_default_settings_app_conf(void) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  const char *default_app_diff[] = {"kompare", "meld", "fldiff", "diffuse", NULL } ;

  const char *default_app_debugger[] = { "ddd", "xxdbg", NULL } ;

  const char *default_app_python[] = {"pycrust", "idle-python2.7", "dreampie", "idle-python3.4", NULL } ;

  const char *default_app_gui_generator[] = {"glade", "wxglade", NULL } ;

  const char *default_app_devhelp[] = {"devhelp", NULL} ;

  const char *default_app_dict[] = {"goldendict", "stardict", "opendict", "babiloo", NULL } ;

  const char *default_app_color_picker[] = {"gcolor2", "kcolorchooser", "gpick", NULL} ;

  const char *default_app_calculator[] = { "galculator", "kcalc", "speedcrunch", NULL } ;

  const char *default_app_file_manager[] = { "nautilus", "dolphin", "thunar", "xfe", "pcmanfm", NULL } ;

  const char *default_app_notes[] = { "keepnote", "bijiben", "gnotes" , "xpad", "kjots" , "tuxcards", "rhinote", NULL } ;  // pkg-search note

  const char *default_app_browser[] = {"firefox", "chromium-browser", "konqueror", NULL } ;

  gui_app.diff = have_app_application(default_app_diff) ;

  gui_app.debugger = have_app_application(default_app_debugger) ;

  gui_app.python = have_app_application(default_app_python) ;

  gui_app.gui_designer = have_app_application(default_app_gui_generator) ;

  gui_app.devhelp = have_app_application(default_app_devhelp) ;

  gui_app.calculator = have_app_application(default_app_calculator) ;

  gui_app.color_picker = have_app_application(default_app_color_picker) ;

  gui_app.dictionary = have_app_application(default_app_dict) ;

  gui_app.file_manager = have_app_application(default_app_file_manager) ;

  gui_app.notes = have_app_application(default_app_notes) ;

  gui_app.browser = have_app_application(default_app_browser) ;

  gui_app.others = NULL ;

  gui_app.nb_of_others = 0 ;

  //write_changes_to_app_file() ;

  return ;

}

void set_default_settings_main_conf(void) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Editor settings **/
  settings.scheme_default       = "kate" ;
  settings.editor_font          = g_strdup_printf("%s", "Monospace 10") ;
  settings.backup_file          = TRUE ;
  settings.display_line_numbers = TRUE ;
  settings.display_tabs_chars   = TRUE ;
  settings.use_spaces_as_tabs   = TRUE ;
  settings.tabs_width           = 2    ;
  settings.use_auto_indent      = TRUE ;
  settings.indent_width         = 2    ;
  settings.rm_trailing_spaces   = TRUE ;

  /** Terminal settings **/
  settings.term_font            = g_strdup_printf("%s","Monospace 10") ;
  settings.term_bg              = g_strdup_printf("%s","#000000") ;
  settings.term_fg              = g_strdup_printf("%s","#FFFFFF") ;
  settings.texture_filepath     = g_strdup_printf("%s", g_get_user_special_dir(G_USER_DIRECTORY_PICTURES)) ;
  settings.image_filepath       = g_strdup_printf("%s", g_get_user_special_dir(G_USER_DIRECTORY_PICTURES)) ;
  settings.user_shell           = g_strdup_printf("%s", vte_get_user_shell()) ;
  settings.start_dir            = g_strdup_printf("%s", (gchar *) g_get_home_dir()) ;
  settings.regex_word_chars     = g_strdup_printf("%s", "-A-Za-z0-9,./?%&#:_=+@~")  ;
  settings.cursor_shape         =  0 ;
  settings.blink_mode           =  0 ;
  settings.scrollback_lines     = -1 ;
  settings.scroll_on_output     = TRUE ;
  settings.use_bg_image         = FALSE ;
  settings.use_texture          = FALSE ;
  settings.use_image            = FALSE ;
  settings.scroll_background    = FALSE ;
  settings.scroll_on_keystroke  = FALSE ;
  settings.backspace_binding    = 0     ;
  settings.delete_binding       = 0     ;
  settings.command              = g_strdup_printf("%s", "") ;


  /** Application settings **/
  settings.side_terms_factor    = 0.385 ;
  settings.side_terms_on        = FALSE ;
  settings.big_term_on          = FALSE ;
  settings.big_term_div         = FALSE ;
  settings.buttonbar_on         = TRUE  ;
  settings.fullscreen           = FALSE ;

  GKeyFile *conf_file = g_key_file_new() ;

  GError *error = NULL ;

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

void get_main_configuration(void) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Programm configuration file. **/
  GKeyFile *conf_file = g_key_file_new() ;
  GError *err = NULL ;
  g_key_file_load_from_file(conf_file, PATH_TO_CONF_FILE, G_KEY_FILE_NONE, &err) ;

  if (err != NULL) {
    set_default_settings_main_conf() ;
    g_error_free(err)  ;
    return ;
  }





  /** Read the configuration file:  getting strings values: **/
  settings.scheme_default   = g_key_file_get_string(conf_file, "Editor",  "scheme",            NULL)  ;
  settings.editor_font      = g_key_file_get_string(conf_file, "Editor",  "font",              NULL)  ;
  settings.term_font        = g_key_file_get_string(conf_file, "Terminal", "font",             NULL)  ;
  settings.term_bg          = g_key_file_get_string(conf_file, "Terminal", "background",       NULL)  ;
  settings.term_fg          = g_key_file_get_string(conf_file, "Terminal", "foreground",       NULL)  ;
  settings.texture_filepath = g_key_file_get_string(conf_file, "Terminal", "texture_filepath", NULL)  ;
  settings.image_filepath   = g_key_file_get_string(conf_file, "Terminal", "image_filepath",   NULL)  ;
  settings.user_shell       = g_key_file_get_string(conf_file, "Terminal", "user_shell",       NULL)  ;
  settings.start_dir        = g_key_file_get_string(conf_file, "Terminal", "start_dir",        NULL)  ;
  settings.regex_word_chars = g_key_file_get_string(conf_file, "Terminal", "regex_word_chars", NULL)  ;
  settings.command          = g_key_file_get_string(conf_file, "Terminal", "command",          NULL)  ;
  //settings.emulation        = g_key_file_get_string(conf_file, "Terminal", "emulation",        NULL)  ;
  //settings.encoding         = g_key_file_get_string(conf_file, "Terminal", "encoding",         NULL)  ;

  /** Read the configuration file: getting boolean or integer values. **/
  settings.backup_file           = g_key_file_get_boolean(conf_file, "Editor",   "backup",               NULL) ;
  settings.display_line_numbers  = g_key_file_get_boolean(conf_file, "Editor",   "display_line_numbers", NULL) ;
  settings.display_tabs_chars    = g_key_file_get_boolean(conf_file, "Editor",   "display_tabs_chars",   NULL) ;
  settings.use_spaces_as_tabs    = g_key_file_get_boolean(conf_file, "Editor",   "use_spaces_as_tabs",   NULL) ;
  settings.tabs_width            = g_key_file_get_integer(conf_file, "Editor",   "tabs_width",           NULL) ;
  settings.use_auto_indent       = g_key_file_get_boolean(conf_file, "Editor",   "use_auto_indent",      NULL) ;
  settings.rm_trailing_spaces    = g_key_file_get_boolean(conf_file, "Editor",   "rm_trailing_spaces",   NULL) ;
  settings.indent_width          = g_key_file_get_integer(conf_file, "Editor",   "indent_width",         NULL) ;

  settings.cursor_shape          = g_key_file_get_integer(conf_file, "Terminal", "cursor_shape",         NULL) ;
  settings.blink_mode            = g_key_file_get_integer(conf_file, "Terminal", "cursor_blink",         NULL) ;
  settings.scrollback_lines      = g_key_file_get_integer(conf_file, "Terminal", "scrollback_lines",     NULL) ;
  settings.backspace_binding     = g_key_file_get_integer(conf_file, "Terminal", "backspace_binding",    NULL) ;
  settings.delete_binding        = g_key_file_get_integer(conf_file, "Terminal", "delete_binding",       NULL) ;
  settings.scroll_on_output      = g_key_file_get_boolean(conf_file, "Terminal", "scroll_on_output",     NULL) ;
  settings.use_bg_image          = g_key_file_get_boolean(conf_file, "Terminal", "use_background_image", NULL) ;
  settings.use_texture           = g_key_file_get_boolean(conf_file, "Terminal", "use_texture",          NULL) ;
  settings.use_image             = g_key_file_get_boolean(conf_file, "Terminal", "use_image",            NULL) ;
  settings.scroll_background     = g_key_file_get_boolean(conf_file, "Terminal", "scroll_bg",            NULL) ;
  settings.scroll_on_keystroke   = g_key_file_get_boolean(conf_file, "Terminal", "scroll_on_keystroke",  NULL) ;

  settings.side_terms_factor     = g_key_file_get_double(conf_file,  "GUI",      "side_terms_factor",    NULL) ;
  settings.side_terms_on         = g_key_file_get_boolean(conf_file, "GUI",      "side_terms_on",        NULL) ;
  settings.buttonbar_on          = g_key_file_get_boolean(conf_file, "GUI",      "buttonbar_on",         NULL) ;
  settings.big_term_on           = g_key_file_get_boolean(conf_file, "GUI",      "big_term_on",          NULL) ;
  settings.big_term_div          = g_key_file_get_boolean(conf_file, "GUI",      "big_term_div",         NULL) ;
  settings.fullscreen            = g_key_file_get_boolean(conf_file, "GUI",      "fullscreen",           NULL) ;


  g_key_file_unref(conf_file) ;

  return ;
}

void get_app_configuration(void) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Programm configuration file. **/
  GKeyFile *conf_file = g_key_file_new() ;
  GError *err = NULL ;

  g_key_file_load_from_file(conf_file, PATH_TO_APP_FILE, G_KEY_FILE_NONE, &err) ;

  if (err != NULL) {
 
    /** Application configuration file not found so we generate it. **/
 
    g_error_free(err)  ;
    set_default_settings_app_conf() ;

    conf_file = g_key_file_new() ;

    int fd = g_creat(PATH_TO_APP_FILE, 00777) ;

    err = NULL ;

    g_close(fd, NULL) ;

    apply_applications_change(conf_file) ;

    g_key_file_set_string_list(conf_file, "Others",  "others",  (const gchar **) gui_app.others, gui_app.nb_of_others)  ;

    err = NULL ;

    g_key_file_save_to_file(conf_file, PATH_TO_APP_FILE, &err);


    if (err != NULL) {

      g_warning("Error generating apps conf file:\n%s\n", err->message) ;

    }

    g_key_file_unref(conf_file) ;

    return ;
 
  }



  /** Read the configuration file:  getting strings values: **/
  gui_app.diff              = g_key_file_get_string(conf_file, "Programming",  "diff",            NULL)  ;
  gui_app.debugger          = g_key_file_get_string(conf_file, "Programming",  "debugger",        NULL)  ;
  gui_app.python            = g_key_file_get_string(conf_file, "Programming",  "python",          NULL)  ;
  gui_app.gui_designer      = g_key_file_get_string(conf_file, "Programming",  "gui_designer",    NULL)  ;
  gui_app.devhelp           = g_key_file_get_string(conf_file, "Programming",  "devhelp",         NULL)  ;

  gui_app.calculator        = g_key_file_get_string(conf_file, "Utils",        "calculator",      NULL)  ;
  gui_app.color_picker      = g_key_file_get_string(conf_file, "Utils",        "color_picker",    NULL)  ;
  gui_app.dictionary        = g_key_file_get_string(conf_file, "Utils",        "dictionary",      NULL)  ;
  gui_app.file_manager      = g_key_file_get_string(conf_file, "Utils",        "file_manager",    NULL)  ;
  gui_app.notes             = g_key_file_get_string(conf_file, "Utils",        "notes",           NULL)  ;
  gui_app.browser           = g_key_file_get_string(conf_file, "Utils",        "browser",         NULL)  ;

  gui_app.others            = g_key_file_get_string_list(conf_file, "Others",  "others",  &gui_app.nb_of_others, NULL)  ;

  g_key_file_unref(conf_file) ;

  return ;


}
