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

#include "search_settings_callbacks.h"

#include "../GUI/dialogs/message_dialog.h"

#include "../Headers/defines.h"

#ifdef DEBUG
  #include "../DEBUG/debug_search_by_signals.h"
#endif

void set_search_settings_default(Search_Settings *search_settings) {
  /** Set default search settings. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  search_settings->case_sensitive = FALSE    ;

  search_settings->wrap_around    = FALSE    ;

  search_settings->mode           = RAW_TEXT ;

  return ;
}

void remove_searching_tag(void) {
  /** Removing the occurence highlighting tag. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  searching.search_tag = (GtkTextTag *) g_object_get_data(G_OBJECT(current_editor.current_buffer), "Tag_highlight_search") ;

  if (searching.search_tag != NULL) {

      GtkTextIter start_iter, end_iter ;

      gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer), &start_iter) ;

      gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(current_editor.current_buffer),   &end_iter) ;

      gtk_text_buffer_remove_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), searching.search_tag, &start_iter, &end_iter);

      searching.search_tag = NULL ;

  }

  return ;

}

void set_search_mode(GtkComboBox *widget, gpointer user_data) {
  /** Set search mode settings. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  search_settings->mode = gtk_combo_box_get_active(widget) ;

  switch (search_settings->mode) {

    case 0 :
      /** RAW_TEXT **/
      gtk_source_search_settings_set_at_word_boundaries(searching.source_search_settings, FALSE) ;
      gtk_source_search_settings_set_regex_enabled(searching.source_search_settings,      FALSE) ;

      gtk_source_search_context_set_settings(searching.source_search_steps_context, searching.source_search_settings);
      break ;

    case 1 :
      /** WORD BOUNDARIES **/
      gtk_source_search_settings_set_at_word_boundaries(searching.source_search_settings, TRUE) ;
      gtk_source_search_settings_set_regex_enabled(searching.source_search_settings,      FALSE) ;

      gtk_source_search_context_set_settings(searching.source_search_steps_context, searching.source_search_settings);
      break ;

    case 2 :
      /** REGEX **/

      gtk_source_search_settings_set_at_word_boundaries(searching.source_search_settings, FALSE) ;
      gtk_source_search_settings_set_regex_enabled(searching.source_search_settings,      TRUE) ;

      gtk_source_search_context_set_settings(searching.source_search_steps_context, searching.source_search_settings);
      break ;

    default :

      break ;

  }

  /** Remove the current occurence highlight Tag if any. **/
  remove_searching_tag() ;

  return ;

}

void set_case_sensitive(GtkToggleButton *togglebutton, gpointer user_data) {

  /** Set if the search should be case-sensitive. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  search_settings->case_sensitive = gtk_toggle_button_get_active(togglebutton) ;

  gtk_source_search_settings_set_case_sensitive(searching.source_search_settings, search_settings->case_sensitive) ;

  gtk_source_search_context_set_settings(searching.source_search_steps_context, searching.source_search_settings);

  /** Remove the current occurence highlight Tag if any. **/
  remove_searching_tag() ;

  return ;

}

void set_wrap_around(GtkToggleButton *togglebutton, gpointer user_data) {

  /** Set if the search should wrap around from end to begin. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  search_settings->wrap_around = gtk_toggle_button_get_active(togglebutton) ;

  gtk_source_search_settings_set_wrap_around(searching.source_search_settings, search_settings->wrap_around) ;

  gtk_source_search_context_set_settings(searching.source_search_steps_context, searching.source_search_settings);

  /** Remove the current occurence highlight Tag if any. **/
  remove_searching_tag() ;

  return ;
}



