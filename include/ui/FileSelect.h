#ifndef FILE_SELECT_H
#define FILE_SELECT_H

#include <gtkmm.h>

class FileSelectWindow;
class FileSelect : public Gtk::Application {
  private:
    FileSelectWindow* create_appwindow();
    void on_hide_window(Gtk::Window* window);

  protected:
    FileSelect();

    void on_activate() override;
    void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint) override;

  public:
    static Glib::RefPtr<FileSelect> create();

};

#endif
