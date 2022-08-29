#include "appwindow.h"
#include <stdexcept>

AppWindow::AppWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
  : Gtk::ApplicationWindow(cobject), builder(builder) {
}

AppWindow* AppWindow::create() {
  // Load the Builder file and instantiate its widgets.
  auto builder = Gtk::Builder::create_from_resource("/io/github/com/jmdaemon/oggex/../../../resources/gtk/oggex-window.ui");

  auto window = Gtk::Builder::get_widget_derived<AppWindow>(builder, "app_window");
  if (!window)
    throw std::runtime_error("No \"app_window\" object in window.ui");

  return window;
}

void AppWindow::open_file_view(const Glib::RefPtr<Gio::File>& /* file */) {
}
