#include "Dashboard.h"

#include <gtkmm.h>
#include <gtkmm/dialog.h>
#include <gtkmm/filefilter.h>

#include <iostream>

DashboardController::DashboardController(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade):
  Glib::ObjectBase("MyButton"), m_refGlade(refGlade), m_pButton(nullptr) { 

  m_pButton = Gtk::Builder::get_widget_derived<DerivedButton>(m_refGlade, "quit_button");
  if (m_pButton) {
    m_pButton->signal_clicked().connect( sigc::mem_fun(*this, &DerivedDialog::on_button_quit) );
  }
}

DashboardController::~DashboardController() {}

void DashboardController::clickToBrowse() {
  auto selectFile = new Gtk::FileChooserDialog("Please choose an image file", Gtk::FileChooser::Action::OPEN);

  selectFile->set_transient_for(*this);
  selectFile->set_modal(true);
  selectFile->signal_response().connect(sigc::bind(
  sigc::mem_fun(*this, &DashboardController::on_file_dialog_response), selectFile));

  //Add response buttons to the dialog:
  selectFile->add_button("_Cancel", Gtk::ResponseType::CANCEL);
  selectFile->add_button("_Open", Gtk::ResponseType::OK);

  //Add filters, so that only certain file types can be selected:

  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  selectFile->add_filter(filter_text);

  auto filter_cpp = Gtk::FileFilter::create();
  filter_cpp->set_name("C/C++ files");
  filter_cpp->add_mime_type("text/x-c");
  filter_cpp->add_mime_type("text/x-c++");
  filter_cpp->add_mime_type("text/x-c-header");
  selectFile->add_filter(filter_cpp);

  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  selectFile->add_filter(filter_any);

  //Show the dialog and wait for a user response:
  selectFile->show();
}

void DashboardController::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* selectFile) {
  switch (response_id) {
    case Gtk::ResponseType::OK: {
      //Notice that this is a std::string, not a Glib::ustring.
      auto filename = selectFile->get_file()->get_path();
      std::cout << "File selected: " <<  filename << std::endl;
      break;
    }
    case Gtk::ResponseType::CANCEL:
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
  delete selectFile;
}

//DashboardController::addSound() {}
//DashboardController::removeSoundFile() {}
//DashboardController::readSoundFile() {}

//DashboardController::setQuality() {}
//DashboardController::embed() {}
//DashboardController::extract(){}

void DashboardController::on_button_folder_clicked() {
  auto dialog = new Gtk::FileChooserDialog("Please choose a folder", Gtk::FileChooser::Action::SELECT_FOLDER);
  dialog->set_transient_for(*this);
  dialog->set_modal(true);
  dialog->signal_response().connect(sigc::bind(
    sigc::mem_fun(*this, &ExampleWindow::on_folder_dialog_response), dialog));

  //Add response buttons to the dialog:
  dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
  dialog->add_button("Select", Gtk::ResponseType::OK);

  //Show the dialog and wait for a user response:
  dialog->show();
}

void DashboardController::on_folder_dialog_response(int response_id, Gtk::FileChooserDialog* dialog) {
  //Handle the response:
  switch (response_id) {
    case Gtk::ResponseType::OK: {
      std::cout << "Select clicked." << std::endl;
      std::cout << "Folder selected: " << dialog->get_file()->get_path() << std::endl;
      break;
    }
    case Gtk::ResponseType::CANCEL: {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default: {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
  delete dialog;
}


