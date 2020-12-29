#include "DashboardWindow.h"
#include "oggex.gresource.c"

#include <gtkmm.h>
#include <stdexcept>
#include <iostream>
#include <giomm/resource.h>
#include <glibmm/fileutils.h>

DashboardWindow::DashboardWindow(BaseObjectType* cobject,
  const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::ApplicationWindow(cobject),
  m_refBuilder(refBuilder)
{
}

//static
DashboardWindow* DashboardWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_resource("../../Dashboard.glade");
  //auto refBuilder = Gtk::Builder::create_from_file("../../Dashboard.glade");
  //auto refBuilder = Gtk::Builder::create_from_resource("/com/github/jmdaemon/oggex/Dashboard.glade");
  //auto refBuilder = Gtk::Builder::create_from_resource("resource:///com/github/jmdaemon/oggex/Dashboard.glade"); 
  //auto refBuilder = Gtk::Builder::create_from_resource("/com/github/jmdaemon/oggex/resources/xml/Dashboard.glade"); 
  //auto refBuilder = Gtk::Builder::create_from_resource("/com/github/jmdaemon/oggex/resources/xml/Dashboard.glade"); 
  //auto refBuilder = Gtk::Builder::create_from_resource("/com/github/jmdaemon/oggex/../../Dashboard.glade"); 
  //auto refBuilder = Gtk::Builder::create_from_resource("/com/github/jmdaemon/oggex/Dashboard.glade"); 
  //auto refBuilder = Gtk::Builder::create_from_file("/com/github/jmdaemon/oggex/Dashboard.glade"); 
  //auto refBuilder = Gtk::Builder::create_from_resource("oggex.gresource.c"); 
  //auto refBuilder = Gtk::Builder::create_from_resource("/com/github/jmd/dashboard/Dashboard.glade");
  //auto refBuilder = Gtk::Builder::create_from_resource("oggex.resource.c");
  //auto refBuilder = Gtk::Builder::create_from_resource("/dashboard/Dashboard.glade");
  //auto refBuilder = Gtk::Builder::new_from_resource("/dashboard/Dashboard.glade");
  //auto refBuilder = gtk_builder_new_from_resource("/dashboard/Dashboard.glade");
  //auto refBuilder = Gtk::Builder::create_from_resource("/dashboard/Dashboard.glade", Glib::ustring("Dashboard"));
  //auto refBuilder = Gtk::Builder::create_from_resource("/dashboard/Dashboard.glade", Glib::ustring("Dashboard"));
  //std::string resource = "/dashboard/Dashboard.glade";
  std::string resource = "/dashboard/Dashboard.glade";
  //try { 
    ////Gio::Resource::get_file_exists(resource);
    //Gio::Resource::lookup_data_global(resource);
    //} catch (const Gio::ResourceError& error) {
    //std::cerr << "Gio::ResourceError: " << error.what() << std::endl;
  //}
  //auto refBuilder = Gtk::Builder::create_from_resource("resource:///dashboard/Dashboard.glade");
  //auto refBuilder = Gtk::Builder::create_from_resource("/dashboard/Dashboard.glade");
  auto refBuilder = Gtk::Builder::create_from_resource("/com/github/jmd/dashboard/dashboard.glade");
  //auto refBuilder = Gtk::Builder::create_from_resource("dashboard/Dashboard.glade");
  //auto refBuilder = Gtk::Builder::create_from_resource("Dashboard.glade");

  DashboardWindow* window = nullptr;
  refBuilder->get_widget_derived("Dashboard", window);
  if (!window)
    throw std::runtime_error("No \"Dashboard\" object in Dashboard.glade");

  return window;
}


void DashboardWindow::open_file_view(const Glib::RefPtr<Gio::File>&) { }