void reset_search(void) {

  /** Reset search settings: after closing the search and replace bar. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  if (searching.source_search_highlight_context != NULL) {
    gtk_source_search_context_set_highlight(searching.source_search_highlight_context, FALSE) ;
  }

  if (searching.search_tag != NULL) {
    /** Remove the current occurence highlight Tag if any. **/
    remove_searching_tag() ;
  }

  /** Getting search term. **/
  searching.search_text = g_strdup_printf("%s","") ;

  /** Setting search control boolean variables: **/
  searching.only_highlight    = FALSE ;
  searching.complete_search   = FALSE ;
  searching.get_an_occurrence = FALSE ;
  searching.restart_search    = TRUE  ;
  search_history_start        = TRUE  ;

  searching.start_search_offset = 0 ;
  searching.start_match_offset  = 0 ;
  searching.end_match_offset    = 0 ;

  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search, 0) ;
  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_match,  0) ;
  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.end_match,    0) ;

  return ;
}

gboolean search_history_callback(GtkWidget *widget,  GdkEventKey  *event, gpointer   user_data) {

  /** Search history arrow up, arrow down callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif





  if (event->keyval == GDK_KEY_Up) {
    /** Arrow up press: **/

    if (search_history_start) {
      /** We begin from history start. **/
      search_history = g_list_first (search_history) ;

      if (search_history->data != NULL) {
        /** We display the first search history item in the search entry. **/
        gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->search_entry), (char *) search_history->data) ;

        search_history_start=FALSE ;

        return TRUE ; /** We return TRUE to keep the focus by arrows keys pressing. **/
      }
    }
    else {
      /** Move the search history one item next. **/
      if ( search_history->next != NULL) {

        search_history = search_history->next ;
        if (search_history->data != NULL) {
          /** We display the search history item in the search entry. **/
          gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->search_entry), (char *) search_history->data) ;
        }
        return TRUE ; /** We return TRUE to keep the focus by arrows keys pressing. **/
      }
    }

    return TRUE ; /** We return TRUE to keep the focus by arrows keys pressing. **/

  }
  else if (event->keyval == GDK_KEY_Down) {
    /** Arrow down press: **/
    if (search_history_start) {
      /** We begin from history end. **/
      search_history = g_list_last(search_history) ;

      if (search_history->data != NULL) {
          /** We display the search history item in the search entry. **/
          gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->search_entry), (char *) search_history->data) ;
          search_history_start=FALSE ;
          return TRUE ;  /** We return TRUE to keep the focus by arrows keys pressing. **/
      }
    }
    else {
      if ( search_history->prev != NULL) {

        search_history = search_history->prev ;
        if (search_history->data != NULL) {
          /** We display the search history item in the search entry. **/
          gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->search_entry), (char *) search_history->data) ;
          return TRUE ;  /** We return TRUE to keep the focus by arrows keys pressing. **/
        }
      }
    }

    return TRUE ;

  }

  return FALSE ;

}


