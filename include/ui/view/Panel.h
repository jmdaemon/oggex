#ifndef PANEL_H
#define PANEL_H

#include "Audio.h"
#include "Resources.h"
#include "View.h"

class Panel : public View {
  private:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Audio::AudioData data;

  public:
    Gtk::FileChooserButton* imageFilePath;
    Gtk::Entry* outputFileName;
    Gtk::Label* imageFileLabel;
    Gtk::Button* removeImageFile;

    Glib::RefPtr<Gtk::Adjustment> qualityAdjustment;
    Gtk::SpinButton* pAudioQuality;

    Gtk::Button* readSound;
    Gtk::Button* reset;

  public:
    Panel();
    //void on_qualityChange();
    virtual void create();
    void on_readSound();
    void on_removeImageFile();
};
#endif
