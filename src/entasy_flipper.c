#include "entasy_flipper.h"
#include "entasy_cb.h"

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

