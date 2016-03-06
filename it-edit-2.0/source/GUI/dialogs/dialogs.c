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

#include "./dialogs.h"



void go_to_line(gint line_count) {
  /** Go to line callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Getting the user entry. **/
  const gchar *line_number = gtk_entry_get_text(GTK_ENTRY(gui->go_to_line_dialog->go_to_line_entry)) ;

  gint c ;

  for (c=0 ; c < (gint) strlen(line_number) ; c++) {
    /** Check if the user entry is a valid line number. **/
    if (! g_ascii_isdigit(line_number[c]) ) {
      gtk_widget_destroy(gui->go_to_line_dialog->go_to_line_dialog);
      return ;
    }
  }

  gint line ;
  sscanf(line_number,"%d", &line) ;

  /** Check if th user entry is a valid line number. **/
  if (line > line_count || line_count < 1) {
    gtk_widget_destroy(gui->go_to_line_dialog->go_to_line_dialog);
    return ;
  }

  /** Move to the wanted line number. **/
  GtkTextIter line_iter ;
  gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(current_editor.current_buffer), &line_iter, line-1) ;
  gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(current_editor.current_textview),     &line_iter, 0.25,  TRUE, 0.5, 0.5) ;
  gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(current_editor.current_buffer),     &line_iter) ;

  /** Highlight the line. **/
  gtk_source_view_set_highlight_current_line(GTK_SOURCE_VIEW(current_editor.current_textview), TRUE);


  gtk_widget_destroy(gui->go_to_line_dialog->go_to_line_dialog);

  return ;
}



void display_go_to_line_dialog(GtkWidget *button, gpointer user_data) {
  /** Generate the line number asking toplevel dialog window. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gui->go_to_line_dialog->go_to_line_dialog  = gtk_dialog_new() ;

  GError *err = NULL ;

  gtk_window_set_icon_from_file(GTK_WINDOW(gui->go_to_line_dialog->go_to_line_dialog), PATH_TO_BUTTON_ICON "edit-text-frame-update.png", &err) ;
  gtk_window_set_decorated(GTK_WINDOW(gui->go_to_line_dialog->go_to_line_dialog), FALSE) ;
  gtk_window_set_position(GTK_WINDOW(gui->go_to_line_dialog->go_to_line_dialog), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(gui->go_to_line_dialog->go_to_line_dialog), "Go to line...");

  gui->go_to_line_dialog->go_to_line_content = gtk_dialog_get_content_area(GTK_DIALOG(gui->go_to_line_dialog->go_to_line_dialog));

  gui->go_to_line_dialog->go_to_line_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  /** Window content label in form: " Go to line (1 - line_count) ". **/
  char *label_text ;
  label_text = g_strdup_printf(" Go to line: (1- %d) ", gtk_text_buffer_get_line_count(current_editor.current_buffer) ) ;
  gui->go_to_line_dialog->go_to_line_label = gtk_label_new(label_text);
  free(label_text) ;

  /** Line number entry field. **/
  gui->go_to_line_dialog->go_to_line_entry = gtk_entry_new() ;


  GFile *gicon_file = g_file_new_for_path(PATH_TO_BUTTON_ICON "format-line-spacing-normal.png");
  GIcon *icon       = g_file_icon_new(gicon_file) ;
  g_object_set(G_OBJECT(gui->go_to_line_dialog->go_to_line_entry), "primary-icon-gicon", icon, NULL) ;


  gtk_entry_set_input_purpose(GTK_ENTRY(gui->go_to_line_dialog->go_to_line_entry), GTK_INPUT_PURPOSE_DIGITS);


  char *len_chars ;
  len_chars = g_strdup_printf("%d", gtk_text_buffer_get_line_count(current_editor.current_buffer)) ;

  int length = (int) strlen(len_chars) ;

  g_free(len_chars) ;

  GtkEntryBuffer *entry_buffer = gtk_entry_buffer_new(NULL, -1) ;
  g_object_set(G_OBJECT(entry_buffer), "max-length", length, NULL) ;
  gtk_entry_set_buffer(GTK_ENTRY(gui->go_to_line_dialog->go_to_line_entry), entry_buffer) ;



  gtk_box_pack_start(GTK_BOX(gui->go_to_line_dialog->go_to_line_vbox), gui->go_to_line_dialog->go_to_line_label, FALSE, FALSE, 8 ) ;
  gtk_box_pack_start(GTK_BOX(gui->go_to_line_dialog->go_to_line_vbox), gui->go_to_line_dialog->go_to_line_entry, FALSE, FALSE, 8 ) ;

  gtk_container_add(GTK_CONTAINER (gui->go_to_line_dialog->go_to_line_content), gui->go_to_line_dialog->go_to_line_vbox);


  /** Dialog window buttons: **/
  gui->go_to_line_dialog->go_to_line_apply = gtk_dialog_add_button(GTK_DIALOG(gui->go_to_line_dialog->go_to_line_dialog),"Apply", GTK_RESPONSE_APPLY) ;
  gui->go_to_line_dialog->go_to_line_close = gtk_dialog_add_button(GTK_DIALOG(gui->go_to_line_dialog->go_to_line_dialog),"Close", GTK_RESPONSE_CLOSE) ;

  /** Apply the Return key shortcut to the Apply button: **/
  GtkAccelGroup *accel_group = gtk_accel_group_new();

  gtk_widget_add_accelerator(gui->go_to_line_dialog->go_to_line_apply,
                            "activate",
                            accel_group,
                            GDK_KEY_Return,
                            0,
                            GTK_ACCEL_VISIBLE);

  gtk_window_add_accel_group(GTK_WINDOW(gui->go_to_line_dialog->go_to_line_dialog), accel_group) ;



  gtk_widget_show_all(gui->go_to_line_dialog->go_to_line_dialog) ;

  gint result = gtk_dialog_run (GTK_DIALOG (gui->go_to_line_dialog->go_to_line_dialog));

  switch (result) {

    case GTK_RESPONSE_APPLY :

       go_to_line(gtk_text_buffer_get_line_count(current_editor.current_buffer)) ;
       break;

    case GTK_RESPONSE_CLOSE :

       gtk_widget_destroy(gui->go_to_line_dialog->go_to_line_dialog);
       break;
  }

  return ;
}


