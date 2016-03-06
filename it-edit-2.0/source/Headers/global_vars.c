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

#include "./includes.h"

#include "./defines.h"

/** Program configuration settings. **/
#include "./Structures/setting_structure.h"

/** Editor specific structures. **/
#include "./Structures/editor_structures.h"


/** GUI structures **/
#include "./Structures/GUI_structures.h"

/** Global variables: **/
GUI *gui         ;

/** Programm settings: **/
Settings settings ;

/** Files editors: differents notebook pages. **/
Current_Editor current_editor ;

/** Keep track files selector current folder: **/
gchar *open_file_dirname ;

/** Search functionnalities: **/
Searching        searching ;
Search_Settings *search_settings ;

/** Search history: **/
GList *search_history ;
gboolean search_history_start ;

/** "Files Handler" functionnalities write file tmp buffer single-linked list: **/
GSList *files_manager_list ;

/** stored GUI app for launching. **/
Gui_App gui_app ;

/** At exit unsaved files list. **/
GSList *unsaved_files ;

