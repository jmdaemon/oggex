#include "embedwidget.h"

EmbedWidget::EmbedWidget(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
  : Gtk::Widget(cobject), builder(builder) {

}

EmbedWidget* EmbedWidget::create() {
//EmbedWidget* create() {
  // Load the Builder file and instantiate its widgets.
 auto builder = Gtk::Builder::create_from_resource("/io/github/com/jmdaemon/oggex/../../../resources/gtk/embedwidget.ui");

  auto widget = Gtk::Builder::get_widget_derived<EmbedWidget>(builder, "embed_grid");
  
  if (!widget)
    throw std::runtime_error("No \"app_widget\" object in widget.ui");

  return widget;
}
