bin_PROGRAMS = lxde-pt-os-quit-options

lxde_pt_os_quit_options_CFLAGS = \
	-I$(top_srcdir) \
	-DPACKAGE_LIB_DIR=\""$(libdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)/pt-os-quit-options"\" \
	-DPACKAGE_UI_DIR=\""$(datadir)/pt-os-quit-options/ui"\" \
	-DPACKAGE_BIN_DIR=\""$(bindir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(PACKAGE_CFLAGS) \
	$(G_CAST_CHECKS)

lxde_pt_os_quit_options_SOURCES = pt-os-quit-options.c

lxde_pt_os_quit_options_includedir = $(includedir)/pt-os-quit-options

lxde_pt_os_quit_options_include_HEADERS =

lxde_pt_os_quit_options_LDFLAGS = $(DYNAMIC_FLAGS)
lxde_pt_os_quit_options_DEPENDENCIES_EXTRA = $(BUILTIN_PLUGINS)

lxde_pt_os_quit_options_LDADD = \
		$(BUILTIN_PLUGINS) \
		$(PACKAGE_LIBS) \
		$(X11_LIBS) \
		$(INTLLIBS)

EXTRA_DIST =
