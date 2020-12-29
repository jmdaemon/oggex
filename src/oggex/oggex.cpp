#include "Dashboard.h"

#include <iostream>
#include <string>

#include <gtkmm.h>

#include <fmt/core.h>
#include <fmt/printf.h>

using namespace std;

//namespace { 
  //Gtk::Button* pBrowseImageButton = nullptr;
  //Gtk::Button* pAddSoundButton = nullptr;
  //Gtk::SpinButton* pSetQualitySpinButton = nullptr;
  //Gtk::Window* pWindow = nullptr;

  //Glib::RefPtr<Gtk::Application> app;
  //Glib::RefPtr<Gtk::Adjustment> qualityAdjustment;

  //void on_button_clicked() { 
    //if (pWindow) 
      //pWindow->hide();
  //}

  //void onQualityChange() { 
    //pSetQualitySpinButton->set_value( pSetQualitySpinButton->get_value_as_int() );
  //}

//void on_app_activate() {
  //auto refBuilder = Gtk::Builder::create();
  //try { 
    //refBuilder->add_from_file(DASHBOARD_UI);
    //} catch(const Glib::FileError& ex) { 
      //fmt::fprintf(cerr, "FileError: {}\n", ex.what());
      //return; 
    //} catch(const Glib::MarkupError& ex) { 
      //fmt::fprintf(cerr, "MarkupError: {}\n", ex.what());
      //return; 
    //} catch(const Gtk::BuilderError& ex) { 
      //fmt::fprintf(cerr, "BuilderError: {}\n", ex.what());
      //return; 
    //}

  //refBuilder->get_widget<Gtk::Window>(dashboardID, pWindow);
  //if (!pWindow) {
    //fmt::fprintf(cerr, "Could not get the window");
    //return; 
  //}

  //refBuilder->get_widget<Gtk::Button>(browseImageID, pBrowseImageButton);
  //refBuilder->get_widget<Gtk::Button>(addSoundID, pAddSoundButton);

  //refBuilder->get_widget<Gtk::SpinButton>(setQualityID, pSetQualitySpinButton); 
  //qualityAdjustment = pSetQualitySpinButton->get_adjustment();
  //if (pBrowseImageButton)
    //pBrowseImageButton->signal_clicked().connect([] () { on_button_clicked(); });
  //if (pAddSoundButton)
    //pAddSoundButton->signal_clicked().connect([] () { on_button_clicked(); }); 
  //if (qualityAdjustment)
    //qualityAdjustment->signal_value_changed().connect([] () { onQualityChange(); });

  //pWindow->signal_hide().connect([] () { delete pWindow; });

  //app->add_window(*pWindow);
  //pWindow->show(); 
  //}
//}

int main(int argc, char *argv[]) {
  auto application = DashboardController::create();
  return application->run(argc, argv);

  //app = Gtk::Application::create("com.github.jmdaemon.oggex");
  //app->signal_activate().connect([] () { on_app_activate(); });
  //return app->run(argc, argv);
}
