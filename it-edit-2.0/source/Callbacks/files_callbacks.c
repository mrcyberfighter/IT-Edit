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


#include "files_callbacks.h"



void process_selected_file(gpointer filepath, gpointer user_data) {

  /** Callback from the open file selector for every selected file. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  char *file = realpath(filepath, NULL) ;

  if (file == NULL) {
    return ;
  }

  if (filepath != NULL) {

      /** Every file has an associated File_Editor structure which hold the Scrolled Window, TextView and GtkSourceBuffer. **/
      File_Editor *file_editor = g_malloc0(sizeof(File_Editor)) ;

      /** Add file content to the editor has an new notebook page. @NOTE: this function does more than the initalisation work, take a look at it. **/
      add_file_to_editor(gui->editor_notebook, file_editor , file, false) ;

      /** Setting the filepath text in the bottom bar. **/
      gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), g_path_get_basename(file)) ;

      /** Update current directory tracking. **/
      if (open_file_dirname != NULL) {
        g_free(open_file_dirname) ;
      }
      open_file_dirname = g_strdup_printf("%s", (char *) g_path_get_dirname(file)) ;
 }

 /** @NOTE: the filepath must not be free because it is set as data from the file_editor->buffer for further use. **/

 return ;

}


void open_file(GtkButton *button) {

  /** File open callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *file_chooser = gtk_file_chooser_dialog_new("Open file",
                                                        NULL,
                                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                                        "Cancel", GTK_RESPONSE_CANCEL,
                                                        "Open",  GTK_RESPONSE_ACCEPT,
                                                        NULL);

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser), open_file_dirname) ;
  gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(file_chooser), TRUE) ;


  gint res ;

  res = gtk_dialog_run (GTK_DIALOG (file_chooser));


  if (res == GTK_RESPONSE_ACCEPT) {
    /** The user has selected file(s) **/

    GtkFileChooser *chooser = GTK_FILE_CHOOSER (file_chooser);

    GSList *selected_files = gtk_file_chooser_get_filenames(chooser) ;


    g_slist_foreach(selected_files, &process_selected_file, NULL) ;

    g_slist_free(selected_files) ;

  }

  /** @NOTE: the filepath must not be free because it is set as data from the file_editor->buffer for further use. **/

  gtk_widget_destroy(file_chooser);

  return ;
}

void open_recent(GtkRecentChooser *chooser, gpointer user_data) {
  /** The user select an item from the recent file list. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  /** retrieve the file URI from the selected item. **/
  gchar *uri = gtk_recent_chooser_get_current_uri(GTK_RECENT_CHOOSER(chooser)) ;

  if (uri) {

    /** Convert the URI in a filepath. **/
    gchar *filepath = g_filename_from_uri(uri, NULL, NULL) ;

    /** Storing last opened file folder. **/
    if (open_file_dirname != NULL) {
      free(open_file_dirname) ;
    }

    open_file_dirname = g_strdup_printf("%s", (char *) g_path_get_dirname(filepath)) ;

    /** Every file has an associated File_Editor structure which hold the Scrolled Window, TextView and GtkSourceBuffer. **/
    File_Editor *file_editor = g_malloc0(sizeof(File_Editor)) ;

    /** Add file content to the editor has an new notebook page. @NOTE: this function does more than the initalisation work, take a look at it. **/
    add_file_to_editor(gui->editor_notebook, file_editor , filepath, false) ;

    /** Setting the filepath text in the bottom bar. **/
    gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), g_path_get_basename(filepath)) ;

    g_free(uri) ;
  }

  return ;

}

