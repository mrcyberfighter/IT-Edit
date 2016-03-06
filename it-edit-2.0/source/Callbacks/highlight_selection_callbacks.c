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

#include "highlight_selection_callbacks.h"


void disable_all_highlight(void) {
  /** Disable the search highlighting all occurrences which are enbale per default. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  gtk_source_search_context_set_highlight(searching.source_search_highlight_context, FALSE) ;
  gtk_source_search_context_set_highlight(searching.source_search_steps_context,     FALSE) ;

  return ;

}


void destroy_highlight_selection(void) {
  /** Remove all occurrences highlighting. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  Highlight_Selection *highlight_textview_selection =  (Highlight_Selection *) g_object_get_data(G_OBJECT(current_editor.current_textview), "highlight_textview_selection") ;

  if (highlight_textview_selection->source_search_highlight_context != NULL) {
    gtk_source_search_context_set_highlight(highlight_textview_selection->source_search_highlight_context, FALSE) ;
  }



  return ;
}


void highlight_selection(GtkTextView *textview) {
    /** Mouse selection highlighting matching occurences callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  destroy_highlight_selection() ;


  GtkTextIter start ;
  GtkTextIter end   ;

  /** Getting selection. **/
  gtk_text_buffer_get_selection_bounds(current_editor.current_buffer, &start, &end) ;

  Highlight_Selection *highlight_textview_selection =  (Highlight_Selection *) g_object_get_data(G_OBJECT(textview), "highlight_textview_selection") ;

  gtk_source_search_settings_set_search_text(highlight_textview_selection->source_search_settings, gtk_text_iter_get_slice(&start, &end));

  gtk_source_search_context_set_settings(highlight_textview_selection->source_search_highlight_context, highlight_textview_selection->source_search_settings);
  gtk_source_search_context_set_highlight(highlight_textview_selection->source_search_highlight_context, TRUE) ;

  return ;
}

