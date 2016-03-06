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

#include "edition_callbacks.h"

void undo(GtkWidget *button, gpointer user_data) {
  /** Undo menu item callback. @NOTE: This does not work well so use the shortcut (Ctrl + z) or the contextual menu for undo operations. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkSourceUndoManager *source_undo_manager = gtk_source_buffer_get_undo_manager(GTK_SOURCE_BUFFER(current_editor.current_buffer));

  gtk_source_buffer_set_undo_manager(GTK_SOURCE_BUFFER(current_editor.current_buffer), source_undo_manager);

  if ( gtk_source_undo_manager_can_undo(source_undo_manager) ) {

    gtk_text_buffer_begin_user_action(current_editor.current_buffer) ;

    gtk_source_undo_manager_undo(source_undo_manager)  ;

     /*
     while (gtk_events_pending()) {
       gtk_main_iteration() ;
     }
    */

    GtkTextIter start, end ;
    gtk_text_buffer_get_bounds(current_editor.current_buffer, &start, &end);

    gchar *content = NULL ;

    content = gtk_text_buffer_get_text(current_editor.current_buffer, &start, &end, FALSE);

    if (content) {
      gtk_text_buffer_set_text(current_editor.current_buffer,content, -1) ;
      g_free(content) ;
    }

    gtk_text_buffer_end_user_action(current_editor.current_buffer) ;

  }



  return ;

}

void redo(GtkWidget *button, gpointer user_data) {
  /** Redo button callback. @NOTE: This does not work well so use the shortcut (Ctrl + Maj + Z) or the contextual menu for redo operations.  **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  GtkSourceUndoManager *source_undo_manager = gtk_source_buffer_get_undo_manager(GTK_SOURCE_BUFFER(current_editor.current_buffer));

  gtk_source_buffer_set_undo_manager(GTK_SOURCE_BUFFER(current_editor.current_buffer), source_undo_manager);





  if ( gtk_source_undo_manager_can_redo(source_undo_manager) ) {

    gtk_text_buffer_begin_user_action(current_editor.current_buffer) ;

    gtk_source_undo_manager_redo(source_undo_manager)  ;


    /*
    while (gtk_events_pending()) {
      gtk_main_iteration() ;
    }
    */

    GtkTextIter start, end ;
    gtk_text_buffer_get_bounds(current_editor.current_buffer, &start, &end);

    gchar *content = NULL ;

    content = gtk_text_buffer_get_text(current_editor.current_buffer, &start, &end, FALSE);

    if (content) {
      gtk_text_buffer_set_text(current_editor.current_buffer,content, -1) ;
      g_free(content) ;
    }

    gtk_text_buffer_end_user_action(current_editor.current_buffer) ;

  }

  return ;


}

void cut(GtkWidget *button, gpointer user_data) {
  /** Text cutting callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  /** Checking if some text is selected. **/
  gboolean has_selection ;
  g_object_get(G_OBJECT(current_editor.current_buffer), "has-selection", &has_selection, NULL) ;

  if (has_selection) {
    /** Perform cut action on selected text in the current editor (notebook page). **/
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY) ;
    gtk_text_buffer_cut_clipboard(GTK_TEXT_BUFFER(current_editor.current_buffer), clipboard, TRUE);

  }

  return ;

}

void copy(GtkWidget *button, gpointer user_data) {
  /** Text copying callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  /** Checking if some text is selected. **/
  gboolean has_selection ;
  g_object_get(G_OBJECT(current_editor.current_buffer), "has-selection", &has_selection, NULL) ;

  if (has_selection) {
    /** Perform copy action on selected text in the current editor (notebook page). **/
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY) ;
    gtk_text_buffer_copy_clipboard(GTK_TEXT_BUFFER(current_editor.current_buffer), clipboard) ;
  }

  return ;

}

void paste(GtkWidget *button, gpointer user_data) {
  /** Text pasting callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  /** Perform pasting action in the current editor (notebook page). **/
  GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY) ;

  GtkTextIter cursor_position ;
  gint cursor_offset ;
  g_object_get(G_OBJECT(current_editor.current_buffer),"cursor-position", &cursor_offset, NULL) ;

  gtk_text_buffer_get_iter_at_offset(current_editor.current_buffer, &cursor_position, cursor_offset) ;

  gtk_text_buffer_paste_clipboard(GTK_TEXT_BUFFER(current_editor.current_buffer), clipboard, &cursor_position, TRUE) ;

  return ;

}