void get_iter_offset(void) {
  /** Getting the TextIter positions as an offset integer from the begin count in characters. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  searching.start_search_offset = gtk_text_iter_get_offset(&searching.start_search) ;
  searching.start_match_offset  = gtk_text_iter_get_offset(&searching.start_match) ;
  searching.end_match_offset    = gtk_text_iter_get_offset(&searching.end_match) ;

  if (searching.start_search_offset < 0) {
    searching.start_search_offset = 0 ;
  }
  if (searching.start_match_offset < 0) {
    searching.start_match_offset = 0 ;
  }
  if (searching.end_match_offset < 0) {
    searching.end_match_offset = 0 ;
  }

  return ;
}

void get_iter_at_offset(void) {
  /** Assign the TextIter to an position given as an integer representing the offset from Textview Begin in characters. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search, searching.start_search_offset) ;
  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_match,  searching.start_match_offset)  ;
  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.end_match,    searching.end_match_offset)    ;

  return ;

}



void activate_search_accelator(GtkWidget *widget, gpointer user_data) {
  /** The user has selected text and want start a search on the selected text and from current position. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ( gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) <= 0)  {

    return ;
  }


  /** Disable mouse selection occurrences highlight if any **/
  destroy_highlight_selection() ;


  /** disable all highlights forms **/
  disable_all_highlight() ;


  GtkTextIter start ;
  GtkTextIter end ;

  /** Check if an the user has selecting text **/
  gboolean selection = gtk_text_buffer_get_selection_bounds(GTK_TEXT_BUFFER(current_editor.current_buffer), &start, &end) ;

  if (selection) {

    gint start_int = gtk_text_iter_get_offset(&start) ;
    gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search, start_int) ;

  }
  else {

    gint start_int ;

    g_object_get(G_OBJECT(current_editor.current_buffer), "cursor-position", &start_int, NULL) ;

    gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search, start_int) ;
  }





  if (! gtk_widget_get_visible(gui->search_and_replace->search_and_replace_main_vbox) ) {
    /** Show search and replace bar. **/
    gtk_widget_show(gui->search_and_replace->search_and_replace_main_vbox) ;
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->buttons->search_and_replace_button), TRUE);
    gtk_widget_grab_focus(gui->search_and_replace->search_entry) ;
  }
  else if (! selection && gtk_widget_get_visible(gui->search_and_replace->search_and_replace_main_vbox) ) {
    gtk_widget_grab_focus(gui->search_and_replace->search_entry) ;
  }



  if ( selection  || (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(GTK_ENTRY(gui->search_and_replace->search_entry))), "") != 0) ) {

    /** Remove the current occurence highlight Tag if any. **/
    remove_searching_tag() ;

    if (searching.search_text != NULL) {
      g_free(searching.search_text) ;
    }

    if (selection) {
      searching.search_text = g_strdup_printf("%s", gtk_text_iter_get_slice(&start, &end)) ;
    }
    else {
      searching.search_text = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) ;
    }


    if (g_list_find(search_history, searching.search_text) == NULL) {
      /** Add search term to history if this is not yet present in search history. **/
      search_history = g_list_insert(search_history, searching.search_text, 0) ;
    }

    /** Move cursor for disable mouse selected text. @NOTE: this can have side-effect by modifcation like unwanted highlighed character(s).  **/
    gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(current_editor.current_buffer), &start);


    gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->search_entry),  searching.search_text ) ;


    gtk_source_search_settings_set_search_text(searching.source_search_settings, searching.search_text );


    gtk_source_search_context_set_highlight(searching.source_search_steps_context, FALSE) ;



    gboolean search_found = gtk_source_search_context_forward(searching.source_search_steps_context, &searching.start_search, &searching.start_match, &searching.end_match) ;


    if (search_found) {

      /** Construct a tag for highlight selected text which replace the mouse selection normally. **/
      searching.search_tag = gtk_text_buffer_create_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), NULL, "background","#43ace8", "background-full-height", TRUE, "foreground", "#FFFFFF", "weight", PANGO_WEIGHT_NORMAL,  NULL) ;

      g_object_set_data(G_OBJECT(current_editor.current_buffer), "Tag_highlight_search", searching.search_tag) ;

      gtk_text_buffer_apply_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), searching.search_tag, &searching.start_match, &searching.end_match) ;

      /** Setting search control boolean variables: **/
      searching.complete_search   = TRUE  ;
      searching.only_highlight    = FALSE ;
      searching.get_an_occurrence = TRUE  ;
      searching.has_selection     = TRUE  ;
      searching.restart_search    = FALSE ;

      /** Getting TextIter offset: for keeping the TextIter valid !!! **/
      get_iter_offset() ;

    }
    else {

      gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search);
      gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_match);
      gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.end_match);

      /** Getting TextIter offset: for keeping the TextIter valid !!! **/
      get_iter_offset() ;
    }



  }

  return ;

}

