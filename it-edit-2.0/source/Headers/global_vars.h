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

#ifndef IT_EDIT_GLOBAL_VARIABLE_HH
#define IT_EDIT_GLOBAL_VARIABLE_HH

#include "./includes.h"

#include "./defines.h"

/** Program configuration settings. **/
#include "./Structures/setting_structure.h"

/** Editor specific structures. **/
#include "./Structures/editor_structures.h"


/** GUI structures **/
#include "./Structures/GUI_structures.h"

/** Global variables: **/
extern GUI *gui         ;

/** Programm settings: **/
extern Settings settings ;

/** Files editors: differents notebook pages. **/
extern Current_Editor current_editor ;

/** Keep track files selector current folder: **/
extern gchar *open_file_dirname ;

/** Search functionnalities: **/
extern Searching        searching ;
extern Search_Settings *search_settings ;

/** Search history: **/
extern GList *search_history ;
extern gboolean search_history_start ;

/** "Files Handler" functionnalities write file tmp buffer single-linked list: **/
extern GSList *files_manager_list ;

/** stored GUI app for launching. **/
extern Gui_App gui_app ;

/** At exit unsaved files list. **/
extern GSList *unsaved_files ;

#endif