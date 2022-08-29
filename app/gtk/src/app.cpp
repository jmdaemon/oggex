#include "app.h"
#include "appwindow.h"

App::App()
: Gtk::Application("org.gtkmm.examples.application", Gio::Application::Flags::HANDLES_OPEN) {
}

Glib::RefPtr<App> App::create() {
  return Glib::make_refptr_for_instance<App>(new App());
}

AppWindow* App::create_appwindow() {
  auto appwindow = new AppWindow();

  // Make sure that the application runs for as long this window is still open.
  add_window(*appwindow);

  // A window can be added to an application with Gtk::Application::add_window()
  // or Gtk::Window::set_application(). When all added windows have been hidden
  // or removed, the application stops running (Gtk::Application::run() returns()),
  // unless Gio::Application::hold() has been called.

  // Delete the window when it is hidden.
  appwindow->signal_hide().connect(sigc::bind(sigc::mem_fun(*this,
    &App::on_hide_window), appwindow));

  return appwindow;
}

void App::on_activate() {
  // The application has been started, so let's show a window.
  auto appwindow = create_appwindow();
  appwindow->present();
}

void App::on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& /* hint */) {
  // The application has been asked to open some files,
  // so let's open a new view for each one.
  AppWindow* appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<AppWindow*>(windows[0]);

  if (!appwindow)
    appwindow = create_appwindow();

  for (const auto& file : files)
    appwindow->open_file_view(file);

  appwindow->present();
}

void App::on_hide_window(Gtk::Window* window) {
  delete window;
}
