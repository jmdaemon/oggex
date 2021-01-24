#ifndef EMBED_WINDOW_H
#define EMBED_WINDOW_H

#include <gtkmm.h>
#include <vector>
#include <string>

#include "Panel.h"
#include "AudioInputManager.h"
#include "SoundTagManager.h"

#include "Audio.h"
#include "Resources.h"

class EmbedWindow : public Gtk::ApplicationWindow {
  protected: 
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Glib::RefPtr<Gtk::Grid> EmbedGrid;

    Audio::AudioData data;
    //Panel panel;
    //AudioInputManager audioInputManager;
    //SoundTagManager soundTagManager;

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

  public: 
    EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static EmbedWindow* create();

    void on_qualityChange();
    void toggleMonoAudioChannel();
    void toggle4MiBLimit();
};

#endif
