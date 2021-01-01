#include "DashboardWindow.h"
#include "DashboardID.h"

#include "Embed.h"
#include "EmbedWindow.h"
#include "oggex.gresource.c"

#include <gtkmm.h>
#include <stdexcept>
#include <iostream>
#include <giomm/resource.h>
#include <glibmm/fileutils.h>

DashboardWindow::DashboardWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {
    //refBuilder->add_from_resource("");
    //refBuilder->add_from_file("Embed", embedWindow);

    //refBuilder->get_widget("embedWindow", embedWindowButton);
    //embedWindowButton->signal_clicked().connect(sigc::bind(*this, &EmbedController::create));
}

//static
DashboardWindow* DashboardWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_file("../../Dashboard.glade");
  auto refBuilder = Gtk::Builder::create_from_resource(Dashboard::DASHBOARD_RESOURCE_FILE);
  
  DashboardWindow* window = nullptr;
  refBuilder->get_widget_derived(Dashboard::dashboardID, window);
  if (!window)
    throw std::runtime_error("No \"Dashboard\" object in Dashboard.glade");

  //refBuilder->add_from_file("resources/xml/Embed.glade");
  //refBuilder->get_widget("appSidebar", sidebar);
  //refBuilder->add_from_file("resources/xml/Extract.glade");
  //refBuilder->add_from_file("resources/xml/FileSelect.glade");
  //EmbedWindow* embedWindow = nullptr;
  //refBuilder->get_widget_derived("Embed", embedWindow);
  //window->set_application(embedWindow);
  //embedWindow->show();

  //window->add_window(embedWindow);
  //gtk_application_add_window(embedWindow)
  //if (!embedWindow)
    //throw std::runtime_error("No \"Embed\" object in Embed.glade");

  return window;
}

//void on_button_clicked() { 
  //if (pWindow) 
    //pWindow->hide();
//}

//void onQualityChange() { 
  //std::cout << "audioQality" << pSetQualitySpinButton->get_value_as_int() << std::endl;
  ////pSetQualitySpinButton->set_value( pSetQualitySpinButton->get_value_as_int() );
//}

