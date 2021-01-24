#include "Panel.h"

Panel::Panel() {
  m_refBuilder = Gtk::Builder::create_from_resource(Resource::PANEL);

  m_refBuilder->get_widget("imageFileLabel", imageFileLabel);
  m_refBuilder->get_widget("imageFilePath", imageFilePath);
  m_refBuilder->get_widget("readSound", readSound);
  m_refBuilder->get_widget("reset", reset);
  m_refBuilder->get_widget("imageFilePath", imageFilePath);
  m_refBuilder->get_widget("removeImageFile", removeImageFile);

  readSound->signal_clicked().connect(sigc::mem_fun(*this, &Panel::on_readSound));
  removeImageFile->signal_clicked().connect(sigc::mem_fun(*this, &Panel::on_removeImageFile));

} 

//void Panel::on_readSound() {
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

void Panel::on_removeImageFile() {
  if (imageFilePath->get_file()) {
    //imageFilePath->unselect_file(imageFilePath->get_file());
    imageFilePath->unselect_all();
    fmt::print("Remove image file\n");
  }
}

void Panel::on_readSound() {}
//void Panel::on_removeImageFile() {}
