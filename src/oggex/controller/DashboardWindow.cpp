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
  //: Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder), m_Button_File("Choose File"), m_Button_Folder("Choose Folder") {
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

void DashboardWindow::open_file_view(const Glib::RefPtr<Gio::File>&) { }

//void on_button_clicked() { 
  //if (pWindow) 
    //pWindow->hide();
//}

//void onQualityChange() { 
  //std::cout << "audioQality" << pSetQualitySpinButton->get_value_as_int() << std::endl;
  ////pSetQualitySpinButton->set_value( pSetQualitySpinButton->get_value_as_int() );
//}


//void DashboardWindow::on_button_folder_clicked() {
  //Gtk::FileChooserDialog dialog("Please choose a folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
  //dialog.set_transient_for(*this);

  //dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  //dialog.add_button("Select", Gtk::RESPONSE_OK);

  //int result = dialog.run();

  //switch(result) {
    //case(Gtk::RESPONSE_OK): {
      //std::cout << "Select clicked." << std::endl;
      //std::cout << "Folder selected: " << dialog.get_filename()
          //<< std::endl;
      //break;
    //}
    //case(Gtk::RESPONSE_CANCEL): {
      //std::cout << "Cancel clicked." << std::endl;
      //break;
    //}
    //default: {
      //std::cout << "Unexpected button clicked." << std::endl;
      //break;
    //}
  //}
//}

//void DashboardWindow::on_button_file_clicked() {
  //Gtk::FileChooserDialog dialog("Please choose a file",
          //Gtk::FILE_CHOOSER_ACTION_OPEN);
  //dialog.set_transient_for(*this);

  ////Add response buttons the the dialog:
  //dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  //dialog.add_button("_Open", Gtk::RESPONSE_OK);


  //int result = dialog.run();

  //switch(result) {
    //case(Gtk::RESPONSE_OK): {
      //std::cout << "Open clicked." << std::endl;

      //std::string filename = dialog.get_filename();
      //std::cout << "File selected: " <<  filename << std::endl;
      //break;
    //}
    //case(Gtk::RESPONSE_CANCEL): {
      //std::cout << "Cancel clicked." << std::endl;
      //break;
    //}
    //default: {
      //std::cout << "Unexpected button clicked." << std::endl;
      //break;
    //}
  //}
//}

