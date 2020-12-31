#include "DashboardWindow.h"
#include "DashboardID.h"
//#include "Embed.h"
//#include "EmbedWindow.h"
#include "oggex.gresource.c"

#include <gtkmm.h>
#include <stdexcept>
#include <iostream>
#include <giomm/resource.h>
#include <glibmm/fileutils.h>

DashboardWindow::DashboardWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  //m_Button_File.signal_clicked().connect(sigc::mem_fun(*this, &DashboardWindow::on_button_file_clicked) );
  //m_Button_Folder.signal_clicked().connect(sigc::mem_fun(*this, &DashboardWindow::on_button_folder_clicked) );
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {

}

//static
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

//void onQualityChange() { 
  //std::cout << "audioQality" << pSetQualitySpinButton->get_value_as_int() << std::endl;
  ////pSetQualitySpinButton->set_value( pSetQualitySpinButton->get_value_as_int() );
//}

