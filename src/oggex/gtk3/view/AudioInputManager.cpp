#include "AudioInputManager.h"

using namespace std;

AudioInputManager::AudioInputManager() {

  m_refBuilder = Gtk::Builder::create_from_resource("/com/github/jmd/oggex/AudioInputView.ui");
  m_refBuilder->get_widget("inputSoundsWindow", inputSoundsWindow);
  m_refBuilder->get_widget("inputSounds", inputSoundsTreeView);

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
