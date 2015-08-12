#include "entasy_cb.h"


void
ent_create_control_buttons()
{

    Evas_Object *buttonPlay, *buttonPause, *buttonStop, *buttonPrev, *buttonNext;
    Evas_Object *buttonPrefs, *iconPrefs;

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


    // Preferences Button
    buttonPrefs = elm_button_add(entUI.window);
    iconPrefs = elm_icon_add(buttonPrefs);
    elm_icon_standard_set(iconPrefs, "preferences-desktop");
    
    evas_object_size_hint_weight_set(iconPrefs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(iconPrefs, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_weight_set(buttonPrefs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(buttonPrefs, EVAS_HINT_FILL, EVAS_HINT_FILL);

    elm_object_part_content_set(buttonPrefs, "icon", iconPrefs);
    elm_table_pack(entUI.controls, buttonPrefs, 11, 0, 2, 1);
    evas_object_show(iconPrefs);
    evas_object_show(buttonPrefs);


    // Setting up callbacks
    evas_object_smart_callback_add(buttonPlay, "clicked", ent_play, NULL);
    evas_object_smart_callback_add(buttonPause, "clicked", ent_pause, NULL);
    evas_object_smart_callback_add(buttonStop, "clicked", ent_stop, NULL);
    evas_object_smart_callback_add(buttonPrev, "clicked", ent_prev_item_play, entUI.tracklist);
    evas_object_smart_callback_add(buttonNext, "clicked", ent_next_item_play, entUI.tracklist);
    evas_object_smart_callback_add(buttonPrefs, "clicked", ent_open_prefs, NULL);
}



void
ent_create_flipper()
{

    // Create and setup the flipper)
    entUI.flipper = elm_flip_add(entUI.window);
    evas_object_resize(entUI.flipper, 200, 200);
    elm_table_pack(entUI.controls, entUI.flipper, 0, 0, 6, 6);
    evas_object_show(entUI.flipper);

    elm_flip_interaction_set(entUI.flipper, ELM_FLIP_INTERACTION_ROTATE);
    elm_flip_interaction_direction_enabled_set(entUI.flipper, ELM_FLIP_DIRECTION_LEFT, 1);
    elm_flip_interaction_direction_enabled_set(entUI.flipper, ELM_FLIP_DIRECTION_RIGHT, 1);

    // Creating the album cover
    entUI.flipperCover = elm_photo_add(entUI.window);
    elm_photo_size_set(entUI.flipperCover, 200);
    elm_photo_fill_inside_set(entUI.flipperCover, EINA_TRUE);
    elm_photo_file_set(entUI.flipperCover, "data/nullcover.jpg");
    elm_object_part_content_set(entUI.flipper, "front", entUI.flipperCover);
    evas_object_show(entUI.flipperCover);

    // Creating the lyrics textbox
    entUI.flipperLyrics = elm_entry_add(entUI.window);
    elm_entry_entry_set (entUI.flipperLyrics, "No Lyrics Found!");
    elm_object_part_content_set(entUI.flipper, "back", entUI.flipperLyrics);
    evas_object_show(entUI.flipperLyrics);

    // Setup the callbacks
    evas_object_smart_callback_add(entUI.flipperCover, "clicked", ent_flip_panel, entUI.flipper);
    evas_object_smart_callback_add(entUI.flipperLyrics, "clicked", ent_flip_panel, entUI.flipper);
}



void
ent_create_sliders()
{

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
    elm_table_pack(entUI.controls, entUI.volumeSlider, 10, 1, 4, 1);
    evas_object_show(entUI.volumeSlider);
}



void
ent_create_tracklist()
{
    entUI.tracklist = elm_list_add(entUI.window);
    elm_list_mode_set(entUI.tracklist, ELM_LIST_LIMIT);
    evas_object_size_hint_weight_set(entUI.tracklist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(entUI.tracklist, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_table_pack(entUI.controls, entUI.tracklist, 6, 2, 6, 4);
    evas_object_show(entUI.tracklist);
}



void
ent_load_elm_preferences()
{
    if (entUI.window) {
        entUI.preferences_window = elm_win_add(entUI.window, "entasy_prefs", ELM_WIN_DIALOG_BASIC);
        elm_win_title_set(entUI.preferences_window, "Entasy Preferences");
        elm_win_autodel_set(entUI.preferences_window, 0);
        elm_win_size_base_set(entUI.preferences_window, 270, 120);

        Evas_Object *pfbackground = elm_bg_add(entUI.preferences_window);
        evas_object_size_hint_weight_set(pfbackground, 1.0, 1.0);
        elm_win_resize_object_add(entUI.preferences_window, pfbackground);
        evas_object_show(pfbackground);

        entUI.preferences = elm_prefs_add(entUI.preferences_window);
        elm_prefs_autosave_set(entUI.preferences, EINA_FALSE);
        elm_prefs_file_set(entUI.preferences, "data/prefs.epb", "main");

        elm_win_resize_object_add(entUI.preferences_window, entUI.preferences);
        evas_object_show(entUI.preferences);
    } else {
        printf("* Window not initialized! Tried to load the elm preferences before initializing the window?\n");
    }
}