void display_execute_command_terminal(char *execute_command_string) {
  /** Generate the terminal include window for executing the wanted command. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  if ( g_strcmp0(execute_command_string,"") == 0) {
    return ;
  }

  GtkWidget *execute_command_terminal_dialog  = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;


  gtk_window_set_icon_from_file(GTK_WINDOW(execute_command_terminal_dialog), PATH_TO_BUTTON_ICON "utilities-terminal.png", NULL) ;
  gtk_window_set_decorated(GTK_WINDOW(execute_command_terminal_dialog), TRUE) ;
  gtk_window_set_position(GTK_WINDOW(execute_command_terminal_dialog), GTK_WIN_POS_CENTER);
  gtk_window_set_destroy_with_parent(GTK_WINDOW(execute_command_terminal_dialog), TRUE);
  gtk_window_set_title(GTK_WINDOW(execute_command_terminal_dialog), "Execute command");


  char *default_shell = settings.user_shell ;

  char *command_string ;
  command_string = g_strdup_printf("%s \r", execute_command_string) ;

  free(execute_command_string) ;


  GtkWidget *exec_terminal = vte_terminal_new() ;

  /** Configure terminal partially according to the configuration stored settings. **/
  configure_terminal(exec_terminal, true) ;

  GtkWidget *terminal_scrollbar = gtk_scrollbar_new( GTK_ORIENTATION_VERTICAL, gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(exec_terminal)) ) ;
  GtkWidget *terminal_hbox      = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0)  ;


  gtk_box_pack_start(GTK_BOX(terminal_hbox),exec_terminal,TRUE,TRUE,0) ;
  gtk_box_pack_start(GTK_BOX(terminal_hbox),terminal_scrollbar,FALSE,FALSE,0) ;

  gtk_box_set_homogeneous(GTK_BOX(terminal_hbox), FALSE);

  char *argv_cmd[2] = {default_shell, NULL} ;

  /** Fork a new process: your default shell. The configurations files like .bashrc will be reading. **/
  vte_terminal_fork_command_full(VTE_TERMINAL(exec_terminal), VTE_PTY_DEFAULT, g_get_home_dir(), argv_cmd, NULL, G_SPAWN_DEFAULT, NULL,NULL, NULL, NULL);

  /** Wait for the forking has been done. **/
  usleep(100000) ;

  /** Launch the wanted command in the terminal. **/
  vte_terminal_feed_child(VTE_TERMINAL(exec_terminal), command_string, strlen(command_string) );


  free(command_string) ;

  /** Generate clipboard menu connect to the terminal. **/
  GtkWidget *clipboard_menu = gtk_menu_new() ;

  GtkWidget *copy_label = gtk_menu_item_new_with_label("Copy to clipboard") ;
  GtkWidget *paste_label = gtk_menu_item_new_with_label("Paste to terminal") ;

  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu),copy_label)  ;
  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu),paste_label) ;

  gtk_widget_show_all(clipboard_menu);

  g_signal_connect(G_OBJECT(exec_terminal), "button-press-event", G_CALLBACK(display_clipboard_menu), clipboard_menu) ;

  g_signal_connect(G_OBJECT(copy_label),  "activate", G_CALLBACK(clipboard_copy),  exec_terminal) ;
  g_signal_connect(G_OBJECT(paste_label), "activate", G_CALLBACK(clipboard_paste), exec_terminal) ;


  gtk_container_add(GTK_CONTAINER(execute_command_terminal_dialog), terminal_hbox);

  gtk_widget_show_all(execute_command_terminal_dialog) ;


  return ;

 }

void display_execute_command_dialog(GtkWidget *button, gpointer user_data) {
  /** Generate the execute command dialog, asking the user for the command to execute. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *execute_command_dialog  = gtk_dialog_new_with_buttons ("Execute a command",
                                                NULL,
                                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                "Execute",
                                                GTK_RESPONSE_APPLY,
                                                "Cancel",
                                                GTK_RESPONSE_CLOSE,
                                                NULL);

  GError *err = NULL ;

  gtk_window_set_decorated(GTK_WINDOW(execute_command_dialog), FALSE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(execute_command_dialog), TRUE);
  gtk_window_set_position(GTK_WINDOW(execute_command_dialog), GTK_WIN_POS_CENTER);
  gtk_window_set_modal(GTK_WINDOW(execute_command_dialog), TRUE);
  gtk_window_set_icon_from_file(GTK_WINDOW(execute_command_dialog), PATH_TO_BUTTON_ICON "system-run.png", &err) ;
  gtk_window_set_title(GTK_WINDOW(execute_command_dialog), "Execute command");


  GtkWidget *execute_command_dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(execute_command_dialog));

  GtkWidget *execute_command_dialog_vbox    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  GtkWidget *execute_command_dialog_label = gtk_label_new(" Enter a command (per example: man [section] page) ");

  GtkWidget *execute_command_dialog_entry = gtk_entry_new() ;



  GFile *gicon_file = g_file_new_for_path(PATH_TO_BUTTON_ICON "system-run.png");
  GIcon *icon       = g_file_icon_new(gicon_file) ;
  g_object_set(G_OBJECT(execute_command_dialog_entry), "primary-icon-gicon", icon, NULL) ;


  gtk_box_pack_start(GTK_BOX(execute_command_dialog_vbox), execute_command_dialog_label, FALSE, FALSE, 8 ) ;
  gtk_box_pack_start(GTK_BOX(execute_command_dialog_vbox), execute_command_dialog_entry, FALSE, FALSE, 8 ) ;


  gtk_container_add(GTK_CONTAINER (execute_command_dialog_content), execute_command_dialog_vbox);


  GtkWidget *execute_command_dialog_apply = gtk_dialog_get_widget_for_response(GTK_DIALOG(execute_command_dialog), GTK_RESPONSE_APPLY) ;

  /** Assign the Return key shortcut to the Apply button. **/
  GtkAccelGroup *accel_group = gtk_accel_group_new();
  gtk_widget_add_accelerator(execute_command_dialog_apply,
                           "activate",
                           accel_group,
                           GDK_KEY_Return,
                           0,
                           GTK_ACCEL_VISIBLE);

  gtk_window_add_accel_group(GTK_WINDOW(execute_command_dialog), accel_group) ;


  GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(execute_command_dialog));
  gtk_button_box_set_layout(GTK_BUTTON_BOX(action_area), GTK_BUTTONBOX_EDGE);


  gtk_widget_show_all(execute_command_dialog) ;



  gint result = gtk_dialog_run (GTK_DIALOG (execute_command_dialog));

  char *exec_cmd ;

  switch (result) {

    case GTK_RESPONSE_APPLY :

       exec_cmd = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(execute_command_dialog_entry)) ) ;

       gtk_widget_destroy(execute_command_dialog) ;
       display_execute_command_terminal(exec_cmd) ;

       break;

    case GTK_RESPONSE_CLOSE :

       gtk_widget_destroy(execute_command_dialog);

       break;
  }

  return ;


}

void application_selected(GtkAppChooserWidget *self, GAppInfo *application, gpointer user_data) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  g_app_info_launch(application, NULL, NULL , NULL) ;

  return ;

}

void display_application_laucher_dialog(GtkWidget *widget, gpointer user_data) {
  /** Generate application launcher dialog window. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *app_launcher_dialog = gtk_app_chooser_dialog_new_for_content_type(NULL, GTK_DIALOG_MODAL, "." ) ;

  gtk_app_chooser_dialog_set_heading(GTK_APP_CHOOSER_DIALOG(app_launcher_dialog), "Select application to launch") ;

  GtkWidget *app_launcher_widget = gtk_app_chooser_dialog_get_widget(GTK_APP_CHOOSER_DIALOG(app_launcher_dialog) );

  gtk_app_chooser_widget_set_show_all(GTK_APP_CHOOSER_WIDGET(app_launcher_widget), TRUE) ;

  g_signal_connect(G_OBJECT(app_launcher_widget), "application-activated", G_CALLBACK(application_selected), NULL) ;

  gint result = gtk_dialog_run(GTK_DIALOG(app_launcher_dialog));

  switch (result) {

    default :

      gtk_widget_destroy(app_launcher_dialog) ;
      break ;

   }

   return ;

}

void display_file_handler_dialog(GtkWidget *widget, gpointer user_data) {
  /** Generate "File Handler" feature dialog window. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Open file which containing the titles (the buttons labels) and the corresponding file URI. **/
  FILE *fp = fopen(PATH_TO_LINKS_FILE, "r");


  GtkWidget *file_handler_dialog_main_window = gtk_dialog_new() ;

  gtk_window_set_destroy_with_parent(GTK_WINDOW(file_handler_dialog_main_window), TRUE)    ;
  gtk_window_set_resizable(GTK_WINDOW(file_handler_dialog_main_window),           FALSE)   ;
  gtk_window_set_position(GTK_WINDOW(file_handler_dialog_main_window), GTK_WIN_POS_CENTER) ;
  gtk_window_set_decorated(GTK_WINDOW(file_handler_dialog_main_window),           TRUE)    ;

  gtk_window_set_title(GTK_WINDOW(file_handler_dialog_main_window),               "Files Handler");
  gtk_widget_set_size_request(GTK_WIDGET(file_handler_dialog_main_window),        400, 600);


  GtkWidget *file_handler_scrolled_window    = gtk_scrolled_window_new(NULL, NULL) ;

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(file_handler_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );

  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(file_handler_scrolled_window),  400) ;
  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(file_handler_scrolled_window), 600) ;

  GtkWidget *file_handler_vbox               = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0) ;


  gint c = 0 ;

  while (fp != NULL) {

    size_t n = 0  ;

    /** Getting the title from the entry (button label text). **/
    char *label = NULL ;
    if ( getline(&label, &n, fp) == -1) {
      break ;
    }

    char *label_linefeed = strrchr(label,'\n') ;
    if ( label_linefeed != NULL  ) {
      label[label_linefeed - label] = '\0' ;
    }



    n = 0 ;

    /** Getting the URI corresponding to the file to be launched. **/
    char *uri = NULL ;
    if (  getline(&uri, &n, fp) == -1) {
      break ;
    }

    char *uri_linefeed = strrchr(uri,'\n') ;
    if ( uri_linefeed != NULL  ) {
      uri[uri_linefeed - uri] = '\0' ;
    }

    /** Contruct a "link button" with the URI and the label (title). **/
    GtkWidget *file_handler_button =  gtk_link_button_new_with_label(uri, label);
    gtk_button_set_relief(GTK_BUTTON(file_handler_button), GTK_RELIEF_NORMAL) ;

    gtk_box_pack_start(GTK_BOX(file_handler_vbox),  file_handler_button, FALSE, FALSE, 5) ;

    free(label) ;
    free(uri)   ;

    c++ ;

  }

  fclose(fp) ;

  gtk_container_set_border_width(GTK_CONTAINER(file_handler_vbox), 5);

  gtk_container_add(GTK_CONTAINER(file_handler_scrolled_window), file_handler_vbox) ;


  GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(file_handler_dialog_main_window));

  gtk_container_add(GTK_CONTAINER(content_area), file_handler_scrolled_window) ;


  gtk_widget_show_all(file_handler_dialog_main_window) ;

  return ;

}



