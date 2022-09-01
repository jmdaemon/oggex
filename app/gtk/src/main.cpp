#include <glib/gi18n.h>
#include <gio/gio.h>

#include "oggex-config.h"
#include "oggex-application.h"
#include "oggex_gtk.h"

/* Disable command line parsing with glib */
static int command_line (GApplication *application, GApplicationCommandLine /* *cmdline */) {
	// Show gtk app
	g_application_activate(application);
  return 0;
}

int main (int argc, char **argv) {
	// Current arg parsing code
	// Defaults the arguments and toggles logging by default

	args.args[0] = (char*) "";
	args = set_default_args();
	args.nolimit = true;
	args.verbose = 1;
	setup_logging(args);
	// TODO: Parse command line args here

	// Ideal arg parsing setup code
	//args.args[0] = (char*) "";
	//args.verbose = 1;
	//args = init_args(argc, argv);
	//setup_logging(args);
	////struct arguments arguments = init_args(argc, argv);
	//char* command = args.args[0];
	//Media media = {args.sound, args.settings, args};
	//setup_logging(args);

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
	app = oggex_application_new ((gchar*) APP_ID, G_APPLICATION_HANDLES_COMMAND_LINE);
	g_signal_connect (app, "command-line", G_CALLBACK (command_line), NULL);

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
	ret = g_application_run (G_APPLICATION (app), NULL, NULL);

	return ret;
}
