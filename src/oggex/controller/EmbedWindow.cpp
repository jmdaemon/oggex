#include "Embed.h"
#include "EmbedWindow.h"
#include "EmbedAudio.h"

EmbedWindow::EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {
  refBuilder->get_widget("imageFilePath", imageFilePath);
  refBuilder->get_widget("outputFileName", outputFileName);
  refBuilder->get_widget("embed", embed);

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

  row = *(m_refTreeModel->append());
  row[m_Columns.m_selected] = false;
  row[m_Columns.m_soundTag] = "[audio03]";
  row[m_Columns.m_filePath] = "/home/user/some/directory/";
  row[m_Columns.m_fileSize] = "452.9 kB";
  row[m_Columns.m_deleteEntry] = false;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_selected] = true;
  row[m_Columns.m_soundTag] = "[audio04]";
  row[m_Columns.m_filePath] = "/home/user/some/directory/";
  row[m_Columns.m_fileSize] = "1553.9 kB";
  row[m_Columns.m_deleteEntry] = false;

  (*m_TreeView).append_column_editable("", m_Columns.m_selected);
  //Gtk::CellRendererToggle toggleSelected = Gtk::make_managed<Gtk::CellRendererToggle>();
  //(*m_TreeView).append_column(, m_Columns.m_selected);

  (*m_TreeView).append_column_editable("Sound Tag", m_Columns.m_soundTag);
  (*m_TreeView).append_column_editable("File Path", m_Columns.m_filePath);
  (*m_TreeView).append_column("File Size", m_Columns.m_fileSize);
  (*m_TreeView).append_column_editable("Delete", m_Columns.m_deleteEntry);

  //auto cols_count = m_TreeView.append_column_editable(, m_columns.alex);
  //auto pColumn = m_TreeView.get_column(cols_count-1);
  //if(pColumn)
  //{
    //auto pRenderer = static_cast<Gtk::CellRendererToggle*>(pColumn->get_first_cell());
    //pColumn->add_attribute(pRenderer->property_visible(), m_columns.visible);
    //pColumn->add_attribute(pRenderer->property_activatable(), m_columns.world);
  //}

  //embed.signal_clicked().connect(sigc::ptr_fun(&on_embed_button_clicked));


  //Gtk::CellRendererToggle toggleSelected = new Gtk::CellRendererToggle;
  //toggleSelected->signal_changed().connect(sigc::men_func(*this, &EmbedWindow::on_toggleSelected_changed);


  //Gtk::CellRendererCombo *combo = manage (new Gtk::CellRendererCombo);
  //combo->signal_changed ().connect (sigc::mem_fun (*this, &EmbedWindow::on_combo_changed);

  //Gtk::TreeViewColumn *column = manage (new Gtk::TreeViewColumn ("Title", *combo));

  //column->add_attribute (*combo, "model", model_column_record.combo_model);
  //column->add_attribute (*combo, "text-column", model_column_record.combo_text_column);
  //treeview.append_column (*column);

  show_all_children();
  //refBuilder
}

EmbedWindow* EmbedWindow::create() {
  //auto refBuilder = Gtk::Builder::create_from_resource(Dashboard::DASHBOARD_RESOURCE_FILE);
  auto refBuilder = Gtk::Builder::create_from_file("resources/xml/Embed.glade");
  refBuilder->add_from_file("resources/xml/FileSelect.glade");
  
  EmbedWindow* window = nullptr;
  refBuilder->get_widget_derived("Embed", window);
  if (!window)
    throw std::runtime_error("No \"Embed\" object in Embed.glade");

  return window;
}

//void on_embed_button_clicked() {
  //for (auto row: refModel->children()) {
    //auto soundTag = row[m_Columns.m_soundTag];
    //auto filePath = row[m_Columns.m_filePath];
  //}
//}
