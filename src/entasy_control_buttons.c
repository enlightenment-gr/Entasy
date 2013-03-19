#include "entasy_control_buttons.h"
#include "entasy_cb.h"

void
ent_create_control_buttons(){
       // THE BUTTOONNZZ
       Evas_Object *buttonPlay, *buttonPause, *buttonStop, *buttonPrev, *buttonNext;

       // PLAY Button
       buttonPlay = elm_button_add(entUI.window);
       elm_object_text_set(buttonPlay,"Play");
       evas_object_size_hint_weight_set(buttonPlay, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
       evas_object_size_hint_align_set(buttonPlay, EVAS_HINT_FILL, EVAS_HINT_FILL);
       elm_table_pack(entUI.controls, buttonPlay, 6, 0, 1, 1);
       evas_object_show(buttonPlay);


       // PAUSE Button
       buttonPause = elm_button_add(entUI.window);
       elm_object_text_set(buttonPause,"Pause");
       evas_object_size_hint_weight_set(buttonPause, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
       evas_object_size_hint_align_set(buttonPause, EVAS_HINT_FILL, EVAS_HINT_FILL);
       elm_table_pack(entUI.controls, buttonPause, 7, 0, 1, 1);
       evas_object_show(buttonPause);


       // STOP Button
       buttonStop = elm_button_add(entUI.window);
       elm_object_text_set(buttonStop,"Stop");
       evas_object_size_hint_weight_set(buttonStop, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
       evas_object_size_hint_align_set(buttonStop, EVAS_HINT_FILL, EVAS_HINT_FILL);
       elm_table_pack(entUI.controls, buttonStop, 8, 0, 1, 1);
       evas_object_show(buttonStop);


       // PREVIOUS Button
       buttonPrev = elm_button_add(entUI.window);
       elm_object_text_set(buttonPrev,"<<");
       evas_object_size_hint_weight_set(buttonPrev, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
       evas_object_size_hint_align_set(buttonPrev, EVAS_HINT_FILL, EVAS_HINT_FILL);
       elm_table_pack(entUI.controls, buttonPrev, 9, 0, 1, 1);
       evas_object_show(buttonPrev);


       // NEXT Button
       buttonNext = elm_button_add(entUI.window);
       elm_object_text_set(buttonNext,">>");
       evas_object_size_hint_weight_set(buttonNext, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
       evas_object_size_hint_align_set(buttonNext, EVAS_HINT_FILL, EVAS_HINT_FILL);
       elm_table_pack(entUI.controls, buttonNext, 10, 0, 1, 1);
       evas_object_show(buttonNext);


       // Setting up callbacks
       evas_object_smart_callback_add(buttonPlay, "clicked", ent_play, NULL);
       evas_object_smart_callback_add(buttonPause, "clicked", ent_pause, NULL);
       evas_object_smart_callback_add(buttonStop, "clicked", ent_stop, NULL);
       ent_load_file_list(entUI.tracklist,NULL,NULL);
       evas_object_smart_callback_add(buttonPrev, "clicked", ent_prev_item_play, entUI.tracklist);
       evas_object_smart_callback_add(buttonNext, "clicked", ent_next_item_play, entUI.tracklist);
}
