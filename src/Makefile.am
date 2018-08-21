bin_PROGRAMS = lxde-pi-shutdown-helper

lxde_pi_shutdown_helper_CFLAGS = \
	-I$(top_srcdir) \
	-DPACKAGE_LIB_DIR=\""$(libdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)/pt-shutdown-helper"\" \
	-DPACKAGE_UI_DIR=\""$(datadir)/pt-shutdown-helper/ui"\" \
	-DPACKAGE_BIN_DIR=\""$(bindir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(PACKAGE_CFLAGS) \
	$(G_CAST_CHECKS)

lxde_pi_shutdown_helper_SOURCES = pt-shutdown-helper.c

lxde_pi_shutdown_helper_includedir = $(includedir)/pt-shutdown-helper

lxde_pi_shutdown_helper_include_HEADERS =

lxde_pi_shutdown_helper_LDFLAGS = $(DYNAMIC_FLAGS)
lxde_pi_shutdown_helper_DEPENDENCIES_EXTRA = $(BUILTIN_PLUGINS)

lxde_pi_shutdown_helper_LDADD = \
		$(BUILTIN_PLUGINS) \
		$(PACKAGE_LIBS) \
		$(X11_LIBS) \
		$(INTLLIBS)

EXTRA_DIST =
