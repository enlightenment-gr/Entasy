#include "entasy_tracklist.h"

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
