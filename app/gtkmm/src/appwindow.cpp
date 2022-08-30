#include "appwindow.h"
#include <stdexcept>

AppWindow::AppWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
  : Gtk::ApplicationWindow(cobject), builder(builder) {

  //GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(cobject);
  //gtk_widget_class_set_template_from_resource(widget_class, "/io/github/com/jmdaemon/oggex/../../../resources/gtk/oggex-window.ui");
  //gtk_widget_init_template (GTK_WIDGET (this->gobj()));

  //gtk_widget_init_template (GTK_WIDGET (this->gobj()));
  //gtk_widget_init_template (GTK_WIDGET (this));
}

AppWindow* AppWindow::create() {
  // Load the Builder file and instantiate its widgets.

  //auto builder = Gtk::Builder::create_from_resource("/io/github/com/jmdaemon/oggex/../../../resources/gtk/oggex-window.ui");
  //builder->add_from_resource("/io/github/com/jmdaemon/oggex/../../../resources/gtk/embedwindow.ui");

  auto builder = Gtk::Builder::create_from_resource("/io/github/com/jmdaemon/oggex/../../../resources/gtk/embedwindow.ui");
  builder->add_from_resource("/io/github/com/jmdaemon/oggex/../../../resources/gtk/oggex-window.ui");

  //gtk_widget_class_set_template_from_resource(&AppWindow, "/io/github/com/jmdaemon/oggex/../../../resources/gtk/oggex-window.ui");


  auto window = Gtk::Builder::get_widget_derived<AppWindow>(builder, "app_window");
  
  //window->create();
  if (!window)
    throw std::runtime_error("No \"app_window\" object in window.ui");

  return window;
}

void AppWindow::open_file_view(const Glib::RefPtr<Gio::File>& /* file */) {
}
