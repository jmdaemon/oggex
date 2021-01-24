#ifndef AUDIO_INPUT_MANAGER_H
#define AUDIO_INPUT_MANAGER_H

#include <gtkmm.h>
#include <vector>
#include <string>

#include <filesystem>
#include "Audio.h"

#include <fmt/core.h>
#include <fmt/printf.h> 

class AudioInputManager {
  Glib::RefPtr<Gtk::Builder> m_refBuilder;

  Gtk::TreeView* inputSoundsTreeView;
  Glib::RefPtr<Gtk::ListStore> inputSoundsTreeModel;
  Gtk::ScrolledWindow* inputSoundsWindow;

  AudioInputManager();

  class InputSoundsColumns : public Gtk::TreeModelColumnRecord {
    public:
      InputSoundsColumns() { add(m_soundTag); add(m_filePath); }
      Gtk::TreeModelColumn<Glib::ustring> m_soundTag;
      Gtk::TreeModelColumn<Glib::ustring> m_filePath;
  };
  InputSoundsColumns inputSoundsColumns;

  void createInputColumns();
  void inputSounds(std::string soundTag, std::string filePath);
};

#endif