gboolean display_unsaved_files_dialog(void) {
  /** Generate the unsaved files at application exit dialog window. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *unsaved_files_dialog  = gtk_dialog_new_with_buttons("Some files still are unsaved...",
                                                  NULL,
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  "Save selected files",
                                                  GTK_RESPONSE_APPLY,
                                                  "Cancel close IT-Edit",
                                                  GTK_RESPONSE_CANCEL,
                                                  "I don't mind, close !",
                                                  GTK_RESPONSE_CLOSE,
                                                  NULL);

  gtk_window_set_destroy_with_parent(GTK_WINDOW(unsaved_files_dialog), TRUE)  ;
  gtk_window_set_decorated(GTK_WINDOW(unsaved_files_dialog),           FALSE)  ;
  gtk_window_set_resizable(GTK_WINDOW(unsaved_files_dialog),           FALSE) ;
  gtk_window_set_position(GTK_WINDOW(unsaved_files_dialog),            GTK_WIN_POS_CENTER) ;
  gtk_window_set_title(GTK_WINDOW(unsaved_files_dialog),               "Some files still are unsaved...") ;



             
  GtkWidget *unsaved_files_content_area = gtk_dialog_get_content_area(GTK_DIALOG(unsaved_files_dialog)) ;

  GtkWidget *unsaved_files_action_area =  gtk_dialog_get_action_area(GTK_DIALOG(unsaved_files_dialog)) ;


  gtk_button_box_set_layout(GTK_BUTTON_BOX(unsaved_files_action_area), GTK_BUTTONBOX_EDGE);

  gtk_container_set_border_width(GTK_CONTAINER(unsaved_files_content_area), 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(unsaved_files_action_area),  5) ;


  GtkWidget *unsaved_files_scrolled_window = gtk_scrolled_window_new(NULL, NULL) ;

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(unsaved_files_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC) ;



  GtkWidget *unsaved_files_listbox      = gtk_list_box_new() ;            

  gtk_list_box_set_selection_mode(GTK_LIST_BOX(unsaved_files_listbox), GTK_SELECTION_NONE);

  gint c = 0 ;

  /** The unsaved_files GSList is yet filled with the unsaved files list from the function: files_not_saved_check(). **/

  while (unsaved_files->data != NULL) {

    gchar *filepath = (gchar *) ((struct Unsaved_File *) (unsaved_files->data))->filepath ;

    /** Generate an entry in the GtkListBox as a checked checkbutton. **/
    GtkWidget *file_checkbox = gtk_check_button_new_with_label(g_path_get_basename(filepath)) ;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(file_checkbox), TRUE) ;


    gint *num = &((struct Unsaved_File *) (unsaved_files->data))->page_number ;

    /** Setting datas for further saving processing. **/
    g_object_set_data(G_OBJECT(file_checkbox), "page_number", num) ;
    g_object_set_data(G_OBJECT(file_checkbox), "filepath", filepath) ;


    gtk_list_box_insert(GTK_LIST_BOX(unsaved_files_listbox), file_checkbox, c) ;

    c++ ;



    if (unsaved_files->next == NULL) {
      break ;
    }

    unsaved_files = unsaved_files->next ;



  }

  gint cc = 0  ;

  while (cc < c) {
    /** Clean the unsaved_files GSList, to not have doubles if the user choose to not close the application and try to quit. **/
    unsaved_files = g_slist_remove(unsaved_files, g_slist_nth_data(unsaved_files, cc)) ;
    cc++ ;

    /** @NOTE: the files saving, if the user choose it will happend throught the checkbutton datas. **/
  }


  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(unsaved_files_scrolled_window), c < 9 ? c * 32 : 256) ;

  gtk_container_add(GTK_CONTAINER(unsaved_files_scrolled_window), unsaved_files_listbox) ;
  gtk_container_add(GTK_CONTAINER(unsaved_files_content_area),    unsaved_files_scrolled_window) ;

  gtk_widget_show_all(unsaved_files_dialog) ;

  gint result = gtk_dialog_run (GTK_DIALOG (unsaved_files_dialog));


  cc = 0 ;

  switch (result) {

    case GTK_RESPONSE_APPLY :

      while (cc < c) {

        GtkListBoxRow *listbox_row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(unsaved_files_listbox), cc);

        GtkWidget *file_checkbox = gtk_bin_get_child(GTK_BIN(listbox_row)) ;

        if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(file_checkbox)) ) {

          gint page_number = *(gint *) g_object_get_data(G_OBJECT(file_checkbox), "page_number") ;

          gchar *filepath  = (gchar *) g_object_get_data(G_OBJECT(file_checkbox), "filepath") ;


          /** Getting the notebook page to save. **/
          GtkWidget *notebook_page        = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), page_number) ;
          GtkWidget *current_textview     = gtk_bin_get_child(GTK_BIN(notebook_page)) ;
          GtkTextBuffer *current_buffer   = gtk_text_view_get_buffer(GTK_TEXT_VIEW(current_textview)) ;

          /** Getting current editor content **/
          GtkTextIter iter_start, iter_end ;
          GError *error=NULL               ;

          gtk_text_buffer_get_start_iter(current_buffer,&iter_start);
          gtk_text_buffer_get_end_iter(current_buffer,&iter_end);

          gchar *file_content = gtk_text_buffer_get_text(current_buffer, &iter_start, &iter_end, FALSE);

          gchar *back_up_filepath = NULL ;

          if (settings.backup_file) {

            back_up_filepath = g_strdup_printf("%s~", filepath) ;

            rename(filepath,back_up_filepath) ;

          }

          if ( ! g_file_set_contents(filepath, file_content, -1, &error) ) {
            /** Failed to save editor content as file, display an error message and return. **/

              rename(back_up_filepath, filepath) ;
        
              char *msg = g_strdup_printf("Failed to save file:\n%s", (gchar *) filepath) ;
        
              display_message_dialog("Cannot save file !!!", msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;
         
              free(msg) ;
         
            }


          g_free(back_up_filepath) ;

          g_free(filepath) ;
        }

        cc++ ;

      }


      gtk_widget_destroy(unsaved_files_dialog) ;

      return FALSE ;

    case GTK_RESPONSE_CANCEL :

      gtk_widget_destroy(unsaved_files_dialog) ;
      return TRUE ;  /** Do not propagate the signal to the destroy signal handler wich will exit the application. **/

    case GTK_RESPONSE_CLOSE :

      gtk_widget_destroy(unsaved_files_dialog) ;
      return FALSE ;

  }

  return FALSE ;
}

