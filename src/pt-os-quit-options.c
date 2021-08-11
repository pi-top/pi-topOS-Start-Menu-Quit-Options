/*
Copyright (c) 2018 Raspberry Pi (Trading) Ltd.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>

#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdkx.h>

static void get_string (char *cmd, char *name)
{
    FILE *fp = popen (cmd, "r");
    char buf[128];

    name[0] = 0;
    if (fp == NULL) return;
    if (fgets (buf, sizeof (buf) - 1, fp) != NULL)
    {
        sscanf (buf, "%s", name);
    }
    pclose (fp);
}

void button_handler (GtkWidget *widget, gpointer data)
{
    if (!strcmp (data, "shutdown")) system ("/sbin/shutdown -h now");
    if (!strcmp (data, "reboot")) system ("/sbin/reboot");
    if (!strcmp (data, "recovery"))
    {
        system ("/usr/bin/rm /recovery/autoboot.txt");
        system ("/sbin/reboot");
    }
}

gint delete_event (GtkWidget *widget, GdkEvent *event, gpointer data)
{
    gtk_main_quit ();
    return FALSE;
}

static gboolean check_escape (GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Escape) {
        gtk_main_quit ();
        return TRUE;
    }
    return FALSE;
}

/* The dialog... */

int main (int argc, char *argv[])
{
    GtkWidget *dlg, *btn, *box;
    GtkRequisition req;
    char buffer[128];
    int width;

#ifdef ENABLE_NLS
    setlocale (LC_ALL, "");
    bindtextdomain ( GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR );
    bind_textdomain_codeset ( GETTEXT_PACKAGE, "UTF-8" );
    textdomain ( GETTEXT_PACKAGE );
#endif

    // GTK setup
    gtk_init (&argc, &argv);
    gtk_icon_theme_prepend_search_path (gtk_icon_theme_get_default(), PACKAGE_DATA_DIR);

    // build the UI
    dlg = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (dlg), _("Shutdown Options"));

    gtk_container_set_border_width (GTK_CONTAINER (dlg), 10);
    gtk_window_set_icon (GTK_WINDOW (dlg), gdk_pixbuf_new_from_file ("/usr/share/icons/Papirus/64x64/apps/system-shutdown.svg", NULL));
    gtk_window_set_resizable (GTK_WINDOW (dlg), FALSE);
    gtk_signal_connect (GTK_OBJECT (dlg), "delete_event", G_CALLBACK (delete_event), NULL);
    gtk_signal_connect (GTK_OBJECT (dlg), "key_press_event", G_CALLBACK(check_escape), NULL);

    box = gtk_table_new (3, 1, TRUE);

    gtk_table_set_row_spacings (GTK_TABLE (box), 5);

    gtk_container_add (GTK_CONTAINER (dlg), box);

    // use dummy button to find title width
    btn = gtk_button_new_with_mnemonic (_("Shutdown Options"));
    gtk_widget_size_request (btn, &req);
    width = req.width * 2;

    btn = gtk_button_new_with_mnemonic (_("Shutdown"));
    gtk_signal_connect (GTK_OBJECT (btn), "clicked", G_CALLBACK (button_handler), "shutdown");
    gtk_table_attach_defaults (GTK_TABLE (box), btn, 0, 1, 0, 1);
    gtk_widget_size_request (btn, &req);
    if (req.width < width) gtk_widget_set_size_request (box, width, -1);

    btn = gtk_button_new_with_mnemonic (_("Reboot"));
    gtk_widget_size_request (btn, &req);
    if (req.width < width) gtk_widget_set_size_request (box, width, -1);
    gtk_signal_connect (GTK_OBJECT (btn), "clicked", G_CALLBACK (button_handler), "reboot");
    gtk_table_attach_defaults (GTK_TABLE (box), btn, 0, 1, 1, 2);

    btn = gtk_button_new_with_mnemonic (_("Reboot into pi-topOS Recovery"));
    gtk_widget_size_request (btn, &req);
    if (req.width < width) gtk_widget_set_size_request (box, width, -1);
    gtk_signal_connect (GTK_OBJECT (btn), "clicked", G_CALLBACK (button_handler), "recovery");
    gtk_table_attach_defaults (GTK_TABLE (box), btn, 0, 1, 2, 3);

    gtk_window_set_position (GTK_WINDOW(dlg), GTK_WIN_POS_CENTER_ALWAYS);
    gtk_widget_show_all (dlg);

    gtk_main ();

    return 0;
}
