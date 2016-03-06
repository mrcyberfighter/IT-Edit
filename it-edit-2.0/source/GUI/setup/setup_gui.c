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

#include "./setup_gui.h"



void setup_search_and_replace_bar(Search_And_Replace *search_and_replace) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  search_and_replace->search_and_replace_main_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL,   0) ;

  search_and_replace->search_and_replace_main_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;


  search_and_replace->search_and_replace_label_vbox    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  search_and_replace->search_and_replace_entry_vbox    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  search_and_replace->search_and_replace_button_vbox_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  search_and_replace->search_and_replace_button_vbox_2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  gtk_box_set_homogeneous(GTK_BOX(search_and_replace->search_and_replace_label_vbox), TRUE) ;

  gtk_box_set_homogeneous(GTK_BOX(search_and_replace->search_and_replace_entry_vbox), TRUE) ;

  gtk_box_set_homogeneous(GTK_BOX(search_and_replace->search_and_replace_button_vbox_1), TRUE) ;

  gtk_box_set_homogeneous(GTK_BOX(search_and_replace->search_and_replace_button_vbox_2), TRUE) ;



  search_and_replace->search_button = gtk_button_new_with_label(" Search ") ;

  search_and_replace->search_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "system-search.png") ;

  gtk_button_set_image(GTK_BUTTON(search_and_replace->search_button), search_and_replace->search_image);

  g_object_set(G_OBJECT(search_and_replace->search_button),"always-show-image",TRUE,NULL) ;

  g_signal_connect(G_OBJECT(search_and_replace->search_button), "clicked", G_CALLBACK(search), NULL ) ;



  search_and_replace->replace_button = gtk_button_new_with_label(" Replace") ;

  search_and_replace->replace_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "edit-find-replace.png") ;

  gtk_button_set_image(GTK_BUTTON(search_and_replace->replace_button), search_and_replace->replace_image);

  g_object_set(G_OBJECT(search_and_replace->replace_button),"always-show-image",TRUE,NULL) ;

  g_signal_connect(G_OBJECT(search_and_replace->replace_button),"clicked", G_CALLBACK(replace_one_occurence), NULL) ;



  search_and_replace->search_entry   = gtk_search_entry_new() ;

  g_signal_connect(G_OBJECT(search_and_replace->search_entry), "key-press-event", G_CALLBACK(search_history_callback), NULL) ;

  g_signal_connect(G_OBJECT(search_and_replace->search_entry), "activate",        G_CALLBACK(search_next), NULL) ;

  search_and_replace->replace_entry  = gtk_entry_new() ;

  search_and_replace->search_next_button  = gtk_button_new_with_label("Next") ;

  search_and_replace->search_next_image   = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "go-down-search.png") ;

  gtk_button_set_image(GTK_BUTTON(search_and_replace->search_next_button), search_and_replace->search_next_image);

  g_object_set(G_OBJECT(search_and_replace->search_next_button),"always-show-image",TRUE,NULL) ;

  g_signal_connect(G_OBJECT(search_and_replace->search_next_button),"clicked", G_CALLBACK(search_next), NULL) ;


  search_and_replace->search_prev_button  = gtk_button_new_with_label("Previous") ;

  search_and_replace->search_next_image   = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "go-up-search.png") ;

  gtk_button_set_image(GTK_BUTTON(search_and_replace->search_prev_button), search_and_replace->search_next_image);

  g_object_set(G_OBJECT(search_and_replace->search_prev_button),"always-show-image",TRUE,NULL) ;

  g_signal_connect(G_OBJECT(search_and_replace->search_prev_button), "clicked", G_CALLBACK(search_previous), NULL) ;

  search_and_replace->replace_one_button      = gtk_button_new_with_label("Replace") ;

  g_signal_connect(G_OBJECT(search_and_replace->replace_one_button),"clicked", G_CALLBACK(replace_one_occurence), NULL) ;

  search_and_replace->replace_all_button      = gtk_button_new_with_label("Replace all") ;

  g_signal_connect(G_OBJECT(search_and_replace->replace_all_button), "clicked", G_CALLBACK(replace_all_occurence), NULL) ;




  search_and_replace->search_settings_image   = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "preferences-system.png") ;

  search_and_replace->search_settings_button  = gtk_button_new_with_label(" Mode    ") ;

  g_object_set(G_OBJECT(search_and_replace->search_settings_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(search_and_replace->search_settings_button), search_and_replace->search_settings_image);


  search_and_replace->search_settings_hbox     = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  search_and_replace->search_settings_combobox = gtk_combo_box_text_new_with_entry() ;

  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(search_and_replace->search_settings_combobox),"1","Raw text") ;
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(search_and_replace->search_settings_combobox),"2","Word boundary") ;
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(search_and_replace->search_settings_combobox),"3","Regular expression") ;

  gtk_combo_box_set_active (GTK_COMBO_BOX(search_and_replace->search_settings_combobox), 0) ;

  gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(search_and_replace->search_settings_combobox), GTK_SENSITIVITY_AUTO );

  g_signal_connect(G_OBJECT(search_and_replace->search_settings_combobox),"changed",G_CALLBACK(set_search_mode), NULL) ;

  GtkWidget *combobox_entry = gtk_bin_get_child(GTK_BIN(search_and_replace->search_settings_combobox)) ;

  g_object_set(G_OBJECT(combobox_entry),"editable", FALSE, NULL) ;


  search_and_replace->search_settings_padding_1 = gtk_label_new("") ;

  search_and_replace->search_settings_case_checkbox = gtk_check_button_new_with_label("Case-sensitive")  ;

  g_signal_connect(G_OBJECT(search_and_replace->search_settings_case_checkbox),"toggled", G_CALLBACK(set_case_sensitive), NULL) ;

  search_and_replace->search_settings_wrap_checkbox = gtk_check_button_new_with_label("Wrap around") ;

  g_signal_connect(G_OBJECT(search_and_replace->search_settings_wrap_checkbox),"toggled", G_CALLBACK(set_wrap_around), NULL) ;

  gtk_widget_set_margin_left(GTK_WIDGET(search_and_replace->search_settings_case_checkbox),  8 );
  gtk_widget_set_margin_right(GTK_WIDGET(search_and_replace->search_settings_case_checkbox), 8 );
  gtk_widget_set_margin_left(GTK_WIDGET(search_and_replace->search_settings_wrap_checkbox),  8 );
  gtk_widget_set_margin_right(GTK_WIDGET(search_and_replace->search_settings_wrap_checkbox), 8 );


  search_and_replace->search_settings_padding_2 = gtk_label_new("") ;

  gtk_box_pack_start(GTK_BOX(search_and_replace->search_settings_hbox), search_and_replace->search_settings_combobox,       FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_settings_hbox), search_and_replace->search_settings_padding_1,      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_settings_hbox), search_and_replace->search_settings_case_checkbox,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_settings_hbox), search_and_replace->search_settings_wrap_checkbox,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_settings_hbox), search_and_replace->search_settings_padding_2,      TRUE,  TRUE, 0) ;

  search_and_replace->search_settings_match_label         = gtk_label_new("") ;

  search_and_replace->search_settings_close_image         = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "window-close.png") ;

  search_and_replace->search_settings_close_button        = gtk_button_new_with_label(" Close    ") ;

  g_object_set(G_OBJECT(search_and_replace->search_settings_close_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(search_and_replace->search_settings_close_button), search_and_replace->search_settings_close_image);

  g_signal_connect(G_OBJECT(search_and_replace->search_settings_close_button),"clicked",G_CALLBACK(close_search_and_replace_bar), NULL) ;


  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_label_vbox), search_and_replace->search_button,          FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_label_vbox), search_and_replace->replace_button,         FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_label_vbox), search_and_replace->search_settings_button, FALSE, FALSE, 0 ) ;

  gtk_box_set_spacing(GTK_BOX(search_and_replace->search_and_replace_label_vbox), 4) ;

  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_entry_vbox), search_and_replace->search_entry,         FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_entry_vbox), search_and_replace->replace_entry,        FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_entry_vbox), search_and_replace->search_settings_hbox, FALSE, FALSE, 0 ) ;

  gtk_box_set_spacing(GTK_BOX(search_and_replace->search_and_replace_entry_vbox), 4) ;

  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_button_vbox_1), search_and_replace->search_next_button,           FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_button_vbox_1), search_and_replace->replace_one_button,           FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_button_vbox_1), search_and_replace->search_settings_match_label,  FALSE, FALSE, 0 ) ;

  gtk_box_set_spacing(GTK_BOX(search_and_replace->search_and_replace_button_vbox_1), 4) ;

  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_button_vbox_2), search_and_replace->search_prev_button,            FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_button_vbox_2), search_and_replace->replace_all_button,            FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_button_vbox_2), search_and_replace->search_settings_close_button,  FALSE, FALSE, 0 ) ;

  gtk_box_set_spacing(GTK_BOX(search_and_replace->search_and_replace_button_vbox_2), 4) ;

  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_main_hbox), search_and_replace->search_and_replace_label_vbox,     FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_main_hbox), search_and_replace->search_and_replace_entry_vbox,     TRUE, TRUE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_main_hbox), search_and_replace->search_and_replace_button_vbox_1,  FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(search_and_replace->search_and_replace_main_hbox), search_and_replace->search_and_replace_button_vbox_2,  FALSE, FALSE, 0 ) ;

  return ;

}