void search(GtkButton *button, gpointer user_data) {
  /** User press the Search button: perform a search and highlight all matches. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif







  if ( gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) <= 0)  {

    return ;
  }

  /** Disable mouse selection occurrences highlight if any **/
  destroy_highlight_selection() ;

  if (  g_strcmp0("", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry)) ) != 0 ) {

    if (searching.search_text != NULL) {
      g_free(searching.search_text) ;
    }

    if (g_list_find(search_history, (gchar *) gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry)) ) == NULL) {
      /** Add search term to history if this is not yet present in search history. **/
      search_history = g_list_insert(search_history, g_strdup(gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))), 0) ;
    }


    /** Remove the current occurence highlight Tag if any. **/
    remove_searching_tag() ;


    /** Getting search term. **/
    searching.search_text = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry)) ) ;

    gtk_source_search_settings_set_search_text(searching.source_search_settings, searching.search_text );

    gtk_source_search_context_set_highlight(searching.source_search_highlight_context, TRUE) ;

    gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search);

    /** Move cursor for disable mouse selected text if any selection. @NOTE: this can have side-effect by modifcation like unwanted highlighed character(s).  **/
    gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search) ;

    /** Perform the search: **/
    gboolean search_found = gtk_source_search_context_forward(searching.source_search_highlight_context, &searching.start_search, &searching.start_match, &searching.end_match) ;

    if (search_found) {
      /** The search term was found. **/

      gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW(current_editor.current_textview), &searching.start_match, 0.25, TRUE, 0.5, 0.5) ;

      gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer),&searching.start_search);

      /** Setting search control boolean variables: **/
      searching.only_highlight    = TRUE  ;
      searching.complete_search   = TRUE  ;
      searching.get_an_occurrence = FALSE ;

      /** Getting TextIter offset: for keeping the TextIter valid !!! **/
      get_iter_offset() ;

    }
    else {
      /** Display an error message dialog in case the term is not found. **/

      GtkWidget *not_found_message_dialog = error_message_dialog_not_found("Pattern not found !!!", g_strdup_printf("Pattern:\n\" %s \"\nnot found in file !", searching.search_text)) ;

      g_timeout_add(1750, (GSourceFunc) destroy_message_dialog_not_found, GTK_WIDGET(not_found_message_dialog) );
 
      gtk_widget_show_all(GTK_WIDGET(not_found_message_dialog)) ;


    }



  }

  return ;

}



