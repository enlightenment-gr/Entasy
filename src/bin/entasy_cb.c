#include "entasy_cb.h"
#include "entasy.h"



// Entasy Callbacks

char *
_parent_directory(char *folder)
{
    int i=0, pos=0, len = strlen(folder);
    char *parent_folder;

    for (i=len; i>=0; i--) {
        if (folder[i] == '/') {
            pos = i;
            break;
        }
    }
    parent_folder = (char *) malloc(sizeof(char) * len);

    if (parent_folder) {
        for (i=0; i<pos; i++)
            parent_folder[i] = folder[i];

        *(parent_folder+pos) = '\0';

        return parent_folder;
    }

    return NULL;
}



// Window Quit Callback
void
ent_quit(void *data, Evas_Object *obj, void *event_info)
{
    ent_stop(NULL, NULL, NULL);
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
    // char file[100];    
    // sprintf(file,"%s/%s", config.directory, (char*)data);
    char* item = (char*)data;
    int fullpathSize = strlen(entState.current_directory) + strlen(item) + 2;
    char* fullpathItem = malloc( sizeof(char) * ( fullpathSize ) );
    fullpathItem[fullpathSize] = '\0';
    sprintf(fullpathItem, "%s/%s\0", entState.current_directory, item);

    ent_stop(NULL, NULL, NULL);

    if (strcmp(item, "..") == 0) { // 0 means same
        //ent_stop(NULL, NULL, NULL);
        entState.current_directory = _parent_directory(entState.current_directory);
        ent_load_file_list(entUI.tracklist, NULL, NULL);
    }
    else if (ecore_file_is_dir(fullpathItem)) {
        //ent_stop(NULL, NULL, NULL);
        //free(config.directory);
        entState.current_directory = malloc( fullpathSize );
        sprintf(entState.current_directory, "%s", fullpathItem);
        ent_load_file_list(entUI.tracklist, NULL, NULL);
    } else {
        //printf("Playing file: %s\n", file);
        emotion_object_file_set(entUI.emotion, fullpathItem);
        curSong = elm_list_selected_item_get(obj);
        ent_play(NULL, NULL, NULL);
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
        sprintf(file,"%s/%s", entState.current_directory, elm_object_item_text_get(song));
        
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
        sprintf(file,"%s/%s", entState.current_directory, elm_object_item_text_get(song));
    
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
    char *filename, dir[1024];

    list = ecore_file_ls(entState.current_directory);
    if (list)
       elm_list_clear(plist);

    sep = elm_list_item_append(plist, "This is the separator, you're not \
                                       suppose to see this message in the \
                                       list", NULL, NULL, ent_list_item_play,
                                       "error");

    char foundCover = 0;
    EINA_LIST_FOREACH(list, l, filename)
    {
        // *FIXME* eina list can hold the fullpath+file data instead of just the name(?)
        sprintf(dir, "%s/%s", entState.current_directory, filename);
        if (ecore_file_is_dir(dir))
            elm_list_item_insert_before(plist, sep, filename, NULL, NULL, ent_list_item_play, filename);
        else {
            elm_list_item_append(plist, filename, NULL, NULL, ent_list_item_play, filename);
            
            // if the file is named folder.jpg or smth add as cover
            if ( !foundCover && (eina_str_has_extension(filename, ".jpg")  ||
                                 eina_str_has_extension(filename, ".jpeg") ||
                                 eina_str_has_extension(filename, ".png")  ||
                                 eina_str_has_extension(filename, ".bmp")   )
                ) {

                foundCover = 1;
                entState.hasCoverOn = 1;
                elm_photo_file_set(entUI.flipperCover, dir);
            }
        }
    }

    if (!foundCover && entState.hasCoverOn)
        elm_photo_file_set(entUI.flipperCover, "data/nullcover.jpg");

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



// Opens up the preferences dialog
void
ent_open_prefs(void* data, Evas_Object* obj, void *event_info)
{
    evas_object_show(entUI.preferences_window);
}




// Preferences Callbacks

void
ent_preferences_save(void * data, Evas_Object *obj, void *event_info)
{
    Evas_Object *prefs, *label;
    prefs = obj;
    label = (Evas_Object*) elm_prefs_item_object_get(prefs, "main:pref1_label");
    elm_object_text_set(label, "<b>Your changes have been saved.</b>");
    evas_object_hide(entUI.preferences_window);
}

