#ifndef SOUND_TAG_MANGER_H
#define SOUND_TAG_MANGER_H

#include <gtkmm.h>
#include <vector>
#include <string>

#include <filesystem>
#include "Audio.h"

#include <fmt/core.h>
#include <fmt/printf.h> 

class SoundTagManager { 
  private:
  Glib::RefPtr<Gtk::Builder> m_refBuilder;

  public:
  std::vector<std::string> audioFilePaths;
  std::vector<std::string> soundTags;
  Audio::AudioData data;

  Gtk::TreeView* m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  Gtk::ScrolledWindow* m_ScrolledWindow;

  SoundTagManager();
  
  class ModelColumns : public Gtk::TreeModelColumnRecord { 
    public: 
      ModelColumns() 
      { add(m_selected); add(m_soundTag); add(m_filePath); add(m_fileSize); add(m_deleteEntry); }

      Gtk::TreeModelColumn<bool> m_selected;
      Gtk::TreeModelColumn<Glib::ustring> m_soundTag;
      Gtk::TreeModelColumn<Glib::ustring> m_filePath;
      Gtk::TreeModelColumn<Glib::ustring> m_fileSize;
      Gtk::TreeModelColumn<bool> m_deleteEntry; 
  };
  ModelColumns m_Columns;

  void on_deleteSelected();
  void on_readSound();
  void on_embed();
  void on_removeImageFile();

  void createModelColumns();
  void createNewSoundTag(bool isSelected, std::string soundTag, std::string filePath, std::string fileSize, bool deleteEntry);
};

#endif
