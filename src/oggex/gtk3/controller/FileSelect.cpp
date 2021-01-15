#include "FileSelect.h"
#include "FileSelectWindow.h"

#include <iostream>
#include <exception>

FileSelectWindow* FileSelect::create_appwindow() {
  auto appwindow = FileSelectWindow::create();

  add_window(*appwindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::ApplicationWindow*>(sigc::mem_fun(*this,
    &FileSelect::on_hide_window), appwindow));

  return appwindow;
}

void FileSelect::on_activate() {
  try {
  auto appwindow = create_appwindow();
  appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "FileSelect::on_activate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "FileSelect::on_activate(): " << ex.what() << std::endl;
  }

}

void FileSelect::on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& ) {
  FileSelectWindow* appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<FileSelectWindow*>(windows[0]);

  try {
    if (!appwindow)
      appwindow = create_appwindow();

    for (const auto& file : files)
      appwindow->open_file_view(file);

    appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "FileSelect::on_open(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "FileSelect::on_open(): " << ex.what() << std::endl;
  }
}

void FileSelect::on_hide_window(Gtk::Window* window) {
  delete window;
}

