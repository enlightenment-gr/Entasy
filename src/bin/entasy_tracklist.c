#include "entasy_tracklist.h"

Evas_Object *
ent_create_directory(){
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
