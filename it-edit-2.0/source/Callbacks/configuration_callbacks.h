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

#ifndef IT_EDIT_CONFIGURATION_CALLBACKS_HH
#define IT_EDIT_CONFIGURATION_CALLBACKS_HH

#include "../Headers/global_vars.h"

#include "../Callbacks/configuration_callbacks.h"

#include "../GUI/dialogs/message_dialog.h"

extern void view_buttonbar(GtkWidget *widget, GtkWidget *to_show) ;

extern void toggle_fullscreen(GtkWidget *widget, GtkWidget *window) ;

extern void switch_spaces_tabs(GtkWidget *widget, gboolean *switcher) ;

extern void change_texture(GtkButton *button, char *user_data) ;

extern void apply_configuration_change(GKeyFile *conf_file) ;

extern inline void apply_applications_change(GKeyFile *conf_file) ;

extern void write_changes_to_conf_file(void) ;

extern void write_changes_to_app_file(void) ;

extern void remove_selected_items_from_files_manager(GtkWidget *widget, GtkWidget *files_manager_vbox) ;

#endif

