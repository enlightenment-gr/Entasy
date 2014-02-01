#include "entasy_sliders.h"
#include "entasy_cb.h"

void
ent_create_sliders() {
   // Creating time text/label
   entUI.timeText = elm_label_add(entUI.window);
   elm_object_text_set(entUI.timeText, "0:00");
   //elm_label_text_align_set(lb_time,"right");
   evas_object_size_hint_weight_set(entUI.timeText, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(entUI.timeText, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(entUI.controls, entUI.timeText, 6, 1, 1, 1);
   evas_object_show(entUI.timeText);

   // Creating time slider
   entUI.timeSlider = elm_slider_add(entUI.window);
   elm_slider_min_max_set(entUI.timeSlider,0,100);
   evas_object_size_hint_weight_set(entUI.timeSlider, EVAS_HINT_EXPAND, 0);
   evas_object_size_hint_align_set(entUI.timeSlider, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(entUI.controls, entUI.timeSlider, 7, 1, 3, 1);
   evas_object_show(entUI.timeSlider);

   // Creating volume slider
   entUI.volumeSlider = elm_slider_add(entUI.window);
   elm_object_text_set(entUI.volumeSlider,"Volume");
   elm_slider_value_set(entUI.volumeSlider,100);
   evas_object_size_hint_weight_set(entUI.volumeSlider, EVAS_HINT_FILL, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(entUI.volumeSlider, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(entUI.controls, entUI.volumeSlider, 10, 1, 1, 1);
   evas_object_show(entUI.volumeSlider);

   // Setting up callbacks
   evas_object_smart_callback_add(entUI.volumeSlider, "changed", ent_change_volume, NULL);
   evas_object_smart_callback_add(entUI.timeSlider, "changed", ent_change_time, NULL);
   evas_object_smart_callback_add(entUI.emotion, "position_update", ent_update_time, entUI.timeSlider);
}
