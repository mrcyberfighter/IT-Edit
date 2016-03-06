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

#ifndef IT_EDIT_FILES_CALLBACKS_HH
#define IT_EDIT_FILES_CALLBACKS_HH

#include "../Headers/global_vars.h"

#include "./gui_callbacks.h"

#include "../Editor/editor.h"

#include "../GUI/dialogs/message_dialog.h"

#include "editor_callbacks.h"

extern void process_selected_file(gpointer filepath, gpointer user_data) ;

extern void open_file(GtkButton *button) ;

extern void open_recent(GtkRecentChooser *chooser, gpointer user_data) ;

extern void save_as_file(GtkButton *button) ;

extern void save_file(GtkButton *button) ;

extern void save_all_file(GtkWidget *button, gpointer user_data) ;

extern void new_file(GtkWidget *button, gpointer user_data) ;

extern void reloading_file(GtkWidget *widget, gpointer user_data) ;

extern guint files_not_saved_check(void) ;

#endif

