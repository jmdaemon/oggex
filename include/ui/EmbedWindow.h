#ifndef EMBED_WINDOW_H
#define EMBED_WINDOW_H

#include <gtkmm.h>
#include <vector>
#include <string>

class EmbedWindow : public Gtk::ApplicationWindow {
  protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::FileChooserButton* imageFilePath;
    Gtk::Entry* outputFileName;
    Gtk::Button* embed;

    std::vector<std::string> audioFilePaths;
    std::vector<std::string> soundTags;

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
};


#endif
