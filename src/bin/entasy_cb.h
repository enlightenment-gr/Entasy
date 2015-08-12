#ifndef _ENTASY_CB_H_
#define _ENTASY_CB_H_

#include "entasy.h"



// Basic application callbacks

void ent_directory_changed(void* data, Evas_Object *obj, void *event_info);

void ent_quit(void* data, Evas_Object *obj, void *event_info);

void ent_play(void* data, Evas_Object *obj, void *event_info);
void ent_pause(void* data, Evas_Object *obj, void *event_info);
void ent_stop(void* data, Evas_Object *obj, void *event_info);

void ent_list_item_play(void* data, Evas_Object *obj, void *event_info);
void ent_eina_list_item_play(void* data);
void ent_prev_item_play(void* data, Evas_Object *obj, void *event_info);
void ent_next_item_play(void* data, Evas_Object *obj, void *event_info);

void ent_change_volume(void* data, Evas_Object *obj, void *event_info);
void ent_flip_panel(void* data, Evas_Object *obj, void *event_info);
void ent_load_file_list(void* data, Evas_Object *obj, void *event_info);

void ent_change_time(void* data, Evas_Object *obj, void *event_info);
void ent_update_time(void* data, Evas_Object *obj, void *event_info);

void ent_open_prefs(void* data, Evas_Object* obj, void *event_info);


// Preferences Callbacks
void ent_preferences_save(void * data, Evas_Object *obj, void *event_info);


#endif

