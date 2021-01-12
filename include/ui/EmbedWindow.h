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

    Gtk::ScrolledWindow* m_ScrolledWindow;
    Gtk::TreeView* m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

  public: 
    EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static EmbedWindow* create();

    void on_button_embed_clicked();
    void on_button_extract_clicked();

    void on_quality_change_value();
    void toggleMonoAudioChannel();
    void toggle4MiBLimit();
    void on_deleteSelected();
    void on_readSound();
    void on_embed();
    void on_removeImageFile();

    void createNewSoundTag(bool isSelected, std::string soundTag, std::string filePath, std::string fileSize, bool deleteEntry);

};


#endif