void save_as_file(GtkButton *button) {
  /** Save the current editor content as the choosen file. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif





  GtkWidget *file_chooser = gtk_file_chooser_dialog_new("Save as file",
                                                        NULL,
                                                        GTK_FILE_CHOOSER_ACTION_SAVE,
                                                        "Cancel",  GTK_RESPONSE_CANCEL,
                                                        "Save as", GTK_RESPONSE_ACCEPT,
                                                        NULL) ;


  /** Retrieve the stored filepath: **/
  gpointer stored_filepath = g_object_get_data(G_OBJECT(current_editor.current_buffer), "filepath") ;

  /** Storing last opened file folder. **/
  if (open_file_dirname != NULL) {
    g_free(open_file_dirname) ;
  }
  open_file_dirname = g_strdup_printf("%s", (char *) g_path_get_dirname(stored_filepath)) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser), open_file_dirname );

  gint res;

  GtkFileChooser *chooser;
  chooser = GTK_FILE_CHOOSER(file_chooser);


  gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

  res = gtk_dialog_run(GTK_DIALOG(file_chooser)) ;

  if (res == GTK_RESPONSE_ACCEPT) {

    char *filepath ;
    filepath = gtk_file_chooser_get_filename(chooser);

    /** Getting current editor content **/
    GtkTextIter iter_start, iter_end  ;
    GError *error = NULL              ;

    gtk_text_buffer_get_start_iter(current_editor.current_buffer, &iter_start);
    gtk_text_buffer_get_end_iter(current_editor.current_buffer,   &iter_end);

    gchar *file_content = gtk_text_buffer_get_text(current_editor.current_buffer, &iter_start, &iter_end, FALSE) ;


    if (! g_file_set_contents(filepath, file_content, -1, &error) ) {
      /** Failed to save editor content as file, display an error message and return. **/

      char *msg = g_strdup_printf("Failed to save file:\n%s", filepath) ;

      display_message_dialog("Cannot save file !!!", msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

      free(msg) ;

      return ;

    }

    /** Mark the TextBuffer as not modfied. **/
    gtk_text_buffer_set_modified(current_editor.current_buffer, FALSE) ;

    /** Only useful if the content type has changed like a new file saved as a *.c file. **/
    GtkSourceLanguage        *source_language         = NULL ;
    GtkSourceLanguageManager *source_language_manager = gtk_source_language_manager_get_default();

    gboolean result_uncertain ;
    gchar *content_type ;

    content_type = g_content_type_guess( g_path_get_basename(filepath), (const guchar *) file_content, strlen(file_content), &result_uncertain) ;

    if (content_type && source_language_manager) {

      source_language = gtk_source_language_manager_guess_language(source_language_manager, g_path_get_basename(filepath), content_type);

      if (source_language) {

        set_syntax_highlight_radio(gtk_source_language_get_id(source_language)) ;

        gtk_source_buffer_set_language(GTK_SOURCE_BUFFER(current_editor.current_buffer), source_language) ;

        g_object_set_data(G_OBJECT(current_editor.current_textview), "lang_id", (char *) gtk_source_language_get_id(source_language)) ;
      }

      g_free(content_type) ;
    }



    /** Update the notebook label tab **/
    GtkWidget *notebook_tab = gtk_notebook_get_tab_label(GTK_NOTEBOOK(gui->editor_notebook), current_editor.current_notebook_page);

    /** The tab contains an mimetype icon, the filename and the page closing button. **/
    GList *tab_compound_list = gtk_container_get_children(GTK_CONTAINER(notebook_tab)) ;

    tab_compound_list = g_list_first(tab_compound_list) ;

    while (tab_compound_list->data != NULL) {
        /** We iterate over the notebook tab component **/
        if  (g_object_get_data(G_OBJECT(tab_compound_list->data), "tab_filename_widget")) {
          /** Set the new filename in the tab. **/
          gtk_label_set_text(GTK_LABEL(tab_compound_list->data), g_path_get_basename(filepath)) ;
        }

        if  (g_object_get_data(G_OBJECT(tab_compound_list->data), "tab_icon") && source_language) {


          uint8_t c ;
          for ( c=0 ; ; c++) {
            
              if (gtk_source_language_get_mime_types(source_language) == NULL) {
             
                break ;
              }
            
              char *mimetype = gtk_source_language_get_mime_types(source_language)[c] ;

              if (mimetype == NULL) {
                  /** don't find an specific mimetype for this new file extension use default icon. **/
                  g_object_set(G_OBJECT(tab_compound_list->data),"file", PATH_TO_MIMETYPE_ICON "unknown.png", NULL) ;
                  break ;
              }

              /** We search for an image filename ending with the corresponding mimetype: **/
              char *ptr = strchr(mimetype, '/') ;

              if (ptr != NULL) {

                /** Simply pointer arithmetic to exchange the '/' (used in mimetypes) and the '-' (used in the images names) character **/
                mimetype[ptr - mimetype] = '-' ;


                gchar *filepath = g_strdup_printf("%s%s.png", PATH_TO_MIMETYPE_ICON, mimetype) ;

                if ( g_file_test(filepath, G_FILE_TEST_EXISTS) ) {
                  /** We found an corresponding image for this mimetype. **/
                  g_object_set(G_OBJECT(tab_compound_list->data),"file", filepath, NULL) ;
                  free(filepath) ;
                  break ;
                }

                free(filepath) ;

              }

          }
        }

        if (tab_compound_list->next == NULL) {
          break ;
        }

        tab_compound_list = tab_compound_list->next ;
    }

    g_free(file_content)   ;

    /** Storing filepath for further saving operations. **/
    g_object_set_data(G_OBJECT(current_editor.current_buffer), "filepath", filepath) ;

    /** setting the base filename in the bottom bar. **/
    gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), g_path_get_basename(filepath)) ;


    if (settings.rm_trailing_spaces) {
      /** Deleting trailing spaces. **/
      char *trailing_spaces_deleting ;
      trailing_spaces_deleting = g_strdup_printf("sed -i 's/[[:space:]]$//' '%s'", (char *) filepath) ;
      int ret ;
      if ((ret = system(trailing_spaces_deleting)) == -1) {
        g_warning("Removing trailing space failure:\n%s\n", trailing_spaces_deleting) ;
      }

      free(trailing_spaces_deleting) ;
    }

    #ifdef RELOADING_FUNC
    /** Update Last modification timestamp. **/
    File_Editor *file_editor = (File_Editor *) g_object_get_data(G_OBJECT(current_editor.current_textview), "file_editor") ;
    g_stat(filepath, &file_editor->file_info) ;
    #endif


  }

  /** @NOTE: the filepath must not be free because it is set as data from the file_editor->buffer for further use. **/

  gtk_widget_destroy(file_chooser);
}

