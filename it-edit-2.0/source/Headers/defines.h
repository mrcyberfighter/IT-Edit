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

#ifndef IT_EDIT_DEFINES_HH
#define IT_EDIT_DEFINES_HH



/** About definition: **/
#define AUTHOR                  "Brüggemann Eddie"
#define MAIL                    "<mrcyberfighter@gmail.com>"
#define PRGNAME                 "it-edit"
#define VERSION                 "2.0"
#define LICENSE                 "GPLv3"
#define PRGWEBURL               "http://www.open-source-projects.net/IT-Edit/IT-Edit_presentation.html"
#define COPYRIGHT               "Copyright (C) 2016 Brüggeman Eddie GPLv3 License."


/** Conditional Prefix definition. **/
#ifndef PREFIX
#define PREFIX ".."
#endif

/** Path definitions: **/
#define DATADIR                 PREFIX "/share/it-edit"

#define PATH_TO_TEXTURE         DATADIR "/Textures/Textures/"

#define PATH_TO_SCHEME          DATADIR "/Styles"

#define PATH_TO_CONF_FILE       DATADIR "/Configuration/it-edit.conf"

#define PATH_TO_APP_FILE        DATADIR "/Configuration/gui-applications.conf"



#define PATH_TO_TINY_IMAGE      DATADIR "/Textures/Textures_tiny/"

#define PATH_TO_LINKS_FILE      DATADIR "/Files_handler/Files_handler.conf"

#define PATH_TO_ICON            DATADIR "/Icons/it-edit_icon.png"

#define PATH_TO_README          DATADIR "/README/README.html"

#define PATH_TO_GPL_TEXT        DATADIR "/License/gpl.txt"

#define PATH_TO_GPL_HTML        DATADIR "/License/gpl.html"
   
/** Image path **/
#define PATH_TO_IMAGE           DATADIR "/Icons/"

#define PATH_TO_MENU_ICON       PATH_TO_IMAGE      "/16x16/"
#define PATH_TO_BUTTON_ICON     PATH_TO_IMAGE      "/22x22/"

#define PATH_TO_MIMETYPE_ICON   PATH_TO_MENU_ICON  "/mimetypes/"

#define PATH_TO_MIMETYPE_BIG    PATH_TO_IMAGE      "/64x64/" "mimetypes/"

#define PATH_TO_BIN_FOLDER      "/usr/bin"

#define PATH_TO_IT_EDIT         PREFIX  "/bin/it-edit"



#define USR_R(m)  S_IRUSR & (m)
#define USR_W(m)  S_IWUSR & (m)
#define USR_X(m)  S_IXUSR & (m)

#define GRP_R(m)  S_IRGRP & (m)
#define GRP_W(m)  S_IWGRP & (m)
#define GRP_X(m)  S_IXGRP & (m)

#define OTH_R(m)  S_IROTH & (m)
#define OTH_W(m)  S_IWOTH & (m)
#define OTH_X(m)  S_IXOTH & (m)


#ifdef TRIBOOL // The idea is to make a trilogic boolean type.
#include <stdint.h>

typedef int_least8_t tbool ; // This doens't really make sens but we can do this in assembly with (a one or two)  bit test feature...

tbool tb_minus = -1 ;
tbool tb_none  =  0 ;
tbool tb_plus  =  1 ;

#endif


#ifdef DEBUG
#define DEBUG_PT          fprintf(stderr,"\n%s:%s(...) at line: %d\n", __FILE__, __func__, __LINE__) ;

#define DEBUG_INT(x)      fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;
#define DEBUG_LINT(x)     fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;
#define DEBUG_LLINT(x)    fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;

#define DEBUG_FLOAT(x)    fprintf(stderr,"DEBUG PT N° %f\n",   (x)) ;
#define DEBUG_DOUBLE(x)   fprintf(stderr,"DEBUG PT N° %lf\n",  (x)) ;
#define DEBUG_LDOUBLE(x)  fprintf(stderr,"DEBUG PT N° %llf\n", (x)) ;

#define DEBUG_STR(str)          fprintf(stderr,"%s\n", (str)) ;
#define DEBUG_PTR(ptr)          fprintf(stderr,"%p\n", (ptr)) ;


// Extended DEBUGGING
#define EDEBUG_INT(str, x)      fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LINT(str, x)     fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LLINT(str, x)    fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;

#define EDEBUG_FLOAT(str, x)    fprintf(stderr,"%s(line:%d): %s %f\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_DOUBLE(str, x)   fprintf(stderr,"%s(line:%d): %s %lf\n",  __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LDOUBLE(str, x)  fprintf(stderr,"%s(line:%d): %s %llf\n", __func__, __LINE__, (str), (x)) ;

#define EDEBUG_STR(str)        fprintf(stderr,"%s(%d): %s\n", __func__, __LINE__, (str)) ;
#define EDEBUG_PTR(ptr)        fprintf(stderr,"%s(%d): %s\n", __func__, __LINE__, (ptr)) ;

#define DEBUG_FUNC_MARK        fprintf(stderr,"\n%s:%s(...) called\n",__FILE__, __func__) ;

#endif



#ifndef PATH_MAX
#define PATH_MAX 255 // MAX_PATH
#endif


#endif