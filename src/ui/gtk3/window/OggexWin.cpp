#include "OggexWin.h"

#include "oggex.gresource.c"

#include <iostream>
#include <stdexcept>
#include <giomm/resource.h>
#include <glibmm/fileutils.h>

OggexWin::OggexWin(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {

    //m_refBuilder->add_from_file("resources/xml/gtk3/MenuBar.ui");
    //set_menubar(m_refBuilder->get_object("MenuBar"))
    m_refBuilder->get_widget("pages", pages);
    m_refBuilder->get_widget("navigationPanel", navigationPanel);

    navigationPanel->set_stack(*pages); 
}

OggexWin* OggexWin::create() {
  auto refBuilder = Gtk::Builder::create_from_resource(Resource::DASHBOARD);
  
  OggexWin* window = nullptr;
  refBuilder->get_widget_derived(Resource::Dashboard::dashboardID, window);
  if (!window)
    throw std::runtime_error("No \"Dashboard\" object in Dashboard.ui");

  return window;
}
