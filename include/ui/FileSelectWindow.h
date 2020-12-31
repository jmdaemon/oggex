#ifndef FILE_SELECT_WINDOW_H
#define FILE_SELECT_WINDOW_H

#include <gtkmm.h>

class FileSelectWindow : public Gtk::ApplicationWindow {
  protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
  public:
    FileSelectWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static FileSelectWindow* create();
    void open_file_view(const Glib::RefPtr<Gio::File>& file);

};

#endif
