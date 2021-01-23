#include "Embed.h"
#include "EmbedWindow.h"
#include "InterfaceID.h"
#include "EmbedAudio.h"

#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

EmbedWindow::EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder), m_Box(Gtk::ORIENTATION_VERTICAL) { 


  data = Audio::AudioData();
  add(m_Box);

  //Edit menu:
  add_action("copy", sigc::mem_fun(*this, &EmbedWindow::on_menu_others));
  add_action("paste", sigc::mem_fun(*this, &EmbedWindow::on_menu_others));
  add_action("something", sigc::mem_fun(*this, &EmbedWindow::on_menu_others));

  //Choices menus, to demonstrate Radio items,
  //using our convenience methods for string and int radio values:
  m_refChoice = add_action_radio_string("choice",
    sigc::mem_fun(*this, &EmbedWindow::on_menu_choices), "a");

  m_refChoiceOther = add_action_radio_integer("choiceother",
    sigc::mem_fun(*this, &EmbedWindow::on_menu_choices_other), 1);

  m_refToggle = add_action_bool("sometoggle",
    sigc::mem_fun(*this, &EmbedWindow::on_menu_toggle), false);

  //Help menu:
  add_action("about", sigc::mem_fun(*this, &EmbedWindow::on_menu_others));


  refBuilder->get_widget("quality", pAudioQuality); 
  Glib::RefPtr<Glib::Object> adjustmentObject  = refBuilder->get_object("qualityAdjustment"); 
  qualityAdjustment = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(adjustmentObject);
  qualityAdjustment->signal_value_changed().connect(sigc::mem_fun(*this, &EmbedWindow::on_qualityChange));

  refBuilder->get_widget("imageFilePath", imageFilePath);
  refBuilder->get_widget("outputFileName", outputFileName);
  refBuilder->get_widget("embed", embed);
  embed->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_embed));

  refBuilder->get_widget("audioChannel", pAudioChannel);
  pAudioChannel->signal_toggled().connect(sigc::mem_fun(*this, &EmbedWindow::toggleMonoAudioChannel));

  refBuilder->get_widget("limit4MiB", limit4MiB);
  limit4MiB->signal_toggled().connect(sigc::mem_fun(*this, &EmbedWindow::toggle4MiBLimit));

  refBuilder->get_widget("readSound", readSound);
  readSound->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_readSound));

  refBuilder->get_widget("deleteSelected", deleteSelected);
  deleteSelected->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_deleteSelected));

  refBuilder->get_widget("imageFilePath", imageFilePath);
  refBuilder->get_widget("removeImageFile", removeImageFile);
  removeImageFile->signal_clicked().connect(sigc::mem_fun(*this, &EmbedWindow::on_removeImageFile));

  refBuilder->get_widget("soundsWindow", m_ScrolledWindow);
  refBuilder->get_widget("soundTagMetadata", m_TreeView);

  refBuilder->get_widget("inputSoundsWindow", inputSoundsWindow);
  refBuilder->get_widget("inputSounds", inputSoundsTreeView);

  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView->set_model(m_refTreeModel);
  createNewSoundTag(true, "[audio02]", "/home/user/directory", "156.6kB", true);
  createNewSoundTag(false, "[audio03]", "/home/user/some/directory/", "452.9 kB", false);
  createNewSoundTag(true, "[audio04]", "/home/user/some/directory/", "1553.9 kB", false);
  createModelColumns();

  inputSoundsTreeModel = Gtk::ListStore::create(inputSoundsColumns);
  inputSoundsTreeView->set_model(inputSoundsTreeModel);
  inputSounds("[testAudioTag]", "/home/user/path/to/audio/file");
  inputSounds("[audio01]", "/home/user/audio01.ogg");
  inputSounds("[audio02]", "/home/user/audio02.ogg");
  inputSounds("[ominous01]", "/home/user/ominous.ogg");
  inputSounds("[cave01]", "/home/user/cave.ogg");
  createInputColumns();

  show_all_children();
}

EmbedWindow* EmbedWindow::create() {
  auto refBuilder = Gtk::Builder::create_from_resource(Embed::EMBED_RESOURCE_FILE);
  //refBuilder->add_from_file("resources/xml/FileSelect.ui");
  refBuilder->add_from_file("resources/xml/gtk3/FileSelect.ui");
  
  EmbedWindow* window = nullptr;
  refBuilder->get_widget_derived("Embed", window);
  if (!window)
    throw std::runtime_error("No \"Embed\" object in Embed.glade");

  return window;
}

void EmbedWindow::on_qualityChange() {
  fmt::print("Set audioQuality to: {}\n", pAudioQuality->get_value_as_int());
  data.audioQuality = pAudioQuality->get_value_as_int();
}

