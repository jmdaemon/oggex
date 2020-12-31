#ifndef DASHBOARD_WINDOW_H
#define DASHBOARD_WINDOW_H

#include <gtkmm.h>

class DashboardWindow : public Gtk::ApplicationWindow {
  protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;

    //Gtk::SpinButton* pSetQualitySpinButton;
    //// FileChooserDialog
    //Gtk::Box m_ButtonBox;
    //Gtk::Button m_Button_File, m_Button_Folder;

  public: 
    DashboardWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static DashboardWindow* create();

    void open_file_view(const Glib::RefPtr<Gio::File>& file);

    // FileChooserDialog
    //void on_button_file_clicked();
    //void on_button_folder_clicked();
    //void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);
    //void on_folder_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);

};

#endif
