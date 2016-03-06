/** ***********************************************************************************
  * it-edit the Integrated Terminal Editor: a text editor with severals               *
  * integrated functionnalities.                                                      *
  *                                                                                   *
  * Copyright (C) 2016 Bruggemann Eddie.                                              *
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

#include "./Headers/includes.h"
#include "./Headers/defines.h"

#include "./Headers/global_vars.h"


#include "./Configuration/configuration.h"

#include "./Callbacks/configuration_callbacks.h"
#include "./Callbacks/edition_callbacks.h"
#include "./Callbacks/editor_callbacks.h"
#include "./Callbacks/files_callbacks.h"
#include "./Callbacks/gui_callbacks.h"
#include "./Callbacks/highlight_selection_callbacks.h"
#include "./Callbacks/search_settings_callbacks.h"
#include "./Callbacks/terminals_callbacks.h"

#include "./Editor/editor.h"

#include "./GUI/dialogs/message_dialog.h"

#include "./GUI/configure/configure_gui_elements.h"

#include "./GUI/configure/configuration_dialog.h"

#include "./GUI/dialogs/dialogs.h"

#include "./GUI/setup/setup_gui.h"


#ifdef DEBUG
  #include "./DEBUG/debug_search_by_signals.h" /** Debugging utilities **/
#endif


static void destroy(GtkWidget *widget ,gpointer pointer) ;
static gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) ;

void check_applications(char *app_name, GtkWidget *menu_item) ;

gboolean set_terminals_container_size(gpointer user_data) ;

void on_size_allocated(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) ;



