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

#include "editor.h"


void add_file_to_editor(GtkWidget *editor_notebook, File_Editor *file_editor,const char *filepath, bool start) {
  /** This function does all the file loading into the editor work and some other like.
    * +) Test the file mimetype as for the syntax highilight as for displaying the corresponding icon in the notebook tab.
    * +) Store some informations used in the future like the filepath for saving per example.
    */

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  gchar *file_content = NULL ;

  gchar *file_content_to_utf_8 = NULL ;

  gboolean result_uncertain ;

  gchar *content_type = NULL ;

  bool support_source_language = true ;

  GtkSourceLanguage *source_language = NULL ;

  GtkSourceUndoManager *source_undo_manager ;

  GtkSourceLanguageManager *source_language_manager ;

  char *style_id         = NULL ;

  char *style_name       = NULL ;
  char **style_mimetypes = NULL ;
  char **style_globs     = NULL ;


  if ( ! start ) {
    /** Loaded file. **/

    gsize  file_size ;
    GError *error = NULL  ;

    if (! g_file_get_contents(filepath, &file_content, &file_size, &error) ) {
      /** Cannot get file content **/

      /** Display en error message: **/
      display_message_dialog("Cannot open file !!!", error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

      /** Freing the GError pointer **/
      g_error_free(error) ;

      return ;
    }


    if (file_content == NULL) {
      return ;
    }


    bool converto_to_utf_8 = false ;

    if (! g_utf8_validate(file_content, -1, NULL)) {  // TODO: this not work as expected.
      /** File is not UTF-8 encoded. **/

      /** Try to convert file content in UTF-8. **/
      file_content_to_utf_8 = g_locale_to_utf8(file_content, -1, NULL, NULL, &error);

      /** In case the utf-8 transformation succed. **/
      converto_to_utf_8 = true ;

      g_free(file_content) ;


      if (file_content_to_utf_8 == NULL) {
        /** Failed to convert file content in UTF-8, display an error message and return. **/

        display_message_dialog("Cannot open file !!!", error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

        /** Freeing failed utf-8 conversion. **/
        g_free(file_content_to_utf_8) ;

        /** Freing the GError pointer **/
        g_error_free(error) ;

        return ;
      }

    }

    if (converto_to_utf_8) {
      file_content = file_content_to_utf_8 ;
    }


    source_language_manager = gtk_source_language_manager_get_default();

    char *filename_dup = g_strdup_printf("%s", filepath) ;

    while (filename_dup[(int) strlen(filename_dup)-1] == '~') {
      /** Remove backup suffix for filetype autodetection. **/
      filename_dup[(int) strlen(filename_dup)-1] = '\0' ;
    }


    /** Try to guess the file content type. **/
    content_type = g_content_type_guess( g_path_get_basename(filename_dup), NULL, file_size, &result_uncertain);

    if (result_uncertain) {
      g_free(content_type);
      content_type = NULL;
   
      /** Try to guess the file content type. **/
      content_type = g_content_type_guess(NULL, (const guchar *) file_content, file_size, &result_uncertain);
 
      if (result_uncertain) {
   
        g_free (content_type);
        content_type = NULL;
 
      }
 
    }


    if (source_language_manager) {

      /** Try to guess the loaded source file language: **/
      source_language = gtk_source_language_manager_guess_language(source_language_manager, g_path_get_basename(filename_dup), content_type);

      if (source_language != NULL) {


        style_id = (char *) gtk_source_language_get_id(source_language) ; // TODO: Do not remove !

        if (style_id == NULL) {
  
          goto no_style ;
        }

 
        if ((style_name = (char *) gtk_source_language_get_name(source_language)) != NULL) {
          //fprintf(stdout,"source language name       %s\n", style_name) ;
        }


        //fprintf(stdout,"source language id         %s\n", style_id) ;

        if ((style_mimetypes=gtk_source_language_get_mime_types(source_language)) != NULL) {
          //fprintf(stdout,"source language mime-type  %s\n", gtk_source_language_get_mime_types(source_language)[0]) ;
        }
        if ( (style_globs=gtk_source_language_get_globs(source_language)) != NULL) {
          //fprintf(stdout,"source language globs      %s\n", gtk_source_language_get_globs(source_language)[0]) ;
        }
 
 
        /** Settting the menu item from the differents supported language on the right value. **/
        set_syntax_highlight_radio(style_id) ;

      }
      else if (source_language == NULL) {
        /** Language guessing failed. **/

        no_style :

        support_source_language=false ;

        /** Settting the menu item from the differents supported language on the default value. **/
        set_syntax_highlight_radio("text") ;
      }
 
      if (content_type != NULL) {
        g_free(content_type) ;
      }
  
      g_free(filename_dup) ;

    }
  }


  file_editor->scrolled_window=gtk_scrolled_window_new(NULL,NULL);

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(file_editor->scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC) ;



  if ( ! start && support_source_language ) {
    /** file open and source language detected. **/
    file_editor->buffer = gtk_source_buffer_new_with_language(gtk_source_language_manager_get_language(source_language_manager, style_id )) ;
  }
  else {
    /** Default New named file or source language not detected. **/
    GtkTextTagTable *text_tag_table = gtk_text_tag_table_new() ;
    file_editor->buffer = gtk_source_buffer_new(text_tag_table) ;
  }

  file_editor->textview = gtk_source_view_new_with_buffer(file_editor->buffer);

  source_undo_manager = gtk_source_buffer_get_undo_manager(file_editor->buffer) ;

  /** This call is important so that by undoing the user does not return to an empty editor but at the loaded file begin state.  **/
  gtk_source_undo_manager_begin_not_undoable_action(source_undo_manager);

  if ( ! start ) {
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(file_editor->buffer), file_content, -1) ;
    g_free(file_content) ;
  }
  else {
    /** Start file **/
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(file_editor->buffer), "",           -1) ;
  }

  /** Mark the buffer as not modified for asterix indication displaying. **/
  gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(file_editor->buffer), FALSE) ;


  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(file_editor->textview), TRUE);

  GtkTextIter start_iter ;
  gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(file_editor->buffer), &start_iter);
  gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(file_editor->buffer),   &start_iter);

  /** End of undoable action. **/
  gtk_source_undo_manager_end_not_undoable_action(source_undo_manager);

  gtk_text_view_set_left_margin(GTK_TEXT_VIEW(file_editor->textview), 10) ;


  gtk_container_add(GTK_CONTAINER(file_editor->scrolled_window),file_editor->textview) ;


  GtkWidget *tab_hbox   ;  /** Notebook tab container. **/
  GtkWidget *tab_icon   ;  /** Add an filetype icon.   **/
  GtkWidget *tab_label  ;  /** Filename label.         **/
  GtkWidget *tab_pad    ;  /** Padding label.          **/
  GtkWidget *tab_button ;  /** Close button.           **/
  GtkWidget *tab_image  ;  /** Close button image.     **/

  tab_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0) ;

  tab_pad = gtk_label_new("  ") ;

  tab_button = gtk_button_new() ;
  gtk_button_set_always_show_image(GTK_BUTTON(tab_button), TRUE);
  gtk_button_set_relief(GTK_BUTTON(tab_button),GTK_RELIEF_NONE) ;

  tab_image = gtk_image_new_from_file(PATH_TO_MENU_ICON "window-close.png") ;
  gtk_button_set_image(GTK_BUTTON(tab_button),tab_image) ;

  if ( ! start ) {
    /** Loaded file. **/

   /** Setting filename as notebook tab content and setting the language corresponding image on tab. **/

   if (support_source_language) {


    /** Store the source file language. **/
    g_object_set_data(G_OBJECT(file_editor->textview), "lang_id", (char *) gtk_source_language_get_id(source_language)) ;

    uint16_t c ;

    if (style_mimetypes == NULL) {

      goto unavailable_mimetypes ;
    }

    for (c=0 ; ; c++) {
        /** Try to find an icon for the source file language. **/

        char *mimetype = style_mimetypes[c] ;

        if (mimetype == NULL) {
          /** Default filetype icon. **/
          tab_icon = gtk_image_new_from_file(PATH_TO_MIMETYPE_ICON "unknown.png") ;
          break ;
        }

        char *ptr = strchr(mimetype, '/') ;

        if (ptr != NULL) {

          /** Simple pointer arithmetic '/' replacement to '-'. **/
          mimetype[ptr - mimetype] = '-' ;

          char *filepath = g_strdup_printf("%s/%s.png", PATH_TO_MIMETYPE_ICON, mimetype) ;

          /** Try if the mimetype coresponding icon is present in the icon set. **/
          if ( g_file_test(filepath, G_FILE_TEST_EXISTS) ) {
            /** Setting filetype icon. **/
            tab_icon = gtk_image_new_from_file(filepath) ;
            free(filepath) ;
            break ;
          }

          free(filepath) ;

        }

    }

   }
   else {

     unavailable_mimetypes :

     /** Default filetype icon. **/
     tab_icon = gtk_image_new_from_file(PATH_TO_MIMETYPE_ICON "unknown.png") ;
     /** Store the source file language. **/
     g_object_set_data(G_OBJECT(file_editor->textview), "lang_id", "text") ;
   }

   if (style_mimetypes != NULL) {
     g_strfreev(style_mimetypes) ;
   }

   tab_label = gtk_label_new(g_path_get_basename(filepath)) ;

  }
  else {
    /** Default New named file. **/
    tab_icon  = gtk_image_new_from_file(PATH_TO_MIMETYPE_ICON "unknown.png") ;
    tab_label = gtk_label_new("New") ;
    g_object_set_data(G_OBJECT(file_editor->textview), "lang_id", "text") ;
  }

  g_object_set_data(G_OBJECT(file_editor->buffer), "tab_label", tab_label) ;

  /** String set as data to retrieve the tab_label wenn we get the tab childs list used as boolean. **/
  g_object_set_data(G_OBJECT(tab_label), "tab_filename_widget", "tab") ;

  gtk_box_pack_start(GTK_BOX(tab_hbox),tab_icon,   TRUE,  TRUE,  4) ;
  gtk_box_pack_start(GTK_BOX(tab_hbox),tab_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(tab_hbox),tab_pad,    TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(tab_hbox),tab_button, TRUE,  TRUE,  0) ;

  gtk_widget_show_all(tab_hbox) ;


  gtk_widget_set_can_focus(file_editor->textview, TRUE);

  #ifdef RELOADING_FUNC
  file_editor->must_reload = FALSE ;
  file_editor->timeout_return = TRUE ;
  #endif

  if (! start) {
    /** Loaded file. **/

    /** Storing filepath for saving it, will be free by closing file. **/
    g_object_set_data(G_OBJECT(file_editor->buffer), "filepath", (char *) filepath) ;
    /** Set the base filename in the bottom bar. **/
    gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), g_path_get_basename(filepath)) ;

    #ifdef RELOADING_FUNC
    /** Add a timeout for checking about file informations for reload file if change by other process. **/
    g_stat(filepath, &file_editor->file_info) ;
    g_timeout_add(999, (GSourceFunc) check_file_has_change, file_editor) ;
    #endif
  }
  else {
    /** The default New named file. **/

    /** Storing filepath for saving it, will be free by closing file. **/
    g_object_set_data(G_OBJECT(file_editor->buffer), "filepath", g_strdup_printf("%s/New",g_get_home_dir()) ) ;
    /** Set the base filename in the bottom bar. **/
    gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), "New") ;


    #ifdef RELOADING_FUNC
    /** Stub file for timeout convienence and for file stats correctness. **/
    gchar *tmp_filepath ;
    gint fd = g_file_open_tmp("New_XXXXXX", &tmp_filepath, NULL) ;
    g_chmod(tmp_filepath, 0644);
    g_stat(tmp_filepath, &file_editor->file_info) ;
    g_close(fd, NULL)    ;
    g_free(tmp_filepath) ;
    /** Add a timeout for checking about file informations for reload file if change by other process. **/
    g_timeout_add(999, (GSourceFunc) check_file_has_change, file_editor) ;
    #endif
  }

  gtk_source_buffer_set_max_undo_levels(file_editor->buffer, -1);


  GtkSourceStyleSchemeManager *style_scheme_manager = gtk_source_style_scheme_manager_get_default() ;

  /** The application does not use the default schemes files but the latest version schemes (which are numerous). **/
  gtk_source_style_scheme_manager_append_search_path(style_scheme_manager, PATH_TO_SCHEME) ;

  GtkSourceStyleScheme *style_scheme = gtk_source_style_scheme_manager_get_scheme(style_scheme_manager, settings.scheme_default)  ;


  gtk_source_buffer_set_style_scheme(file_editor->buffer, style_scheme) ;




  GtkSourceCompletion *source_completion = gtk_source_view_get_completion(GTK_SOURCE_VIEW(file_editor->textview)) ;

  GtkSourceCompletionWords *source_completion_words = gtk_source_completion_words_new("completion", NULL) ;

  gtk_source_completion_words_register(source_completion_words, GTK_TEXT_BUFFER(file_editor->buffer)) ;

  GError *error = NULL ;

  gtk_source_completion_add_provider(source_completion,GTK_SOURCE_COMPLETION_PROVIDER(source_completion_words), &error) ;

  g_object_set(G_OBJECT(source_completion_words),"scan-batch-size", gtk_text_buffer_get_line_count(GTK_TEXT_BUFFER(file_editor->buffer)), NULL ) ;

  g_object_set(G_OBJECT(source_completion_words), "minimum-word-size", 3, NULL) ;

  g_object_set(G_OBJECT(source_completion), "show-headers", FALSE, NULL ) ;


  setting_sourceview_settings(GTK_SOURCE_VIEW(file_editor->textview)) ;

  Highlight_Selection *highlight_textview_selection = g_malloc(sizeof(Highlight_Selection)) ;

  /** Setting up settings highlight for selection matches. **/
  highlight_textview_selection->source_search_settings = gtk_source_search_settings_new() ;

  gtk_source_search_settings_set_at_word_boundaries(highlight_textview_selection->source_search_settings, TRUE) ;
  gtk_source_search_settings_set_case_sensitive(highlight_textview_selection->source_search_settings,     TRUE) ;

  /** Setting up source context. **/
  highlight_textview_selection->source_search_highlight_context = gtk_source_search_context_new(GTK_SOURCE_BUFFER(file_editor->buffer), highlight_textview_selection->source_search_settings);

  g_object_set_data(G_OBJECT(file_editor->textview), "highlight_textview_selection", highlight_textview_selection) ;

  GtkSourceSearchContext  *source_search_steps_context      = gtk_source_search_context_new(GTK_SOURCE_BUFFER(file_editor->buffer), searching.source_search_settings );
  GtkSourceSearchContext  *source_search_highlight_context  = gtk_source_search_context_new(GTK_SOURCE_BUFFER(file_editor->buffer), searching.source_search_settings );

  g_object_set_data(G_OBJECT(file_editor->textview), "source_search_steps_context",     source_search_steps_context) ;
  g_object_set_data(G_OBJECT(file_editor->textview), "source_search_highlight_context", source_search_highlight_context) ;


  gint *ret=malloc(sizeof(gint)) ; /** Will be free wenn closing file **/
  *ret = gtk_notebook_append_page(GTK_NOTEBOOK(editor_notebook), file_editor->scrolled_window, tab_hbox);

  /** Update current notebook page editor. **/
  current_editor.current_notebook_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook),  *ret) ;
  current_editor.current_textview      = gtk_bin_get_child(GTK_BIN(current_editor.current_notebook_page)) ;
  current_editor.current_buffer        = gtk_text_view_get_buffer(GTK_TEXT_VIEW(current_editor.current_textview)) ;

  g_object_set_data(G_OBJECT(tab_button),            "page_number", ret) ;
  g_object_set_data(G_OBJECT(tab_icon),              "tab_icon", "  tab") ;
  g_object_set_data(G_OBJECT(file_editor->textview), "file_editor", file_editor) ;


  /** Connecting signals: **/

  /** Auto-completion updating every buffer content change. **/
  g_signal_connect(G_OBJECT(file_editor->buffer),   "changed", G_CALLBACK(update_completion), file_editor->textview) ;

  /** Update the bottom bar displayed informations everytime an event occurs: very often. **/
  g_signal_connect(G_OBJECT(file_editor->textview), "event-after", G_CALLBACK(update_rows_cols_info), NULL) ;

  /** Update the asterix indication in the filename tab component. **/
  g_signal_connect(G_OBJECT(file_editor->buffer),   "modified-changed", G_CALLBACK(textbuffer_changed_modified), tab_label)  ;
  g_signal_connect(G_OBJECT(file_editor->buffer),   "modified-changed", G_CALLBACK(textbuffer_changed_modified), tab_label)  ;

  /** Buttons event. **/
  g_signal_connect(G_OBJECT(file_editor->textview), "button-press-event",   G_CALLBACK(textview_button_press_event),   NULL)  ;
  g_signal_connect(G_OBJECT(file_editor->textview), "button-release-event", G_CALLBACK(textview_button_release_event), NULL)  ;

  /** Close page by click on the button included in the tab. **/
  g_signal_connect(G_OBJECT(tab_button), "clicked", G_CALLBACK(close_page), NULL) ;

  /** Page reorder callback: we update the "page_number" data from tab_button. **/
  g_signal_connect(G_OBJECT(editor_notebook), "page-reordered", G_CALLBACK(page_reorder), NULL) ;


  gtk_widget_show_all(file_editor->scrolled_window);

  gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(editor_notebook), file_editor->scrolled_window, TRUE) ;

  gtk_notebook_set_menu_label_text(GTK_NOTEBOOK(editor_notebook), file_editor->scrolled_window, g_path_get_basename( (gchar *) g_object_get_data(G_OBJECT(file_editor->buffer), "filepath")) ) ;

  gtk_notebook_set_current_page(GTK_NOTEBOOK(editor_notebook), *ret) ;

  gtk_widget_grab_focus(file_editor->textview) ;

  return ;

}

