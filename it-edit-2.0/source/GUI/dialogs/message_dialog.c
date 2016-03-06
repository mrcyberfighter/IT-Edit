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

#include "./message_dialog.h"

gboolean destroy_message_dialog_not_found(GtkWidget *dialog) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  g_free(g_object_get_data(G_OBJECT(dialog),  "message_one")) ;
  g_free(g_object_get_data(G_OBJECT(dialog),  "message_two")) ;

  gtk_widget_destroy(dialog) ;

  return FALSE ;

}

GtkWidget  *error_message_dialog_not_found(const gchar *message, gchar *secondary_message)  {
  /** Return a message dialog according to the given arguments. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gchar *message_one = g_strdup(message); // This must be free in the destroy func with g_object_set_data() && g_object_get_data().
  gchar *message_two = g_strdup(secondary_message); // This must be free in the destroy func with g_object_set_data() && g_object_get_data().

  GtkWidget *message_dialog = gtk_message_dialog_new(NULL,  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT ,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_NONE,
                                                            message_one,
                                                            NULL);

  gtk_window_set_position(GTK_WINDOW(message_dialog), GTK_WIN_POS_CENTER) ;

  g_object_set_data(G_OBJECT(message_dialog), "message_one", message_one) ;
  g_object_set_data(G_OBJECT(message_dialog), "message_two", message_two) ;


  if (secondary_message != NULL) {
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(message_dialog), message_two, NULL) ;
    g_free(secondary_message) ;
  }

  return message_dialog ;
}                                          

                                           

void display_message_dialog(const gchar *message, gchar *secondary_message, gint message_type, gint buttons)  {
  /** Return a message dialog according to the given arguments. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *message_dialog = gtk_message_dialog_new(NULL,  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT ,
                                                            message_type,       /** GTK_MESSAGE_INFO || GTK_MESSAGE_ERROR  **/
                                                            buttons,            /** GTK_BUTTONS_NONE || GTK_BUTTONS_CLOSE  **/
                                                            message,
                                                            NULL);

  gtk_window_set_position(GTK_WINDOW(message_dialog), GTK_WIN_POS_CENTER) ;

  if (secondary_message != NULL) {
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(message_dialog), secondary_message, NULL) ;
  }

  gtk_dialog_run(GTK_DIALOG(message_dialog))  ; // Display message dialog.

  gtk_widget_destroy(message_dialog) ;

  return ;
}                                  