void search_next(GtkWidget *widget, gpointer user_data) {
  /** User press the search next button, shortcut or hit enter in the search bar. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ( gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) <= 0)  {

    return ;
  }

  /** Disable mouse selection occurrences highlight if any **/
  destroy_highlight_selection() ;

  if ( (g_strcmp0(searching.search_text, gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry)) ) != 0 &&  g_strcmp0("", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) != 0)  || ! searching.complete_search) {
    /** New search because the search term is different from the search entry content. **/

    if (g_list_find(search_history, (gchar *) gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry)) ) == NULL) {
      /** Add search term to history if this is not yet present in search history. **/
      search_history = g_list_insert(search_history, g_strdup(gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))), 0) ;
    }

    if (searching.search_text != NULL) {
      g_free(searching.search_text) ;
    }



    /** Remove the current occurence highlight Tag if any. **/
    remove_searching_tag() ;


    /** Getting search term. **/
    searching.search_text = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) ;

    gtk_source_search_settings_set_search_text(searching.source_search_settings, searching.search_text) ;


    /** disable all highlights forms **/
    disable_all_highlight() ;

  
  
    if (GTK_IS_ENTRY(widget)) {
      /** User press enter in the search bar so we start searching at file start.  **/
 
      /** Getting textview start position iterator. **/
      gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer),&searching.start_search);
    }
    else {
      /** User press the Next button or use the shortcut. **/
   
   
      /** Uncomment to start search at cursor position.  **/
      GtkTextIter start ;
      GtkTextIter end ;

      // Check if an the user has selecting text
      gboolean selection = gtk_text_buffer_get_selection_bounds(GTK_TEXT_BUFFER(current_editor.current_buffer), &start, &end) ;

      if (selection) {
   
         // The search will start at selection.
   
         gint start_int = gtk_text_iter_get_offset(&start) ;
         gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search, start_int) ;

      }
      else {
 
        // The search will start at cursor position.
 
        gint start_int ;

        g_object_get(G_OBJECT(current_editor.current_buffer), "cursor-position", &start_int, NULL) ;

        gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search, start_int) ;
      }
 
    }
 



    /** Perform the search: **/
    gboolean search_found = gtk_source_search_context_forward(searching.source_search_steps_context, &searching.start_search, &searching.start_match, &searching.end_match) ;


    if (search_found) {
      /** The search term was found. **/

      /** Construct a tag for highlight the match. **/
      searching.search_tag = gtk_text_buffer_create_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), NULL, "background","#43ace8", "background-full-height", TRUE, "foreground", "#FFFFFF",    NULL) ;

      g_object_set_data(G_OBJECT(current_editor.current_buffer), "Tag_highlight_search", searching.search_tag) ;

      gtk_text_buffer_apply_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), searching.search_tag, &searching.start_match, &searching.end_match) ;

      gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(current_editor.current_textview), &searching.start_match, 0.25, TRUE, 0.5, 0.5) ;

      /** Move cursor for disable mouse selected text if any selection. @NOTE: this can have side-effect by modifcation like unwanted highlighed character(s).  **/
      gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(current_editor.current_buffer),&searching.start_match) ;

      /** Setting search control boolean variables: **/
      searching.complete_search   = TRUE  ;
      searching.only_highlight    = FALSE ;
      searching.restart_search    = FALSE ;
      searching.get_an_occurrence = TRUE  ;

      /** Getting TextIter offset: for keeping the TextIter valid !!! **/
      get_iter_offset() ;

    } /** Uncomment to display an error message window if no match were found. in find_next.
    else {

      GtkWidget *not_found_message_dialog = error_message_dialog_not_found("Pattern not found !!!", g_strdup_printf("Pattern:\n\" %s \"\nnot found in file !", searching.search_text)) ;

      g_timeout_add(1750, (GSourceFunc) destroy_message_dialog_not_found, GTK_WIDGET(not_found_message_dialog) );
 
      gtk_widget_show_all(GTK_WIDGET(not_found_message_dialog)) ;


    } */

    return ;

  }
  else if ( g_strcmp0(searching.search_text, gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) == 0 && searching.complete_search ) {
    /** We search the next occurrence from the same term: **/

    if ( searching.only_highlight || searching.restart_search ) {
      /** The last search was an occurence highlight search but the term is the same.
        * So we restart from textview start.                                          */

      gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_match);
      gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(current_editor.current_buffer),   &searching.end_match) ;

      /** Remove the current occurence highlight Tag if any. **/
      remove_searching_tag() ;

      searching.only_highlight = FALSE ;
      searching.restart_search = FALSE ;

      searching.start_search=searching.start_match ;

    }
    else {

      /** Setting the TextIter at precedent saved offset: to keep the TextIter valid. **/
      get_iter_at_offset() ;  // This call can maybe be remove if the other is always executed.

      /** We replace the TextIter for searching the next occurrence:  the search will begin at the end from the last match. **/
      searching.start_search=searching.end_match ;

    }


    gtk_source_search_settings_set_search_text(searching.source_search_settings, searching.search_text);

    /** disable all highlights forms **/
    disable_all_highlight() ;

    /** Perform the search from the next occurrence: **/
    gboolean search_found = gtk_source_search_context_forward(searching.source_search_steps_context, &searching.start_search, &searching.start_match, &searching.end_match) ;

    if (search_found) {
      /** The search term was found. **/

      /** Remove the current occurence highlight Tag if any. **/
      remove_searching_tag() ;

      /** Construct a tag for highlight the match. **/
      searching.search_tag = gtk_text_buffer_create_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), NULL, "background","#43ace8", "background-full-height", TRUE, "foreground", "#FFFFFF",     NULL) ;

      g_object_set_data(G_OBJECT(current_editor.current_buffer), "Tag_highlight_search", searching.search_tag) ;

      gtk_text_buffer_apply_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), searching.search_tag, &searching.start_match, &searching.end_match) ;

      gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW(current_editor.current_textview), &searching.start_match, 0.25, TRUE, 0.5, 0.5) ;

      /** Move cursor for disable mouse selected text if any selection. @NOTE: this can have side-effect by modifcation like unwanted highlighed character(s).  **/
      gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(current_editor.current_buffer),&searching.start_match) ;


      /** Getting TextIter offset: for keeping the TextIter valid !!! **/
      get_iter_offset() ;


      /** Setting search control boolean variable: **/
      searching.get_an_occurrence = TRUE ;

    } /** Uncomment to display an error message window if no match were found.
    else {

      GtkWidget *not_found_message_dialog = error_message_dialog_not_found("Pattern not found !!!", g_strdup_printf("Pattern:\n\" %s \"\nnot found in file !", searching.search_text)) ;

      g_timeout_add(1750, (GSourceFunc) destroy_message_dialog_not_found, GTK_WIDGET(not_found_message_dialog) );
 
      gtk_widget_show_all(GTK_WIDGET(not_found_message_dialog)) ;


    } */

    return ;

  }

  return ;
}


