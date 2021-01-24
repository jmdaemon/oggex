#include "DashboardWindow.h"
#include "InterfaceID.h"

#include "EmbedWindow.h"

#include "oggex.gresource.c"

#include <gtkmm.h>
#include <stdexcept>
#include <iostream>
#include <giomm/resource.h>
#include <glibmm/fileutils.h>

DashboardWindow::DashboardWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {

    //m_refBuilder->add_from_file("resources/xml/gtk3/MenuBar.ui");
    //set_menubar(m_refBuilder->get_object("MenuBar"))
    m_refBuilder->get_widget("pages", pages);
    m_refBuilder->get_widget("navigationPanel", navigationPanel);

    //Gtk::Label home("Embed");
    ////pages->add(home, "Embed");
    ////pages->add(home, "Embed", "Embed");
    //pages->add(home, "Embed", "Embed");

    navigationPanel->set_stack(*pages); 

    //m_refBuilder->add_from_resource("resources/xml/FileSelect.ui");
    //m_refBuilder->add_from_file("resources/xml/FileSelect.ui");
    //m_refBuilder->get_widget("EmbedGrid", embedGrid);

    //m_refBuilder->add_from_file("resources/xml/Embed.ui");
    //Glib::RefPtr<Glib::Object> embedGridObj = m_refBuilder->get_object("EmbedGrid");
    //embedGrid = Glib::RefPtr<Gtk::Grid>::cast_dynamic(embedGridObj);
    //Gtk::Label embedLabel("Embed");
    //pages->add(embedLabel, "Embed", "Embed");
    //gtk_stack_add_titled (*pages, home, "Home", "Home")

    //m_refBuilder->add_from_file("resources/xml/Embed.ui");
    //m_refBuilder->get_widget("embedGrid", embedGrid);
    //pages->add(*(Gtk::Widget *) (embedGrid), "Embed", "Embed");

    //pages->add("Home", "Home");
    //m_refBuilder->add_from_resource()
    
    //pages->set_visible_child_name("Home");
    //pages->visible-child-name("Home");

}

DashboardWindow* DashboardWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_file("../../Dashboard.glade");
  auto refBuilder = Gtk::Builder::create_from_resource(Dashboard::DASHBOARD_RESOURCE_FILE);
  
  DashboardWindow* window = nullptr;
  refBuilder->get_widget_derived(Dashboard::dashboardID, window);
  if (!window)
    throw std::runtime_error("No \"Dashboard\" object in Dashboard.glade");

  //m_refBuilder->add_from_file("resources/xml/Embed.ui");
  //EmbedWindow* embedWindow = nullptr;
  //refBuilder->get_widget_derived("Embed", embedWindow);

  return window;
}

//DashboardWindow::on_navigate() {
//}
