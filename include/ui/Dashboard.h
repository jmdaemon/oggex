#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtkmm.h>
//#include <gtkmm/window.h>
////#include <gtkmm/overlay.h>
////#include <gtkmm/filechooser.h>
//#include <gtkmm/entry.h>
//#include <gtkmm/button.h>
//#include <gtkmm/spinbutton.h>
//#include <gtkmm/progressbar.h>

//class DashboardController : public Gtk::Window {
class DashboardWindow;
class DashboardController : public Gtk::Application {
  private:
    DashboardWindow* create_appwindow();
    void on_hide_window(Gtk::Window* window);

  protected:
    DashboardController();

    // Override default signal handlers:
    void on_activate() override;
    void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint) override;

  public:
    static Glib::RefPtr<DashboardController> create();
  //protected: 
    //Gtk::Entry imageFilePath;
    //Gtk::Entry audioFilePath;

    //Gtk::Button browseImage;
    //Gtk::Button addSound;
    //Gtk::Button readSound;
    //Gtk::Button reset;

    //Gtk::Entry outputFileName;
    //Gtk::SpinButton quality;
    //Gtk::Button browseSaveOutput;
    //Gtk::Button embed;
    //Gtk::Button extract;

    ////GtkOverlay* browseFiles;
    ////GtkFileChooser* selectFile;
    //Gtk::ProgressBar progressBar;

    ////Signal handlers 
    //void on_button_file_clicked();
    //void on_button_folder_clicked();
    //void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);
    //void on_folder_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);

    //void clickToBrowse();
    ////void addSoundFile();
    ////void removeSoundFile();
    ////void readSoundFile();

    ////void setQuality();
    ////void embedAudio();
    ////void extractAudio();

  //public:
    //DashboardController();
    //DashboardController(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    //virtual ~DashboardController();
};

#endif
