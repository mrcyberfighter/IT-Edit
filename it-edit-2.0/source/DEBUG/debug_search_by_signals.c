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

#include "./debug_search_by_signals.h"

char get_rand_ascii_print(void) {

   GRand *rand ;

   struct timeval tv ;

   gettimeofday(&tv, NULL) ;

   g_usleep(tv.tv_usec % 256) ;

   rand = g_rand_new_with_seed((guint32) tv.tv_usec);

   return  (char) ((g_rand_int(rand) % 26) + 97) ;

}




void debug_searching_and_replace_by_signal_emit(GtkWidget *widget, gpointer user_data) {
  /** To perform this test you must open any files,
    * and press the "Replace debug" button.
    ********************************************************************************/
  int c ;

  GtkWidget *widgets[5]={gui->search_and_replace->search_button,
                         gui->search_and_replace->replace_one_button,
                         gui->search_and_replace->search_next_button,
                         gui->search_and_replace->replace_all_button,
                         gui->search_and_replace->search_prev_button } ;


  GtkWidget *widget_emitter = NULL ;

  GRand *rand ;

  struct timeval tv ;

  gettimeofday(&tv, NULL) ;

  for (c=0 ; c < 1024 ; c++) {



    g_usleep(tv.tv_usec % 256) ;

    gettimeofday(&tv, NULL) ;

    rand = g_rand_new_with_seed((guint32) tv.tv_usec);

    if ( g_rand_int(rand) % 5 == 0 ) {
      widget_emitter = widgets[g_rand_int(rand) % 5] ;
    }

    g_usleep(tv.tv_usec % 256) ;

    gettimeofday(&tv, NULL) ;

    rand = g_rand_new_with_seed((guint32) tv.tv_usec);


    if (g_rand_int(rand) % 5 == 0) {

      gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->search_entry), "") ;
    }
    else {

      char char_one = get_rand_ascii_print() ;
      char char_two = get_rand_ascii_print() ;

      char text[3]={char_one,char_two,'\0'} ;

      gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->search_entry), text) ;
    }

 

    g_usleep(tv.tv_usec % 256) ;

    gettimeofday(&tv, NULL) ;

    rand = g_rand_new_with_seed((guint32) tv.tv_usec);

    if (g_rand_int(rand) % 5 == 0) {
      gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->replace_entry), "") ;
    }
    else {

      char char_one = get_rand_ascii_print() ;
      char char_two = get_rand_ascii_print() ;

      char text[3]={char_one,char_two,'\0'} ;

      gtk_entry_set_text(GTK_ENTRY(gui->search_and_replace->replace_entry), text) ;
    }


    g_usleep(tv.tv_usec % 256) ;

    gettimeofday(&tv, NULL) ;

    rand = g_rand_new_with_seed((guint32) tv.tv_usec);

    if (g_rand_int(rand) % 5 == 0) {
      gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->editor_notebook), g_rand_int(rand) % gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) ) ;
    }

    g_signal_emit_by_name((gpointer) widget_emitter, "clicked", NULL);

    while (gtk_events_pending()) {
       gtk_main_iteration() ;
    }

    g_usleep(125000/5) ;
  }

  fprintf(stdout,"End of tests successfull !!!\n") ;
  fflush(stdout) ;

  return ;

}
