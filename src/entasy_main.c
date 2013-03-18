#include "entasy.h"
#include "entasy_cb.h"

EAPI_MAIN int
elm_main(int argc, char **argv)
{

// Needed Evas_Object s

    Evas_Object *win, *bg, *table, *box, *mlist, *cover, *lyrFrame, *lyrEntry, *btn_play, *btn_pause;
    Evas_Object *btn_prev, *btn_next, *btn_stop, *sld_volume, *sld_time, *lb_time;
    Evas_Object *flip;
 // char buf[PATH_MAX];

// Window

    win = elm_win_add(NULL, "entasy", ELM_WIN_BASIC);
    elm_win_title_set(win, "Entasy");
    elm_win_autodel_set(win, 1);

// Emotion

    ent_player = emotion_object_add(evas_object_evas_get(win));
    if( emotion_object_init(ent_player,"xine") == EINA_FALSE )
    printf("Emotion not properly initialized!");

// Background

   bg = elm_bg_add(win);
   evas_object_size_hint_weight_set(bg, 1.0, 1.0);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

// Widgets Box

   box = elm_box_add(win);
   elm_box_horizontal_set(box,EINA_TRUE);
   elm_win_resize_object_add(win, box);
   //~ evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   //~ evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(box);

// Table of buttons

   table = elm_table_add(win);
   //elm_win_resize_object_add(win, table);
   elm_box_pack_end(box, table);
   evas_object_size_hint_align_set(table, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(table);

// Flip Widget

   flip = elm_flip_add(win);
   evas_object_resize(flip, 200, 200);
   //~ evas_object_size_hint_weight_set(flip, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   //~ evas_object_size_hint_align_set(flip, EVAS_HINT_FILL, EVAS_HINT_FILL);
   //evas_object_move(flip, 10, 10); 
   elm_table_pack(table, flip, 0, 0, 6, 6);
   evas_object_show(flip);

   elm_flip_interaction_set(flip, ELM_FLIP_INTERACTION_PAGE);

   //elm_flip_interaction_enabled_set(flip, ELM_FLIP_DIRECTION_LEFT, EINA_TRUE);
   //elm_flip_interaction_enabled_set(flip, ELM_FLIP_DIRECTION_RIGHT, EINA_TRUE);

   elm_flip_interaction_direction_hitsize_set(flip, ELM_FLIP_DIRECTION_LEFT, 1);
   elm_flip_interaction_direction_hitsize_set(flip, ELM_FLIP_DIRECTION_RIGHT, 1);

// Album Cover

   cover = elm_photo_add(win);
   elm_photo_size_set(cover,200);
   elm_photo_fill_inside_set(cover, EINA_TRUE);
   elm_photo_file_set(cover, "nullcover.jpg");
   //~ evas_object_size_hint_weight_set(cover, EVAS_HINT_FILL, EVAS_HINT_FILL);
   //~ evas_object_size_hint_align_set(cover, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_part_content_set(flip, "front", cover);
   evas_object_show(cover);

// Lyrics - Frame

   lyrFrame = elm_frame_add(win);
   //elm_flip_interaction_get(flip, lyrFrame);
   elm_object_part_content_set(flip, "back", lyrFrame);
   evas_object_show(lyrFrame);

// Lyrics - Entry

   lyrEntry = elm_entry_add(win);
   //~ evas_object_size_hint_weight_set(lyrEntry, EVAS_HINT_FILL, EVAS_HINT_FILL);
   //~ evas_object_size_hint_align_set(lyrEntry, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_entry_entry_set (lyrEntry,"No Lyrics Found!");
   //elm_frame_content_set(lyrFrame,lyrEntry);
   evas_object_show(lyrEntry);

// BUTTONS

   btn_play = elm_button_add(win);
   elm_object_text_set(btn_play,"Play");
   evas_object_size_hint_weight_set(btn_play, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn_play, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table, btn_play, 6, 0, 1, 1);

   evas_object_show(btn_play);

   btn_pause = elm_button_add(win);
   elm_object_text_set(btn_pause,"Pause");
   evas_object_size_hint_weight_set(btn_pause, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn_pause, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table, btn_pause, 7, 0, 1, 1);
   evas_object_show(btn_pause);

   btn_stop = elm_button_add(win);
   elm_object_text_set(btn_stop,"Stop");
   evas_object_size_hint_weight_set(btn_stop, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn_stop, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table, btn_stop, 8, 0, 1, 1);
   evas_object_show(btn_stop);

   btn_prev = elm_button_add(win);
   elm_object_text_set(btn_prev,"<<");
   evas_object_size_hint_weight_set(btn_prev, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn_prev, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table, btn_prev, 9, 0, 1, 1);
   evas_object_show(btn_prev);

   btn_next = elm_button_add(win);
   elm_object_text_set(btn_next,">>");
   evas_object_size_hint_weight_set(btn_next, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn_next, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table, btn_next, 10, 0, 1, 1);
   evas_object_show(btn_next);

// Time Label

   lb_time = elm_label_add(win);
   elm_object_text_set(lb_time, "0:00");
   //elm_label_text_align_set(lb_time,"right");
   evas_object_size_hint_weight_set(lb_time, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(lb_time, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table,lb_time, 6, 1, 1, 1);
   evas_object_show(lb_time);

// Time slider

   sld_time = elm_slider_add(win);
   elm_slider_min_max_set(sld_time,0,100);
   evas_object_size_hint_weight_set(sld_time, EVAS_HINT_EXPAND, 0);
   evas_object_size_hint_align_set(sld_time, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table, sld_time, 7, 1, 3, 1);
   evas_object_show(sld_time);

// Volume slider

   sld_volume = elm_slider_add(win);
   elm_object_text_set(sld_volume,"Volume");
   elm_slider_value_set(sld_volume,100);
   evas_object_size_hint_weight_set(sld_volume, EVAS_HINT_FILL, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(sld_volume, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table, sld_volume, 10, 1, 1, 1);
   evas_object_show(sld_volume);

// Playlist

   mlist = elm_list_add(win);
   elm_list_mode_set(mlist, ELM_LIST_LIMIT);
   evas_object_size_hint_weight_set(mlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(mlist, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(table, mlist, 6, 2, 6, 4);
   evas_object_show(mlist);

// Window CBs

   evas_object_smart_callback_add(win, "delete,request", ent_quit, NULL);

// Slider Change CBs

   evas_object_smart_callback_add(sld_volume,"changed",ent_change_volume,NULL);
   evas_object_smart_callback_add(sld_time,"changed",ent_change_time,NULL);
   evas_object_smart_callback_add(ent_player, "position_update", ent_update_time, sld_time);

// Cotrolls CBs

   evas_object_smart_callback_add(btn_play, "clicked", ent_play, NULL);
   evas_object_smart_callback_add(btn_pause, "clicked", ent_pause, NULL);
   evas_object_smart_callback_add(btn_stop, "clicked", ent_stop, NULL);
   ent_load_file_list(mlist,NULL,NULL);
   evas_object_smart_callback_add(btn_prev, "clicked", ent_prev_item_play, mlist);
   evas_object_smart_callback_add(btn_next, "clicked", ent_next_item_play, mlist);

// Cover Lyrics Flip CBs

   evas_object_smart_callback_add(cover, "clicked", ent_flip_panel, flip);
   evas_object_smart_callback_add(lyrEntry, "clicked", ent_flip_panel, flip);

// Display Window

   evas_object_show(win);
   elm_run();
   return 0;
}
ELM_MAIN()

