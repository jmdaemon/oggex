#include "Embed.h"
#include "EmbedWindow.h"

EmbedWindow::EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {
  refBuilder->get_widget("imageFilePath", imageFilePath);

  refBuilder->get_widget("soundsWindow",m_ScrolledWindow);
  refBuilder->get_widget("soundTagMetadata", m_TreeView);

  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  (*m_TreeView).set_model(m_refTreeModel);

  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_selected] = true;
  row[m_Columns.m_soundTag] = "[audio02]";
  row[m_Columns.m_filePath] = "/home/user/directory/";
  row[m_Columns.m_fileSize] = "156.6 kB";
  row[m_Columns.m_deleteEntry] = true;

  //refBuilder
}

EmbedWindow* EmbedWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_resource(Dashboard::DASHBOARD_RESOURCE_FILE);
  auto refBuilder = Gtk::Builder::create_from_file("resources/xml/Embed.glade");
  //refBuilder->add_from_file("resources/xml/FileSelect.glade");
  
  EmbedWindow* window = nullptr;
  refBuilder->get_widget_derived("Embed", window);
  if (!window)
    throw std::runtime_error("No \"Embed\" object in Embed.glade");

  return window;
}

