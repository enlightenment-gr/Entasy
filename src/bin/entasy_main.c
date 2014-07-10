#include "entasy.h"
#include "entasy_cb.h"
#include "entasy_tracklist.h"
#include "entasy_flipper.h"
#include "entasy_control_buttons.h"
#include "entasy_sliders.h"

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
    if( emotion_object_init(entUI.emotion,"gstreamer") == EINA_FALSE)
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

   //Create parent folder input
   entUI.folder = ent_create_folder();

   // Creating tracklist
   entUI.tracklist = ent_create_tracklist();

   // Setting up the flipper widget
   entUI.flipper = ent_create_flipper();

   // Creating control buttons (Play, Pause, Stop etc)
   ent_create_control_buttons();

   // Creating the sliders (Time, Volume)
   ent_create_sliders();

   // Window callbacks
   evas_object_smart_callback_add(entUI.window, "delete,request", ent_quit, NULL);
   evas_object_smart_callback_add(entUI.folder, "changed", ent_directory_changed, NULL);

   // Show the window and RUN!
   evas_object_show(entUI.window);
   elm_run();
   return 0;
}
ELM_MAIN()