void setup_menu_item(MenuItem *menuitem, const char *label, const char *accel_label, const char *image, GtkAccelGroup *menu_files_accel_group,  GdkModifierType accel_modifier,  guint accel_key, int8_t type) {
  /** Generate one menu item according to the given settings **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  switch (type) {

    case 0 :
      menuitem->menuitem  = gtk_menu_item_new() ;
      break ;

    case 1 :
      menuitem->menuitem  = gtk_check_menu_item_new() ;
      break ;
  }


  menuitem->label = gtk_label_new(label) ;

  gtk_label_set_justify(GTK_LABEL(menuitem->label), GTK_JUSTIFY_LEFT);


  if (accel_label != NULL) {
    /** Menu item has an shortcut **/

    menuitem->accel_label = gtk_label_new(accel_label) ;

    gtk_label_set_justify(GTK_LABEL(menuitem->accel_label), GTK_JUSTIFY_RIGHT) ;


    if (accel_key != 0) {

      gtk_widget_add_accelerator(menuitem->menuitem,
                                 "activate",
                                 menu_files_accel_group,
                                 accel_key,
                                 accel_modifier,
                                 GTK_ACCEL_VISIBLE);
    }
  }

  if (image != NULL) {
    /** Menu item has an associate image **/

    gchar *filepath = g_strdup_printf ("%s%s", PATH_TO_MENU_ICON, image);

    menuitem->image = gtk_image_new_from_file(filepath) ;

    free(filepath) ;
  }

  /** Menu item container **/
  menuitem->hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0) ;

  if (image) {
    gtk_box_pack_start(GTK_BOX(menuitem->hbox), menuitem->image, FALSE, FALSE, 0) ;
  }

  gtk_box_pack_start(GTK_BOX(menuitem->hbox),   menuitem->label, FALSE, FALSE, 0) ;

  GtkWidget *dummy_label=gtk_label_new("") ; /** For expand between Text and shortcut text **/

  gtk_box_pack_start(GTK_BOX(menuitem->hbox),  dummy_label,      TRUE,  TRUE,  0) ;



  if (accel_label != NULL) {
    gtk_box_pack_start(GTK_BOX(menuitem->hbox), menuitem->accel_label, FALSE, FALSE, 0) ;
  }


  gtk_container_add(GTK_CONTAINER(menuitem->menuitem),menuitem->hbox) ;



  return ;
}