void search_previous(GtkWidget *widget, gpointer user_data) {
  /** User press the search previous button. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ( gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) <= 0)  {

    return ;
  }

  /** Disable mouse selection occurrences highlight if any **/
  destroy_highlight_selection() ;

  if ( (g_strcmp0(searching.search_text, gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry)) ) != 0 &&  g_strcmp0("", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) != 0) || ! searching.complete_search ) {
    /** New search because the search term is different from the search entry content. **/

    if (g_list_find(search_history, (gchar *) gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry)) ) == NULL) {
      /** Add search term to history if this is not yet present in search history. **/
      search_history = g_list_insert(search_history, g_strdup(gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))), 0) ;
    }

    if (searching.search_text != NULL) {
      g_free(searching.search_text) ;
    }


    /** Remove the current occurence highlight Tag if any. **/
    remove_searching_tag() ;


    /** Getting search term. **/
    searching.search_text = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) ;

    gtk_source_search_settings_set_search_text(searching.source_search_settings, searching.search_text) ;


    /** disable all highlights forms **/
    disable_all_highlight() ;
 
 
 
    /** Getting textview end position iterator. **/
    //gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search) ;


    /** Start search at cursor position. **/
 
    GtkTextIter start ;
    GtkTextIter end ;

    // Check if an the user has selecting text
    gboolean selection = gtk_text_buffer_get_selection_bounds(GTK_TEXT_BUFFER(current_editor.current_buffer), &start, &end) ;

    if (selection) {
 
       // The search will start at selection.
 
       gint start_int = gtk_text_iter_get_offset(&start) ;
       gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search, start_int) ;

    }
    else {

      // The search will start at cursor position.

      gint start_int ;

      g_object_get(G_OBJECT(current_editor.current_buffer), "cursor-position", &start_int, NULL) ;

      gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_search, start_int) ;
    }
 


    /** Perform the search from the next occurrence: **/
    gboolean search_found = gtk_source_search_context_backward(searching.source_search_steps_context, &searching.start_search, &searching.start_match, &searching.end_match) ;

    if (search_found) {
      /** The search term was found. **/

      /** Construct a tag for highlight the match. **/
      searching.search_tag = gtk_text_buffer_create_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), NULL, "background","#43ace8", "background-full-height", TRUE, "foreground", "#FFFFFF",     NULL) ;

      g_object_set_data(G_OBJECT(current_editor.current_buffer), "Tag_highlight_search", searching.search_tag) ;

      gtk_text_buffer_apply_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), searching.search_tag, &searching.start_match, &searching.end_match) ;

      gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW(current_editor.current_textview), &searching.start_match, 0.25, TRUE, 0.5, 0.5) ;

      /** Move cursor for disable mouse selected text if any selection. @NOTE: this can have side-effect by modifcation like unwanted highlighed character(s).  **/
      gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(current_editor.current_buffer),&searching.start_match) ;

      /** Setting search control boolean variables: **/
      searching.complete_search   = TRUE  ;
      searching.only_highlight    = FALSE ;
      searching.get_an_occurrence = TRUE  ;
      searching.restart_search    = FALSE ;

      /** Getting TextIter offset: for keeping the TextIter valid !!! **/
      get_iter_offset() ;

    } /** Uncomment to display an error message window if no match were found.
    else {

      GtkWidget *not_found_message_dialog = error_message_dialog_not_found("Pattern not found !!!", g_strdup_printf("Pattern:\n\" %s \"\nnot found in file !", searching.search_text)) ;

      g_timeout_add(1750, (GSourceFunc) destroy_message_dialog_not_found, GTK_WIDGET(not_found_message_dialog) );

      gtk_widget_show_all(GTK_WIDGET(not_found_message_dialog)) ;


    } */

    return ;
  }
  else if ( g_strcmp0(searching.search_text, gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) == 0 && searching.complete_search ) {
    /** We search the next occurrence from the same term: **/

    if ( searching.only_highlight || searching.restart_search ) {
      /** The last search was an occurence highlight search but the term is the same.
        * So we restart from textview start.                                          */

      gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(current_editor.current_buffer), &searching.start_match);
      gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(current_editor.current_buffer),   &searching.end_match) ;

      /** Remove the current occurence highlight Tag if any. **/
      remove_searching_tag() ;

      searching.only_highlight = FALSE ;
      searching.restart_search = FALSE ;

      searching.start_search=searching.end_match ;

    }
    else {
      /** We move iterator for searching next occurrence. **/

      /** Setting the TextIter at precedent saved offset: to keep the TextIter valid. **/
      get_iter_at_offset() ; // This call can maybe be remove if the other is always executed.

      /** We replace the TextIter for searching the next occurrence:  the search will begin at the start from the last match. **/
      searching.start_search=searching.start_match ;
    }


    gtk_source_search_settings_set_search_text(searching.source_search_settings, searching.search_text);

    /** disable all highlights forms **/
    disable_all_highlight() ;

    /** Perform the search from the next occurrence: **/
    gboolean search_found = gtk_source_search_context_backward(searching.source_search_steps_context, &searching.start_search, &searching.start_match, &searching.end_match) ;

    if (search_found) {
      /** The search term was found. **/

      /** Remove the current occurence highlight Tag if any. **/
      remove_searching_tag() ;

      /** Construct a tag for highlight the match. **/
      searching.search_tag = gtk_text_buffer_create_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), NULL, "background","#43ace8", "background-full-height", TRUE, "foreground", "#FFFFFF",     NULL) ;

      g_object_set_data(G_OBJECT(current_editor.current_buffer), "Tag_highlight_search", searching.search_tag) ;

      gtk_text_buffer_apply_tag(GTK_TEXT_BUFFER(current_editor.current_buffer), searching.search_tag, &searching.start_match, &searching.end_match) ;

      gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW(current_editor.current_textview), &searching.start_match, 0.25, TRUE, 0.5, 0.5) ;

      /** Move cursor for disable mouse selected text if any selection. @NOTE: this can have side-effect by modifcation like unwanted highlighed character(s).  **/
      gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(current_editor.current_buffer),&searching.start_match) ;

      /** Getting TextIter offset: for keeping the TextIter valid !!! **/
      get_iter_offset() ;

      searching.get_an_occurrence = TRUE ;

    } /** Uncomment to display an error message window if no match were found.
    else {

      GtkWidget *not_found_message_dialog = error_message_dialog_not_found("Pattern not found !!!", g_strdup_printf("Pattern:\n\" %s \"\nnot found in file !", searching.search_text)) ;

      g_timeout_add(1750, (GSourceFunc) destroy_message_dialog_not_found, GTK_WIDGET(not_found_message_dialog) );

      gtk_widget_show_all(GTK_WIDGET(not_found_message_dialog)) ;


    } */

    return ;

  }

  return ;


}

