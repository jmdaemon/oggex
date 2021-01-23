#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class MenuBar {
  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  Gtk::Box m_Box; 

  //Two sets of choices:
  Glib::RefPtr<Gio::SimpleAction> m_refChoice;
  Glib::RefPtr<Gio::SimpleAction> m_refChoiceOther;

  Glib::RefPtr<Gio::SimpleAction> m_refToggle;
};

#endif