void display_about_dialog(GtkWidget *widget, gpointer user_data) {


  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  GtkWidget *about_dialog = gtk_about_dialog_new() ;

  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), PRGNAME) ;

  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog),      VERSION)   ;

  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),    COPYRIGHT)   ;



  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),     "IT-Edit the terminals integrated text-editor,\n"
                                                                    "with severals functionnalities.") ;

  gchar *file_content ;

  g_file_get_contents(PATH_TO_GPL_TEXT, &file_content, NULL, NULL) ;

  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about_dialog), file_content) ;

  g_free(file_content) ;

  gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(about_dialog), FALSE);

  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog), PRGWEBURL) ;

  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog), PRGNAME " Website") ;

  const gchar *author[2] = {AUTHOR " " MAIL, NULL} ;

  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), author);

  gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(about_dialog), author);

  gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), NULL) ;

  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_dialog), NULL);

  const gchar *thanks[2] = {"Thanks to my beloved mother, my family and the doctors.", NULL} ;

  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog), "Thank's", thanks);

  const gchar *advice[2] = {"Stay away from drugs: drugs destroy your brain and your life.", NULL} ;

  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog), "Advice:", advice);

  gtk_dialog_run(GTK_DIALOG(about_dialog)) ;

  gtk_widget_destroy(about_dialog) ;

  return ;

}

GtkWidget *ctime_entry ;
GtkWidget *atime_entry ;
GtkWidget *mtime_entry ;

GtkWidget *file_name_entry ;

GtkWidget* generate_calendar(GStatBuf *datetime, int16_t type) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *calendar = gtk_calendar_new() ;

  GDateTime *datetime_file = g_date_time_new_from_unix_local( (type == -1) ?  datetime->st_atime : (type == 0) ? datetime->st_ctime : datetime->st_mtime) ;

  gtk_calendar_select_month(GTK_CALENDAR(calendar), (guint) g_date_time_get_month(datetime_file)-1, (guint) g_date_time_get_year(datetime_file));

  gtk_calendar_mark_day(GTK_CALENDAR(calendar), g_date_time_get_day_of_month(datetime_file)) ;

  gtk_calendar_set_display_options(GTK_CALENDAR(calendar), GTK_CALENDAR_SHOW_HEADING | GTK_CALENDAR_SHOW_DAY_NAMES) ;

  gtk_calendar_set_detail_width_chars(GTK_CALENDAR(calendar), 63) ;

  gtk_calendar_set_detail_height_rows(GTK_CALENDAR(calendar), 63) ;

  g_date_time_unref(datetime_file) ;

  return calendar ;
}

void generate_calendar_and_timer(GtkWidget *widget, GStatBuf *datetime) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *dialog = gtk_dialog_new_with_buttons("Select new timestamp",
                                                  NULL,
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  "OK",
                                                  GTK_RESPONSE_ACCEPT,
                                                  "Cancel",
                                                  GTK_RESPONSE_REJECT,
                                                  NULL) ;
                               
  GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog)) ;                               

  GtkWidget *calendar = NULL ;

  GtkWidget *label_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;
  GtkWidget *time_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *hour_label = gtk_label_new("Hours") ;
  GtkWidget *min_label  = gtk_label_new("Minutes") ;
  GtkWidget *sec_label  = gtk_label_new("Seconds") ;

  GtkWidget *hour = gtk_spin_button_new_with_range(0, 23, 1);
  GtkWidget *min  = gtk_spin_button_new_with_range(0, 59, 1);
  GtkWidget *sec  = gtk_spin_button_new_with_range(0, 59, 1);

  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(hour), FALSE) ;
  gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(hour), GTK_UPDATE_IF_VALID) ;
  gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(hour), TRUE) ;

  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(min), FALSE) ;
  gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(min), GTK_UPDATE_IF_VALID) ;
  gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(min), TRUE) ;

  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(sec), FALSE) ;
  gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(sec), GTK_UPDATE_IF_VALID) ;
  gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(sec), TRUE) ;



  if ( g_strcmp0(gtk_widget_get_name(widget), "ctime") == 0 ) {

    calendar = generate_calendar(datetime, 0) ;

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(hour), g_date_time_get_hour(g_date_time_new_from_unix_local(datetime->st_ctime))   ) ;
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(min),  g_date_time_get_minute(g_date_time_new_from_unix_local(datetime->st_ctime)) ) ;
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(sec),  g_date_time_get_second(g_date_time_new_from_unix_local(datetime->st_ctime)) ) ;


  }
  else if ( g_strcmp0(gtk_widget_get_name(widget), "atime") == 0 ) {

    calendar = generate_calendar(datetime, -1) ;

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(hour), g_date_time_get_hour(g_date_time_new_from_unix_local(datetime->st_atime))   ) ;
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(min),  g_date_time_get_minute(g_date_time_new_from_unix_local(datetime->st_atime)) ) ;
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(sec),  g_date_time_get_second(g_date_time_new_from_unix_local(datetime->st_atime)) ) ;


  }
  else if ( g_strcmp0(gtk_widget_get_name(widget), "mtime") == 0 ) {

    calendar = generate_calendar(datetime, 1) ;

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(hour), g_date_time_get_hour(g_date_time_new_from_unix_local(datetime->st_mtime))   ) ;
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(min),  g_date_time_get_minute(g_date_time_new_from_unix_local(datetime->st_mtime)) ) ;
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(sec),  g_date_time_get_second(g_date_time_new_from_unix_local(datetime->st_mtime)) ) ;


  }


  gtk_box_pack_start(GTK_BOX(label_hbox), hour_label, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(label_hbox), min_label,  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(label_hbox), sec_label,  TRUE, TRUE, 0) ;

  gtk_box_pack_start(GTK_BOX(time_hbox), hour, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(time_hbox), min,  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(time_hbox), sec,  TRUE, TRUE, 0) ;

  gtk_box_pack_start(GTK_BOX(content_area), calendar,   TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(content_area), label_hbox, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(content_area), time_hbox,  TRUE, TRUE, 0) ;


  GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(dialog)) ;


  gtk_button_box_set_layout(GTK_BUTTON_BOX(action_area), GTK_BUTTONBOX_EDGE) ;

  gtk_widget_show_all(dialog) ;

  int ret = gtk_dialog_run(GTK_DIALOG(dialog)) ;

  guint year  ;
  guint month ;
  guint day   ;

  switch (ret) {

    case GTK_RESPONSE_ACCEPT :

      gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day) ;

      gint64 timestamp = g_date_time_to_unix(g_date_time_new_local(year, month+1, day,
                            gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(hour)),
                            gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(min)),
                            gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sec)) ) ) ;

      if ( g_strcmp0(gtk_widget_get_name(widget), "ctime") == 0 ) {

        datetime->st_ctime = timestamp ;

        GDateTime *tmp = g_date_time_new_from_unix_local(timestamp) ;

        gtk_entry_set_text(GTK_ENTRY(ctime_entry), g_date_time_format(tmp, "%F %T")) ;

        g_date_time_unref(tmp) ;

      }
      else if ( g_strcmp0(gtk_widget_get_name(widget), "atime") == 0 ) {

        datetime->st_atime = timestamp ;

        GDateTime *tmp = g_date_time_new_from_unix_local(timestamp) ;

        gtk_entry_set_text(GTK_ENTRY(atime_entry), g_date_time_format(tmp, "%F %T")) ;

        g_date_time_unref(tmp) ;

      }
      else if ( g_strcmp0(gtk_widget_get_name(widget), "mtime") == 0 ) {

        datetime->st_mtime = timestamp ;

        GDateTime *tmp = g_date_time_new_from_unix_local(timestamp) ;

        gtk_entry_set_text(GTK_ENTRY(mtime_entry), g_date_time_format(tmp, "%F %T")) ;

        g_date_time_unref(tmp) ;

      }







      break ;

  }

  gtk_widget_destroy(dialog) ;

  return ;

}

