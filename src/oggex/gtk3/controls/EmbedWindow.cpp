#include "Embed.h"
#include "EmbedWindow.h"
#include "Resources.h"
#include "EmbedAudio.h"

#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

EmbedWindow::EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder) { 

  //refBuilder->get_widget("quality", pAudioQuality); 
  //Glib::RefPtr<Glib::Object> adjustmentObject  = refBuilder->get_object("qualityAdjustment"); 
  //qualityAdjustment = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(adjustmentObject);
  //qualityAdjustment->signal_value_changed().connect(sigc::mem_fun(*this, &EmbedWindow::on_qualityChange));

  //m_refBuilder->add_from_file("resources/xml/gtk3/Panel.ui");
  //m_refBuilder->add_from_file("resources/xml/gtk3/AudioInputView.ui");
  //m_refBuilder->add_from_file("resources/xml/gtk3/SoundTagView.ui");

  refBuilder->get_widget("imageFilePath", imageFilePath);
  refBuilder->get_widget("outputFileName", outputFileName);

  //refBuilder->get_widget("embed", embed);
  //embed->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_embed)); 
  //refBuilder->get_widget("audioChannel", pAudioChannel);
  //pAudioChannel->signal_toggled().connect(sigc::mem_fun(*this, &EmbedWindow::toggleMonoAudioChannel));

  refBuilder->get_widget("limit4MiB", limit4MiB);
  limit4MiB->signal_toggled().connect(sigc::mem_fun(*this, &EmbedWindow::toggle4MiBLimit));

  //refBuilder->get_widget("readSound", readSound);
  //readSound->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_readSound));

  //refBuilder->get_widget("deleteSelected", deleteSelected);
  //deleteSelected->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_deleteSelected));

  refBuilder->get_widget("imageFilePath", imageFilePath);
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
