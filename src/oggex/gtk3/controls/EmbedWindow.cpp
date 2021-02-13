#include "EmbedWindow.h"
#include "EmbedAudio.h"

#include <filesystem>
#include <memory>

using namespace std;
namespace fs = std::filesystem;

EmbedWindow::EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder): 
  Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) { 

  soundTagManager.create();
  Glib::RefPtr<Glib::Object> object = m_refBuilder->get_object("EmbedGrid"); 
  EmbedGrid = Glib::RefPtr<Gtk::Grid>::cast_dynamic(object);

  m_refBuilder->get_widget("quality", pAudioQuality); 
  Glib::RefPtr<Glib::Object> adjustmentObject  = m_refBuilder->get_object("qualityAdjustment"); 
  qualityAdjustment = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(adjustmentObject);
  qualityAdjustment->signal_value_changed().connect(sigc::mem_fun(*this, &EmbedWindow::on_qualityChange));

  //Panel panel;
  //AudioInputManager audioInputManager;
  //SoundTagManager soundTagManager;

  //panel.removeImageFile->signal_clicked().connect(sigc::mem_fun(&panel, &Panel::on_removeImageFile));
  // 1: Left:   the column number to attach the left side of child to 
  // 2: Top:    the row number to attach the top side of child to 
  // 3: Width   the number of columns that child will span
  // 4: Height: the number of rows that child will span

  // Row 1:
  EmbedGrid->attach(*panel.imageFileLabel, 0, 0, 1, 1);
  EmbedGrid->attach(*panel.imageFilePath, 1, 0, 2, 1);
  EmbedGrid->attach(*panel.removeImageFile, 3, 0, 1, 1);

  // Row 2:
  EmbedGrid->attach(*audioInputManager.inputSoundsWindow, 0, 1, 4, 1);

  // Row 3:
  EmbedGrid->attach(*soundTagManager.m_ScrolledWindow, 0, 2, 4, 1);

  // Row 4:
  EmbedGrid->attach(*panel.reset, 3, 3, 1, 1);
  EmbedGrid->attach(*panel.readSound, 2, 4, 1, 1);


  //refBuilder->get_widget("imageFilePath", imageFilePath);
  //refBuilder->get_widget("outputFileName", outputFileName);

  //refBuilder->get_widget("embed", embed);
  //embed->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_embed)); 
  //refBuilder->get_widget("audioChannel", pAudioChannel);
  //pAudioChannel->signal_toggled().connect(sigc::mem_fun(*this, &EmbedWindow::toggleMonoAudioChannel));

  //refBuilder->get_widget("limit4MiB", limit4MiB);
  //limit4MiB->signal_toggled().connect(sigc::mem_fun(*this, &EmbedWindow::toggle4MiBLimit));

  //refBuilder->get_widget("readSound", readSound);
  //readSound->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_readSound));

  //refBuilder->get_widget("deleteSelected", deleteSelected);
  //deleteSelected->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_deleteSelected));

  //refBuilder->get_widget("imageFilePath", imageFilePath);
  //refBuilder->get_widget("removeImageFile", removeImageFile);
  //removeImageFile->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_removeImageFile)); 

  show_all_children();
}

EmbedWindow* EmbedWindow::create() {
  auto refBuilder = Gtk::Builder::create_from_resource(Resource::EMBED);
  //refBuilder->add_from_file("resources/xml/FileSelect.ui");
  refBuilder->add_from_file("resources/xml/gtk3/FileSelect.ui");
  
  EmbedWindow* window = nullptr;
  refBuilder->get_widget_derived("Embed", window);
  if (!window)
    throw std::runtime_error("No \"Embed\" object in Embed.glade");

  return window;
}

//void EmbedWindow::toggleMonoAudioChannel() {
  //fmt::print("Set Mono Audio Channel: {}\n", pAudioChannel->get_active());
  //data.lowQuality = pAudioChannel->get_active();
//}

void EmbedWindow::toggle4MiBLimit() {
  fmt::print("Toggle 4MiB Limit\n"); // Use defaults
  // Toggle under4MiB Flag
}

void EmbedWindow::on_qualityChange() {
  fmt::print("Set audioQuality to: {}\n", pAudioQuality->get_value_as_int());
  data.audioQuality = pAudioQuality->get_value_as_int();
}