void replace_one_occurence(GtkButton *button, gpointer user_data) {
  /** Replace current occurence. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if ( gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) <= 0)  {

    return ;
  }

  if (searching.search_text != NULL) {
    g_free(searching.search_text) ;
  }

  /** Getting search term. **/
  searching.search_text = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) ;

  if (g_strcmp0(searching.search_text, "") == 0 ) {
      return ;
  }


  if ( searching.get_an_occurrence && ! searching.only_highlight && searching.source_search_steps_context != NULL ) {

    GtkTextIter start_replace     = searching.start_match ;
    GtkTextIter end_replace       = searching.end_match   ;

    /** Getting TextIter offset. **/
    get_iter_offset() ;


    gtk_source_search_settings_set_search_text(searching.source_search_settings,  searching.search_text );
    gtk_source_search_context_set_settings(searching.source_search_steps_context, searching.source_search_settings);

    GError *error = NULL ;

    /** Perform the replacement: **/
    gtk_source_search_context_replace(searching.source_search_steps_context, &start_replace, &end_replace, gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->replace_entry)), -1, &error) ;

    /** Restore the TextIter from offset saved previously to keep it valid after modifcation (replacement). **/
    get_iter_at_offset() ;

  }


  /** Remove the current occurence highlight Tag if any. **/
  remove_searching_tag() ;

  return ;

}

