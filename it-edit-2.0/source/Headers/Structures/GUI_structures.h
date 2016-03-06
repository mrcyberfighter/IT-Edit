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

#ifndef IT_EDIT_GUI_STRUCTURES_HH 
#define IT_EDIT_GUI_STRUCTURES_HH 

#include "../includes.h"

typedef struct {

    /** Structure for holding one file open in the editor **/

    GtkWidget *scrolled_window ;

    GtkWidget *textview ;

    GtkSourceBuffer *buffer ;

    GStatBuf file_info ;
  
    #ifdef RELOADING_FUNC
  
    bool must_reload ;

    gboolean timeout_return ;
  
    #endif
  
} File_Editor ;

typedef struct {

   /** Structure for one terminal width
     * -) Terminal
     * -) Scrollbar for the terminal.
     * -) hbox container.
     ***********************************/

   GtkWidget *terminal ;

   GtkWidget *terminal_scrollbar  ;

   GtkWidget *terminal_hbox ;

} Terminal ;

typedef struct {

   /** Hard coded terminals. **/

   Terminal *terminal_1 ;

   Terminal *terminal_2 ;

   GtkWidget *terminals_vertical_paned ;

} Terminals ;

typedef struct {

  Terminal *terminal_1 ;

  Terminal *terminal_2 ;

  Terminal *terminal_3 ;

  Terminal *terminal_4 ;

  GtkWidget *vertical_paned_up   ;
  GtkWidget *vertical_paned_down ;

  GtkWidget *horizontal_paned ;

} FTerms ;


typedef struct {

    /** Structure for one menu item. **/

    GtkWidget *image ;

    GtkWidget *label ;

    GtkWidget *accel_label ;

    GtkWidget *menuitem ;

    GtkWidget *hbox ;

} MenuItem ;

typedef struct {

  /** Main menu structure **/

  GtkWidget *menu_bar  ;

  GtkAccelGroup *menu_files_accel_group ;

  GtkAccelGroup *menu_edition_accel_group ;

  GtkAccelGroup *menu_action_accel_group ;

  GtkAccelGroup *menu_view_accel_group ;

  GSList *syntax_radiogroup ;

  MenuItem *files_button ;

  MenuItem *edition_button ;

  MenuItem *settings_button ;

  MenuItem *actions_button  ;

  MenuItem *about_button  ;

  GtkWidget *main_menu  ;

  GtkWidget *menu_files  ;

  GtkWidget *menu_recent ;

  GtkWidget *menu_edition ;

  GtkWidget *menu_settings ;

  GtkWidget *menu_syntax ;

  GtkWidget *menu_scheme ;

  GtkWidget *menu_action ;

  GtkWidget *app_main_menu ;

  GtkWidget *app_programming_menu ;

  GtkWidget *app_utils_menu ;

  GtkWidget *app_others_menu ;

  GtkWidget *menu_view ;

  GtkWidget *menu_about ;





  MenuItem *new_file     ;

  GtkWidget *separator_01 ;

  MenuItem *open_file    ;

  MenuItem *recent_files ;

  GtkWidget *separator_02 ;

  MenuItem *save_file    ;

  MenuItem *save_as_file ;

  MenuItem *save_all     ;

  GtkWidget *separator_03 ;

  MenuItem *reload_page  ;

  GtkWidget *separator_04 ;

  MenuItem *file_info    ;

  GtkWidget *separator_05 ;

  MenuItem *quit         ;




  MenuItem *undo         ;

  MenuItem *redo         ;

  GtkWidget *separator_06 ;

  MenuItem *find         ;

  MenuItem *find_all     ;

  MenuItem *find_next    ;

  MenuItem *find_prev    ;

  MenuItem *replace      ;

  MenuItem *replace_all  ;

  MenuItem *go_to_line   ;

  GtkWidget *separator_07 ;

  MenuItem *cut          ;

  MenuItem *copy         ;

  MenuItem *paste        ;

  MenuItem *duplicate    ;

  GtkWidget *separator_08 ;

  MenuItem *switch_tabs ;







  MenuItem *exec_cmd ;

  GtkWidget *separator_09 ;

  MenuItem *switch_big_terms ;

  MenuItem *add_term ;

  GtkWidget *separator_10 ;

  MenuItem *files_handler ;

  MenuItem *app_launcher  ;




  MenuItem *app_menubutton ;

  MenuItem *app_programming_menuitem ;

  MenuItem *app_programming_diff ;

  MenuItem *app_programming_debugger ;

  MenuItem *app_programming_python ;

  MenuItem *app_programming_gui_designer ;

  MenuItem *app_programming_devhelp ;

  MenuItem *app_utils_menuitem ;

  MenuItem *app_utils_calculator ;

  MenuItem *app_utils_color_picker ;

  MenuItem *app_utils_dictionary ;

  MenuItem *app_utils_file_manager ;

  MenuItem *app_utils_notes ;

  MenuItem *app_utils_browser ;

  MenuItem *app_others_menuitem ;



  MenuItem *view_menubutton ;

  MenuItem *big_term ;

  MenuItem *show_term ;

  GtkWidget *separator_11 ;

  MenuItem *display_buttonbar  ;

  MenuItem *toggle_fullscreen  ;



  MenuItem *syntax_highlight ;

  MenuItem *syntax_scheme ;

  MenuItem *program_setting  ;



  MenuItem *readme ;

  MenuItem *license ;

  MenuItem *about ;

} Menu ;