void save_file(GtkButton *button) {
  /** Save editor content as the stored filename. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  /** Retrieve the stored filepath: **/
  gpointer filepath = g_object_get_data(G_OBJECT(current_editor.current_buffer), "filepath") ;

  char *cmp_filepath = g_strdup_printf("%s/New", (char *) g_get_home_dir()) ;
  if ( g_strcmp0(filepath,cmp_filepath) == 0) {
    /** File is the start file **/

    free(cmp_filepath) ;
    save_as_file(NULL) ;
    return ;
  }

  free(cmp_filepath) ;


  /** Getting current editor content **/
  GtkTextIter iter_start, iter_end ;
  GError *error=NULL               ;

  gtk_text_buffer_get_start_iter(current_editor.current_buffer,&iter_start);
  gtk_text_buffer_get_end_iter(current_editor.current_buffer,&iter_end);

  gchar *file_content = gtk_text_buffer_get_text(current_editor.current_buffer, &iter_start, &iter_end, FALSE);


  char *back_up_filepath = NULL ;

  if (settings.backup_file) {
    /** backup creation by renaming the ancient (last saved) file (content) by adding an '~' the backup files suffix. **/

    back_up_filepath = g_strdup_printf("%s~",(char *) filepath) ;
    rename(filepath,back_up_filepath) ;

  }

  if ( ! g_file_set_contents(filepath, file_content, -1, &error) ) {
    /** Failed to save editor content as file, display an error message and return. **/


    rename(back_up_filepath, filepath) ; /** We must reset the renaming because else we lost the correct filename in this error case. **/
    free(back_up_filepath) ;

    char *msg = g_strdup_printf("Failed to save file:\n%s", (gchar *) filepath) ;

    display_message_dialog("Cannot save file !!!", msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    free(msg) ;

    return ;
  }

  free(back_up_filepath) ;


  /** Update the notebook label tab **/
  GtkWidget *notebook_tab = gtk_notebook_get_tab_label(GTK_NOTEBOOK(gui->editor_notebook), current_editor.current_notebook_page);

  /** The tab contains an mimetype icon, the filename and the page closing button. **/
  GList *tab_compound_list = gtk_container_get_children(GTK_CONTAINER(notebook_tab)) ;

  tab_compound_list = g_list_first(tab_compound_list) ;

  while (tab_compound_list->data != NULL) {
      /** We iterate over the notebook tab component to find the filename label.**/

      if  (g_object_get_data(G_OBJECT(tab_compound_list->data), "tab_filename_widget")) {
        /** We reset the filename without the asterix ('*'). **/
        gtk_label_set_text(GTK_LABEL(tab_compound_list->data), g_path_get_basename(filepath)) ;
        break ;
      }

      tab_compound_list = tab_compound_list->next ;
  }


  /** We mark the TextBuffer as not modified since last saving operation. **/
  gtk_text_buffer_set_modified(current_editor.current_buffer, FALSE) ;


  /** setting the base filename in the bottom bar. **/
  gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), g_path_get_basename(filepath)) ;

  g_free(file_content) ;


  if (settings.rm_trailing_spaces) {
    /** Deleting trailing spaces. **/
    char *trailing_spaces_deleting ;
    trailing_spaces_deleting = g_strdup_printf("sed -i 's/[[:space:]]$//' '%s'", (char *) filepath) ;
    int ret ;
    if ((ret = system(trailing_spaces_deleting)) == -1) {
      g_warning("Removing trailing space failure:\n%s\n", trailing_spaces_deleting) ;
    }
    free(trailing_spaces_deleting) ;
  }

  #ifdef RELOADING_FUNC
  /** Update Last modification timestamp. **/
  File_Editor *file_editor = (File_Editor *) g_object_get_data(G_OBJECT(current_editor.current_textview), "file_editor") ;
  g_stat(filepath, &file_editor->file_info) ;
  #endif

  return ;

}

