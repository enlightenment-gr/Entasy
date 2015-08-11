#include "entasy.h"
#include "entasy_ui.h"
#include "entasy_cb.h"



EAPI_MAIN int
elm_main(int argc, char **argv)
{
    Evas_Object *o;
    config.directory = "/home/YourUsername/Music";


    // Setting up the window
    entUI.window = elm_win_add(NULL, "entasy", ELM_WIN_BASIC);
    elm_win_title_set(entUI.window, "Entasy");
    elm_win_autodel_set(entUI.window, 1);


    // Setting up emotion
    entUI.emotion = emotion_object_add( evas_object_evas_get(entUI.window) );
    if( emotion_object_init(entUI.emotion,"gstreamer1") == EINA_FALSE)
      printf("Emotion not properly initialized!");


   // Setting up background
   entUI.background = elm_bg_add(entUI.window);
   evas_object_size_hint_weight_set(entUI.background, 1.0, 1.0);
   elm_win_resize_object_add(entUI.window, entUI.background);
   evas_object_show(entUI.background);


   // Settin up widgets box
   entUI.box = elm_box_add(entUI.window);
   elm_box_horizontal_set(entUI.box,EINA_TRUE);
   elm_win_resize_object_add(entUI.window, entUI.box);
   evas_object_show(entUI.box);


   // Setting up controls
   entUI.controls = elm_table_add(entUI.window);
   elm_box_pack_end(entUI.box, entUI.controls);
   evas_object_size_hint_align_set(entUI.controls, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(entUI.controls);


   //Create parent directory input
   ent_create_directory();

   // Creating tracklist
   ent_create_tracklist();
   ent_load_file_list(entUI.tracklist, NULL, NULL);

   // Setting up the flipper widget
   ent_create_flipper();

   // Creating control buttons (Play, Pause, Stop etc)
   ent_create_control_buttons();

   // Creating the sliders (Time, Volume)
   ent_create_sliders();


   // Loading-up the preferences dialog
   ent_load_elm_preferences();
   Elm_Prefs_Data* prefs = elm_prefs_data_new("entasy.cfg", NULL, EET_FILE_MODE_READ_WRITE);
   elm_prefs_data_set(entUI.preferences, prefs);

   // Load the preference data
   Elm_Prefs_Item_Type prefType;
   Eina_Value prefValue;
   if ( elm_prefs_data_value_get(prefs, "main:musiclib_path", &prefType, &prefValue) ) {
        eina_value_get(&prefValue, config.directory);
   }


   // Preferences callback(s)
    evas_object_smart_callback_add(entUI.preferences, "page,saved", ent_preferences_save, NULL);

   // Window callbacks
   evas_object_smart_callback_add(entUI.window, "delete,request", ent_quit, NULL);
   evas_object_smart_callback_add(entUI.directory, "changed", ent_directory_changed, NULL);
   evas_object_smart_callback_add(entUI.volumeSlider, "changed", ent_change_volume, NULL);
   evas_object_smart_callback_add(entUI.timeSlider, "changed", ent_change_time, NULL);
   //evas_object_smart_callback_add(entUI.flipper, "clicked", ent_flip_panel, entUI.flipper);
   evas_object_smart_callback_add(entUI.emotion, "playback_finished", ent_next_item_play, NULL);
   evas_object_smart_callback_add(entUI.emotion, "position_update", ent_update_time, entUI.timeSlider);


   // Show the window and RUN!
   evas_object_show(entUI.window);
   elm_run();
   return 0;
}
ELM_MAIN()