void replace_all_occurence(GtkButton button, gpointer user_data) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  if ( gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) <= 0)  {

    return ;
  }

  if (searching.search_text != NULL) {
    g_free(searching.search_text) ;
  }

  /** Getting search term. **/
  searching.search_text = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry))) ;

  if (g_strcmp0(searching.search_text, "") == 0 ) {
      return ;
  }

  if ( searching.only_highlight && searching.source_search_highlight_context != NULL  ) {
    /** Replacement trought highlight all matches search. **/

    /** Getting TextIter offset. **/
    get_iter_offset() ;

    gtk_source_search_settings_set_search_text(searching.source_search_settings,      searching.search_text );

    gtk_source_search_context_set_settings(searching.source_search_highlight_context, searching.source_search_settings);

    /** Perform the replacements: **/
    gtk_source_search_context_replace_all(searching.source_search_highlight_context, gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->replace_entry)), -1, NULL) ;

    /** Restore the TextIter from offset saved previously to keep it valid after modifcation (replacement). **/
    get_iter_at_offset() ;

    return ;

  }
  else if (searching.get_an_occurrence  && searching.source_search_steps_context != NULL ) {
    /** Replacement trought single match search (Next | Previous buttons) search. **/

    /** Getting TextIter offset. **/
    get_iter_offset() ;

    gtk_source_search_settings_set_search_text(searching.source_search_settings,  searching.search_text );

    gtk_source_search_context_set_settings(searching.source_search_steps_context, searching.source_search_settings);

    /** Perform the replacements: **/
    gtk_source_search_context_replace_all(searching.source_search_steps_context, gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->replace_entry)), -1, NULL) ;

    /** Restore the TextIter from offset saved previously to keep it valid after modifcation (replacement). **/
    get_iter_at_offset() ;

    return ;

  }

  else if ( g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->search_entry)),"") != 0) {

    /** Getting TextIter offset. **/
    get_iter_offset() ;

    GtkSourceSearchContext *current_context = gtk_source_search_context_new(GTK_SOURCE_BUFFER(current_editor.current_buffer), searching.source_search_settings) ;

    gtk_source_search_settings_set_search_text(searching.source_search_settings, searching.search_text) ;

    gtk_source_search_context_set_settings(current_context , searching.source_search_settings);

    gtk_source_search_context_replace_all(current_context, gtk_entry_get_text(GTK_ENTRY(gui->search_and_replace->replace_entry)), -1, NULL) ;

    /** Restore the TextIter from offset saved previously to keep it valid after modifcation (replacement). **/
    get_iter_at_offset() ;

    return ;
  }

  return ;

}


