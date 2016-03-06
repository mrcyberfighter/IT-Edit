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

#ifndef IT_EDIT_SETUP_GUI_HH
#define IT_EDIT_SETUP_GUI_HH

#include "../../Headers/global_vars.h"


#include "../dialogs/dialogs.h"


#include "../../GUI/dialogs/dialogs.h"


#include "../configure/configuration_dialog.h"

#include "../../Callbacks/files_callbacks.h"

#include "../../Callbacks/edition_callbacks.h"

#include "../../Callbacks/search_settings_callbacks.h"

#include "../../Callbacks/terminals_callbacks.h"

#include "../../Callbacks/gui_callbacks.h"

#include "../../Callbacks/configuration_callbacks.h"




extern void setup_search_and_replace_bar(Search_And_Replace *search_and_replace) ;

extern void setup_menu_item(MenuItem *menuitem, const char *label, const char *accel_label, const char *image, GtkAccelGroup *menu_files_accel_group,  GdkModifierType accel_modifier,  guint accel_key, int8_t type) ;

extern void initialize_menu(Menu *menu) ;

extern void initialize_button_box(Buttons *buttons) ;

extern void initialize_terminal(Terminal *terminal) ;

extern void setup_terminal(GtkWidget *vteterminal) ;

#endif