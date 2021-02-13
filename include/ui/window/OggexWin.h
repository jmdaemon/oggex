#ifndef OGGEX_WIN_H
#define OGGEX_WIN_H

#include <gtkmm.h>
#include "Resources.h"

class OggexWin : public Gtk::ApplicationWindow {
  protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    //Gtk::Button* embedWindowButton;

    Gtk::Stack* pages;
    Gtk::StackSidebar* navigationPanel;
    //Gtk::StackSwitcher* navigationPanel;
    Gtk::Grid* embedGrid;
    //Glib::RefPtr<Gtk::Grid> embedGrid;

  public: 
    //Gtk::Stack* pages;
    //Gtk::StackSidebar* navigationPanel;
    OggexWin(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static OggexWin* create();
};

#endif
