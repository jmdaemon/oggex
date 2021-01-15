#ifndef DASHBOARD_ID_H
#define DASHBOARD_ID_H

#include <string>
#include <gtkmm.h>

namespace Dashboard {
  const static std::string DASHBOARD_RESOURCE_FILE = "/com/github/jmd/oggex/Dashboard.ui";

  const static Glib::ustring dashboardID   = "Dashboard";
  const static Glib::ustring browseImageID = "browseImage";
  const static Glib::ustring addSoundID    = "addSound";
  const static Glib::ustring fileChooserID = "selectFile";
  const static Glib::ustring setQualityID  = "quality";
  const static Glib::ustring qualityAdjustmentID  = "qualityAdjustment";

};

namespace Embed {
  const static std::string EMBED_RESOURCE_FILE = "/com/github/jmd/oggex/Embed.ui";
};

#endif
