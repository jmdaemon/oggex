#include "Embed.h"
#include "EmbedWindow.h"

EmbedWindow::EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {
  refBuilder->get_widget("imageFilePath", imageFilePath);
}

EmbedWindow* EmbedWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_resource(Dashboard::DASHBOARD_RESOURCE_FILE);
  auto refBuilder = Gtk::Builder::create_from_file("resources/xml/Embed.glade");
  refBuilder->add_from_file("resources/xml/FileSelect.glade");
  
  EmbedWindow* window = nullptr;
  refBuilder->get_widget_derived("Embed", window);
  if (!window)
    throw std::runtime_error("No \"Embed\" object in Embed.glade");

  return window;
}