void duplicate(GtkWidget *button, gpointer user_data) {
  /** Text duplicating callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Checking if some text is selected. **/
  gboolean has_selection ;
  g_object_get(G_OBJECT(current_editor.current_buffer), "has-selection", &has_selection, NULL) ;

  if (has_selection) {
    /** Some text is selected we duplicated it. **/

    GtkTextIter start_selection  ;
    GtkTextIter end_selection    ;

    GtkTextIter start_insertion  ;

    /** Getting selection iterators **/
    gtk_text_buffer_get_selection_bounds(GTK_TEXT_BUFFER(current_editor.current_buffer), &start_selection, &end_selection);

    /** set iterator on selection line begin for characters before selection: indenting purpose. **/
    gint line_number = gtk_text_iter_get_line(&start_selection);
    gtk_text_buffer_get_iter_at_line(current_editor.current_buffer, &start_insertion,line_number);

    /** Getting selected text **/
    gchar *selection_text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(current_editor.current_buffer), &start_insertion, &end_selection, TRUE);

    /** Add linefeed so that the following line is on a new line . **/
    gchar *selection_text_linefeed = g_strconcat(selection_text, "\n", NULL) ;

    /** We insert at the line after selection. **/
    gtk_text_iter_forward_line(&end_selection);

    gtk_text_buffer_insert(GTK_TEXT_BUFFER(current_editor.current_buffer), &end_selection, selection_text_linefeed, (int) strlen(selection_text_linefeed));

    g_free(selection_text) ;
    g_free(selection_text_linefeed) ;
  }
  else {
    /** No selection: we duplicate the line at cursor location: **/


    /** Getting cursor location. **/
    GtkTextIter cursor_position ;
    gint cursor_offset ;
    g_object_get(G_OBJECT(current_editor.current_buffer),"cursor-position", &cursor_offset, NULL) ;
    gtk_text_buffer_get_iter_at_offset(current_editor.current_buffer, &cursor_position, cursor_offset) ;


    GtkTextIter insertion ;
    insertion = cursor_position ;
    gtk_text_iter_forward_to_line_end(&insertion) ;


    if (gtk_text_iter_get_char(&cursor_position) == '\n') {
      /** Cursor at an empty line. Or at line end, but we don't take the risk to duplicate an empty line. **/
      return ;
    }


    /** Check  if next line is empty **/
    GtkTextIter next_line ;
    next_line = insertion ;

    gtk_text_iter_forward_line(&next_line) ;

    gboolean next_line_empty = gtk_text_iter_get_char(&next_line) == '\n' ? TRUE : FALSE ;

    if  ( next_line_empty) {
      /** Delete empty line '\n' character, for inserting, it disturb. **/
      GtkTextIter start_del,  end_del ;
      start_del = next_line ;
      end_del   = next_line ;

      gtk_text_iter_forward_char(&end_del) ;

      /** Delete the '\n' character from empty line. **/
      gtk_text_buffer_delete(GTK_TEXT_BUFFER(current_editor.current_buffer), &start_del, &end_del);

      /** Must update iterators after an deleting '\n' **/
      gtk_text_buffer_get_iter_at_offset(current_editor.current_buffer, &insertion, cursor_offset) ;

      gtk_text_iter_forward_to_line_end(&insertion) ;
    }


    /** Getting current line: the line where the cursor is located **/
    gint line_number = gtk_text_iter_get_line(&insertion);

    GtkTextIter current_line_start ;
    GtkTextIter current_line_end   ;

    gtk_text_buffer_get_iter_at_line(current_editor.current_buffer, &current_line_start, line_number);
    gtk_text_buffer_get_iter_at_line(current_editor.current_buffer, &current_line_end,   line_number);

    gtk_text_iter_forward_to_line_end(&current_line_end) ;

    /** Getting line text **/
    gchar *selection_text  = gtk_text_iter_get_text(&current_line_start, &current_line_end);


    /** Add linefeed so that the following line is on a new line. **/
    gchar *selection_text_linefeed = g_strconcat(selection_text, "\n", NULL) ;

    if (next_line_empty) {
      /** Add a second linefeed to compensate the erase linefeed character by empty line. **/
      g_free(selection_text_linefeed) ;
      selection_text_linefeed = g_strconcat(selection_text, "\n", NULL) ;
    }

    gtk_text_iter_forward_line(&insertion);

    gtk_text_buffer_insert(GTK_TEXT_BUFFER(current_editor.current_buffer), &insertion, selection_text_linefeed, (int) strlen(selection_text_linefeed));

    g_free(selection_text) ;
    g_free(selection_text_linefeed) ;

  }

  return ;

}
