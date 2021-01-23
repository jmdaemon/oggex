#include "SoundTagManager.h"

using namespace std;
SoundTagManager::SoundTagManager(const Glib::RefPtr<Gtk::Builder>& refBuilder): m_refBuilder(refBuilder) {

  data = Audio::AudioData();
  refBuilder->get_widget("soundsWindow", m_ScrolledWindow);
  refBuilder->get_widget("soundTagMetadata", m_TreeView);

  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView->set_model(m_refTreeModel);
  createNewSoundTag(true, "[audio02]", "/home/user/directory", "156.6kB", true);
  createNewSoundTag(false, "[audio03]", "/home/user/some/directory/", "452.9 kB", false);
  createNewSoundTag(true, "[audio04]", "/home/user/some/directory/", "1553.9 kB", false);
  createModelColumns();

  refBuilder->get_widget("inputSoundsWindow", inputSoundsWindow);
  refBuilder->get_widget("inputSounds", inputSoundsTreeView);

  inputSoundsTreeModel = Gtk::ListStore::create(inputSoundsColumns);
  inputSoundsTreeView->set_model(inputSoundsTreeModel);
  inputSounds("[testAudioTag]", "/home/user/path/to/audio/file");
  inputSounds("[audio01]", "/home/user/audio01.ogg");
  inputSounds("[audio02]", "/home/user/audio02.ogg");
  inputSounds("[ominous01]", "/home/user/ominous.ogg");
  inputSounds("[cave01]", "/home/user/cave.ogg");
  createInputColumns();
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

void SoundTagManager::on_readSound() {
  auto children = m_refTreeModel->children();
  for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
    auto row = *iter;
    int index = std::distance(children.begin(), iter);
    Glib::ustring soundTag = row[m_Columns.m_soundTag];
    Glib::ustring filePath = row[m_Columns.m_filePath];
    if (!soundTag.empty() && !filePath.empty()) {
      fmt::print("row: {}\n", index);
      fmt::print("soundTag: {}\n", soundTag);
      fmt::print("filePath: {}\n", filePath);
      fmt::print("Reading Sounds...\n\n");
      // Read audio file path
      // Create AudioData object with soundTag and fileSize
      // Call createNewSoundTag with the data
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

//void SoundTagManager::on_removeImageFile() {
  //imageFilePath->unselect_file(imageFilePath->get_file());
  //fmt::print("Remove image file\n");
//}

void SoundTagManager::createModelColumns() {
  m_TreeView->append_column_editable("", m_Columns.m_selected);
  m_TreeView->append_column_editable("Sound Tag", m_Columns.m_soundTag);
  m_TreeView->append_column_editable("File Path", m_Columns.m_filePath);
  m_TreeView->append_column("File Size", m_Columns.m_fileSize);
  m_TreeView->append_column_editable("Delete", m_Columns.m_deleteEntry);
}

void SoundTagManager::createInputColumns() {
  inputSoundsTreeView->append_column_editable("Sound Tag", inputSoundsColumns.m_soundTag);
  inputSoundsTreeView->append_column_editable("File Path", inputSoundsColumns.m_filePath);
}

void SoundTagManager::createNewSoundTag(bool isSelected, string soundTag, string filePath, string fileSize, bool deleteEntry) {
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_selected]       = isSelected;
  row[m_Columns.m_soundTag]       = soundTag;
  row[m_Columns.m_filePath]       = filePath;
  row[m_Columns.m_fileSize]       = fileSize;
  row[m_Columns.m_deleteEntry]    = deleteEntry;
}

void SoundTagManager::inputSounds(string soundTag, string filePath) {
  Gtk::TreeModel::Row row = *(inputSoundsTreeModel->append());
  row[inputSoundsColumns.m_soundTag]       = soundTag;
  row[inputSoundsColumns.m_filePath]       = filePath;
} 
