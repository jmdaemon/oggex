#ifndef AUDIO_INPUT_MANAGER_H
#define AUDIO_INPUT_MANAGER_H

#include "Resources.h"
#include "Audio.h"
#include "View.h"
#include <vector>
#include <filesystem>

class AudioInputManager : public View {
  private: 
    Glib::RefPtr<Gtk::Builder> m_refBuilder;

  public:
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

  virtual void create();
  void createInputColumns();
  void inputSounds(std::string soundTag, std::string filePath);
};

#endif
