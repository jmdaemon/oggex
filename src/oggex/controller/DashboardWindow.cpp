#include "DashboardWindow.h"
#include "InterfaceID.h"

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
    m_refBuilder->get_widget("audioQuality", pAudioQuality);
}

DashboardWindow* DashboardWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_file("../../Dashboard.glade");
  auto refBuilder = Gtk::Builder::create_from_resource(Dashboard::DASHBOARD_RESOURCE_FILE);
  
  DashboardWindow* window = nullptr;
  refBuilder->get_widget_derived(Dashboard::dashboardID, window);
  if (!window)
    throw std::runtime_error("No \"Dashboard\" object in Dashboard.glade");

  return window;
}

//void on_button_clicked() { 
  //if (pWindow) 
    //pWindow->hide();
//}

void DashboardWindow::onQualityChange() {
  std::cout << "audioQuality" << pAudioQuality->get_value_as_int() << std::endl;
  //pSetQualitySpinButton->set_value( pSetQualitySpinButton->get_value_as_int() );
}