int main(int argc, char *argv[]) {


  /** We use the american language in this application. **/
  setlocale(LC_ALL, "") ;

  gtk_init(&argc,&argv) ;

  /** The search history double-linked list
    * which purpose is to navigate into the previous search terms,
    * throught the UP and DOWN arrow wenn the search entry has the focus.
    *********************************************************************/

  extern GList *search_history ;
  extern gboolean search_history_start ;

  search_history = g_list_alloc () ;

  search_history_start = TRUE ;


  /** Files Handler file managing single-linked list: **/
  files_manager_list =  g_slist_alloc() ;



  /** Last opened file folder storing. **/
  extern gchar *open_file_dirname ;

  open_file_dirname = g_strdup_printf("%s", g_get_home_dir()) ;


  get_main_configuration() ;

  get_app_configuration() ;

  /** GUI structure initialization. **/
  GUI    pgui     ;  /** Pointer initialisation corrected by:  **/
  extern GUI *gui ;  /** Mickaël <Mickaël_mail@gmail.com>      **/
  gui = &pgui     ;

  /** main window **/
  gui->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;

  gui->editor_notebook = NULL ;


  gtk_window_set_default_icon_from_file(PATH_TO_ICON, NULL) ;
  gtk_window_maximize(GTK_WINDOW(gui->main_window));
  gtk_window_set_title(GTK_WINDOW(gui->main_window), PRGNAME) ;

  g_object_set(G_OBJECT(gui->main_window), "border-width", 8, NULL) ;

  g_signal_connect_after(G_OBJECT(gui->main_window), "delete-event", G_CALLBACK(delete_event), NULL) ;
  g_signal_connect(G_OBJECT(gui->main_window), "destroy",      G_CALLBACK(destroy),      NULL) ;





  /** Main GUI container containing all the widgets. **/
  gui->main_vbox   = gtk_box_new(GTK_ORIENTATION_VERTICAL,   0) ;





  /** Menu: **/
  gui->menu = g_malloc0(sizeof(Menu)) ;

  gui->menu->menu_files_accel_group    = gtk_accel_group_new() ;
  gui->menu->menu_edition_accel_group  = gtk_accel_group_new() ;
  gui->menu->menu_action_accel_group   = gtk_accel_group_new() ;
  gui->menu->menu_view_accel_group     = gtk_accel_group_new() ;


  initialize_menu(gui->menu) ;

  gtk_window_add_accel_group(GTK_WINDOW(gui->main_window), gui->menu->menu_files_accel_group)   ;
  gtk_window_add_accel_group(GTK_WINDOW(gui->main_window), gui->menu->menu_edition_accel_group) ;
  gtk_window_add_accel_group(GTK_WINDOW(gui->main_window), gui->menu->menu_action_accel_group)  ;
  gtk_window_add_accel_group(GTK_WINDOW(gui->main_window), gui->menu->menu_view_accel_group)    ;





  /** Buttons **/
  gui->buttons = g_slice_new(Buttons) ;

  gui->buttons_accel_group   = gtk_accel_group_new() ;

  initialize_button_box(gui->buttons) ;

  /** Buttons containers: **/
  gui->left_buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;
  gtk_box_set_spacing(GTK_BOX(gui->left_buttonbox),    8) ;

  gui->padding_buttonbox_1 = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;

  gui->edition_buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;
  gtk_button_box_set_layout(GTK_BUTTON_BOX(gui->edition_buttonbox), GTK_BUTTONBOX_CENTER);
  gtk_box_set_spacing(GTK_BOX(gui->edition_buttonbox), 8) ;

  gui->padding_buttonbox_2 = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;

  gui->action_buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;
  gtk_button_box_set_layout(GTK_BUTTON_BOX(gui->action_buttonbox), GTK_BUTTONBOX_CENTER);
  gtk_box_set_spacing(GTK_BOX(gui->action_buttonbox),  8) ;

  gui->padding_buttonbox_3 = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;

  gui->right_buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;
  gtk_button_box_set_layout(GTK_BUTTON_BOX(gui->right_buttonbox), GTK_BUTTONBOX_END) ;
  gtk_box_set_spacing(GTK_BOX(gui->right_buttonbox),   8) ;


  gtk_box_pack_start(GTK_BOX(gui->left_buttonbox), gui->buttons->open_file_button,             FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->left_buttonbox), gui->buttons->save_file_button,             FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->left_buttonbox), gui->buttons->save_file_as_button,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->left_buttonbox), gui->buttons->save_file_all_button,         FALSE, FALSE, 0) ;


  /** Pack buttonbar images buttons. */
  gtk_box_pack_start(GTK_BOX(gui->edition_buttonbox), gui->buttons->tabs_button,               FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->edition_buttonbox), gui->buttons->cut_button,                FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->edition_buttonbox), gui->buttons->copy_button,               FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->edition_buttonbox), gui->buttons->paste_button,              FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->edition_buttonbox), gui->buttons->duplicate_button,          FALSE, FALSE, 0) ;

  /** This are image button which must set non-homogeneous for not expand for having an square size. **/
  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->edition_buttonbox),gui->buttons->tabs_button,      TRUE) ;
  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->edition_buttonbox),gui->buttons->cut_button,       TRUE) ;
  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->edition_buttonbox),gui->buttons->copy_button,      TRUE) ;
  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->edition_buttonbox),gui->buttons->paste_button,     TRUE) ;
  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->edition_buttonbox),gui->buttons->duplicate_button, TRUE) ;


  gtk_box_pack_start(GTK_BOX(gui->action_buttonbox), gui->buttons->go_to_line_button,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->action_buttonbox), gui->buttons->search_and_replace_button,  FALSE, FALSE, 0) ;


  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->action_buttonbox),gui->buttons->go_to_line_button,         TRUE);
  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->action_buttonbox),gui->buttons->search_and_replace_button, TRUE);

  #ifdef DEBUG
  GtkWidget *debug_search_and_replace_button = gtk_button_new_with_label("Find Replace debug") ;

  g_signal_connect(G_OBJECT(debug_search_and_replace_button), "clicked", G_CALLBACK(debug_searching_and_replace_by_signal_emit) , NULL) ;

  gtk_box_pack_start(GTK_BOX(gui->right_buttonbox), debug_search_and_replace_button,                FALSE, FALSE, 0) ;
  #endif



  gtk_box_pack_start(GTK_BOX(gui->right_buttonbox), gui->buttons->exec_button,                  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->right_buttonbox), gui->buttons->big_terminal_button,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->right_buttonbox), gui->buttons->terminals_show_button,        FALSE, FALSE, 0) ;

  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->right_buttonbox),gui->buttons->exec_button,           TRUE);
  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(gui->right_buttonbox),gui->buttons->terminals_show_button, TRUE);


  gtk_window_add_accel_group(GTK_WINDOW(gui->main_window), gui->buttons_accel_group);

  /** Main buttons box toolbar container: **/
  gui->buttonbox_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0) ;

  gtk_box_set_spacing(GTK_BOX(gui->buttonbox_hbox), 8) ;

  gtk_box_pack_start(GTK_BOX(gui->buttonbox_hbox), gui->left_buttonbox,      FALSE, FALSE, 0 )  ;
  gtk_box_pack_start(GTK_BOX(gui->buttonbox_hbox), gui->padding_buttonbox_1, TRUE,  TRUE,  0 )  ;
  gtk_box_pack_start(GTK_BOX(gui->buttonbox_hbox), gui->edition_buttonbox,   FALSE, FALSE, 0 )  ;
  gtk_box_pack_start(GTK_BOX(gui->buttonbox_hbox), gui->padding_buttonbox_2, TRUE,  TRUE,  0 )  ;
  gtk_box_pack_start(GTK_BOX(gui->buttonbox_hbox), gui->action_buttonbox,    FALSE, FALSE, 0 )  ;
  gtk_box_pack_start(GTK_BOX(gui->buttonbox_hbox), gui->padding_buttonbox_3, TRUE,  TRUE,  0 )  ;
  gtk_box_pack_start(GTK_BOX(gui->buttonbox_hbox), gui->right_buttonbox,     FALSE, FALSE, 0 )  ;

  g_object_set(G_OBJECT(gui->buttonbox_hbox), "margin", 4, NULL) ;




  gui->go_to_line_dialog = g_slice_new(Go_To_Line_Dialog) ;



  gui->editor_notebook = gtk_notebook_new() ;

  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(gui->editor_notebook), GTK_POS_TOP) ;
  gtk_notebook_set_show_border(GTK_NOTEBOOK(gui->editor_notebook), TRUE);
  gtk_notebook_set_scrollable(GTK_NOTEBOOK(gui->editor_notebook), TRUE);
  gtk_notebook_popup_enable(GTK_NOTEBOOK(gui->editor_notebook));

  g_signal_connect(G_OBJECT(gui->editor_notebook), "switch-page", G_CALLBACK(change_current_page), NULL) ;


  /** Main editor container **/
  gui->editor_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gui->bottom_bar  = g_slice_new(BottomBar) ;

  /** Editor bottom info bar: currrent line,column \t filename \t total lines,characters **/
  gui->bottom_bar->info_bottom_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_widget_set_margin_left(GTK_WIDGET(gui->bottom_bar->info_bottom_bar),   4) ;
  gtk_widget_set_margin_right(GTK_WIDGET(gui->bottom_bar->info_bottom_bar),  4) ;


  gui->bottom_bar->current_row_col  = gtk_label_new("") ;
  gui->bottom_bar->padding_left     = gtk_label_new("") ;
  gui->bottom_bar->filename_label   = gtk_label_new("") ;
  gui->bottom_bar->padding_right    = gtk_label_new("") ;
  gui->bottom_bar->total_rows_cols  = gtk_label_new("") ;


  gtk_widget_set_size_request(gui->bottom_bar->current_row_col, -1, 8) ;
  gtk_widget_set_size_request(gui->bottom_bar->info_bottom_bar, -1, 8) ;



  gtk_box_pack_start(GTK_BOX(gui->bottom_bar->info_bottom_bar), gui->bottom_bar->current_row_col,  FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(gui->bottom_bar->info_bottom_bar), gui->bottom_bar->padding_left,     TRUE,  TRUE,  0 ) ;
  gtk_box_pack_start(GTK_BOX(gui->bottom_bar->info_bottom_bar), gui->bottom_bar->filename_label,   FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(gui->bottom_bar->info_bottom_bar), gui->bottom_bar->padding_right,    TRUE,  TRUE,  0 ) ;
  gtk_box_pack_start(GTK_BOX(gui->bottom_bar->info_bottom_bar), gui->bottom_bar->total_rows_cols,  FALSE, FALSE, 0 ) ;


  /** Search and replace functionnality. **/

  /** Search settings. **/
  search_settings = g_malloc(sizeof(Search_Settings)) ;

  set_search_settings_default(search_settings) ;

  searching.search_text       = NULL  ;
  searching.search_tag        = NULL  ;
  searching.complete_search   = FALSE ;
  searching.get_an_occurrence = FALSE ;
  searching.restart_search    = FALSE ;


  searching.source_search_settings = gtk_source_search_settings_new() ;


  gui->search_and_replace = g_slice_new(Search_And_Replace) ;

  setup_search_and_replace_bar(gui->search_and_replace) ;

  gtk_box_set_spacing(GTK_BOX(gui->search_and_replace->search_and_replace_main_vbox), 4) ;

  g_object_set(G_OBJECT(gui->search_and_replace->search_and_replace_main_vbox), "margin", 4, NULL) ;

  gtk_box_set_spacing(GTK_BOX(gui->search_and_replace->search_and_replace_main_hbox), 4) ;

  gtk_box_pack_start(GTK_BOX(gui->search_and_replace->search_and_replace_main_vbox), gui->search_and_replace->search_and_replace_main_hbox, FALSE, FALSE, 0) ;


  /** Pack editor containers. **/
  gtk_box_pack_start(GTK_BOX(gui->editor_vbox), gui->editor_notebook,                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(gui->editor_vbox), gui->search_and_replace->search_and_replace_main_vbox, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->editor_vbox), gui->bottom_bar->info_bottom_bar,                      FALSE, FALSE, 0) ;




  /** Hard GUI coded terminals notebook container: **/
  gui->terminal_notebook = gtk_notebook_new() ;

  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(gui->terminal_notebook), GTK_POS_TOP) ;
  gtk_notebook_set_show_border(GTK_NOTEBOOK(gui->terminal_notebook), TRUE);
  gtk_notebook_set_scrollable(GTK_NOTEBOOK(gui->terminal_notebook),  TRUE);
  gtk_notebook_popup_enable(GTK_NOTEBOOK(gui->terminal_notebook));

  set_new_terminals(gui->terminal_notebook) ;


  /** We preset an arbitrary size for displaying problems patching and resize it into the function: set_terminals_container_size ; **/
  gtk_widget_set_size_request(gui->terminal_notebook, 724,-1) ; /** The place where the size id define is important for terminal prompt right displaying **/





  /** Initialized the big terminal **/
  gui->big_terminal = g_malloc(sizeof(Terminal)) ;

  gui->big_terminal->terminal = vte_terminal_new() ;


  /** Initialized GUI part of the terminal. **/
  initialize_terminal(gui->big_terminal) ;

  /** Configure terminal partially according to the configuration stored settings and launch the user shell. **/
  setup_terminal(gui->big_terminal->terminal) ;

  /** Big terminal divided into 4 terminals. **/
  gui->big_four_terminals = g_malloc(sizeof(FTerms)) ;

  gui->big_four_terminals->terminal_1 = g_malloc(sizeof(Terminal)) ;
  gui->big_four_terminals->terminal_2 = g_malloc(sizeof(Terminal)) ;
  gui->big_four_terminals->terminal_3 = g_malloc(sizeof(Terminal)) ;
  gui->big_four_terminals->terminal_4 = g_malloc(sizeof(Terminal)) ;

  gui->big_four_terminals->terminal_1->terminal = vte_terminal_new() ;
  gui->big_four_terminals->terminal_2->terminal = vte_terminal_new() ;
  gui->big_four_terminals->terminal_3->terminal = vte_terminal_new() ;
  gui->big_four_terminals->terminal_4->terminal = vte_terminal_new() ;

  /** Initialized GUI part of the terminal. **/
  initialize_terminal(gui->big_four_terminals->terminal_1) ;
  initialize_terminal(gui->big_four_terminals->terminal_2) ;
  initialize_terminal(gui->big_four_terminals->terminal_3) ;
  initialize_terminal(gui->big_four_terminals->terminal_4) ;

  /** Configure terminal partially according to the configuration stored settings and launch shell. **/
  setup_terminal(gui->big_four_terminals->terminal_1->terminal) ;
  setup_terminal(gui->big_four_terminals->terminal_2->terminal) ;
  setup_terminal(gui->big_four_terminals->terminal_3->terminal) ;
  setup_terminal(gui->big_four_terminals->terminal_4->terminal) ;


  gui->big_four_terminals->vertical_paned_up   = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL) ;
  gui->big_four_terminals->vertical_paned_down = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL) ;

  gui->big_four_terminals->horizontal_paned    = gtk_paned_new(GTK_ORIENTATION_VERTICAL)   ;

  gtk_paned_pack1(GTK_PANED(gui->big_four_terminals->vertical_paned_up),   gui->big_four_terminals->terminal_1->terminal_hbox, TRUE, TRUE);
  gtk_paned_pack2(GTK_PANED(gui->big_four_terminals->vertical_paned_up),   gui->big_four_terminals->terminal_2->terminal_hbox, TRUE, TRUE);

  gtk_paned_pack1(GTK_PANED(gui->big_four_terminals->vertical_paned_down), gui->big_four_terminals->terminal_3->terminal_hbox, TRUE,TRUE);
  gtk_paned_pack2(GTK_PANED(gui->big_four_terminals->vertical_paned_down), gui->big_four_terminals->terminal_4->terminal_hbox, TRUE,TRUE);

  gtk_paned_pack1(GTK_PANED(gui->big_four_terminals->horizontal_paned),    gui->big_four_terminals->vertical_paned_up,         TRUE, TRUE) ;
  gtk_paned_pack2(GTK_PANED(gui->big_four_terminals->horizontal_paned),    gui->big_four_terminals->vertical_paned_down,       TRUE, TRUE) ;


  /** Main window middle resizing between editor and terminals. **/
  gui->middle_paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL) ;

  gtk_paned_pack1(GTK_PANED(gui->middle_paned),gui->editor_vbox,       TRUE,  FALSE) ;
  gtk_paned_pack2(GTK_PANED(gui->middle_paned),gui->terminal_notebook, FALSE, TRUE)  ;


  /** Main notebook will permit to switch between big terminal and editor with side terminals. **/
  gui->main_notebook = gtk_notebook_new() ;
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(gui->main_notebook),   FALSE) ;
  gtk_notebook_set_show_border(GTK_NOTEBOOK(gui->main_notebook), TRUE)  ;


  gtk_notebook_append_page(GTK_NOTEBOOK(gui->main_notebook), gui->middle_paned,                         FALSE) ;
  gtk_notebook_append_page(GTK_NOTEBOOK(gui->main_notebook), gui->big_terminal->terminal_hbox,          FALSE) ;
  gtk_notebook_append_page(GTK_NOTEBOOK(gui->main_notebook), gui->big_four_terminals->horizontal_paned, FALSE) ;



  /** Main GUI container. **/
  gui->main_hbox   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;


  gtk_box_pack_start(GTK_BOX(gui->main_hbox),gui->main_notebook,  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox),gui->menu->menu_bar, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox),gui->buttonbox_hbox, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox),gui->main_hbox,      TRUE,  TRUE,  0) ;



  gtk_container_add(GTK_CONTAINER(gui->main_window), gui->main_vbox) ;



  /** Parse argument vector **/
  if (argc > 1) {
    int c ;
    for (c=1 ; c < argc ; c++) {
      char *path = realpath(argv[c], NULL) ;
      if (path != NULL && ! g_file_test(path, G_FILE_TEST_IS_DIR)) {
        process_selected_file(path, NULL) ;
      }
    }
  }
  else {
    File_Editor *start_file = g_malloc(sizeof(File_Editor)) ;
    add_file_to_editor(gui->editor_notebook, start_file, NULL, true) ;
  }

  g_signal_connect(G_OBJECT(gui->menu->display_buttonbar->menuitem), "activate", G_CALLBACK(view_buttonbar), gui->buttonbox_hbox) ;

  g_signal_connect(G_OBJECT(gui->menu->toggle_fullscreen->menuitem), "activate", G_CALLBACK(toggle_fullscreen), gui->main_window) ;



  gtk_widget_show_all(gui->main_window) ;


  /** Check if applications detected if not then hide the menuitem widget. **/
  check_applications(gui_app.diff,         gui->menu->app_programming_diff->menuitem) ;
  check_applications(gui_app.debugger,     gui->menu->app_programming_debugger->menuitem) ;
  check_applications(gui_app.python,       gui->menu->app_programming_python->menuitem) ;
  check_applications(gui_app.gui_designer, gui->menu->app_programming_gui_designer->menuitem) ;
  check_applications(gui_app.devhelp,      gui->menu->app_programming_devhelp->menuitem) ;
  check_applications(gui_app.calculator,   gui->menu->app_utils_calculator->menuitem) ;
  check_applications(gui_app.color_picker, gui->menu->app_utils_color_picker->menuitem) ;
  check_applications(gui_app.dictionary,   gui->menu->app_utils_dictionary->menuitem) ;
  check_applications(gui_app.file_manager, gui->menu->app_utils_file_manager->menuitem) ;
  check_applications(gui_app.notes,        gui->menu->app_utils_notes->menuitem) ;
  check_applications(gui_app.browser,      gui->menu->app_utils_browser->menuitem) ;

  /** Check if their are user defined applications, if not hide the menuitem widget. **/
  if (gui_app.nb_of_others == 0) {
    gtk_widget_hide(gui->menu->app_others_menuitem->menuitem) ;
  }

  /** Hide the search and replace bar at application start. **/
  gtk_widget_hide(gui->search_and_replace->search_and_replace_main_vbox) ;

  /** Hide the terminals at application start. **/
  gtk_widget_hide(gui->terminal_notebook) ;

  /** Set editor noetbook page. **/
  gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), 0) ;

  /** This function set the terminals default size in relationship to your screen relationship because the application is maximize at start. And set startup settings. **/
  g_signal_connect(G_OBJECT(gui->main_window), "size-allocate", G_CALLBACK(on_size_allocated), NULL) ;


  gtk_main() ;

  exit(EXIT_SUCCESS) ;

}

