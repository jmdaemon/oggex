#include "Dashboard.h"
#include "DashboardWindow.h"

#include <iostream>
#include <exception>

DashboardController::DashboardController() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<DashboardController> DashboardController::create() {
  return Glib::RefPtr<DashboardController>(new DashboardController());
}

DashboardWindow* DashboardController::create_appwindow() {
  auto appwindow = DashboardWindow::create();

  add_window(*appwindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::ApplicationWindow*>(sigc::mem_fun(*this,
    &DashboardController::on_hide_window), appwindow));

  //refBuilder->get_widget("embedWindowButton", embedWindow);
  //refBuilder->get_widget("extractWindowButton", extractWindow);

  //embedWindow->signal_clicked().connect(sigc::bind(*this, &DashboardWindow::on_button_embed_clicked), &window);
  //extractWindow->signal_clicked().connect(sigc::bind(*this, &DashboardWindow::on_button_extract_clicked), &window);


  return appwindow;
}

void DashboardController::on_activate() {
  try {
  auto appwindow = create_appwindow();
  appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "DashboardController::on_activate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "DashboardController::on_activate(): " << ex.what() << std::endl;
  }

}

//void DashboardWindow::on_button_embed_clicked() {
  //EmbedWindow* newWindow = nullptr;
  //refBuilder->add_from_file("resources/xml/Embed.glade");
  //refBuilder->get_widget_derived("Embed", newWindow);
  //window.add(newWindow);
  //window.show_all();
  //window.destroy();
//}

//void DashboardWindow::on_button_extract_clicked() {
//}

void DashboardController::on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& ) {
  DashboardWindow* appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<DashboardWindow*>(windows[0]);

  try {
    if (!appwindow)
      appwindow = create_appwindow();

    for (const auto& file : files)
      appwindow->open_file_view(file);

    appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "DashboardController::on_open(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "DashboardController::on_open(): " << ex.what() << std::endl;
  }
}

void DashboardController::on_hide_window(Gtk::Window* window) {
  delete window;
}

