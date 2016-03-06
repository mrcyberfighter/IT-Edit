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

#ifndef SEARCH_SETTINGS_CALLBACKS_HH
#define SEARCH_SETTINGS_CALLBACKS_HH

#include "../Headers/global_vars.h"

#include "./highlight_selection_callbacks.h"

extern void set_search_settings_default(Search_Settings *search_settings) ;

extern void remove_searching_tag(void) ;

extern void set_search_mode(GtkComboBox *widget, gpointer user_data) ;

extern void set_case_sensitive(GtkToggleButton *togglebutton, gpointer user_data) ;

extern void set_wrap_around(GtkToggleButton *togglebutton, gpointer user_data) ;

extern void reset_search(void) ;

extern gboolean search_history_callback(GtkWidget *widget,  GdkEventKey  *event, gpointer   user_data) ;

extern void get_iter_offset(void) ;

extern void get_iter_at_offset(void) ;

extern void activate_search_accelator(GtkWidget *widget, gpointer user_data) ;

extern void search(GtkButton *button, gpointer user_data) ;

extern void search_next(GtkWidget *button, gpointer user_data) ;

extern void search_previous(GtkWidget *button, gpointer user_data) ;

extern void replace_one_occurence(GtkButton *button, gpointer user_data) ;

extern void replace_all_occurence(GtkButton button, gpointer user_data) ;

#endif