inline void check_applications(char *app_name, GtkWidget *menu_item) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (g_strcmp0(app_name, "") == 0) {
    gtk_widget_hide(menu_item) ;
    g_signal_handlers_disconnect_by_func(menu_item, launch_application, app_name) ;
  }

  return ;
}


void on_size_allocated(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  static bool is_on = false ;

  if (is_on) {

    g_signal_handlers_disconnect_by_func(widget, on_size_allocated, NULL) ;

    return ;

  }

  /** The default value from the factor reflect a 80 char size terminal according my system resolution (1920x1080) but you can set it at your convienence. **/
  gint width, height ;
  gtk_window_get_size(GTK_WINDOW(gui->main_window), &width, &height) ;

  /** Must compute the ratio depending of the resolution. **/
  gtk_widget_set_size_request(gui->terminal_notebook, (int) round(settings.side_terms_factor *  allocation->width), -1) ; /** The place where the size id define is important for terminal prompt right displaying **/


  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->terminals_show_button), (settings.side_terms_on) ? TRUE : FALSE) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->big_terminal_button), (settings.big_term_on) ? TRUE : FALSE) ;

  if (settings.big_term_div) {

    gtk_widget_activate(gui->menu->switch_big_terms->menuitem) ;

  }

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->big_terminal_button), (settings.big_term_on) ? TRUE : FALSE) ;

  if (! settings.buttonbar_on) {
    gtk_widget_hide(gui->buttonbox_hbox) ;
  }
  if (settings.fullscreen) {
    gtk_window_fullscreen(GTK_WINDOW(gui->main_window)) ;
  }

  is_on = true ;

  return ;

}


static void destroy(GtkWidget *widget,gpointer pointer) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gtk_main_quit() ;

  exit(EXIT_SUCCESS) ;
}


static gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) {
  /** Check if any file still unsaved before exit the application **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (files_not_saved_check() > 0) {
    /** Any file is not saved by exiting the application. **/

    /** Display an last chance saving window
      * and return an boolean value according user choice
      * which eventually prevent to close the application.
      ****************************************************/

    return display_unsaved_files_dialog() ;

  }

  return FALSE ;
}
