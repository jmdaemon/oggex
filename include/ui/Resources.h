#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <gtkmm.h>

#include <fmt/core.h>
#include <fmt/format.h>

namespace Resource {
  const static std::string PREFIX="/com/github/jmd/oggex";
  static std::string formatResourceID(std::string xmlFile) { return fmt::format("{}/{}", PREFIX, xmlFile); }

  const static std::string MENU_BAR = formatResourceID("MenuBar.ui");

  namespace Dashboard {
    const static std::string RESOURCE_FILE = formatResourceID("Dashboard.ui");

    const static Glib::ustring dashboardID   = "Dashboard";
    const static Glib::ustring browseImageID = "browseImage";
    const static Glib::ustring addSoundID    = "addSound";
    const static Glib::ustring fileChooserID = "selectFile";
    const static Glib::ustring setQualityID  = "quality";
    const static Glib::ustring qualityAdjustmentID  = "qualityAdjustment";
  };

  namespace Embed {
    const static std::string RESOURCE_FILE = formatResourceID("Embed.ui");
  };

  namespace Panel {
    const static std::string RESOURCE_FILE = formatResourceID("Panel.ui");
  };

  namespace SoundTagManager {
    const static std::string RESOURCE_FILE = formatResourceID("SoundTagView.ui");
  };

  namespace AudioInputManager { 
    const static std::string RESOURCE_FILE = formatResourceID("AudioInputView.ui");
  };
};

#endif
