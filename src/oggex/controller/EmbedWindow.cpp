#include "Embed.h"
#include "EmbedWindow.h"
#include "oggex.gresource.c";

EmbedWindow::DashboardWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {

}

EmbedWindow* DashboardWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_resource(Dashboard::DASHBOARD_RESOURCE_FILE);
  auto refBuilder = Gtk::Builder::create_from_file("resources/xml/Embed.glade");
  
  EmbedWindow* window = nullptr;
  refBuilder->get_widget_derived("Embed", window);
  if (!window)
    throw std::runtime_error("No \"Dashboard\" object in Dashboard.glade");

  return window;
}