void rename_file(GtkWidget *widget, File_Editor *file_editor) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *file_chooser_dialog = gtk_file_chooser_dialog_new("Rename file as:", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
                                                               "Cancel" , GTK_RESPONSE_CANCEL,
                                                               "Rename",  GTK_RESPONSE_ACCEPT,
                                                               NULL);

  gchar *filepath = g_object_get_data(G_OBJECT(file_editor->buffer), "filepath") ;

  gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(file_chooser_dialog), TRUE) ;

  gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(file_chooser_dialog), g_path_get_basename(filepath)) ;

  const char *current_dir = (g_strcmp0(g_path_get_dirname(filepath), g_get_tmp_dir()) == 0) ? g_get_home_dir() : g_path_get_dirname(filepath) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser_dialog), current_dir) ;

  gtk_file_chooser_set_use_preview_label(GTK_FILE_CHOOSER(file_chooser_dialog), TRUE) ;

  int ret = gtk_dialog_run(GTK_DIALOG(file_chooser_dialog)) ;

  switch (ret) {

    case GTK_RESPONSE_ACCEPT :
      #ifdef RELOADING_FUNC
      file_editor->must_reload = FALSE ;

      file_editor->timeout_return = FALSE ;

      check_file_has_change(file_editor) ;
      #endif

      g_rename(filepath, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser_dialog)) ) ;

      gtk_entry_set_text(GTK_ENTRY(file_name_entry), g_path_get_basename(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser_dialog))) ) ;

      #ifdef RELOADING_FUNC
      file_editor->must_reload    = FALSE ;
      file_editor->timeout_return = TRUE ;
      g_stat(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser_dialog)), &file_editor->file_info) ;
      g_timeout_add(999, (GSourceFunc) check_file_has_change, file_editor) ;
      #endif

      g_object_set_data(G_OBJECT(file_editor->buffer), "filepath", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser_dialog))) ;



      break ;

  }

  gtk_widget_destroy(file_chooser_dialog) ;

  return ;
}



inline void toggle_mode_bit(GtkWidget *widget, File_Editor *file_editor) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {

    if ( g_strcmp0(gtk_widget_get_name(widget), "ur") == 0) {

      file_editor->file_info.st_mode |= S_IRUSR ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "uw") == 0) {

      file_editor->file_info.st_mode |= S_IWUSR ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "ux") == 0) {

      file_editor->file_info.st_mode |= S_IXUSR ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "gr") == 0) {

      file_editor->file_info.st_mode |= S_IRGRP ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "gw") == 0) {

      file_editor->file_info.st_mode |= S_IWGRP ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "gx") == 0) {

      file_editor->file_info.st_mode |= S_IXGRP ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "or") == 0) {

      file_editor->file_info.st_mode |= S_IROTH ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "ow") == 0) {

      file_editor->file_info.st_mode |= S_IWOTH ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "ox") == 0) {

      file_editor->file_info.st_mode |= S_IXOTH ;
    }

  }
  else {

    if ( g_strcmp0(gtk_widget_get_name(widget), "ur") == 0) {

      file_editor->file_info.st_mode ^= S_IRUSR ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "uw") == 0) {

      file_editor->file_info.st_mode ^= S_IWUSR ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "ux") == 0) {

      file_editor->file_info.st_mode ^= S_IXUSR ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "gr") == 0) {

      file_editor->file_info.st_mode ^= S_IRGRP ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "gw") == 0) {

      file_editor->file_info.st_mode ^= S_IWGRP ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "gx") == 0) {

      file_editor->file_info.st_mode ^= S_IXGRP ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "or") == 0) {

      file_editor->file_info.st_mode ^= S_IROTH ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "ow") == 0) {

      file_editor->file_info.st_mode ^= S_IWOTH ;
    }
    else if ( g_strcmp0(gtk_widget_get_name(widget), "ox") == 0) {

      file_editor->file_info.st_mode ^= S_IXOTH ;
    }
  }

  g_chmod(g_object_get_data(G_OBJECT(file_editor->buffer), "filepath"), file_editor->file_info.st_mode);

  return ;

}

char *g_get_wc(char *filepath, char *option) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gint standard_output ;

  GPid child_pid ;

  GError *error = NULL ;

  char *buffer = calloc(PATH_MAX+32, sizeof(char)) ;

  char *args[] =  {"wc", option, filepath, NULL} ;

  g_spawn_async_with_pipes(NULL,
                          args,
                          NULL,
                          G_SPAWN_SEARCH_PATH,
                          NULL,
                          NULL,
                          &child_pid,
             
                          NULL,
                          &standard_output,
                          NULL,
                          &error);

  if (error != NULL) {

    fprintf(stderr,"%s\n", error->message) ;
    return NULL ;
  }


  if  ( read(standard_output, buffer, sizeof(char) * (PATH_MAX+32) ) <= 0 ) {

    return NULL ;
  }

  close(standard_output) ;

  g_spawn_close_pid(child_pid) ;

  int c=0 ;

  while (g_ascii_isdigit(buffer[c])) {

    ++c ;
  }
  buffer[c]='\0' ;

  return buffer ;

}

