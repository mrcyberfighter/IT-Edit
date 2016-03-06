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

#ifndef IT_EDIT_SETTINGS_STRUCTURES_HH 
#define IT_EDIT_SETTINGS_STRUCTURES_HH 

typedef struct {

 /** Editor settings: **/

 gchar *scheme_default ;

 gboolean backup_file  ;

 gchar *editor_font    ;

 gboolean display_line_numbers ;

 gboolean display_tabs_chars   ;

 gboolean use_auto_indent ;

 gint indent_width ;

 gboolean use_spaces_as_tabs ;

 gint tabs_width    ;

 gboolean rm_trailing_spaces ;


 /** Terminal settings: **/

 gchar *term_font      ;

 gchar  *user_shell    ;

 gchar  *start_dir     ;

 gint cursor_shape     ;

 gint blink_mode       ;

 gchar *term_bg        ;

 gchar *term_fg        ;

 gboolean use_bg_image ;

 gboolean use_texture  ;

 gchar *texture_filepath ;

 gchar *texture_image ;

 gboolean use_image ;

 gchar *image_filepath ;

 gboolean scroll_background ; // Interesting for bg image if right image height !

 gint  scrollback_lines ; // -1 unlimited.

 gboolean scroll_on_output ; // disable per default.

 gchar *regex_word_chars ;

 gboolean scroll_on_keystroke ;

 gint backspace_binding ;

 gint delete_binding ;

 gchar *emulation ;

 gchar *encoding  ;

 gchar *command ;


 /** GUI settings: **/

 gdouble  side_terms_factor ;

 gboolean side_terms_on   ;

 gboolean big_term_on   ;

 gboolean big_term_div ;

 gboolean buttonbar_on ;

 gboolean fullscreen  ;



} Settings ;

typedef struct {

  /** Programming **/

  gchar *diff ;

  gchar *debugger ;

  gchar *python ;

  gchar *perl ;

  gchar *gui_designer ;

  gchar *devhelp ;

  /** Utils  **/
  gchar *calculator ;

  gchar *color_picker ;

  gchar *dictionary ;

  gchar *file_manager ;

  gchar *notes ;

  gchar *browser ;

  gchar *screenshot ;

  gchar *record_desktop ;

  gchar **others ;

  gsize nb_of_others ;

} Gui_App ;

typedef struct {

  char *label ;  /** "Files Handler" functionnality button label. **/

  char *uri   ;  /** Associated file URI. **/

} Files_Manager ;

#endif
