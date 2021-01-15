#ifndef EMBED_WINDOW_H
#define EMBED_WINDOW_H

#include <gtkmm.h>
#include <vector>
#include <string>

#include "Audio.h"

class EmbedWindow : public Gtk::ApplicationWindow {
  protected: Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::FileChooserButton* imageFilePath;
    Gtk::Entry* outputFileName;
    Gtk::Button* embed;

    Glib::RefPtr<Gtk::Adjustment> qualityAdjustment;
    Gtk::SpinButton* pAudioQuality;

    Gtk::CheckButton* limit4MiB;
    Gtk::CheckButton* pAudioChannel;
    Gtk::Button* browseSaveOutput;
    Gtk::Button* readSound;
    Gtk::Button* deleteSelected;
    Gtk::Button* removeImageFile;

    std::vector<std::string> audioFilePaths;
    std::vector<std::string> soundTags;

    Audio::AudioData data;
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

    class InputSoundsColumns : public Gtk::TreeModelColumnRecord {
      public:
        InputSoundsColumns() { add(m_soundTag); add(m_filePath); }
        Gtk::TreeModelColumn<Glib::ustring> m_soundTag;
        Gtk::TreeModelColumn<Glib::ustring> m_filePath;
    };
    InputSoundsColumns inputSoundsColumns;

    Gtk::ScrolledWindow* m_ScrolledWindow;
    Gtk::ScrolledWindow* inputSoundsWindow;

    Gtk::TreeView* m_TreeView;
    Gtk::TreeView* inputSoundsTreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
    Glib::RefPtr<Gtk::ListStore> inputSoundsTreeModel;

  public: 
    EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static EmbedWindow* create();

    void on_qualityChange();
    void toggleMonoAudioChannel();
    void toggle4MiBLimit();
    void on_deleteSelected();
    void on_readSound();
    void on_embed();
    void on_removeImageFile();

    void createModelColumns();
    void createInputColumns();
    void createNewSoundTag(bool isSelected, std::string soundTag, std::string filePath, std::string fileSize, bool deleteEntry);
    void inputSounds(std::string soundTag, std::string filePath);

};


#endif