void save_all_file(GtkWidget *button, gpointer user_data) {
  /** All files saving callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gint number_of_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) ;

  int c ;
  for (c=0 ; c < number_of_pages ; c++) {
    /** We iterate over every notebook page. **/

    GtkWidget *notebook_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), c) ;
    GtkWidget *notebook_tab  = gtk_notebook_get_tab_label(GTK_NOTEBOOK(gui->editor_notebook), notebook_page);

    /** The tab contains an mimetype icon, the filename and the page closing button. **/
    GList *tab_compound_list = gtk_container_get_children(GTK_CONTAINER(notebook_tab)) ;

    tab_compound_list = g_list_first(tab_compound_list) ;

    while (tab_compound_list->data != NULL) {

      if  (g_object_get_data(G_OBJECT(tab_compound_list->data), "tab_filename_widget")) {
        /** We get the filename tab label. **/

        const char *tab_label = gtk_label_get_text(GTK_LABEL(tab_compound_list->data)) ;

        if (tab_label[0] == '*' && g_strcmp0(tab_label,"*New") != 0) {
          /** Check if the file is modified (marked with an'*') and is not the default "New" named file. **/

          GtkWidget     *current_textview        = gtk_bin_get_child(GTK_BIN(notebook_page)) ;
          GtkTextBuffer *current_buffer          = gtk_text_view_get_buffer(GTK_TEXT_VIEW(current_textview)) ;

          gpointer filepath = g_object_get_data(G_OBJECT(current_buffer), "filepath") ;

          if (filepath != NULL) {

            /** Getting current editor content **/
            GtkTextIter iter_start, iter_end ;
            GError *error=NULL               ;

            gtk_text_buffer_get_start_iter(current_buffer, &iter_start);
            gtk_text_buffer_get_end_iter(current_buffer,   &iter_end);

            gchar *file_content = gtk_text_buffer_get_text(current_buffer, &iter_start, &iter_end, FALSE);

            char *back_up_filepath = NULL ;

            if (settings.backup_file) {
              /** backup creation by renaming the ancient (last saved) file (content) by adding an '~' the backup files suffix. **/

              back_up_filepath = g_strdup_printf("%s~", (char *) filepath) ;
              rename(filepath,back_up_filepath) ;

            }

            if ( ! g_file_set_contents(filepath, file_content, -1, &error) ) {
                /** The content saving has failed **/
                rename(back_up_filepath, filepath) ; /** We must reset the renaming because else we lost the correct filename in this error case. **/
          
                char *msg = g_strdup_printf("Failed to save file:\n%s", (gchar *) filepath) ;
          
                display_message_dialog("Cannot save file !!!", msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;
          
                free(msg) ;
          
            }

            g_free(file_content)   ;
            g_free(back_up_filepath) ;

            /** setting the base filename in the bottom bar. **/
            gtk_label_set_text(GTK_LABEL(tab_compound_list->data), g_path_get_basename(filepath)) ;

            /** We mark the TextBuffer as not modified since last saving operation. **/
            gtk_text_buffer_set_modified(current_buffer, FALSE) ;

            if (settings.rm_trailing_spaces) {
              /** Deleting trailing spaces. **/

              char *trailing_spaces_deleting ;
              trailing_spaces_deleting = g_strdup_printf("sed -i 's/[[:space:]]$//' '%s'", (char *) filepath) ;
              int ret ;
              if ((ret = system(trailing_spaces_deleting)) == -1) {
                g_warning("Removing trailing space failure:\n%s\n", trailing_spaces_deleting) ;
              }
              free(trailing_spaces_deleting) ;
            }
  
            #ifdef RELOADING_FUNC
            /** Update Last modification timestamp. **/
            File_Editor *file_editor = (File_Editor *) g_object_get_data(G_OBJECT(current_textview), "file_editor") ;
            g_stat(filepath, &file_editor->file_info) ;
            #endif
  
          }
        }
        break ;
      }

      tab_compound_list = tab_compound_list->next ;
    }


  }

  return ;
}


