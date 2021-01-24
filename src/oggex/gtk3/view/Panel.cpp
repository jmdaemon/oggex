#include "Panel.h"

Panel::Panel() {
  m_refBuilder = Gtk::Builder::create_from_resource(Resource::PANEL);

  refBuilder->get_widget("quality", pAudioQuality); 
  Glib::RefPtr<Glib::Object> adjustmentObject  = refBuilder->get_object("qualityAdjustment"); 
  qualityAdjustment = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(adjustmentObject);
  qualityAdjustment->signal_value_changed().connect(sigc::mem_fun(*this, &Panel::on_qualityChange));

  refBuilder->get_widget("imageFilePath", imageFilePath);

  refBuilder->get_widget("readSound", readSound);
  readSound->signal_clicked().connect(sigc::mem_fun(*this, &Panel::on_readSound));

  refBuilder->get_widget("imageFilePath", imageFilePath);
  refBuilder->get_widget("removeImageFile", removeImageFile);
  removeImageFile->signal_clicked().connect(sigc::mem_fun(*this, &Panel::on_removeImageFile)); 

}

void Panel::on_qualityChange() {
  fmt::print("Set audioQuality to: {}\n", pAudioQuality->get_value_as_int());
  data.audioQuality = pAudioQuality->get_value_as_int();
}

//void SoundTagManager::on_readSound() {
  //auto children = m_refTreeModel->children();
  //for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
    //auto row = *iter;
    //int index = std::distance(children.begin(), iter);
    //Glib::ustring soundTag = row[m_Columns.m_soundTag];
    //Glib::ustring filePath = row[m_Columns.m_filePath];
    //if (!soundTag.empty() && !filePath.empty()) {
      //fmt::print("row: {}\n", index);
      //fmt::print("soundTag: {}\n", soundTag);
      //fmt::print("filePath: {}\n", filePath);
      //fmt::print("Reading Sounds...\n\n");
      //// Read audio file path
      //// Create AudioData object with soundTag and fileSize
      //// Call createNewSoundTag with the data
    //}
  //}
//} 

//void SoundTagManager::on_removeImageFile() {
  //imageFilePath->unselect_file(imageFilePath->get_file());
  //fmt::print("Remove image file\n");
//}
