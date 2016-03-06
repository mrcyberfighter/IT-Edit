AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = it-edit

#EXTRA_DIST = Configuration/ \
#             Files_handler/ \
#             Icons/         \
#             README/        \
#

it_edit_SOURCES = ./main.c \
                  ./Callbacks/configuration_callbacks.c \
                  ./Callbacks/edition_callbacks.c \
                  ./Callbacks/editor_callbacks.c \
                  ./Callbacks/files_callbacks.c \
                  ./Callbacks/gui_callbacks.c \
                  ./Callbacks/highlight_selection_callbacks.c \
                  ./Callbacks/search_settings_callbacks.c \
                  ./Callbacks/terminals_callbacks.c \
                  ./GUI/configure/configuration_dialog.c \
                  ./GUI/configure/configure_gui_elements.c \
                  ./GUI/dialogs/message_dialog.c \
                  ./GUI/dialogs/dialogs.c \
                  ./GUI/setup/setup_gui.c \
                  ./Editor/editor.c \
                  ./Resizer/Resizer.c \
                  ./Configuration/configuration.c \
                  ./DEBUG/debug_search_by_signals.c \
                  ./Headers/global_vars.c

EXTRA_DIST =      ./Callbacks/*.h             \
                  ./GUI/configure/*.h         \
                  ./GUI/dialogs/*.h           \
                  ./GUI/setup/*.h             \
                  ./Editor/*.h                \
                  ./Resizer/*.h               \
                  ./Configuration/*.h         \
                  ./DEBUG/*.h                 \
                  ./Headers/*.h               \
                  ./Headers/Structures/*.h

it_edit_CPPFLAGS = -DPREFIX=\"$(DESTDIR)$(prefix)\"
              
it_edit_CFLAGS = $(GTK_CFLAGS) $(GTKSOURCEVIEW_CFLAGS)

it_edit_LDADD = $(GTK_LIBS) $(GTKSOURCEVIEW_LIBS)                 