void initialize_menu(Menu *menu) {
  /** Generate all the menu, partially trought setup_menu_item() calls. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  extern Settings settings ;

  menu->menu_bar = gtk_menu_bar_new() ;

  gtk_widget_set_name(menu->menu_bar,"menubar") ;

  menu->menu_files   = gtk_menu_new() ;

  menu->files_button = g_slice_new(MenuItem) ;

  setup_menu_item(menu->files_button,"  Files  ",NULL, "text-x-generic.png", NULL, 0, 0, 0) ;


  menu->new_file  = g_slice_new(MenuItem) ;

  setup_menu_item(menu->new_file ,"  New file  "," Ctrl + N ", "document-new.png", menu->menu_files_accel_group, GDK_CONTROL_MASK, GDK_KEY_n, 0) ;

  g_signal_connect(G_OBJECT(menu->new_file->menuitem), "activate", G_CALLBACK(new_file), NULL) ;


  menu->separator_01 = gtk_separator_menu_item_new() ;


  menu->open_file = g_slice_new(MenuItem) ;

  setup_menu_item(menu->open_file,"  Open file  "," Ctrl + O ", "document-open.png", menu->menu_files_accel_group, GDK_CONTROL_MASK, GDK_KEY_o, 0) ;

  g_signal_connect(G_OBJECT(menu->open_file->menuitem), "activate", G_CALLBACK(open_file), NULL) ;


  menu->menu_recent  = gtk_recent_chooser_menu_new() ;

  gtk_recent_chooser_set_show_icons(GTK_RECENT_CHOOSER(menu->menu_recent), TRUE);

  gtk_recent_chooser_set_show_not_found(GTK_RECENT_CHOOSER(menu->menu_recent), FALSE) ;

  gtk_recent_chooser_set_limit(GTK_RECENT_CHOOSER(menu->menu_recent), 20) ;

  GtkRecentFilter *recent_chooser_filter = gtk_recent_filter_new() ;
  gtk_recent_filter_add_mime_type(GTK_RECENT_FILTER(recent_chooser_filter),"text/*") ;

  gtk_recent_chooser_set_filter(GTK_RECENT_CHOOSER(menu->menu_recent),GTK_RECENT_FILTER(recent_chooser_filter));

  gtk_recent_chooser_set_sort_type(GTK_RECENT_CHOOSER(menu->menu_recent), GTK_RECENT_SORT_MRU);

  g_signal_connect(G_OBJECT(menu->menu_recent), "item-activated", G_CALLBACK(open_recent), NULL) ;

  menu->recent_files = g_slice_new(MenuItem) ;

  setup_menu_item(menu->recent_files,"  Recent files  ",NULL, "document-open-recent.png", NULL, 0, 0, 0) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->recent_files->menuitem), menu->menu_recent) ;


  menu->separator_02 = gtk_separator_menu_item_new() ;


  menu->save_file = g_slice_new(MenuItem) ;

  setup_menu_item(menu->save_file,"  Save file  "," Ctrl + S ", "document-save.png", menu->menu_files_accel_group, GDK_CONTROL_MASK, GDK_KEY_s, 0) ;

  g_signal_connect(G_OBJECT(menu->save_file->menuitem), "activate", G_CALLBACK(save_file), NULL) ;


  menu->save_as_file = g_slice_new(MenuItem) ;

  setup_menu_item(menu->save_as_file,"  Save file as  ",NULL, "document-save-as.png", menu->menu_files_accel_group, 0, 0, false) ;

  g_signal_connect(G_OBJECT(menu->save_as_file->menuitem), "activate", G_CALLBACK(save_as_file), NULL) ;



  menu->save_all = g_slice_new(MenuItem) ;

  setup_menu_item(menu->save_all, "  Save all files  "," Ctrl + Maj + S ", "document-save-all.png", menu->menu_files_accel_group, GDK_CONTROL_MASK | GDK_SHIFT_MASK, GDK_KEY_S, 0) ;

  g_signal_connect(G_OBJECT(menu->save_all->menuitem), "activate", G_CALLBACK(save_all_file), NULL) ;


  menu->separator_03 = gtk_separator_menu_item_new() ;


  menu->reload_page = g_slice_new(MenuItem) ;

  setup_menu_item(menu->reload_page, "  Reload file  "," Ctrl + R ", "reload_page.png", menu->menu_files_accel_group, GDK_CONTROL_MASK, GDK_KEY_r, 0) ;

  g_signal_connect(G_OBJECT(menu->reload_page->menuitem), "activate", G_CALLBACK(reloading_file), NULL) ;


  menu->separator_04 = gtk_separator_menu_item_new() ;


  menu->file_info = g_slice_new(MenuItem) ;

  setup_menu_item(menu->file_info, "  File informations  "," Ctrl + I ", "text-x-texinfo.png", menu->menu_files_accel_group, GDK_CONTROL_MASK, GDK_KEY_i, 0) ;

  g_signal_connect(G_OBJECT(menu->file_info->menuitem), "activate", G_CALLBACK(display_file_informations_dialog), NULL) ;


  menu->separator_05 = gtk_separator_menu_item_new() ;

  menu->quit = g_slice_new(MenuItem) ;

  setup_menu_item(menu->quit, "  Quit  "," Ctrl + Q ", "process-stop.png", menu->menu_files_accel_group, GDK_CONTROL_MASK, GDK_KEY_q, 0) ;

  g_signal_connect(G_OBJECT(menu->quit->menuitem), "activate", G_CALLBACK(quit_application), NULL) ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->files_button->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->files_button->menuitem),menu->menu_files);



  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->new_file->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->separator_01) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->open_file->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->recent_files->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->separator_02) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->save_file->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->save_as_file->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->save_all->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->separator_03) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->reload_page->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->separator_04) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->file_info->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->separator_05) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->quit->menuitem) ;


  gtk_menu_set_accel_group(GTK_MENU(menu->menu_files), menu->menu_files_accel_group) ;


  menu->menu_edition = gtk_menu_new() ;


  menu->edition_button = g_slice_new(MenuItem) ;

  setup_menu_item(menu->edition_button,"  Edition  ",NULL, "document-edit.png", NULL, 0, 0, 0) ;


  menu->undo = g_slice_new(MenuItem) ;

  setup_menu_item(menu->undo ,   "  Undo         "," Ctrl + Z ", "edit-undo.png", NULL, 0,0, 0) ;

  g_signal_connect(G_OBJECT(menu->undo->menuitem), "activate", G_CALLBACK(undo), NULL) ;


  menu->redo = g_slice_new(MenuItem) ;

  setup_menu_item(menu->redo ,   "  Redo         "," Ctrl + Maj + Z ", "edit-redo.png", NULL, 0, 0, 0) ;

  g_signal_connect(G_OBJECT(menu->redo->menuitem), "activate", G_CALLBACK(redo), NULL) ;


  menu->separator_06 = gtk_separator_menu_item_new () ;

  menu->find =  g_slice_new(MenuItem) ;

  setup_menu_item(menu->find ,   "  Find text   "," Ctrl + F ", "edit-find.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK, GDK_KEY_f, 0) ;

  g_signal_connect(G_OBJECT(menu->find->menuitem), "activate", G_CALLBACK(activate_search_accelator), NULL) ;


  menu->find_all =  g_slice_new(MenuItem) ;

  setup_menu_item(menu->find_all ,   "  Find all   "," Ctrl + Maj + F ", "system-search.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK  | GDK_SHIFT_MASK, GDK_KEY_f, 0) ;

  g_signal_connect(G_OBJECT(menu->find_all->menuitem), "activate", G_CALLBACK(search), NULL) ;


  menu->find_next =  g_slice_new(MenuItem) ;

  setup_menu_item(menu->find_next ,   "  Find next  "," Ctrl ++ ", "go-down-search.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK, GDK_KEY_KP_Add, 0) ;

  g_signal_connect(G_OBJECT(menu->find_next->menuitem), "activate", G_CALLBACK(search_next), NULL) ;


  menu->find_prev =  g_slice_new(MenuItem) ;

  setup_menu_item(menu->find_prev ,   "  Find previous  "," Ctrl  --  ", "go-up-search.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK, GDK_KEY_KP_Subtract, 0) ;

  g_signal_connect(G_OBJECT(menu->find_prev->menuitem), "activate", G_CALLBACK(search_previous), NULL) ;




  menu->replace =  g_slice_new(MenuItem) ;

  setup_menu_item(menu->replace ,"  Replace text  "," Ctrl + Enter ", "edit-find-replace.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK, GDK_KEY_KP_Enter, 0) ;

  g_signal_connect(G_OBJECT(menu->replace->menuitem), "activate", G_CALLBACK(replace_one_occurence), NULL) ;


  menu->replace_all =  g_slice_new(MenuItem) ;

  setup_menu_item(menu->replace_all ,"  Replace all            "," Ctrl + Maj + Enter ", "edit-find-replace.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK | GDK_SHIFT_MASK, GDK_KEY_KP_Enter, 0) ;

  g_signal_connect(G_OBJECT(menu->replace_all->menuitem), "activate", G_CALLBACK(replace_all_occurence), NULL) ;


  menu->go_to_line = g_slice_new(MenuItem) ;

  setup_menu_item(menu->go_to_line ,   "  Go to line number  "," Ctrl + G ", "edit-text-frame-update.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK, GDK_KEY_g, 0) ;

  g_signal_connect(G_OBJECT(menu->go_to_line->menuitem), "activate", G_CALLBACK(display_go_to_line_dialog), NULL) ;


  menu->separator_07 = gtk_separator_menu_item_new () ;


  menu->cut = g_slice_new(MenuItem) ;

  setup_menu_item(menu->cut ,   "  Cut  "," Ctrl + X ", "edit-cut.png", NULL, 0, 0, 0) ;

  g_signal_connect(G_OBJECT(menu->cut->menuitem), "activate", G_CALLBACK(cut), NULL) ;

  menu->copy = g_slice_new(MenuItem) ;

  setup_menu_item(menu->copy ,   "  Copy  "," Ctrl + C ", "edit-copy.png", NULL, 0, 0, 0) ;

  g_signal_connect(G_OBJECT(menu->copy->menuitem), "activate", G_CALLBACK(copy), NULL) ;

  menu->paste = g_slice_new(MenuItem) ;

  setup_menu_item(menu->paste ,   "  Paste  "," Ctrl + V ", "edit-paste.png", NULL, 0, 0, 0) ;

  g_signal_connect(G_OBJECT(menu->paste->menuitem), "activate", G_CALLBACK(paste), NULL) ;


  menu->duplicate = g_slice_new(MenuItem) ;

  setup_menu_item(menu->duplicate ,   "  Duplicate text  "," Ctrl + D ", "distribute-vertical-bottom.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK, GDK_KEY_d, 0) ;

  g_signal_connect(G_OBJECT(menu->duplicate->menuitem), "activate", G_CALLBACK(duplicate), NULL) ;



  menu->separator_08 = gtk_separator_menu_item_new () ;


  menu->switch_tabs  = g_slice_new(MenuItem) ;

  setup_menu_item(menu->switch_tabs,"  Use space instead of tabs "," Ctrl + P ", settings.use_spaces_as_tabs ? "tabs-off.png" :  "tabs-on.png", menu->menu_edition_accel_group, GDK_CONTROL_MASK , GDK_KEY_p, 0) ;

  g_signal_connect(G_OBJECT(menu->switch_tabs->menuitem), "activate", G_CALLBACK(toggle_use_space_instead_of_tabs), NULL) ;



  gtk_menu_set_accel_group(GTK_MENU(menu->menu_files),menu->menu_edition_accel_group) ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->edition_button->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->edition_button->menuitem),menu->menu_edition);


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->undo->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->redo->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->separator_06) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->find->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->find_all->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->find_next->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->find_prev->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->replace->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->replace_all->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->go_to_line->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->separator_07) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->cut->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->copy->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->paste->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->duplicate->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->separator_08) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_edition), menu->switch_tabs->menuitem) ;

  menu->menu_action   = gtk_menu_new() ;

  menu->actions_button = g_slice_new(MenuItem) ;

  setup_menu_item(menu->actions_button,"  Actions  ",NULL, "system-run.png", NULL, 0, 0, 0) ;


  menu->exec_cmd  = g_slice_new(MenuItem) ;

  setup_menu_item(menu->exec_cmd ,"  Execute a command  " ," Ctrl + E ", "application-x-executable-script.png", menu->menu_action_accel_group, GDK_CONTROL_MASK, GDK_KEY_e, 0) ;

  g_signal_connect(G_OBJECT(menu->exec_cmd->menuitem), "activate", G_CALLBACK(display_execute_command_dialog), NULL) ;


  menu->separator_09 = gtk_separator_menu_item_new() ;


  menu->switch_big_terms = g_slice_new(MenuItem) ;

  setup_menu_item(menu->switch_big_terms ,"  Big term(s) Switch      " ," Ctrl + Maj + B ", "utilities-log-viewer.png", menu->menu_action_accel_group, GDK_CONTROL_MASK | GDK_SHIFT_MASK, GDK_KEY_b, 0) ;

  g_signal_connect(G_OBJECT(menu->switch_big_terms->menuitem), "activate", G_CALLBACK(toogle_between_big_terminal_features), NULL) ;





  menu->add_term  = g_slice_new(MenuItem) ;

  setup_menu_item(menu->add_term ,"  Sidebar terms Add          ", " Ctrl + Maj + T ", "utilities-system-monitor.png", menu->menu_action_accel_group, GDK_CONTROL_MASK | GDK_SHIFT_MASK, GDK_KEY_t, 0) ;

  g_signal_connect(G_OBJECT(menu->add_term->menuitem), "activate", G_CALLBACK(add_new_terminals), NULL) ;


  menu->separator_10 = gtk_separator_menu_item_new () ;




  menu->files_handler  = g_slice_new(MenuItem) ;

  setup_menu_item(menu->files_handler ,"  File handler  "," Ctrl + H ", "quickopen-file.png", menu->menu_action_accel_group, GDK_CONTROL_MASK, GDK_KEY_h, 0) ;

  g_signal_connect(G_OBJECT(menu->files_handler->menuitem), "activate", G_CALLBACK(display_file_handler_dialog), NULL) ;


  menu->app_launcher  = g_slice_new(MenuItem) ;

  setup_menu_item(menu->app_launcher ,"  Application launcher  "," Ctrl + A ", "preferences-desktop-launch-feedback.png", menu->menu_action_accel_group, GDK_CONTROL_MASK, GDK_KEY_a, 0) ;

  g_signal_connect(G_OBJECT(menu->app_launcher->menuitem), "activate", G_CALLBACK(display_application_laucher_dialog), NULL) ;



  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->actions_button->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->actions_button->menuitem),menu->menu_action);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_action), menu->exec_cmd->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_action), menu->separator_09) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_action), menu->add_term->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_action), menu->switch_big_terms->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_action), menu->separator_10) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_action), menu->files_handler->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_action), menu->app_launcher->menuitem) ;








  menu->app_menubutton = g_slice_new(MenuItem) ;

  setup_menu_item(menu->app_menubutton,"  Applications  ", NULL, "preferences-desktop-icons.png", NULL, 0, 0, 0) ;


  menu->app_main_menu = gtk_menu_new() ;



  menu->app_programming_menuitem = g_slice_new(MenuItem) ;

  setup_menu_item(menu->app_programming_menuitem,"  Programming  ",NULL, "system-software-update.png", NULL, 0, 0, 0) ;


  menu->app_programming_menu = gtk_menu_new() ;

  menu->app_programming_diff = g_slice_new(MenuItem) ;

  gchar *gui_app_diff = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.diff)) ;
  setup_menu_item(menu->app_programming_diff, gui_app_diff, NULL, "text-x-ldif.png", NULL, 0, 0, 0) ;
  g_free(gui_app_diff) ;

  menu->app_programming_debugger = g_slice_new(MenuItem) ;
  gchar *gui_app_debugger = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.debugger)) ;
  setup_menu_item(menu->app_programming_debugger, gui_app_debugger, NULL, "debug-run.png", NULL, 0, 0, 0) ;
  g_free(gui_app_debugger) ;

  menu->app_programming_python = g_slice_new(MenuItem) ;
  gchar *gui_app_python = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.python)) ;
  setup_menu_item(menu->app_programming_python, gui_app_python, NULL, "python.png", NULL, 0, 0, 0) ;
  g_free(gui_app_python) ;

  menu->app_programming_gui_designer = g_slice_new(MenuItem) ;
  gchar *gui_app_gui_designer = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.gui_designer)) ;
  setup_menu_item(menu->app_programming_gui_designer, gui_app_gui_designer, NULL, "kde-windows.png", NULL, 0, 0, 0) ;
  g_free(gui_app_gui_designer) ;

  menu->app_programming_devhelp = g_slice_new(MenuItem) ;
  gchar *gui_app_devhelp = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.devhelp)) ;
  setup_menu_item(menu->app_programming_devhelp, gui_app_devhelp, NULL, "devhelp.png", NULL, 0, 0, 0) ;
  g_free(gui_app_devhelp) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_programming_menu), menu->app_programming_diff->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_programming_diff->menuitem), "activate", G_CALLBACK(launch_application), gui_app.diff) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_programming_menu), menu->app_programming_debugger->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_programming_debugger->menuitem), "activate", G_CALLBACK(launch_application), gui_app.debugger) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_programming_menu), menu->app_programming_python->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_programming_python->menuitem), "activate", G_CALLBACK(launch_application), gui_app.python) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_programming_menu), menu->app_programming_gui_designer->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_programming_gui_designer->menuitem), "activate", G_CALLBACK(launch_application), gui_app.gui_designer) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_programming_menu), menu->app_programming_devhelp->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_programming_devhelp->menuitem), "activate", G_CALLBACK(launch_application), gui_app.devhelp) ;






  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->app_menubutton->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->app_menubutton->menuitem), menu->app_main_menu) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_main_menu), menu->app_programming_menuitem->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->app_programming_menuitem->menuitem), menu->app_programming_menu) ;




  menu->app_utils_menuitem = g_slice_new(MenuItem) ;

  setup_menu_item(menu->app_utils_menuitem, "  Utilities  ", NULL, "system-software-update.png", NULL, 0, 0, 0) ;


  menu->app_utils_menu = gtk_menu_new() ;


  menu->app_utils_calculator = g_slice_new(MenuItem) ;
  gchar *gui_app_calculator = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.calculator)) ;
  setup_menu_item(menu->app_utils_calculator, gui_app_calculator, NULL, "accessories-calculator.png", NULL, 0, 0, 0) ;
  g_free(gui_app_calculator) ;

  menu->app_utils_color_picker = g_slice_new(MenuItem) ;
  gchar *gui_app_color_picker = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.color_picker)) ;
  setup_menu_item(menu->app_utils_color_picker, gui_app_color_picker, NULL, "kcolorchooser.png", NULL, 0, 0, 0) ;
  g_free(gui_app_color_picker) ;


  menu->app_utils_dictionary = g_slice_new(MenuItem) ;
  gchar *app_app_dictionary = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.dictionary)) ;
  setup_menu_item(menu->app_utils_dictionary, app_app_dictionary, NULL, "accessories-dictionary.png", NULL, 0, 0, 0) ;
  g_free(app_app_dictionary) ;

  menu->app_utils_file_manager = g_slice_new(MenuItem) ;
  gchar *gui_app_file_manager = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.file_manager)) ;
  setup_menu_item(menu->app_utils_file_manager, gui_app_file_manager, NULL, "system-file-manager.png", NULL, 0, 0, 0) ;
  g_free(gui_app_file_manager) ;

  menu->app_utils_notes = g_slice_new(MenuItem) ;
  gchar *gui_app_notes = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.notes)) ;
  setup_menu_item(menu->app_utils_notes, gui_app_notes, NULL, "knotes.png", NULL, 0, 0, 0) ;
  g_free(gui_app_notes) ;

  menu->app_utils_browser = g_slice_new(MenuItem) ;
  gchar *gui_app_browser = g_strdup_printf("  %s  ", g_path_get_basename(gui_app.browser) ) ;
  setup_menu_item(menu->app_utils_browser, gui_app_browser, NULL, "internet-web-browser.png", NULL, 0, 0, 0) ;
  g_free(gui_app_browser) ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_utils_menu), menu->app_utils_calculator->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_utils_calculator->menuitem), "activate", G_CALLBACK(launch_application), gui_app.calculator) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_utils_menu), menu->app_utils_color_picker->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_utils_color_picker->menuitem), "activate", G_CALLBACK(launch_application), gui_app.color_picker) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_utils_menu), menu->app_utils_dictionary->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_utils_dictionary->menuitem), "activate", G_CALLBACK(launch_application), gui_app.dictionary) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_utils_menu), menu->app_utils_file_manager->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_utils_file_manager->menuitem), "activate", G_CALLBACK(launch_application), gui_app.file_manager) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_utils_menu), menu->app_utils_notes->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_utils_notes->menuitem), "activate", G_CALLBACK(launch_application), gui_app.notes) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_utils_menu), menu->app_utils_browser->menuitem) ;
  g_signal_connect(G_OBJECT(menu->app_utils_browser->menuitem), "activate", G_CALLBACK(launch_application), gui_app.browser) ;




  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_main_menu), menu->app_utils_menuitem->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->app_utils_menuitem->menuitem), menu->app_utils_menu) ;


  menu->app_others_menuitem = g_slice_new(MenuItem) ;

  setup_menu_item(menu->app_others_menuitem, "  Others  ", NULL, "system-software-update.png", NULL, 0, 0, 0) ;


  menu->app_others_menu = gtk_menu_new() ;



  gint c=0 ;

  for (c=0 ; c < gui_app.nb_of_others ; ++c) {

    MenuItem *menu_item = g_malloc(sizeof(MenuItem)) ;

    gchar *menu_item_string =  g_strdup_printf("  %s  ", g_path_get_basename(gui_app.others[c])) ;

    setup_menu_item(menu_item, menu_item_string, NULL, "applications-system.png", NULL, 0, 0, 0) ;

    g_free(menu_item_string) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_others_menu), menu_item->menuitem) ;

    g_signal_connect(G_OBJECT(menu_item->menuitem), "activate", G_CALLBACK(launch_application), gui_app.others[c]) ;

  }


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->app_main_menu), menu->app_others_menuitem->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->app_others_menuitem->menuitem), menu->app_others_menu) ;


  menu->view_menubutton = g_slice_new(MenuItem) ;

  setup_menu_item(menu->view_menubutton ,"  View  ", NULL, "preferences-desktop-display-color.png", NULL, 0, 0, 0) ;

  bool is_big_term_menu_item = true ;

  menu->big_term  = g_slice_new(MenuItem) ;

  setup_menu_item(menu->big_term ,"  Big term(s)   Show|Hide  " ," Ctrl + B ", "applications-utilities.png", menu->menu_view_accel_group, GDK_CONTROL_MASK, GDK_KEY_b, 0) ;

  g_signal_connect(G_OBJECT(menu->big_term->menuitem), "activate", G_CALLBACK(toggle_display_big_terminal_and_main_interface), &is_big_term_menu_item) ;


  bool is_show_term_menu_item = true ;

  menu->show_term  = g_slice_new(MenuItem) ;

  setup_menu_item(menu->show_term ,"  Sidebar terms Show|Hide  "," Ctrl + T ", "utilities-terminal.png", menu->menu_view_accel_group, GDK_CONTROL_MASK, GDK_KEY_t, 0) ;

  g_signal_connect(G_OBJECT(menu->show_term->menuitem), "activate", G_CALLBACK(toggle_display_terminals), &is_show_term_menu_item) ;


  menu->separator_11 = gtk_separator_menu_item_new() ;


  menu->display_buttonbar = g_slice_new(MenuItem) ;

  setup_menu_item(menu->display_buttonbar ,"  Buttonbar Show|Hide  ", NULL, "configure-toolbars.png", NULL, 0, 0, 1) ;

  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu->display_buttonbar->menuitem), settings.buttonbar_on) ;



  menu->toggle_fullscreen = g_slice_new(MenuItem) ;

  setup_menu_item(menu->toggle_fullscreen ,"  Fullscreen  ", NULL, "view-fullscreen.png", NULL, 0, 0, 1) ;

  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu->toggle_fullscreen->menuitem), settings.fullscreen) ;


  menu->menu_view = gtk_menu_new() ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->view_menubutton->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->view_menubutton->menuitem),menu->menu_view);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_view), menu->big_term->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_view), menu->show_term->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_view), menu->separator_11) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_view), menu->display_buttonbar->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_view), menu->toggle_fullscreen->menuitem) ;








  menu->settings_button = g_slice_new(MenuItem) ;

  setup_menu_item(menu->settings_button,"  Settings  ",NULL, "preferences-other.png", NULL, 0, 0, 0) ;

  menu->syntax_highlight = g_slice_new(MenuItem) ;

  setup_menu_item(menu->syntax_highlight,"  Syntax highlight  ",NULL, "preferences-desktop-filetype-association.png", NULL, 0, 0, 0) ;


  menu->menu_settings = gtk_menu_new() ;

  menu->menu_syntax   = gtk_menu_new() ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->settings_button->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->settings_button->menuitem),menu->menu_settings);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_settings), menu->syntax_highlight->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->syntax_highlight->menuitem),menu->menu_syntax);

  g_object_set(G_OBJECT(menu->menu_syntax),"monitor", 11, NULL) ;


  GtkSourceLanguageManager *source_language_manager = gtk_source_language_manager_get_default() ;

  c=0 ;

  char *lang_id = (char *) gtk_source_language_manager_get_language_ids(source_language_manager)[c] ;

  menu->syntax_radiogroup = NULL ;

  GtkWidget *lang ;

  int col = 0 ;
  int row = 0 ;

  if (lang_id) {
    lang = gtk_radio_menu_item_new_with_label(menu->syntax_radiogroup, lang_id) ;

    menu->syntax_radiogroup = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM (lang));
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM (lang), FALSE);

    g_signal_connect(G_OBJECT(lang), "button-press-event", G_CALLBACK(set_syntax_highlight), lang_id) ;
    g_object_set_data(G_OBJECT(lang), "lang_id", lang_id) ;

    gtk_menu_attach (GTK_MENU(menu->menu_syntax),lang, row, row+1, col, col+1);


    while (1) {
      c++ ;
      col++ ;

      if (col == 22) {
        col=0 ;
        row++ ;
      }

      lang_id = (char *) gtk_source_language_manager_get_language_ids(source_language_manager)[c] ;

      if (lang_id == NULL) {
        break ;
      }

      lang = gtk_radio_menu_item_new_with_label(menu->syntax_radiogroup, lang_id) ;
      menu->syntax_radiogroup = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (lang));
      gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM (lang), FALSE);

      g_signal_connect(G_OBJECT(lang), "button-press-event", G_CALLBACK(set_syntax_highlight), lang_id) ;
      g_object_set_data(G_OBJECT(lang), "lang_id", lang_id) ;

      gtk_menu_attach (GTK_MENU(menu->menu_syntax),lang, row, row+1, col, col+1);
    }
  }

  lang = gtk_radio_menu_item_new_with_label(menu->syntax_radiogroup, "text") ;
  menu->syntax_radiogroup = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (lang));
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM (lang), TRUE);

  g_signal_connect(G_OBJECT(lang), "button-press-event", G_CALLBACK(set_syntax_highlight), lang_id) ;
  g_object_set_data(G_OBJECT(lang), "lang_id", "text") ;

  gtk_menu_attach (GTK_MENU(menu->menu_syntax),lang, row, row+1, col, col+1);


  menu->syntax_scheme = g_slice_new(MenuItem) ;

  setup_menu_item(menu->syntax_scheme,"  Editor schemes  ",NULL, "format-text-color.png", NULL, 0, 0, 0) ;

  menu->menu_scheme   = gtk_menu_new() ;



  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->settings_button->menuitem),menu->menu_settings);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_settings), menu->syntax_scheme->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->syntax_scheme->menuitem), menu->menu_scheme);

  GtkSourceStyleSchemeManager *style_scheme_manager = gtk_source_style_scheme_manager_get_default() ;

  /** NOTE:
      *
      * The differents schemes files are not they provide by the package manager
      * but provide from the program sources because they are more schemes available in the last version from gtksourceview-3.0 and on the web
      * as they provide from the current version on my system.
      * So if in any time their will be more schemes available in futures versions from gtksourceview-3.0 the programm will not provide them.
      * I will maybe fix it in the future.
      ***************************************************************************************************************************************/

  gtk_source_style_scheme_manager_append_search_path(style_scheme_manager, PATH_TO_SCHEME);


  //const gchar * const *schemes_string =  gtk_source_style_scheme_manager_get_scheme_ids(style_scheme_manager) ;

  const char *schemes_string[] = { "build", "classic", "cobalt", "emacs",  "kate", "matrix", "oblivion", "slate", "solarized-dark", "solarized-light", "tango", "turbo", "vsdark", NULL } ;

  c=0 ;

  char *scheme = (char *) schemes_string[c] ;

  GtkWidget *widget = NULL ;

  while ( scheme != NULL) {

    if ( c == 0) {

      widget = gtk_radio_menu_item_new_with_label(NULL, scheme) ;
    }
    else {

      widget = gtk_radio_menu_item_new_with_label_from_widget(GTK_RADIO_MENU_ITEM(widget), scheme) ;
    }

    g_signal_connect(G_OBJECT(widget), "activate", G_CALLBACK(set_scheme_highlight), scheme) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_scheme), widget) ;

    if (g_strcmp0(scheme, settings.scheme_default) == 0) {
       gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(widget), TRUE) ;
    }
    else {
      gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(widget), FALSE) ;
    }

    c++ ;

    scheme = (char *) schemes_string[c] ;

  }




  menu->program_setting = g_slice_new(MenuItem) ;

  setup_menu_item(menu->program_setting,"  Configure program  ", NULL, "preferences-desktop.png", NULL, 0, 0, 0) ;

  g_signal_connect(G_OBJECT(menu->program_setting->menuitem), "activate", G_CALLBACK(display_configuration_dialog), NULL) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_settings), menu->program_setting->menuitem) ;




  menu->menu_about   = gtk_menu_new() ;

  menu->about_button = g_slice_new(MenuItem) ;

  setup_menu_item(menu->about_button,"  About  ",NULL, "system-help.png", NULL, 0, 0, 0) ;


  menu->readme = g_slice_new(MenuItem) ;

  setup_menu_item(menu->readme,"  Readme  ",NULL, "help-contents.png", NULL, 0, 0, 0) ;

  g_signal_connect(G_OBJECT(menu->readme->menuitem), "activate", G_CALLBACK(launch_readme_html), NULL) ;


  menu->license = g_slice_new(MenuItem) ;

  setup_menu_item(menu->license,"  License  ",NULL, "document-edit-sign.png", NULL, 0, 0, 0) ;

  g_signal_connect(G_OBJECT(menu->license->menuitem), "activate", G_CALLBACK(launch_license_html), NULL) ;


  menu->about = g_slice_new(MenuItem) ;

  setup_menu_item(menu->about,"  About  ",NULL, "help-about.png", NULL, 0, 0, 0) ;

  g_signal_connect(G_OBJECT(menu->about->menuitem), "activate", G_CALLBACK(display_about_dialog), NULL) ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->about_button->menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->about_button->menuitem),menu->menu_about);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_about), menu->readme->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_about), menu->license->menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_about), menu->about->menuitem) ;


  return ;


}


