#include "AudioInputManager.h"

using namespace std;

AudioInputManager::AudioInputManager(const Glib::RefPtr<Gtk::Builder>& refBuilder): m_refBuilder(refBuilder) {

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

void AudioInputManager::createInputColumns() {
  inputSoundsTreeView->append_column_editable("Sound Tag", inputSoundsColumns.m_soundTag);
  inputSoundsTreeView->append_column_editable("File Path", inputSoundsColumns.m_filePath);
}

void AudioInputManager::inputSounds(string soundTag, string filePath) {
  Gtk::TreeModel::Row row = *(inputSoundsTreeModel->append());
  row[inputSoundsColumns.m_soundTag]       = soundTag;
  row[inputSoundsColumns.m_filePath]       = filePath;
} 
