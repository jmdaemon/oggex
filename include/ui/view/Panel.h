#ifndef PANEL_H
#define PANEL_H

#include "Audio.h"
#include "Resources.h"

class Panel {
  private:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Audio::AudioData data;

  public:
    Gtk::FileChooserButton* imageFilePath;
    Gtk::Entry* outputFileName;
    Gtk::Button* removeImageFile;

    Glib::RefPtr<Gtk::Adjustment> qualityAdjustment;
    Gtk::SpinButton* pAudioQuality;

    Gtk::Button* readSound;

  public:
    Panel();
    //void on_qualityChange();
    void on_readSound();
    void on_removeImageFile();
};
#endif
