//Menubar(const Glib::RefPtr<Gtk::Builder>& refBuilder) {
    //// ExampleApplication displays the menubar. Other stuff, such as a toolbar,
  //// is put into the box.
  //set_child(m_Box);

  //// Create actions for menus and toolbars.
  //// We can use add_action() because Gtk::ApplicationWindow derives from Gio::ActionMap.
  //// This Action Map uses a "win." prefix for the actions.
  //// Therefore, for instance, "win.copy", is used in ExampleApplication::on_startup()
  //// to layout the menu.

  ////Edit menu:
  //add_action("copy", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
  //add_action("paste", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
  //add_action("something", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));

  ////Choices menus, to demonstrate Radio items,
  ////using our convenience methods for string and int radio values:
  //m_refChoice = add_action_radio_string("choice",
    //sigc::mem_fun(*this, &ExampleWindow::on_menu_choices), "a");

  //m_refChoiceOther = add_action_radio_integer("choiceother",
    //sigc::mem_fun(*this, &ExampleWindow::on_menu_choices_other), 1);

  //m_refToggle = add_action_bool("sometoggle",
    //sigc::mem_fun(*this, &ExampleWindow::on_menu_toggle), false);

  ////Help menu:
  //add_action("about", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));

  ////Create the toolbar and add it to a container widget:
  //m_refBuilder = Gtk::Builder::create();
//}
