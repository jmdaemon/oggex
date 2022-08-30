#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

#include <gtkmm.h>

class EmbedWidget : public Gtk::Widget {
protected:
  Glib::RefPtr<Gtk::Builder> builder;
public:
  EmbedWidget(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

  static EmbedWidget* create();
  //EmbedWidget* create();
};

//EmbedWidget* create();

#endif // OGGEX_APP_WINDOW_H
