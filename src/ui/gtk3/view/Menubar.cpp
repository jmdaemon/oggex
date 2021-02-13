#include "MenuBar.h"

MenuBar::MenuBar(const Glib::RefPtr<Gtk::Builder>& refBuilder): m_refBuilder(refBuilder), m_Box(Gtk::ORIENTATION_VERTICAL) {

  add(m_Box); 
  //Edit menu:
  add_action("copy", sigc::mem_fun(*this, &EmbedWindow::on_menu_others));
  add_action("paste", sigc::mem_fun(*this, &EmbedWindow::on_menu_others));
  add_action("something", sigc::mem_fun(*this, &EmbedWindow::on_menu_others));

  //Choices menus, to demonstrate Radio items,
  //using our convenience methods for string and int radio values:
  m_refChoice = add_action_radio_string("choice",
    sigc::mem_fun(*this, &EmbedWindow::on_menu_choices), "a");

  m_refChoiceOther = add_action_radio_integer("choiceother",
    sigc::mem_fun(*this, &EmbedWindow::on_menu_choices_other), 1);

  m_refToggle = add_action_bool("sometoggle",
    sigc::mem_fun(*this, &EmbedWindow::on_menu_toggle), false);

  //Help menu:
  add_action("about", sigc::mem_fun(*this, &EmbedWindow::on_menu_others));
}


void MenuBar::on_menu_others() {
  std::cout << "A menu item was selected." << std::endl;
}

void MenuBar::on_menu_choices(const Glib::ustring& parameter) {
  m_refChoice->change_state(parameter);

  Glib::ustring message;
  if (parameter == "a")
    message = "Choice a was selected.";
  else
    message = "Choice b was selected.";

  std::cout << message << std::endl;
}

void MenuBar::on_menu_choices_other(int parameter) {
  m_refChoiceOther->change_state(parameter);

  Glib::ustring message;
  if (parameter == 1)
    message = "Choice 1 was selected.";
  else
    message = "Choice 2 was selected.";

  std::cout << message << std::endl;
}

void MenuBar::on_menu_toggle() {
  bool active = false;
  m_refToggle->get_state(active);

  active = !active;
  m_refToggle->change_state(active);

  Glib::ustring message;
  if (active)
    message = "Toggle is active.";
  else
    message = "Toggle is not active.";

  std::cout << message << std::endl;
}

