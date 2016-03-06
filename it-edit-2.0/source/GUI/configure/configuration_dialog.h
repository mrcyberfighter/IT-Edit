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

#ifndef IT_EDIT_CONFIGURATION_DIALOG_HH
#define IT_EDIT_CONFIGURATION_DIALOG_HH

#include "../../Headers/global_vars.h"

#include "../setup/setup_gui.h"

#include "../configure/configure_gui_elements.h"

#include "../../Callbacks/configuration_callbacks.h"

#include "../../Resizer/Resizer.h"

extern void add_a_new_item_to_files_manager(GtkWidget *widget, GtkWidget *files_manager_vbox) ;

extern void display_configuration_dialog(GtkWidget *widget, gpointer user_data) ;

#endif