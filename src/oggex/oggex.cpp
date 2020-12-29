//#include "Dashboard.h"

#include <iostream>
#include <string>

#include <gtkmm.h>

#include <fmt/core.h>
#include <fmt/printf.h>

using namespace std;

namespace { 
  const string DASHBOARD_UI = "../../Dashboard.glade";

  Glib::ustring dashboardID   = "Dashboard";
  Glib::ustring browseImageID = "browseImage";
  Glib::ustring addSoundID    = "addSound";
  Glib::ustring fileChooserID = "selectFile";
  Glib::ustring setQualityID  = "quality";
  Glib::ustring qualityAdjustmentID  = "qualityAdjustment";

  Gtk::Button* pBrowseImageButton = nullptr;
  Gtk::Button* pAddSoundButton = nullptr;
  Gtk::SpinButton* pSetQualitySpinButton = nullptr;
  //Gtk::Adjustment* qualityAdjustment = nullptr;
  Gtk::Window* pWindow = nullptr;

  Glib::RefPtr<Gtk::Application> app;
  Glib::RefPtr<Gtk::Adjustment> qualityAdjustment;

  void on_button_clicked() { 
    if (pWindow) 
      pWindow->hide();
  }

  void onQualityChange() { 
    pSetQualitySpinButton->set_digits( pSetQualitySpinButton->get_value_as_int() );
  }

void on_app_activate() {
  auto refBuilder = Gtk::Builder::create();
  try { 
    refBuilder->add_from_file(DASHBOARD_UI);
    } catch(const Glib::FileError& ex) { 
      fmt::fprintf(cerr, "FileError: {}\n", ex.what());
      return; 
    } catch(const Glib::MarkupError& ex) { 
      fmt::fprintf(cerr, "MarkupError: {}\n", ex.what());
      return; 
    } catch(const Gtk::BuilderError& ex) { 
      fmt::fprintf(cerr, "BuilderError: {}\n", ex.what());
      return; 
    }

  refBuilder->get_widget<Gtk::Window>(dashboardID, pWindow);
  if (!pWindow) {
    fmt::fprintf(cerr, "Could not get the window");
    return; 
  }

  refBuilder->get_widget<Gtk::Button>(browseImageID, pBrowseImageButton);
  refBuilder->get_widget<Gtk::Button>(addSoundID, pAddSoundButton);

  refBuilder->get_widget<Gtk::SpinButton>(setQualityID, pSetQualitySpinButton); 
  //qualityAdjustment = refBuilder->get_object<Gtk::Adjustment>(qualityAdjustmentID); 
  //qualityAdjustment = refBuilder->get_object<Gtk::Adjustment>(qualityAdjustmentID); 
  //qualityAdjustment = static_cast<Gtk::Adjustment>(refBuilder->get_object(qualityAdjustmentID)); 
  //qualityAdjustment = Gtk::Adjustment::create(4.0, 0.0, 10.0, 1, 10, 0);
  qualityAdjustment = pSetQualitySpinButton->get_adjustment();
  //pSetQualitySpinButton(qualityAdjustment);
  if (pBrowseImageButton)
    pBrowseImageButton->signal_clicked().connect([] () { on_button_clicked(); });
  if (pAddSoundButton)
    pAddSoundButton->signal_clicked().connect([] () { on_button_clicked(); }); 
  if (qualityAdjustment)
    qualityAdjustment->signal_value_changed().connect([] () { onQualityChange(); });
    //qualityAdjustment->signal_value_changed().connect( sigc::mem_fun(*this, onQualityChange) );

  pWindow->signal_hide().connect([] () { delete pWindow; });

  app->add_window(*pWindow);
  pWindow->show(); 
  }
}

int main(int argc, char *argv[]) {
  app = Gtk::Application::create("com.github.jmdaemon.oggex");
  app->signal_activate().connect([] () { on_app_activate(); });
  return app->run(argc, argv);
}
