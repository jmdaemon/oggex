//#include "Dashboard.h"

#include <iostream>
#include <string>

#include <gtkmm.h>

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/main.h>

using namespace std;

namespace { 
  const string DASHBOARD_UI = "../../Dashboard.glade";

  Glib::ustring dashboardID   = "Dashboard";
  Glib::ustring browseImageID = "browseImage";
  Glib::ustring fileChooserID = "selectFile";

  Gtk::Button* pBrowseImageButton = nullptr;
  Gtk::Window* pWindow = nullptr;

  Glib::RefPtr<Gtk::Application> app;

  void on_button_clicked() { 
    if (pWindow) 
      pWindow->hide();
  }

void on_app_activate() {
  auto refBuilder = Gtk::Builder::create();
  try { 
    refBuilder->add_from_file(DASHBOARD_UI);
    } catch(const Glib::FileError& ex) { 
      std::cerr << "FileError: " << ex.what() << std::endl; 
      return; 
    } catch(const Glib::MarkupError& ex) { 
      std::cerr << "MarkupError: " << ex.what() << std::endl; 
      return; 
    } catch(const Gtk::BuilderError& ex) { 
      std::cerr << "BuilderError: " << ex.what() << std::endl; 
      return; 
    }

  refBuilder->get_widget<Gtk::Window>(dashboardID, pWindow);
  if (!pWindow) {
    std::cerr << "Could not get the window" << std::endl;
    return; 
  }

  refBuilder->get_widget<Gtk::Button>(browseImageID, pBrowseImageButton);
  if (pBrowseImageButton)
    pBrowseImageButton->signal_clicked().connect([] () { on_button_clicked(); });

  pWindow->signal_hide().connect([] () { delete pWindow; });

  app->add_window(*pWindow);
  pWindow->show(); 
  }
}


int main(int argc, char *argv[]) {
  app = Gtk::Application::create("oggex");
  app->signal_activate().connect([] () { on_app_activate(); });
  return app->run(argc, argv);
}