void reload_file(GtkSourceBuffer *buffer, const char *filepath) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  gsize  file_size ;
  GError *error = NULL  ;

  gchar *file_content = NULL ;

  gchar *file_content_to_utf_8 = NULL ;

  if (! g_file_get_contents(filepath, &file_content, &file_size, &error) ) {
    /** Cannot get file content **/

    /** Display en error message: **/
    display_message_dialog("Cannot open file !!!", error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    /** Freing the GError pointer **/
    g_error_free(error) ;

    return ;
  }

  if (file_content == NULL) {
    return ;
  }

  bool converto_to_utf_8 = false ;

  if (! g_utf8_validate(file_content, -1, NULL)) {  // TODO: this not work as expected.
    /** File is not UTF-8 encoded. **/

    /** Try to convert file content in UTF-8. **/
    file_content_to_utf_8 = g_locale_to_utf8(file_content, -1, NULL, NULL, &error);

    /** In case the utf-8 transformation succed. **/
    converto_to_utf_8 = true ;

    g_free(file_content) ;


    if (file_content_to_utf_8 == NULL) {
      /** Failed to convert file content in UTF-8, display an error message and return. **/

      display_message_dialog("Cannot open file !!!", error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

      /** Freeing failed utf-8 conversion. **/
      g_free(file_content_to_utf_8) ;

      /** Freing the GError pointer **/
      g_error_free(error) ;

      return ;
    }

  }

  if (converto_to_utf_8) {
    file_content = file_content_to_utf_8 ;
  }

  GtkTextIter start_iter ;
  GtkTextIter end_iter   ;



  gtk_source_buffer_begin_not_undoable_action(buffer) ;

  gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start_iter) ;
       
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end_iter) ;     

  gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer), &start_iter, &end_iter) ;

  gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), file_content, -1) ;

  gtk_source_buffer_end_not_undoable_action(buffer) ;

  GtkWidget *tab_label = g_object_get_data(G_OBJECT(buffer), "tab_label") ;

  gtk_label_set_text(GTK_LABEL(tab_label), g_path_get_basename(filepath)) ;

  return ;

}

