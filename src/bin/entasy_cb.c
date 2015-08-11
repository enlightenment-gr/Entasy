#include "entasy_cb.h"
#include "entasy.h"



// Entasy Callbacks

char *
_prev_directory(char *folder)
{
    int i=0, pos=0, len = strlen(folder);
    char *prev_folder;

    for (i=len; i>=0; i--)
        if (folder[i] == '/') {
            pos = i;
            break;
        }
    prev_folder = (char *) malloc(sizeof(char) * len);

    for (i=0; i<pos; i++)
        prev_folder[i] = folder[i];
    *(prev_folder+pos) = '\0';

    return prev_folder;
}



// Folder change callback
void
ent_directory_changed(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
    char *txt;

    txt = elm_entry_markup_to_utf8(elm_object_text_get(obj));
    if (txt) {
        config.directory = malloc(strlen(txt) * sizeof(txt));
        sprintf(config.directory, "%s", txt);
        _prev_directory(config.directory);
        free(txt);
        //printf("The new config is: %s\n", config.directory);
    }

    if (ecore_file_is_dir(config.directory))
        ent_load_file_list(entUI.tracklist, NULL, NULL);
}



// Window Quit Callback
void
ent_quit(void *data, Evas_Object *obj, void *event_info)
{
    elm_exit();
}



// Play button callback
void
ent_play(void *data, Evas_Object *obj, void *event_info)
{
    Elm_Object_Item *song = NULL;
    if (curSong) {
        emotion_object_play_set(entUI.emotion, EINA_TRUE);
    }
    else {
        song = elm_list_selected_item_get(entUI.tracklist);
        if (song) {
            emotion_object_play_set(entUI.emotion, EINA_TRUE);
            curSong = song;
        }
    }
}



// Pause button callback
void
ent_pause(void *data, Evas_Object *obj, void *event_info)
{
    emotion_object_play_set(entUI.emotion, EINA_FALSE);
    elm_slider_value_set(entUI.timeSlider, 0.0);
    emotion_object_position_set(entUI.timeSlider, 0.0);
    curSong = NULL;
}



// Stop button callback
void
ent_stop(void *data, Evas_Object *obj, void *event_info)
{
    emotion_object_play_set(entUI.emotion, EINA_FALSE);
    elm_slider_value_set(entUI.timeSlider, 0.0);
    emotion_object_position_set(entUI.emotion, 0.0);
    curSong = NULL;
}



// Play specific item from the file list
void
ent_list_item_play(void *data, Evas_Object *obj, void *event_info)
{
    char file[100];
    //Evas_Object *li = data;

    //elm_list_clear (li);
    //Eina_List *files = NULL;
    if (!strcmp((char *)data, "..")) {
        //printf("Folder up should be opened\n");
        ent_stop(NULL, NULL, NULL);
        sprintf(config.directory,"%s", _prev_directory(config.directory));
        elm_object_text_set(entUI.directory, config.directory);
    }
    else {
        sprintf(file,"%s/%s", config.directory, (char*)data);
    }


    if(ecore_file_is_dir(file)) {
        //printf("Lets open this dir\n");
        ent_stop(NULL, NULL, NULL);
        elm_object_text_set(entUI.directory, file);
    }
    else {
        if (strcmp((char *)data, "..")) {
            printf("Playing file: %s\n", file);
            emotion_object_file_set(entUI.emotion, file);
            //emotion_object_play_set(entUI.emotion, EINA_TRUE);
            //eina_list_free(files);

            curSong = elm_list_selected_item_get(obj);
            ent_play(NULL, NULL, NULL);
        }
    }
}


// *FIXME: Add Description*
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



// Previous button callback
void
ent_prev_item_play(void *data, Evas_Object *obj, void *event_info)
{
    Elm_Object_Item *song = NULL;
    char file[256];

    if (curSong)
        song = elm_list_item_prev(curSong);

    if (song) {
        sprintf(file,"%s/%s", config.directory, elm_object_item_text_get(song));
        
        if (ecore_file_is_dir(file)) {
            ent_stop(NULL, NULL, NULL);
        }
        else {
            ent_stop(NULL, NULL, NULL);
            curSong = song;
            elm_list_item_selected_set(curSong, EINA_TRUE);
            ent_play(NULL, NULL, NULL);
        }
    }
}



// Next button callback
void
ent_next_item_play(void *data, Evas_Object *obj, void *event_info)
{
    Elm_Object_Item *song = NULL;
    char file[256];

    if (curSong)
        song = elm_list_item_next(curSong);

    if (song) {
        sprintf(file,"%s/%s", config.directory, elm_object_item_text_get(song));
    
        if (ecore_file_is_dir(file)) {
            ent_stop(NULL, NULL, NULL);
        }
        else {
            ent_stop(NULL, NULL, NULL);
            curSong = song;
            elm_list_item_selected_set(curSong, EINA_TRUE);
            ent_play(NULL, NULL, NULL);
        }
    }
}



// Volume slide change callback
void
ent_change_volume(void *data, Evas_Object *obj, void *event_info)
{
    double vol = (double)(100*elm_slider_value_get(obj))/100;
    emotion_object_audio_volume_set(entUI.emotion,vol);
}



// Flip panel click callback
void
ent_flip_panel(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *fl = data;
    //! * HERE BE DRA.. HERE BE SONG META-DATA FETCHING CODE!!1
    elm_flip_go(fl, ELM_FLIP_ROTATE_YZ_CENTER_AXIS);
}



// *FIXME: Add Description*
void
ent_load_file_list(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *plist = data;
    Eina_List *list, *l;
    Elm_Object_Item *sep;
    char *zdata, dir[1024];

    list = ecore_file_ls(config.directory);
    if (list)
       elm_list_clear(plist);

    sep = elm_list_item_append(plist, "This is the separator, you're not \
                                       suppose to see this message in the \
                                       list", NULL, NULL, ent_list_item_play,
                                       "error");
    EINA_LIST_FOREACH(list, l, zdata)
    {
        sprintf(dir, "%s/%s", config.directory, zdata);
        if (ecore_file_is_dir(dir))
            elm_list_item_insert_before(plist, sep, zdata, NULL, NULL, ent_list_item_play, zdata);
        else
            elm_list_item_append(plist, zdata, NULL, NULL, ent_list_item_play, zdata);
    }

    elm_object_item_del(sep);
    elm_list_item_prepend(plist, "..", NULL, NULL, ent_list_item_play, "..");

    eina_list_free(list);
    elm_list_go(plist);
}



// Time slider change callback
void
ent_change_time(void *data, Evas_Object *obj, void *event_info)
{
    if (curSong) {
        double len,tPerc;
        len = emotion_object_play_length_get(entUI.emotion);
        tPerc = (double)floor((elm_slider_value_get(obj)));
        double cur = (len*tPerc)/100;
        emotion_object_position_set(entUI.emotion,cur);
    }
    else {
        elm_slider_value_set(entUI.timeSlider, 0.0);
    }
}



// *FIXME: Add Description*
void
ent_update_time(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *timeslide = data;
    double len,cur /* curGEN */ ;
    len = emotion_object_play_length_get(entUI.emotion);
    cur = emotion_object_position_get(entUI.emotion);
    int t = (int)floor((100*cur)/len);
    elm_slider_value_set(timeslide,t);
}




// Preferences Callbacks

void
ent_preferences_save(void * data, Evas_Object *obj, void *event_info)
{
    Evas_Object *prefs, *label;
    prefs = obj;
    label = (Evas_Object*) elm_prefs_item_object_get(prefs, "main:label");
    elm_object_text_set(label, "<b>Your changes have been saved.</b>");
}