void display_file_informations_dialog(GtkWidget *widget, gpointer user_data) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  if (! G_IS_OBJECT(current_editor.current_textview) ) {
    return ;
  }

  GtkWidget *file_informations_dialog  = gtk_dialog_new_with_buttons("File informations", NULL,
                                                                     GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                                     "Close",
                                                                     GTK_RESPONSE_CLOSE,
                                                                     NULL);
                                              
                                            

  gtk_window_set_resizable(GTK_WINDOW(file_informations_dialog), FALSE) ;

  gtk_window_set_position(GTK_WINDOW(file_informations_dialog), GTK_WIN_POS_CENTER_ON_PARENT) ;

  gpointer filepath = g_object_get_data(G_OBJECT(current_editor.current_buffer), "filepath") ;

  File_Editor *file_editor = g_object_get_data(G_OBJECT(current_editor.current_textview), "file_editor") ;

  g_stat((char *) filepath, &file_editor->file_info) ;


  gchar *source_language_name      = NULL ;
  gchar **source_language_mimetype = NULL ;
  gchar **source_language_globs    = NULL ;

  gchar *content_type = NULL ;

  gboolean result_uncertain = true ;

  gsize  file_size = 0 ;

  GtkSourceLanguage *source_language = NULL ;

  GtkSourceLanguageManager *source_language_manager = gtk_source_language_manager_get_default();

  // Try to guess the file content type.
  content_type = g_content_type_guess( g_path_get_basename(filepath), NULL, file_size, &result_uncertain);

  if (content_type && source_language_manager) {

    // Try to guess the loaded source file language:
    source_language = gtk_source_language_manager_guess_language(source_language_manager, g_path_get_basename(filepath), content_type);

    if (source_language != NULL) {

      if (gtk_source_language_get_name(source_language) != NULL) {
        source_language_name      = (char *) gtk_source_language_get_name(source_language) ;
      }
      else {
        source_language_name=NULL ;
      }
      if (gtk_source_language_get_mime_types(source_language) != NULL) {
        source_language_mimetype  = gtk_source_language_get_mime_types(source_language) ;
      }
      else {
        source_language_mimetype=NULL ;
      }
      if (gtk_source_language_get_globs(source_language) != NULL) {
        source_language_globs     = gtk_source_language_get_globs(source_language) ;
      }
      else {
        source_language_globs=NULL ;
      }

    }

    else if (source_language == NULL) {
      // Language guessing failed.
      source_language_name      = NULL ;
      source_language_mimetype  = NULL ;
      source_language_globs     = NULL ;
    }

    g_free(content_type) ;

  }



  GtkWidget *main_info_image ;

  char *dialog_image_filepath = NULL ;

  if (source_language_mimetype == NULL) {

    goto unavailable_mimetype ;
  }

  if (source_language != NULL) {

    uint8_t c ;

    for (c=0 ; ; c++) {
        // Try to find an icon for the source file language.

        char *mimetype = gtk_source_language_get_mime_types(source_language)[c] ;

        if (mimetype == NULL) {
          // Default filetype icon.
          main_info_image = gtk_image_new_from_file(PATH_TO_MIMETYPE_BIG "unknown.png") ;
          dialog_image_filepath = g_strdup_printf("%s", PATH_TO_MIMETYPE_BIG "unknown.png") ;
          break ;
        }

        char *ptr = strchr(mimetype, '/') ;

        if (ptr != NULL) {

          // Simple pointer arithmetic '/' replacement to '-'.
          mimetype[ptr - mimetype] = '-' ;

          fprintf(stdout,"mimetype: %s\n",mimetype) ;

          char *filepath = g_malloc(PATH_MAX) ;
          strcpy(filepath, PATH_TO_MIMETYPE_BIG) ;
          strcat(filepath, mimetype) ;
          strcat(filepath,".png")    ;

          // Try if the mimetype coresponding icon is present in the icon set.
          if ( g_file_test(filepath, G_FILE_TEST_EXISTS) ) {
            // Setting filetype icon.
            main_info_image = gtk_image_new_from_file(filepath) ;
            dialog_image_filepath = g_strdup_printf("%s", filepath) ;
            free(filepath) ;
            break ;
          }

          free(filepath) ;

        }

    }

   }
   else {

     unavailable_mimetype :

     // Default filetype icon.
     main_info_image = gtk_image_new_from_file(PATH_TO_MIMETYPE_BIG "unknown.png") ;
     dialog_image_filepath = g_strdup_printf("%s", PATH_TO_MIMETYPE_BIG "unknown.png") ;
   }




  gtk_window_set_icon_from_file(GTK_WINDOW(file_informations_dialog), dialog_image_filepath, NULL) ;

  g_free(dialog_image_filepath) ;

  GtkWidget *content_vbox = gtk_dialog_get_content_area(GTK_DIALOG(file_informations_dialog));

  GtkWidget *main_info_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_pack_start(GTK_BOX(main_info_hbox), main_info_image, FALSE, FALSE, 0) ;

  gtk_widget_set_margin_left(main_info_image, 16+8) ;

  GtkWidget *main_info_grid = gtk_grid_new() ;

  gtk_grid_set_row_homogeneous(GTK_GRID(main_info_grid),    TRUE) ;
  gtk_grid_set_column_homogeneous(GTK_GRID(main_info_grid), TRUE) ;
  gtk_grid_set_row_spacing(GTK_GRID(main_info_grid),           2) ;
  gtk_grid_set_column_spacing(GTK_GRID(main_info_grid),        2) ;


  GtkWidget *main_info_language_name_label       = gtk_label_new("Language:  ") ;                                          
  GtkWidget *main_info_language_mimetype_label   = gtk_label_new("Mimetype:  ") ;                                          
  GtkWidget *main_info_language_extension_label  = gtk_label_new("Extension: ") ;                                          

  GtkWidget *main_info_language_value            = gtk_label_new( (source_language_name == NULL) ? "Unknow" : source_language_name) ;                                          
  GtkWidget *main_info_mimetype_value            = gtk_label_new( (source_language_mimetype == NULL) ? "Unknow" : source_language_mimetype[0]) ;                                          
  GtkWidget *main_info_extension_value           = gtk_label_new( (source_language_globs == NULL) ? "Unknow" : source_language_globs[0]) ;                                          

  if (source_language_mimetype != NULL) {

    g_strfreev(source_language_mimetype) ;
  }
  if (source_language_globs != NULL) {
    g_strfreev(source_language_globs) ;
  }



  gtk_label_set_justify(GTK_LABEL(main_info_language_name_label),      GTK_JUSTIFY_RIGHT);
  gtk_label_set_justify(GTK_LABEL(main_info_language_mimetype_label),  GTK_JUSTIFY_RIGHT);
  gtk_label_set_justify(GTK_LABEL(main_info_language_extension_label), GTK_JUSTIFY_RIGHT);

  gtk_label_set_justify(GTK_LABEL(main_info_language_value),  GTK_JUSTIFY_LEFT);
  gtk_label_set_justify(GTK_LABEL(main_info_mimetype_value),  GTK_JUSTIFY_LEFT);
  gtk_label_set_justify(GTK_LABEL(main_info_extension_value), GTK_JUSTIFY_LEFT);
                                             
  gtk_grid_attach(GTK_GRID(main_info_grid), main_info_language_name_label,      0, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(main_info_grid), main_info_language_value,           1, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(main_info_grid), main_info_language_mimetype_label,  0, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(main_info_grid), main_info_mimetype_value,           1, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(main_info_grid), main_info_language_extension_label, 0, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(main_info_grid), main_info_extension_value,          1, 2, 1, 1) ;

  gtk_box_pack_start(GTK_BOX(main_info_hbox), main_info_grid, TRUE, TRUE, 8) ;

  gtk_box_pack_start(GTK_BOX(content_vbox), main_info_hbox, TRUE, TRUE, 8) ;




  GtkWidget *mode_count_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;


  GtkWidget *mode_frame = gtk_frame_new(" Mode ") ;

  GtkWidget *mode_grid  = gtk_grid_new() ;

  gtk_grid_set_row_homogeneous(GTK_GRID(mode_grid),    TRUE) ;
  gtk_grid_set_column_homogeneous(GTK_GRID(mode_grid), TRUE) ;
  gtk_grid_set_row_spacing(GTK_GRID(mode_grid),           2) ;
  gtk_grid_set_column_spacing(GTK_GRID(mode_grid),        2) ;

  GtkWidget *r = gtk_label_new("R") ;
  GtkWidget *w = gtk_label_new("W") ;
  GtkWidget *x = gtk_label_new("X") ;

  GtkWidget *u = gtk_label_new("U") ;
  GtkWidget *g = gtk_label_new("G") ;
  GtkWidget *o = gtk_label_new("O") ;

  GtkWidget *ur = gtk_check_button_new() ;
  GtkWidget *uw = gtk_check_button_new() ;
  GtkWidget *ux = gtk_check_button_new() ;


  GtkWidget *gr = gtk_check_button_new() ;
  GtkWidget *gw = gtk_check_button_new() ;
  GtkWidget *gx = gtk_check_button_new() ;


  GtkWidget *or = gtk_check_button_new() ;
  GtkWidget *ow = gtk_check_button_new() ;
  GtkWidget *ox = gtk_check_button_new() ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ur), USR_R(file_editor->file_info.st_mode)) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(uw), USR_W(file_editor->file_info.st_mode)) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ux), USR_X(file_editor->file_info.st_mode)) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gr), GRP_R(file_editor->file_info.st_mode)) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gw), GRP_W(file_editor->file_info.st_mode)) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gx), GRP_X(file_editor->file_info.st_mode)) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(or), OTH_R(file_editor->file_info.st_mode)) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ow), OTH_W(file_editor->file_info.st_mode)) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ox), OTH_X(file_editor->file_info.st_mode)) ;


  gtk_grid_attach(GTK_GRID(mode_grid), r, 1, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), w, 2, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), x, 3, 0, 1, 1) ;

  gtk_grid_attach(GTK_GRID(mode_grid), u, 0, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), g, 0, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), o, 0, 3, 1, 1) ;

  gtk_grid_attach(GTK_GRID(mode_grid), ur, 1, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), uw, 2, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), ux, 3, 1, 1, 1) ;

  gtk_grid_attach(GTK_GRID(mode_grid), gr, 1, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), gw, 2, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), gx, 3, 2, 1, 1) ;

  gtk_grid_attach(GTK_GRID(mode_grid), or, 1, 3, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), ow, 2, 3, 1, 1) ;
  gtk_grid_attach(GTK_GRID(mode_grid), ox, 3, 3, 1, 1) ;


  gtk_widget_set_name(ur, "ur") ;
  gtk_widget_set_name(uw, "uw") ;
  gtk_widget_set_name(ux, "ux") ;
  gtk_widget_set_name(gr, "gr") ;
  gtk_widget_set_name(gw, "gw") ;
  gtk_widget_set_name(gx, "gx") ;
  gtk_widget_set_name(or, "or") ;
  gtk_widget_set_name(ow, "ow") ;
  gtk_widget_set_name(ox, "ox") ;


  g_signal_connect(G_OBJECT(ur), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;
  g_signal_connect(G_OBJECT(uw), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;
  g_signal_connect(G_OBJECT(ux), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;

  g_signal_connect(G_OBJECT(gr), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;
  g_signal_connect(G_OBJECT(gw), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;
  g_signal_connect(G_OBJECT(gx), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;

  g_signal_connect(G_OBJECT(or), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;
  g_signal_connect(G_OBJECT(ow), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;
  g_signal_connect(G_OBJECT(ox), "toggled", G_CALLBACK(toggle_mode_bit), file_editor) ;


  gtk_container_add(GTK_CONTAINER(mode_frame), mode_grid) ;


  GtkWidget *count_frame = gtk_frame_new(" Current count ") ;

  GtkWidget *count_grid  = gtk_grid_new() ;

  gtk_grid_set_row_homogeneous(GTK_GRID(count_grid),    TRUE) ;
  gtk_grid_set_column_homogeneous(GTK_GRID(count_grid), TRUE) ;
  gtk_grid_set_row_spacing(GTK_GRID(count_grid),           2) ;
  gtk_grid_set_column_spacing(GTK_GRID(count_grid),        2) ;


  GtkWidget *line_count_label = gtk_label_new("Lines count") ;
  GtkWidget *byte_count_label = gtk_label_new("Bytes count") ;
  GtkWidget *word_count_label = gtk_label_new("Words count") ;




  GtkWidget *line_count_entry = gtk_entry_new() ;
  char *line_count = g_get_wc(filepath, "-l") ;
  gtk_entry_set_text(GTK_ENTRY(line_count_entry), (line_count != NULL) ? line_count : "0") ;

  free(line_count) ;

  GtkWidget *byte_count_entry = gtk_entry_new() ;
  char *byte_count = g_get_wc(filepath, "-c") ;
  gtk_entry_set_text(GTK_ENTRY(byte_count_entry), (byte_count != NULL) ? byte_count : "0") ;

  free(byte_count) ;

  GtkWidget *word_count_entry = gtk_entry_new() ;

  char *word_count = g_get_wc(filepath, "-w") ;
  gtk_entry_set_text(GTK_ENTRY(word_count_entry), (word_count != NULL) ? word_count : "0") ;

  free(word_count) ;

  g_object_set(G_OBJECT(line_count_entry), "editable", FALSE, NULL) ;
  g_object_set(G_OBJECT(byte_count_entry), "editable", FALSE, NULL) ;
  g_object_set(G_OBJECT(word_count_entry), "editable", FALSE, NULL) ;



  gtk_grid_attach(GTK_GRID(count_grid), line_count_label, 0, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(count_grid), line_count_entry, 1, 0, 1, 1) ;

  gtk_grid_attach(GTK_GRID(count_grid), byte_count_label, 0, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(count_grid), byte_count_entry, 1, 1, 1, 1) ;

  gtk_grid_attach(GTK_GRID(count_grid), word_count_label, 0, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(count_grid), word_count_entry, 1, 2, 1, 1) ;


  gtk_container_set_border_width(GTK_CONTAINER(count_grid), 4) ;

  gtk_container_add(GTK_CONTAINER(count_frame), count_grid) ;

  GtkWidget *mode_count_padding_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_pack_start(GTK_BOX(mode_count_hbox), mode_frame,   TRUE, TRUE, 4) ;
  gtk_box_pack_start(GTK_BOX(mode_count_hbox), count_frame,  TRUE, TRUE, 4) ;

  gtk_box_pack_start(GTK_BOX(mode_count_padding_hbox), mode_count_hbox, TRUE, TRUE, 4) ;

  gtk_box_pack_start(GTK_BOX(content_vbox), mode_count_padding_hbox, TRUE, TRUE, 4) ;


  GtkWidget *chksum_frame = gtk_frame_new(" Checksum ") ;

  GtkWidget *chksum_label_vbox    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  GtkWidget *chksum_entry_vbox    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  GtkWidget *chksum_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,   0) ;

  GtkWidget *chksum_md5_label    = gtk_label_new("MD5    ")    ;
  GtkWidget *chksum_sha1_label   = gtk_label_new("SHA1   ")   ;
  GtkWidget *chksum_sha256_label = gtk_label_new("SHA256 ") ;
  GtkWidget *chksum_sha512_label = gtk_label_new("SHA512 ") ;

  gtk_misc_set_padding(GTK_MISC(chksum_md5_label),    4, 0) ;
  gtk_misc_set_padding(GTK_MISC(chksum_sha1_label),   4, 0) ;
  gtk_misc_set_padding(GTK_MISC(chksum_sha256_label), 4, 0) ;
  gtk_misc_set_padding(GTK_MISC(chksum_sha512_label), 4, 0) ;

  GtkWidget *chksum_md5_entry     = gtk_entry_new() ;
  GtkWidget *chksum_sha1_entry    = gtk_entry_new() ;
  GtkWidget *chksum_sha256_entry  = gtk_entry_new() ;
  GtkWidget *chksum_sha512_entry  = gtk_entry_new() ;


  file_size = 0 ;

  gchar *file_content = NULL ;

  g_file_get_contents(filepath, &file_content, &file_size, NULL) ;


  gtk_entry_set_text(GTK_ENTRY(chksum_md5_entry),    g_compute_checksum_for_string(G_CHECKSUM_MD5,    file_content, (gssize) file_size)) ;
  gtk_entry_set_text(GTK_ENTRY(chksum_sha1_entry),   g_compute_checksum_for_string(G_CHECKSUM_SHA1,   file_content, (gssize) file_size)) ;
  gtk_entry_set_text(GTK_ENTRY(chksum_sha256_entry), g_compute_checksum_for_string(G_CHECKSUM_SHA256, file_content, (gssize) file_size)) ;
  gtk_entry_set_text(GTK_ENTRY(chksum_sha512_entry), g_compute_checksum_for_string(G_CHECKSUM_SHA512, file_content, (gssize) file_size)) ;

  g_object_set(G_OBJECT(chksum_md5_entry),    "editable", FALSE, NULL) ;
  g_object_set(G_OBJECT(chksum_sha1_entry),   "editable", FALSE, NULL) ;
  g_object_set(G_OBJECT(chksum_sha256_entry), "editable", FALSE, NULL) ;
  g_object_set(G_OBJECT(chksum_sha512_entry), "editable", FALSE, NULL) ;

  g_free(file_content) ;

  gtk_box_pack_start(GTK_BOX(chksum_label_vbox), chksum_md5_label,    TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(chksum_label_vbox), chksum_sha1_label,   TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(chksum_label_vbox), chksum_sha256_label, TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(chksum_label_vbox), chksum_sha512_label, TRUE, TRUE,   0) ;


  gtk_box_pack_start(GTK_BOX(chksum_entry_vbox), chksum_md5_entry,    TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(chksum_entry_vbox), chksum_sha1_entry,   TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(chksum_entry_vbox), chksum_sha256_entry, TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(chksum_entry_vbox), chksum_sha512_entry, TRUE, TRUE,   0) ;


  gtk_box_pack_start(GTK_BOX(chksum_hbox), chksum_label_vbox,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(chksum_hbox), chksum_entry_vbox,         TRUE, TRUE,   0) ;


  gtk_container_set_border_width(GTK_CONTAINER(chksum_hbox), 4) ;

  gtk_container_add(GTK_CONTAINER(chksum_frame), chksum_hbox) ;

  GtkWidget *chksum_padding_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_pack_start(GTK_BOX(chksum_padding_box), chksum_frame, TRUE, TRUE, 4) ;

  gtk_box_pack_start(GTK_BOX(content_vbox), chksum_padding_box, TRUE, TRUE, 4) ;


  GtkWidget *time_frame = gtk_frame_new(" Timestamps ") ;

  GtkWidget *time_label_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0)   ;
  GtkWidget *time_entry_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0)   ;
  GtkWidget *time_button_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0)   ;

  GtkWidget *time_hbox        = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GDateTime *datetime_st_ctime = g_date_time_new_from_unix_local(file_editor->file_info.st_ctime) ;
  GDateTime *datetime_st_atime = g_date_time_new_from_unix_local(file_editor->file_info.st_atime) ;
  GDateTime *datetime_st_mtime = g_date_time_new_from_unix_local(file_editor->file_info.st_mtime) ;


  GtkWidget *ctime_label = gtk_label_new("Last status change time") ;
  GtkWidget *atime_label = gtk_label_new("Last access time") ;
  GtkWidget *mtime_label = gtk_label_new("Last modification time") ;

  gtk_misc_set_padding(GTK_MISC(ctime_label),    4, 0) ;
  gtk_misc_set_padding(GTK_MISC(atime_label),    4, 0) ;
  gtk_misc_set_padding(GTK_MISC(mtime_label),    4, 0) ;

  ctime_entry = gtk_entry_new() ;
  atime_entry = gtk_entry_new() ;
  mtime_entry = gtk_entry_new() ;


  GtkWidget *ctime_change_button = gtk_button_new_with_label("  Modify ") ;
  GtkWidget *atime_change_button = gtk_button_new_with_label("  Modify ") ;
  GtkWidget *mtime_change_button = gtk_button_new_with_label("  Modify ") ;

  gtk_widget_set_name(ctime_change_button, "ctime") ;
  gtk_widget_set_name(atime_change_button, "atime") ;
  gtk_widget_set_name(mtime_change_button, "mtime") ;


  g_signal_connect(G_OBJECT(ctime_change_button), "clicked", G_CALLBACK(generate_calendar_and_timer), &file_editor->file_info) ;
  g_signal_connect(G_OBJECT(atime_change_button), "clicked", G_CALLBACK(generate_calendar_and_timer), &file_editor->file_info) ;
  g_signal_connect(G_OBJECT(mtime_change_button), "clicked", G_CALLBACK(generate_calendar_and_timer), &file_editor->file_info) ;




  gtk_entry_set_text(GTK_ENTRY(ctime_entry), g_date_time_format(datetime_st_ctime, "%F %T")) ;
  gtk_entry_set_text(GTK_ENTRY(atime_entry), g_date_time_format(datetime_st_atime, "%F %T")) ;
  gtk_entry_set_text(GTK_ENTRY(mtime_entry), g_date_time_format(datetime_st_mtime, "%F %T")) ;

  g_date_time_unref(datetime_st_ctime) ;
  g_date_time_unref(datetime_st_atime) ;
  g_date_time_unref(datetime_st_mtime) ;



  g_object_set(G_OBJECT(ctime_entry), "editable", FALSE, NULL) ;
  g_object_set(G_OBJECT(atime_entry), "editable", FALSE, NULL) ;
  g_object_set(G_OBJECT(mtime_entry), "editable", FALSE, NULL) ;

  gtk_box_pack_start(GTK_BOX(time_label_vbox), ctime_label, TRUE, TRUE, 2) ;
  gtk_box_pack_start(GTK_BOX(time_label_vbox), atime_label, TRUE, TRUE, 2) ;
  gtk_box_pack_start(GTK_BOX(time_label_vbox), mtime_label, TRUE, TRUE, 2) ;

  gtk_box_pack_start(GTK_BOX(time_entry_vbox), ctime_entry, TRUE, TRUE, 2) ;
  gtk_box_pack_start(GTK_BOX(time_entry_vbox), atime_entry, TRUE, TRUE, 2) ;
  gtk_box_pack_start(GTK_BOX(time_entry_vbox), mtime_entry, TRUE, TRUE, 2) ;

  gtk_box_pack_start(GTK_BOX(time_button_vbox), ctime_change_button, TRUE, TRUE, 2) ;
  gtk_box_pack_start(GTK_BOX(time_button_vbox), atime_change_button, TRUE, TRUE, 2) ;
  gtk_box_pack_start(GTK_BOX(time_button_vbox), mtime_change_button, TRUE, TRUE, 2) ;


  gtk_box_pack_start(GTK_BOX(time_hbox), time_label_vbox,  FALSE,  FALSE, 4) ;
  gtk_box_pack_start(GTK_BOX(time_hbox), time_entry_vbox,  TRUE,   TRUE,  4) ;
  gtk_box_pack_start(GTK_BOX(time_hbox), time_button_vbox, FALSE,  FALSE, 4) ;



  gtk_container_add(GTK_CONTAINER(time_frame), time_hbox) ;



  GtkWidget *time_padding_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_pack_start(GTK_BOX(time_padding_box), time_frame,   TRUE, TRUE, 4) ;

  gtk_box_pack_start(GTK_BOX(content_vbox), time_padding_box, TRUE, TRUE, 4) ;



  GtkWidget *file_frame = gtk_frame_new(" Filename ") ;

  GtkWidget *file_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  file_name_entry = gtk_entry_new() ;

  GtkWidget *file_button_rename = gtk_button_new_with_label("Rename") ;


  gtk_entry_set_text(GTK_ENTRY(file_name_entry),  g_path_get_basename(filepath)) ;

  g_object_set(G_OBJECT(file_name_entry), "editable", FALSE, NULL) ;

  gtk_box_pack_start(GTK_BOX(file_hbox), file_name_entry,    TRUE,   TRUE, 4) ;

  gtk_box_pack_start(GTK_BOX(file_hbox), file_button_rename, FALSE, FALSE, 4) ;

  g_signal_connect(G_OBJECT(file_button_rename), "clicked", G_CALLBACK(rename_file), file_editor) ;

  GtkWidget *file_padding_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(file_hbox), 4) ;

  gtk_container_add(GTK_CONTAINER(file_frame), file_hbox) ;

  gtk_box_pack_start(GTK_BOX(file_padding_box), file_frame, TRUE, TRUE, 4) ;

  gtk_box_pack_start(GTK_BOX(content_vbox), file_padding_box, TRUE, TRUE, 4) ;



  gtk_widget_show_all(file_informations_dialog) ;

  gtk_dialog_run( GTK_DIALOG(file_informations_dialog) ) ;

  gtk_widget_destroy(file_informations_dialog) ;


  return ;

}