void EmbedWindow::toggleMonoAudioChannel() {
  fmt::print("Set Mono Audio Channel: {}\n", pAudioChannel->get_active());
  data.lowQuality = pAudioChannel->get_active();
}

void EmbedWindow::toggle4MiBLimit() {
  fmt::print("Toggle 4MiB Limit\n"); // Use defaults
  // Toggle under4MiB Flag
}

void EmbedWindow::on_deleteSelected() {
  auto children = m_refTreeModel->children();
  for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
    auto row = *iter;
    bool isSelected = row[m_Columns.m_selected];
    int index = std::distance(children.begin(), iter);
    fmt::print("Row: {}\n", index);
    fmt::print("isSelected: {}\n", isSelected);
    if (isSelected == true) {
      fmt::print("Deleting row\n");
      m_refTreeModel->erase(iter);
      iter = children.begin();
    }
  }
}

void EmbedWindow::on_readSound() {
  auto children = m_refTreeModel->children();
  for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
    auto row = *iter;
    int index = std::distance(children.begin(), iter);
    Glib::ustring soundTag = row[m_Columns.m_soundTag];
    Glib::ustring filePath = row[m_Columns.m_filePath];
    if (!soundTag.empty() && !filePath.empty()) {
      fmt::print("row: {}\n", index);
      fmt::print("soundTag: {}\n", soundTag);
      fmt::print("filePath: {}\n", filePath);
      fmt::print("Reading Sounds...\n\n");
      // Read audio file path
      // Create AudioData object with soundTag and fileSize
      // Call createNewSoundTag with the data
    }
  }
}

void EmbedWindow::on_embed() {
  auto children = m_refTreeModel->children();
  for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
    auto row = *iter;
    auto soundTag = row[m_Columns.m_soundTag];
    auto filePath = row[m_Columns.m_filePath];
    int index = std::distance(children.begin(), iter);
    fmt::print("row: {}\n", index);
    fmt::print("soundTag: {}\n", soundTag);
    fmt::print("filePath: {}\n\n", filePath);
  }
}

void EmbedWindow::on_removeImageFile() {
  imageFilePath->unselect_file(imageFilePath->get_file());
  fmt::print("Remove image file\n");
}

void EmbedWindow::createModelColumns() {
  m_TreeView->append_column_editable("", m_Columns.m_selected);
  m_TreeView->append_column_editable("Sound Tag", m_Columns.m_soundTag);
  m_TreeView->append_column_editable("File Path", m_Columns.m_filePath);
  m_TreeView->append_column("File Size", m_Columns.m_fileSize);
  m_TreeView->append_column_editable("Delete", m_Columns.m_deleteEntry);
}

void EmbedWindow::createInputColumns() {
  inputSoundsTreeView->append_column_editable("Sound Tag", inputSoundsColumns.m_soundTag);
  inputSoundsTreeView->append_column_editable("File Path", inputSoundsColumns.m_filePath);
}

void EmbedWindow::createNewSoundTag(bool isSelected, string soundTag, string filePath, string fileSize, bool deleteEntry) {
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_selected]       = isSelected;
  row[m_Columns.m_soundTag]       = soundTag;
  row[m_Columns.m_filePath]       = filePath;
  row[m_Columns.m_fileSize]       = fileSize;
  row[m_Columns.m_deleteEntry]    = deleteEntry;
}

void EmbedWindow::inputSounds(string soundTag, string filePath) {
  Gtk::TreeModel::Row row = *(inputSoundsTreeModel->append());
  row[inputSoundsColumns.m_soundTag]       = soundTag;
  row[inputSoundsColumns.m_filePath]       = filePath;
}

void EmbedWindow::on_menu_others()
{
  std::cout << "A menu item was selected." << std::endl;
}

void EmbedWindow::on_menu_choices(const Glib::ustring& parameter)
{
  //The radio action's state does not change automatically:
  m_refChoice->change_state(parameter);

  Glib::ustring message;
  if (parameter == "a")
    message = "Choice a was selected.";
  else
    message = "Choice b was selected.";

  std::cout << message << std::endl;
}

void EmbedWindow::on_menu_choices_other(int parameter)
{
  //The radio action's state does not change automatically:
  m_refChoiceOther->change_state(parameter);

  Glib::ustring message;
  if (parameter == 1)
    message = "Choice 1 was selected.";
  else
    message = "Choice 2 was selected.";

  std::cout << message << std::endl;
}

void EmbedWindow::on_menu_toggle()
{
  bool active = false;
  m_refToggle->get_state(active);

  //The toggle action's state does not change automatically:
  active = !active;
  m_refToggle->change_state(active);

  Glib::ustring message;
  if (active)
    message = "Toggle is active.";
  else
    message = "Toggle is not active.";

  std::cout << message << std::endl;
}

