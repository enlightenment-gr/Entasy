#include "entasy_cb.h"
void
ent_create_control_buttons() {
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

Evas_Object*
ent_create_flipper() {
     // Create and setup the flipbox (or "flipper")
       Evas_Object *flipbox;

       flipbox = elm_flip_add(entUI.window);
     evas_object_resize(flipbox, 200, 200);
     elm_table_pack(entUI.controls, flipbox, 0, 0, 6, 6);
     evas_object_show(flipbox);

     elm_flip_interaction_set(flipbox, ELM_FLIP_INTERACTION_PAGE);
     elm_flip_interaction_direction_hitsize_set(flipbox, ELM_FLIP_DIRECTION_LEFT, 1);
     elm_flip_interaction_direction_hitsize_set(flipbox, ELM_FLIP_DIRECTION_RIGHT, 1);

     // Creating the album cover
     Evas_Object *cover;
     cover = elm_photo_add(entUI.window);
     elm_photo_size_set(cover,200);
     elm_photo_fill_inside_set(cover, EINA_TRUE);
     elm_photo_file_set(cover, "nullcover.jpg");
     elm_object_part_content_set(flipbox, "front", cover);
     evas_object_show(cover);

     // Creating the lyrics textbox
     Evas_Object *lyricstext;
     lyricstext = elm_entry_add(entUI.window);
     elm_entry_entry_set (lyricstext,"No Lyrics Found!");
     elm_object_part_content_set(flipbox, "back", lyricstext);
     evas_object_show(lyricstext);

     // Setup the callbacks
     evas_object_smart_callback_add(cover, "clicked", ent_flip_panel, flipbox);
       evas_object_smart_callback_add(lyricstext, "clicked", ent_flip_panel, flipbox);

     return flipbox;
}

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

Evas_Object *
ent_create_directory() {
      Evas_Object *o, *folder;

      o = elm_label_add(entUI.window);
      elm_object_text_set(o, "Parent Music Folder");
      evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(entUI.controls, o, 6, 6, 1, 1);
      evas_object_show(o);

      folder = elm_entry_add(entUI.window);
      evas_object_size_hint_weight_set(folder, EVAS_HINT_EXPAND, 0.0);
      evas_object_size_hint_align_set(folder, EVAS_HINT_FILL, 0.5);
      elm_entry_single_line_set(folder, EINA_TRUE);
      elm_entry_scrollable_set(folder, EINA_TRUE);
      elm_scroller_policy_set(folder, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
      elm_object_text_set(folder, config.directory);
      //elm_box_pack_end(entUI.window, folder);
      elm_table_pack(entUI.controls, folder, 6, 7, 5, 1);
      evas_object_show(folder);

      return folder;
}

Evas_Object*
ent_create_tracklist() {
    Evas_Object *tracklist;

    tracklist = elm_list_add(entUI.window);
      elm_list_mode_set(tracklist, ELM_LIST_LIMIT);
      evas_object_size_hint_weight_set(tracklist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(tracklist, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(entUI.controls, tracklist, 6, 2, 6, 4);
      evas_object_show(tracklist);

      return tracklist;
}