void initialize_button_box(Buttons *buttons) {
  /** Initialize the button box. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  buttons->open_file_button = gtk_button_new_with_label("Open file");

  buttons->open_file_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "document-open.png") ;

  g_object_set(G_OBJECT(buttons->open_file_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->open_file_button), buttons->open_file_image);

  g_signal_connect(G_OBJECT(buttons->open_file_button),"clicked",G_CALLBACK(open_file),NULL) ;

  gtk_widget_set_tooltip_text(buttons->open_file_button, "Open a file \t [ Ctrl + O ].");



  buttons->save_file_button = gtk_button_new_with_label("Save") ;

  buttons->save_file_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "document-save.png") ;

  g_object_set(G_OBJECT(buttons->save_file_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->save_file_button), buttons->save_file_image);

  g_signal_connect(G_OBJECT(buttons->save_file_button),"clicked",G_CALLBACK(save_file),NULL) ;

  gtk_widget_set_tooltip_text(buttons->save_file_button, "Save current editor content to current file \t [ Ctrl + S ].");



  buttons->save_file_as_button = gtk_button_new_with_label("Save as") ;

  buttons->save_file_as_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "document-save-as.png") ;

  g_object_set(G_OBJECT(buttons->save_file_as_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->save_file_as_button), buttons->save_file_as_image);

  g_signal_connect(G_OBJECT(buttons->save_file_as_button),"clicked",G_CALLBACK(save_as_file),NULL) ;

  gtk_widget_set_tooltip_text(buttons->save_file_as_button, "Save current editor content to the selected file.");



  buttons->save_file_all_button = gtk_button_new_with_label("Save all") ;

  buttons->save_file_all_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "document-save-all.png") ;

  g_object_set(G_OBJECT(buttons->save_file_all_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->save_file_all_button), buttons->save_file_all_image);

  g_signal_connect(G_OBJECT(buttons->save_file_all_button), "clicked", G_CALLBACK(save_all_file), NULL) ;

  gtk_widget_set_tooltip_text(buttons->save_file_all_button, "Save all files \t [ Ctrl + Maj + S ].");



  buttons->tabs_button = gtk_button_new_with_label("") ;

  buttons->tabs_image  = gtk_image_new_from_file( settings.use_spaces_as_tabs ? PATH_TO_BUTTON_ICON "tabs-off.png"  : PATH_TO_BUTTON_ICON "tabs-on.png") ;

  g_object_set(G_OBJECT(buttons->tabs_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->tabs_button), buttons->tabs_image);

  g_signal_connect(G_OBJECT(buttons->tabs_button), "clicked", G_CALLBACK(toggle_use_space_instead_of_tabs), NULL) ;

  gtk_widget_set_tooltip_text(buttons->tabs_button, "Use space instead of tabs \t [ Ctrl + P ].") ;



  buttons->cut_button = gtk_button_new_with_label("") ;

  buttons->cut_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "edit-cut.png") ;

  g_object_set(G_OBJECT(buttons->cut_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->cut_button), buttons->cut_image);

  g_signal_connect(G_OBJECT(buttons->cut_button), "clicked", G_CALLBACK(cut), NULL) ;

  gtk_widget_set_tooltip_text(buttons->cut_button, "Cut selected text and copy it to clipboard \t [ Ctrl + X ].");



  buttons->copy_button = gtk_button_new_with_label("") ;

  buttons->copy_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "edit-copy.png") ;

  g_object_set(G_OBJECT(buttons->copy_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->copy_button), buttons->copy_image);

  g_signal_connect(G_OBJECT(buttons->copy_button), "clicked", G_CALLBACK(copy), NULL) ;

  gtk_widget_set_tooltip_text(buttons->copy_button, "Copy selected to clipboard \t [ Ctrl + C ].");



  buttons->paste_button = gtk_button_new_with_label("") ;

  buttons->paste_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "edit-paste.png") ;

  g_object_set(G_OBJECT(buttons->paste_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->paste_button), buttons->paste_image);

  g_signal_connect(G_OBJECT(buttons->paste_button), "clicked", G_CALLBACK(paste), NULL) ;

  gtk_widget_set_tooltip_text(buttons->paste_button, "Paste clipboard content at cursor position in the current editor \t [ Ctrl + V ].");



  buttons->duplicate_button = gtk_button_new_with_label("") ;

  buttons->duplicate_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "distribute-vertical-bottom.png") ;

  g_object_set(G_OBJECT(buttons->duplicate_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->duplicate_button), buttons->duplicate_image);

  g_signal_connect(G_OBJECT(buttons->duplicate_button),"clicked",G_CALLBACK(duplicate),NULL) ;

  gtk_widget_set_tooltip_text(buttons->duplicate_button, "Duplicate the selected text or the line at current cursor position \t [ Ctrl + D ].");



  buttons->go_to_line_button = gtk_button_new_with_label("Go to line") ;

  buttons->go_to_line_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "edit-text-frame-update.png") ;

  g_object_set(G_OBJECT(buttons->go_to_line_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->go_to_line_button), buttons->go_to_line_image);

  g_signal_connect(G_OBJECT(buttons->go_to_line_button),"clicked",G_CALLBACK(display_go_to_line_dialog),NULL) ;

  gtk_widget_set_tooltip_text(buttons->go_to_line_button, "Go to the given line number \t [ Ctrl + G ].");



  buttons->search_and_replace_button   = gtk_toggle_button_new_with_label("Find & Replace") ;

  buttons->search_and_replace_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "system-search.png") ;

  g_object_set(G_OBJECT(buttons->search_and_replace_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->search_and_replace_button), buttons->search_and_replace_image);

  g_signal_connect(G_OBJECT(buttons->search_and_replace_button),"toggled",G_CALLBACK(toggle_display_search_and_replace_bar),NULL) ;

  gtk_widget_set_tooltip_text(buttons->search_and_replace_button, "Show | Hide the search & replace bar.\n[ Ctrl + F ] -> Set the selected text as search term.");






  buttons->exec_button       = gtk_button_new_with_label("Cmd") ;

  buttons->exec_image        = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "system-run.png") ;

  g_object_set(G_OBJECT(buttons->exec_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->exec_button), buttons->exec_image);

  g_signal_connect(G_OBJECT(buttons->exec_button), "clicked", G_CALLBACK(display_execute_command_dialog), NULL) ;

  gtk_widget_set_tooltip_text(buttons->exec_button, "Run a command in a terminal (per example man [section] page)\t[ Ctrl + E ].");

  gtk_widget_add_accelerator(buttons->exec_button,
                             "activate",
                             gui->buttons_accel_group,
                             GDK_KEY_e,
                             GDK_CONTROL_MASK,
                             GTK_ACCEL_VISIBLE);




  buttons->big_terminal_button = gtk_toggle_button_new_with_label("Big") ;

  buttons->big_terminal_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "applications-utilities.png") ;

  g_object_set(G_OBJECT(buttons->big_terminal_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->big_terminal_button), buttons->big_terminal_image);

  g_signal_connect(G_OBJECT(buttons->big_terminal_button),"clicked", G_CALLBACK(toggle_display_big_terminal_and_main_interface), NULL) ;

  gtk_widget_set_tooltip_text(buttons->big_terminal_button, "Switch between big terminal(s) and main interface [ Ctrl + b ].\n[ Ctrl + Maj + b ] For switching between big terminal(s) features.");



  buttons->terminals_show_button = gtk_toggle_button_new_with_label("Show") ;

  buttons->terminals_show_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "utilities-terminal.png") ;

  g_object_set(G_OBJECT(buttons->terminals_show_button),"always-show-image",TRUE,NULL) ;

  gtk_button_set_image(GTK_BUTTON(buttons->terminals_show_button), buttons->terminals_show_image);

  g_signal_connect(G_OBJECT(buttons->terminals_show_button),"toggled",G_CALLBACK(toggle_display_terminals),NULL) ;

  gtk_widget_set_tooltip_text(buttons->terminals_show_button, "Show | Hide the terminals window \t [ Ctrl + T ].");

  gtk_widget_add_accelerator(buttons->terminals_show_button,
                            "activate",
                            gui->buttons_accel_group,
                            GDK_KEY_t,
                            GDK_CONTROL_MASK,
                            GTK_ACCEL_VISIBLE);


  return ;
}




void initialize_terminal(Terminal *terminal) {
  /** Pack a terminal with a GtkScrollbar in a container. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  terminal->terminal = vte_terminal_new() ;

  terminal->terminal_scrollbar = gtk_scrollbar_new( GTK_ORIENTATION_VERTICAL, gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(terminal->terminal)) ) ;

  terminal->terminal_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0)  ;


  gtk_box_pack_start(GTK_BOX(terminal->terminal_hbox), terminal->terminal,           TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(terminal->terminal_hbox), terminal->terminal_scrollbar, FALSE, FALSE, 0) ;

  gtk_box_set_homogeneous(GTK_BOX(terminal->terminal_hbox),FALSE);

  return ;

}

void setup_terminal(GtkWidget *vteterminal) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  extern GUI *gui ;

  /** Configure terminal partially according to the configuration stored settings. **/
  configure_terminal(vteterminal, true) ;


  char *argv_cmd[2] = {settings.user_shell, NULL} ;

  /** Fork a new process: your default shell. The configurations files like .bashrc will be reading. **/
  vte_terminal_fork_command_full(VTE_TERMINAL(vteterminal), VTE_PTY_DEFAULT, settings.start_dir, argv_cmd, NULL, G_SPAWN_DEFAULT | G_SPAWN_LEAVE_DESCRIPTORS_OPEN | G_SPAWN_CHILD_INHERITS_STDIN, NULL,NULL, NULL, NULL);


  if ((settings.command != NULL) && (g_strcmp0(settings.command, "") != 0) ) {
    // Wait for the forking has been done.
    usleep(150000) ;

    char *command_string ;
    command_string = g_strdup_printf("%s \r", settings.command) ;

    // Launch the wanted command in the terminal.
    vte_terminal_feed_child(VTE_TERMINAL(vteterminal), command_string, strlen(command_string)) ;

    free(command_string) ;

  }

  /** Generate clipboard menu connect to the terminal. **/
  GtkWidget *clipboard_menu = gtk_menu_new() ;

  GtkWidget *copy_label  = gtk_menu_item_new_with_label("Copy from terminal") ;
  GtkWidget *paste_label = gtk_menu_item_new_with_label("Paste  to terminal") ;

  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu),copy_label)  ;
  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu),paste_label) ;

  GtkAccelGroup *accel_group ;

  accel_group = gtk_accel_group_new() ;
  gtk_window_add_accel_group(GTK_WINDOW(gui->main_window), accel_group);

  gtk_widget_add_accelerator(GTK_WIDGET(copy_label),  "activate", accel_group, GDK_KEY_Copy,   GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE) ;
  gtk_widget_add_accelerator(GTK_WIDGET(paste_label), "activate", accel_group, GDK_KEY_Insert, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE) ;


  gtk_widget_show_all(clipboard_menu) ;

  g_signal_connect(G_OBJECT(vteterminal), "button-press-event", G_CALLBACK(display_clipboard_menu), clipboard_menu) ;

  g_signal_connect(G_OBJECT(copy_label),  "activate", G_CALLBACK(clipboard_copy),  vteterminal) ;
  g_signal_connect(G_OBJECT(paste_label), "activate", G_CALLBACK(clipboard_paste), vteterminal) ;


  return ;

 }
