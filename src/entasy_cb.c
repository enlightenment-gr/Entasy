#include "entasy_cb.h"

// CALLBACKS //

void
ent_quit(void *data, Evas_Object *obj, void *event_info)
{
   elm_exit();
}

void
ent_play(void *data, Evas_Object *obj, void *event_info)
{
	emotion_object_play_set(ent_player,EINA_TRUE);
}

void
ent_pause(void *data, Evas_Object *obj, void *event_info)
{
	emotion_object_play_set(ent_player,EINA_FALSE);
}

void
ent_stop(void *data, Evas_Object *obj, void *event_info)
{
	emotion_object_play_set(ent_player,EINA_FALSE);
	emotion_object_position_set(ent_player,0.0);
}

void
ent_list_item_play(void *data, Evas_Object *obj, void *event_info)
{
 //~ songrunning.title = emotion_object_meta_info_get(ent_player, EMOTION_META_INFO_TRACK_TITLE);
 //~ songrunning.album = emotion_object_meta_info_get(ent_player, EMOTION_META_INFO_TRACK_ALBUM);
 //~ songrunning.artist = emotion_object_meta_info_get(ent_player, EMOTION_META_INFO_TRACK_ARTIST);
 char file[100];
 Evas_Object *li = data;
 elm_list_clear (li);
 Eina_List *files = NULL;	
 sprintf(file,"/home/ragecryx/Music/%s",(char*)data);
 emotion_object_file_set(ent_player, file);
 emotion_object_play_set(ent_player, EINA_TRUE);
 eina_list_free(files);
 curSong = elm_list_selected_item_get(obj);
}

void
ent_eina_list_item_play(void *data)
{
 //char *file = elm_list_item_data_get(data);
 char file[100];
 Evas_Object *li = data;
 elm_list_clear (li);
 Eina_List *files = NULL;
 elm_list_item_selected_set(data, EINA_TRUE);
 ent_list_item_play(file, NULL, NULL);
 eina_list_free(files);
}

void
ent_prev_item_play(void *data, Evas_Object *obj, void *event_info)
{
 Evas_Object *tmp;
 tmp = elm_list_item_prev(curSong);
 elm_list_item_selected_set(curSong, EINA_FALSE);
 ent_eina_list_item_play(tmp);	
}

void
ent_next_item_play(void *data, Evas_Object *obj, void *event_info)
{
 Evas_Object *tmp;
 //elm_list_item *tmp;
 tmp = elm_list_item_next(curSong);
 elm_list_item_selected_set(curSong, EINA_FALSE);
 ent_eina_list_item_play(tmp);
}

void
ent_change_volume(void *data, Evas_Object *obj, void *event_info) 
{
	double vol = (double)(100*elm_slider_value_get(obj))/100;
	emotion_object_audio_volume_set(ent_player,vol);
}

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

void
ent_load_file_list(void *data, Evas_Object *obj, void *event_info)
{
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

void
ent_change_time(void *data, Evas_Object *obj, void *event_info)
{
	double len,tPerc;
	len = emotion_object_play_length_get(ent_player); 
	tPerc = (double)floor((elm_slider_value_get(obj)));
	double cur = (len*tPerc)/100;
	emotion_object_position_set(ent_player,cur);
}


void
ent_update_time(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *timeslide = data;
	double len,cur /* curGEN */ ;
	len = emotion_object_play_length_get(ent_player);
	cur = emotion_object_position_get(ent_player);
	int t = (int)floor((100*cur)/len);
	elm_slider_value_set(timeslide,t);

//~ Evas_Object *win;
//~ win = evas_object_smart_parent_get(timeslide);
//~ curGEN = emotion_object_position_get(ent_player);
//~ curMIN = curGEN / 60;
//~ curSEC = curGEN % 60;
//~ char *label[8];
//~ sprintf(label,"%d:%d",curMIN,curSEC);
//~ elm_object_text_set(lb_time, label);

}

// END OF CALLBACKS

