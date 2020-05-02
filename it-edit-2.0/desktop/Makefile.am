desktopdir = $(DESTDIR)/usr/share/applications


desktop:
	@echo "[Desktop Entry]" > $(desktopdir)/$(PACKAGE).desktop
	@echo "Name=it-edit" >> $(desktopdir)/$(PACKAGE).desktop
	@echo "GenericName=Integrated Terminals Editor" >> $(desktopdir)/$(PACKAGE).desktop
	@echo "Comment=Integrated terminals programming text editor with severals others functionnalities." >> $(desktopdir)/$(PACKAGE).desktop
	@echo "Exec=it-edit %U" >> $(desktopdir)/$(PACKAGE).desktop
	@echo "Icon=$(pkgdatadir)/Icons/it-edit_icon.png" >> $(desktopdir)/$(PACKAGE).desktop
	@echo "Terminal=false" >> $(desktopdir)/$(PACKAGE).desktop
	@echo "X-MultipleArgs=false" >> $(desktopdir)/$(PACKAGE).desktop
	@echo "StartupNotify=true" >> $(desktopdir)/$(PACKAGE).desktop
	@echo "Type=Application" >> $(desktopdir)/$(PACKAGE).desktop
	@echo "MimeType=text/x-actionscript;text/x-ada;text/x-adasrc;text/x-asp;application/x-asp;application/x-asap;application/x-awk;text/x-bibtex;text/x-boo;text/x-c;text/x-csrc;image/x-xpixmap;text/x-csharpsrc;text/x-csharp;text/x-c++;text/x-cpp;text/x-c++src;text/x-chdr;text/x-c++hdr;text/x-changelog;text/css;text/x-dsrc;application/x-gnome-app-info;application/x-desktop;text/x-diff;text/x-patch;application/docbook+xml;text/x-dpatch;text/x-dtd;text/x-eiffel;text/x-erlang;text/x-fsharp;text/x-forth;text/x-fortran;text/x-gap;text/x-po;text/x-pot;text/x-pox;text/x-gettext-translation;text/x-gettext-translation-template;text/vnd.graphviz;text/x-gtkrc;text/x-haskell;text/html;text/x-idl;text/x-ini-file;application/x-ini-file;text/x-java;application/javascript;application/x-javascript;text/x-javascript;text/javascript;text/x-js;text/x-tex;text/x-libtool;text/x-literate-haskell;text/x-lua;application/x-m4;text/x-makefile;text/x-markdown;text/x-octave;text/x-matlab;text/x-modelica;text/x-nemerle;text/x-netrexx;text/x-objcsrc;text/x-objective-j;text/x-ocaml;text/x-ocl;text/x-pascal;text/x-perl;application/x-perl;text/x-php;application/x-php;text/x-php-source;application/x-php-source;text/x-pkg-config;text/x-prolog;text/x-protobuf;text/x-python;application/x-python;text/x-R;text/x-rpm-spec;application/x-ruby;text/x-ruby;text/x-scala;text/x-scheme;text/x-shellscript;application/x-shellscript;text/x-sh;application/sparql-query;text/x-sql;text/x-tcl;application/x-tcl;text/x-texinfo;text/x-vala;text/x-vbnet;text/x-vb;text/x-verilog-src;text/x-vhdl;application/xml;text/xml;application/xslt+xml;text/x-yacc;text/x-bison;"  >> $(desktopdir)/$(PACKAGE).desktop
	@echo "Keywords=ITE;Development;Programming;Editor;Terminal;Text;Plaintext;Write;"  >> $(desktopdir)/$(PACKAGE).desktop
	@echo "Categories=Development;IDE;GTK;"  >> $(desktopdir)/$(PACKAGE).desktop
	@echo "desktop file generated at: $(desktopdir)/$(PACKAGE).desktop"
                    
install-data-hook:
	$(MKDIR_P) -m a+w "$(desktopdir)"
	$(MAKE) desktop
	$(MKDIR_P) -m a+w "$(DESTDIR)$(pkgdatadir)/Configuration"
	$(CHMOD) a+w "$(DESTDIR)$(pkgdatadir)/Files_handler"
	$(CHMOD) a+w "$(DESTDIR)$(pkgdatadir)/Files_handler/Files_handler.conf"

uninstall-hook:
	- $(RM) -f $(desktopdir)/$(PACKAGE).desktop
	- $(RM) -R -f "$(DESTDIR)$(pkgdatadir)"
	- $(RM) -R -f "$(DESTDIR)$(docdir)"
                      