void remove_terminal_tabs(GtkWidget *widget, GtkWidget *user_data) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->terminal_notebook)) == 1) {
    return ;
  }



  Terminals *terminals = g_object_get_data(G_OBJECT(user_data), "terminals") ;

  free(terminals) ;

  gtk_notebook_remove_page(GTK_NOTEBOOK(gui->terminal_notebook), gtk_notebook_page_num(GTK_NOTEBOOK(gui->terminal_notebook), user_data) ) ;

  return ;

}

void set_new_terminals(GtkWidget *terminals_notebook) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Hard GUI coded terminals: **/
  Terminals *terminals  = g_malloc0(sizeof(Terminals)) ;

  terminals->terminal_1 = g_slice_new(Terminal) ;
  terminals->terminal_2 = g_slice_new(Terminal) ;

  initialize_terminal(terminals->terminal_1) ;
  initialize_terminal(terminals->terminal_2) ;

  setup_terminal(terminals->terminal_1->terminal) ;
  setup_terminal(terminals->terminal_2->terminal) ;

  /** So that the hard coded terminals can not only be show|hidden but resize too verticaly. **/
  terminals->terminals_vertical_paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL) ;

  gtk_paned_pack1(GTK_PANED(terminals->terminals_vertical_paned), terminals->terminal_1->terminal_hbox, TRUE, TRUE);
  gtk_paned_pack2(GTK_PANED(terminals->terminals_vertical_paned), terminals->terminal_2->terminal_hbox, TRUE, TRUE);



  /** Hard GUI coded terminals notebook container tab. **/
  GtkWidget *terminal_header_hbox          = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;
  GtkWidget *terminal_header_button        = gtk_button_new() ;
  GtkWidget *terminal_header_image         = gtk_image_new_from_file(PATH_TO_MENU_ICON "utilities-terminal.png") ;
  GtkWidget *terminal_header_label         = gtk_label_new(" Terminals ") ;
  GtkWidget *terminal_header_close_button  = gtk_button_new() ;
  GtkWidget *terminal_header_close_image   = gtk_image_new_from_file(PATH_TO_MENU_ICON "window-close.png") ;


  gtk_button_set_image(GTK_BUTTON(terminal_header_button), terminal_header_image) ;

  gtk_button_set_image(GTK_BUTTON(terminal_header_close_button), terminal_header_close_image) ;

  gtk_box_pack_start(GTK_BOX(terminal_header_hbox),terminal_header_button,        FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_header_hbox),terminal_header_label,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_header_hbox),terminal_header_close_button,  FALSE, FALSE, 0) ;
  gtk_widget_show_all(terminal_header_hbox) ;



  /** Unique first page of the terminal notebook: if the terminals are included in an notebook we can add new pages. **/
  gint *ret=malloc(sizeof(gint)) ;
  *ret = gtk_notebook_append_page(GTK_NOTEBOOK(terminals_notebook), terminals->terminals_vertical_paned, terminal_header_hbox) ;

  if (*ret > 0) {
    gtk_widget_show_all(terminals->terminals_vertical_paned) ;
  }

  /** Store the notebook page. **/
  g_object_set_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(terminals_notebook), *ret)), "terminals", terminals) ;

  g_signal_connect(G_OBJECT(terminal_header_close_button), "clicked", G_CALLBACK(remove_terminal_tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK(terminals_notebook), *ret) ) ;


  gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(terminals_notebook), terminals->terminals_vertical_paned, TRUE) ;

  char *tab_text = g_strdup_printf("Terminals %d",(*ret)+1) ;

  gtk_notebook_set_menu_label_text(GTK_NOTEBOOK(terminals_notebook), terminals->terminals_vertical_paned,  tab_text) ;

  free(tab_text) ;

  gtk_notebook_set_current_page(GTK_NOTEBOOK(terminals_notebook), *ret) ;

  gtk_widget_grab_focus(terminals->terminal_1->terminal) ;

  return ;

}