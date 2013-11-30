#include "entasy_cb.h"

// Entasy Callbacks

// Window Quit Callback
void
ent_quit(void *data, Evas_Object *obj, void *event_info) {
   		elm_exit();
}

// Play button callback
void
ent_play(void *data, Evas_Object *obj, void *event_info) {
		emotion_object_play_set(entUI.emotion, EINA_TRUE);
}

// Pause button callback
void
ent_pause(void *data, Evas_Object *obj, void *event_info) {
		emotion_object_play_set(entUI.emotion, EINA_FALSE);
}

// Stop button callback
void
ent_stop(void *data, Evas_Object *obj, void *event_info) {
		emotion_object_play_set(entUI.emotion, EINA_FALSE);
		emotion_object_position_set(entUI.emotion, 0.0);
}

// Play specific item from the file list
void
ent_list_item_play(void *data, Evas_Object *obj, void *event_info) {
		char file[100];
		Evas_Object *li = data;
 
 		elm_list_clear (li);
 		Eina_List *files = NULL;	
 
 		sprintf(file,"/home/ragecryx/Music/%s",(char*)data);
 
 		emotion_object_file_set(entUI.emotion, file);
 		emotion_object_play_set(entUI.emotion, EINA_TRUE);
 		eina_list_free(files);
 
 		curSong = elm_list_selected_item_get(obj);
}

// 
void
ent_eina_list_item_play(void *data) {
 		//char *file = elm_list_item_data_get(data);
 		char file[100];
 
 		Evas_Object *li = data;
 		elm_list_clear (li);
 		Eina_List *files = NULL;
 
 		elm_list_item_selected_set(data, EINA_TRUE);
 		ent_list_item_play(file, NULL, NULL);
 		eina_list_free(files);
}

// Previous button callback
void
ent_prev_item_play(void *data, Evas_Object *obj, void *event_info) {
 		Evas_Object *tmp;
 		tmp = elm_list_item_prev(curSong);
 
 		elm_list_item_selected_set(curSong, EINA_FALSE);
 		ent_eina_list_item_play(tmp);	
}

// Next button callback
void
ent_next_item_play(void *data, Evas_Object *obj, void *event_info) {
 		Evas_Object *tmp;
 		tmp = elm_list_item_next(curSong);
 
 		elm_list_item_selected_set(curSong, EINA_FALSE);
 		ent_eina_list_item_play(tmp);
}

// Volume slide change callback
void
ent_change_volume(void *data, Evas_Object *obj, void *event_info) {
		double vol = (double)(100*elm_slider_value_get(obj))/100;
		emotion_object_audio_volume_set(entUI.emotion,vol);
}

// Flip panel click callback
void
ent_flip_panel(void *data, Evas_Object *obj, void *event_info)
{
 		Evas_Object *fl = data;

		// STUPID CODE TO FETCH SONG DATA
		// http://www.last.fm/api/show?service=290
		//~ ecore_con_url_init();
		//~ Evas_Object *cover = elm_flip_content_front_get(fl);
		//~ char* query;
		//~ sprintf(query,"http://ws.audioscrobbler.com/2.0/?method=album.getinfo&api_key=b25b959554ed76058ac220b7b2e0a026&artist=%s&album=%s",songrunning.artist,songrunning.album);
		//~ Ecore_Con_Url *url = ecore_con_url_new(query);
		//~ char* info = ecore_con_url_data_get(url);
		//~ char truelink[256];
		//~ sscanf(info,"%*s<image size=\"large\">%s</image>%*s",NULL,truelink,NULL);
		//~ char command[256];
		//~ sprintf(command,"wget -O /tmp/entscurcvr.png %s",truelink);
		//~ system(command);
		//~ ecore_con_url_shutdown();
		//~ elm_photo_file_set(cover, "/tmp/entscurcvr.png");

 		elm_flip_go(fl, ELM_FLIP_ROTATE_YZ_CENTER_AXIS);
}

//
void
ent_load_file_list(void *data, Evas_Object *obj, void *event_info) {
 		Evas_Object *plist = data;
 		Eina_List *list, *l;
 		char *zdata;
 
 		list = ecore_file_ls("/home/ragecryx/Music");
 		EINA_LIST_FOREACH(list, l, zdata)
 		{
	 		elm_list_item_append(plist,zdata,NULL,NULL,ent_list_item_play,zdata);
 		}
 
 		eina_list_free(list);
 		elm_list_go(plist);
}

// Time slider change callback
void
ent_change_time(void *data, Evas_Object *obj, void *event_info) {
		double len,tPerc;
		len = emotion_object_play_length_get(entUI.emotion); 
		tPerc = (double)floor((elm_slider_value_get(obj)));
		double cur = (len*tPerc)/100;
		emotion_object_position_set(entUI.emotion,cur);
}


void
ent_update_time(void *data, Evas_Object *obj, void *event_info) {
		Evas_Object *timeslide = data;
		double len,cur /* curGEN */ ;
		len = emotion_object_play_length_get(entUI.emotion);
		cur = emotion_object_position_get(entUI.emotion);
		int t = (int)floor((100*cur)/len);
		elm_slider_value_set(timeslide,t);
}