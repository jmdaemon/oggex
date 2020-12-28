#include <iostream>
#include <string>

#include <gtkmm.h>
#include <gtkmm/label.h>
//#include <gtkmm/main.h>
//#include <gtkmm/builder.h>
//#include <gtkmm/window.h>

using namespace std;

namespace { 
  string dashboard = "../../Dashboard.glade";
  Glib::ustring dboard = "Dashboard";
  Glib::ustring browseImageID = "browseImage";
  Gtk::Button* pButton = nullptr;

  Gtk::Window* pWindow = nullptr;
  Glib::RefPtr<Gtk::Application> app;

  void on_button_clicked() {
  if (pWindow)
    pWindow->hide();
  }

void on_app_activate() {
  auto refBuilder = Gtk::Builder::create();
  try { 
    refBuilder->add_from_file(dashboard);
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

  //pWindow = refBuilder->get_widget<Gtk::Window>(dboard, pWindow);
  refBuilder->get_widget<Gtk::Window>(dboard, pWindow);
  if (!pWindow) {
    std::cerr << "Could not get the window" << std::endl;
    return;
    }

  //auto pButton = refBuilder->get_widget<Gtk::Button>(browseImageID, browseImage);
  //auto pButton = refBuilder->get_widget<Gtk::Button>(browseImageID, browseImage);
  refBuilder->get_widget<Gtk::Button>(browseImageID, pButton);
  if (pButton)
    pButton->signal_clicked().connect([] () { on_button_clicked(); });

  pWindow->signal_hide().connect([] () { delete pWindow; });

  app->add_window(*pWindow);
  pWindow->show(); 
  }
}


int main(int argc, char *argv[]) {
  //string dashboard = "Dashboard.glade";
  //auto builder = Gtk::Builder::create_from_file(dashboard);
  //auto pWindow = refBuilder->get_widget<Gtk::Window>("Dashboard");

  //auto pWindow = builder->get_widget<Gtk::Window>("Dashboard");
  //app = Gtk::Application::create("oggex");
  //app->signal_activate().connect([] () { on_app_activate(); });
  app = Gtk::Application::create("oggex");
  app->signal_activate().connect([] () { on_app_activate(); });
  return app->run(argc, argv);
}
