#include "SoundTagManager.h"

using namespace std;
SoundTagManager::SoundTagManager() {}

void SoundTagManager::create() {
  m_refBuilder = Gtk::Builder::create_from_resource(Resource::SOUND_TAG_VIEW);

  data = Audio::AudioData();
  m_refBuilder->get_widget("soundsWindow", m_ScrolledWindow);
  m_refBuilder->get_widget("soundTagMetadata", m_TreeView);

  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView->set_model(m_refTreeModel);
  createNewSoundTag(true, "[audio02]", "/home/user/directory", "156.6kB", true);
  createNewSoundTag(false, "[audio03]", "/home/user/some/directory/", "452.9 kB", false);
  createNewSoundTag(true, "[audio04]", "/home/user/some/directory/", "1553.9 kB", false);
  createModelColumns();
}

void SoundTagManager::on_deleteSelected() {
  auto children = m_refTreeModel->children();
  for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
    auto row = *iter;
    bool isSelected = row[m_Columns.m_selected];
    int index = std::distance(children.begin(), iter);
    fmt::print("Row: {}\n", index);
    fmt::print("isSelected: {}\n", isSelected);
    if (isSelected == true) {
      fmt::print("Deleting row\n");
      m_refTreeModel->erase(iter);
      iter = children.begin();
    }
  }
} 

void SoundTagManager::on_embed() {
  auto children = m_refTreeModel->children();
  for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
    auto row = *iter;
    auto soundTag = row[m_Columns.m_soundTag];
    auto filePath = row[m_Columns.m_filePath];
    int index = std::distance(children.begin(), iter);
    fmt::print("row: {}\n", index);
    fmt::print("soundTag: {}\n", soundTag);
    fmt::print("filePath: {}\n\n", filePath);
  }
}

void SoundTagManager::createModelColumns() {
  m_TreeView->append_column_editable("", m_Columns.m_selected);
  m_TreeView->append_column_editable("Sound Tag", m_Columns.m_soundTag);
  m_TreeView->append_column_editable("File Path", m_Columns.m_filePath);
  m_TreeView->append_column("File Size", m_Columns.m_fileSize);
  m_TreeView->append_column_editable("Delete", m_Columns.m_deleteEntry);
} 

void SoundTagManager::createNewSoundTag(bool isSelected, string soundTag, string filePath, string fileSize, bool deleteEntry) {
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_selected]       = isSelected;
  row[m_Columns.m_soundTag]       = soundTag;
  row[m_Columns.m_filePath]       = filePath;
  row[m_Columns.m_fileSize]       = fileSize;
  row[m_Columns.m_deleteEntry]    = deleteEntry;
}
