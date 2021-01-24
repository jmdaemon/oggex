#ifndef PANEL_H
#define PANEL_H

#include <gtkmm.h>

class Panel {
  private:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;

    Gtk::FileChooserButton* imageFilePath;
    Gtk::Button* readSound;
    Gtk::Button* removeImageFile;

  public:
    void on_qualityChange();
    void on_readSound();
    void on_removeImageFile();
};
#endif