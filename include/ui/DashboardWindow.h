#ifndef DASHBOARD_WINDOW_H
#define DASHBOARD_WINDOW_H

#include <gtkmm.h>

class DashboardWindow : public Gtk::ApplicationWindow {
  protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::Button* pBrowseImageButton;
    Gtk::Button* pAddSoundButton;
    Gtk::SpinButton* pSetQualitySpinButton;

  public: 
    DashboardWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static DashboardWindow* create();

    void open_file_view(const Glib::RefPtr<Gio::File>& file);
};

#endif
