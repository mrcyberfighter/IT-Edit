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

#ifndef IT_EDIT_CONFIGURATION_HH
#define IT_EDIT_CONFIGURATION_HH

#include "../Headers/global_vars.h"

#include "../Headers/defines.h"

#include "../GUI/configure/configuration_dialog.h"

#include "../GUI/dialogs/message_dialog.h"

extern char *have_app_application(const char *default_list[]) ;

extern void set_default_settings_app_conf(void) ;

extern void set_default_settings_main_conf(void) ;

extern void get_main_configuration(void) ;

extern void get_app_configuration(void) ;

#endif