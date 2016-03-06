#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([it-edit], [2.0], [mrcyberfighter@gmail.com], , [http://www.open-source-projects.net/IT-Edit/IT-Edit_presentation.html])
AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])


AC_COPYRIGHT([GPLv3])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_LN_S

AC_PATH_PROG([CHMOD], [chmod], AC_MSG_ERROR(Install the coreutils package !, 1))
AC_PATH_PROG([CP],    [cp],    AC_MSG_ERROR(Install the coreutils package !, 1))
AC_PATH_PROG([RM],    [rm],    AC_MSG_ERROR(Install the coreutils package !, 1))
AC_PATH_PROG([WC],    [wc],    AC_MSG_ERROR(Install the coreutils package !, 1))
AC_PATH_PROG([SED],   [sed],   AC_MSG_ERROR(Install the sed program !, 1))

# Checks for libraries.
PKG_CHECK_MODULES([GTK], [gtk+-3.0], , AC_MSG_ERROR(   gtk+3.0 library not detected !!!

   ******************* GTK 3 library required for it-edit *****************
   Install the GTK 3 library from your package manager or from source.

   WARNING: Take care to install the development files from gtk-3 !!!
            Often call: libgtk-3-dev or libgtk-3-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

PKG_CHECK_MODULES([GTKSOURCEVIEW], [gtksourceview-3.0], , AC_MSG_ERROR(   gtksourceview-3.0 library not detected !!!

   ************* gtksourceview-3.0 library required for it-edit ***********
   Install the gtksourceview-3.0 library from your package manager or
   from source.

   You must have the package: libgtksourceview-3.0-common installed too.

   This package provide common files for the GTK+ syntax highlighting
   widget GtkSourceView: this is a text widget that extends the standard
   GTK+ 3.x text widget GtkTextView.

   It improves GtkTextView by implementing syntax highlighting and
   other features typical of a source editor.

   WARNING: Take care to install the development files from gtksourceview !
            Often call: libgtksourceview-3.0-dev or
                        libgtksourceview-3.0-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))


AC_CHECK_LIB([vte2_90],
             [vte_terminal_new],
             ,
             AC_MSG_ERROR(   vte2_90 library not detected !!!

   ****************** vte2_90 library required for it-edit ****************
   Install the vte2_90 library from your package manager or from source.

   WARNING: Take care to install the development files from vte2_90 !!!
            Often call: libvte-2.90-dev or libvte-2.90-devel.

   WARNING: If you install from source install the version 0.34.
            If you install a greater version as 0.34 it won't work.
            Because it is difficult to remark that libvte > 0.34 is
            libvte-2.91 wenn installing from source.
       
   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))


AC_CHECK_LIB([m],
             [roundf],
             ,
             AC_MSG_ERROR(Math library required from it-edit, 1))

# Checks for header files.
AC_CHECK_HEADERS([stdio.h string.h limits.h fcntl.h inttypes.h locale.h stdint.h unistd.h stdlib.h string.h math.h sys/time.h sys/stat.h sys/types.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gettimeofday realpath setlocale strchr strrchr])

AC_CONFIG_FILES([Makefile
                 source/Makefile
                 data/Makefile
                 texi/Makefile
                 man/Makefile
                 desktop/Makefile
                 doc/Makefile])



AC_OUTPUT

AC_MSG_NOTICE(System check OK !!!)

echo "
  ************************ ${PACKAGE_STRING} **********************

  Package: ${PACKAGE_NAME}
  Version: ${PACKAGE_VERSION}
 
  ${PACKAGE_NAME} an integrated terminals programming text editor
  with severals others functionnalities.
 
  Package dependencies: gtk-3, gtksourceview.3.0, vte2_90, math.
 
  Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}

  Prefix: ${prefix}

  Author: Brüggemann Eddie.
  contact: ${PACKAGE_BUGREPORT}

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}."