void new_file(GtkWidget *button, gpointer user_data) {
  /** New file callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  /** Every file has an associated File_Editor structure which hold the Scrolled Window, TextView and GtkSourceBuffer. **/
  File_Editor *file_editor = g_malloc0(sizeof(File_Editor)) ;

  /** Add file content to the editor has an new notebook page. @NOTE: this function does more than the initalisation work, take a look at it. **/
  add_file_to_editor(gui->editor_notebook, file_editor , NULL, true) ;

  /** Setting the filepath text in the bottom bar. **/
  gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), "New") ;

  /** Set the settings->Syntax highlight menu item on text value. **/
  set_syntax_highlight_radio("text") ;
}

void reloading_file(GtkWidget *widget, gpointer user_data) {

  if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) <= 0) {

    return ;
  }

  /** Retrieve the stored filepath: **/
  gpointer filepath = g_object_get_data(G_OBJECT(current_editor.current_buffer), "filepath") ;

  reload_file(GTK_SOURCE_BUFFER(current_editor.current_buffer), filepath) ;

  /** We mark the TextBuffer as not modified. **/
  gtk_text_buffer_set_modified(current_editor.current_buffer, FALSE) ;

}



guint files_not_saved_check(void) {
  /** This function is called by application exit to check is some files still unsaved and reference it at the same time. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  gint number_of_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) ;

  int counter = 0 ;

  int c ;

  for (c=0 ; c < number_of_pages ; c++) {

    GtkWidget *notebook_page        = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), c) ;
    GtkWidget *current_textview     = gtk_bin_get_child(GTK_BIN(notebook_page)) ;
    GtkTextBuffer *current_buffer   = gtk_text_view_get_buffer(GTK_TEXT_VIEW(current_textview)) ;

    if (gtk_text_buffer_get_modified(current_buffer)) {
      /** The editor content has not being saved **/

      struct Unsaved_File *unsaved_file = g_malloc(sizeof(struct Unsaved_File)) ;

      unsaved_file->filepath = g_strdup_printf("%s",(char *) g_object_get_data(G_OBJECT(current_buffer), "filepath")) ;

      unsaved_file->page_number = c ;

      unsaved_files = g_slist_insert(unsaved_files, (gpointer) unsaved_file, -1 ) ;

      counter++ ;
    }

  }

  return counter ;

}