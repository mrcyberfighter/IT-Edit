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

#ifndef IT_EDIT_EDITOR_HH
#define IT_EDIT_EDITOR_HH

#include "../GUI/configure/configure_gui_elements.h"

#include "../GUI/setup/setup_gui.h"

#include "../GUI/dialogs/message_dialog.h"

#include "../Callbacks/gui_callbacks.h"

#include "../Callbacks/editor_callbacks.h"

extern void add_file_to_editor(GtkWidget *editor_notebook, File_Editor *file_editor,const char *filepath, bool start) ;

extern void reload_file(GtkSourceBuffer *buffer, const char *filepath) ;

extern void set_new_terminals(GtkWidget *terminals_notebook) ;

#endif