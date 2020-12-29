#include "DashboardWindow.h"

#include <stdexcept>

DashboardWindow::DashboardWindow(BaseObjectType* cobject,
  const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::ApplicationWindow(cobject),
  m_refBuilder(refBuilder)
{
}

//static
DashboardWindow* DashboardWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_resource("../../Dashboard.glade");
  auto refBuilder = Gtk::Builder::create_from_file("../../Dashboard.glade");

  DashboardWindow* window = nullptr;
  refBuilder->get_widget_derived("Dashboard", window);
  if (!window)
    throw std::runtime_error("No \"Dashboard\" object in Dashboard.glade");

  return window;
}


void DashboardWindow::open_file_view(const Glib::RefPtr<Gio::File>&) { }