typedef struct {

    /** Buttons structure **/

    GtkWidget *open_file_button ;

    GtkWidget *open_file_image ;

    GtkWidget *save_file_as_button ;

    GtkWidget *save_file_as_image ;

    GtkWidget *save_file_button ;

    GtkWidget *save_file_image ;

    GtkWidget *save_file_all_button ;

    GtkWidget *save_file_all_image ;

   
    GtkWidget *tabs_button ;

    GtkWidget *tabs_image ;

    GtkWidget *cut_button ;

    GtkWidget *cut_image ;

    GtkWidget *copy_button ;

    GtkWidget *copy_image ;

    GtkWidget *paste_button ;

    GtkWidget *paste_image ;

    GtkWidget *duplicate_button ;

    GtkWidget *duplicate_image ;
   
   
    GtkWidget *go_to_line_button ;

    GtkWidget *go_to_line_image  ;
  
    GtkWidget *search_and_replace_button ;

    GtkWidget *search_and_replace_image  ;
   
   
    GtkWidget *exec_button ;

    GtkWidget *exec_image  ;

    GtkWidget *big_terminal_button ;

    GtkWidget *big_terminal_image ;

    GtkWidget *terminals_show_button ;

    GtkWidget *terminals_show_image ;






} Buttons ;

typedef struct {

    /** Editor bottom info bar. **/

    GtkWidget *info_bottom_bar       ;

    GtkWidget *current_row_col       ;

    GtkWidget *padding_left          ;

    GtkWidget *filename_label        ;

    GtkWidget *padding_right         ;

    GtkWidget *total_rows_cols       ;

} BottomBar ;

typedef struct {

  /** Main container **/
  GtkWidget *search_and_replace_main_vbox   ;

  /** search and replace main container **/
  GtkWidget *search_and_replace_main_hbox   ;

  /** Search and replace containers **/

  GtkWidget *search_and_replace_label_vbox  ;

  GtkWidget *search_and_replace_entry_vbox  ;

  GtkWidget *search_and_replace_button_vbox_1 ;

  GtkWidget *search_and_replace_button_vbox_2 ;



  GtkWidget *search_button   ;

  GtkWidget *search_image    ;


  GtkWidget *replace_button  ;

  GtkWidget *replace_image   ;


  GtkWidget *search_entry   ;

  GtkWidget *replace_entry  ;


  GtkWidget *search_next_button ;

  GtkWidget *search_next_image  ;

  GtkWidget *search_prev_button ;

  GtkWidget *search_prev_image  ;


  GtkWidget *replace_one_button ;

  GtkWidget *replace_all_button ;


  /** Search settings **/
  GtkWidget *search_settings_main_hbox ;

  GtkWidget *search_settings_button_hbox ;

  GtkWidget *search_settings_button ;

  GtkWidget *search_settings_image ;

  GtkWidget *search_settings_label ;

  GtkWidget *search_settings_hbox  ;

  GtkWidget *search_settings_combobox ;

  GtkWidget *search_settings_padding_1     ;

  GtkWidget *search_settings_case_checkbox ;

  GtkWidget *search_settings_wrap_checkbox ;

  GtkWidget *search_settings_padding_2     ;

  GtkWidget *search_settings_match_label   ;

  GtkWidget *search_settings_close_button  ;

  GtkWidget *search_settings_close_image   ;


} Search_And_Replace ;

typedef struct {

  /** Go to line functionnality. **/

  GtkWidget *go_to_line_dialog  ;

  GtkWidget *go_to_line_content ;

  GtkWidget *go_to_line_vbox    ;

  GtkWidget *go_to_line_label   ;

  GtkWidget *go_to_line_entry   ;

  GtkWidget *go_to_line_apply   ;

  GtkWidget *go_to_line_close   ;

} Go_To_Line_Dialog ;


typedef struct {

    /** Main GUI structure **/

    GtkWidget *main_window ; /** Main window **/

    GtkWidget *main_vbox ;   /** Main container **/

    GtkWidget *main_hbox ;   /** editor + terminals container **/



    Menu *menu ;



    Buttons *buttons ;

    GtkAccelGroup *buttons_accel_group ;

    GtkWidget *buttonbox_hbox      ;

    GtkWidget *left_buttonbox      ;

    GtkWidget *padding_buttonbox_1 ;

    GtkWidget *edition_buttonbox   ;

    GtkWidget *padding_buttonbox_2 ;

    GtkWidget *action_buttonbox    ;

    GtkWidget *padding_buttonbox_3 ;

    GtkWidget *right_buttonbox     ;


    Go_To_Line_Dialog *go_to_line_dialog   ;
   

    Terminal *big_terminal    ;  /** Big terminal. **/

    FTerms   *big_four_terminals ;

    GtkWidget *middle_paned      ;

    GtkWidget *editor_vbox       ;

    Search_And_Replace *search_and_replace ;

    BottomBar *bottom_bar        ;


    GtkWidget *editor_notebook  ;

    GtkWidget *terminal_notebook ;

    GtkWidget *main_notebook ;

} GUI ;

#endif
