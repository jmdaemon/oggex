#include "Embed.h"
#include "EmbedWindow.h"
#include "InterfaceID.h"
#include "EmbedAudio.h"

#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

EmbedWindow::EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) {

  data = Audio::AudioData();
  refBuilder->get_widget("quality", pAudioQuality); 
  Glib::RefPtr<Glib::Object> adjustmentObject  = refBuilder->get_object("qualityAdjustment"); 
  qualityAdjustment = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(adjustmentObject);
  qualityAdjustment->signal_value_changed().connect(sigc::mem_fun(*this, &EmbedWindow::on_quality_change_value));

  refBuilder->get_widget("imageFilePath", imageFilePath);
  refBuilder->get_widget("outputFileName", outputFileName);
  refBuilder->get_widget("embed", embed);

  refBuilder->get_widget("soundsWindow",m_ScrolledWindow);
  refBuilder->get_widget("soundTagMetadata", m_TreeView);

  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView->set_model(m_refTreeModel);

  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  createNewSoundTag(row, true, "[audio02]", "/home/user/directory", "156.6kB", true);

  row = *(m_refTreeModel->append());
  createNewSoundTag(row, false, "[audio03]", "/home/user/some/directory/", "452.9 kB", false);

  row = *(m_refTreeModel->append());
  createNewSoundTag(row, true, "[audio04]", "/home/user/some/directory/", "1553.9 kB", false);

  m_TreeView->append_column_editable("", m_Columns.m_selected);
  //Gtk::CellRendererToggle toggleSelected = Gtk::make_managed<Gtk::CellRendererToggle>();
  //(*m_TreeView).append_column(, m_Columns.m_selected);

  m_TreeView->append_column_editable("Sound Tag", m_Columns.m_soundTag);
  m_TreeView->append_column_editable("File Path", m_Columns.m_filePath);
  m_TreeView->append_column("File Size", m_Columns.m_fileSize);
  m_TreeView->append_column_editable("Delete", m_Columns.m_deleteEntry);

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
  auto refBuilder = Gtk::Builder::create_from_resource(Embed::EMBED_RESOURCE_FILE);
  refBuilder->add_from_file("resources/xml/FileSelect.ui");
  
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

void EmbedWindow::on_quality_change_value() {
  fmt::print("Setting audioQuality to: {}\n", pAudioQuality->get_value_as_int());
  data.audioQuality = pAudioQuality->get_value_as_int();
}

void EmbedWindow::createNewSoundTag(Gtk::TreeModel::Row row, bool isSelected, string soundTag, string filePath, string fileSize, bool deleteEntry) {
  row[m_Columns.m_selected]       = isSelected;
  row[m_Columns.m_soundTag]       = soundTag;
  row[m_Columns.m_filePath]       = filePath;
  row[m_Columns.m_fileSize]       = fileSize;
  row[m_Columns.m_deleteEntry]    = deleteEntry;
}
