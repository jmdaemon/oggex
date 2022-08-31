#include <glib/gi18n.h>

#include "oggex-config.h"
#include "oggex-application.h"

//#include "cli.h"
//#include "ogx.h"
#include "oggex_gtk.h"

int main (int argc, char **argv) {
	args.args[0] = (char*) "";
	args = set_default_args();
	args.verbose = 1;
	setup_logging(args);

	g_autoptr(OggexApplication) app = NULL;
	int ret;

	/* Set up gettext translations */
	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	/*
	 * Create a new GtkApplication. The application manages our main loop,
	 * application windows, integration with the window manager/compositor, and
	 * desktop features such as file opening and single-instance applications.
	 */
	app = oggex_application_new ("io.github.com.jmdaemon.oggex", G_APPLICATION_FLAGS_NONE);

	/*
	 * Run the application. This function will block until the application
	 * exits. Upon return, we have our exit code to return to the shell. (This
	 * is the code you see when you do `echo $?` after running a command in a
	 * terminal.
	 *
	 * Since GtkApplication inherits from GApplication, we use the parent class
	 * method "run". But we need to cast, which is what the "G_APPLICATION()"
	 * macro does.
	 */
	ret = g_application_run (G_APPLICATION (app), argc, argv);

	return ret;
}
