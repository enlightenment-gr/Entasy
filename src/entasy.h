#ifndef _ENTASY_H_
#define _ENTASY_H_

#include <Elementary.h>
#include <Emotion.h>
#include <Ecore_Con.h>
#include <math.h>

// Music Library Structs
typedef struct _Ent_Config{
  const char* directory;
  const char* song_db_file;
  const char* song_db_num;
} Config;

typedef struct _Ent_Song{
  const char* title;
  const char* album;
  const char* artist;
} Song;

// GUI Structs
typedef struct _Ent_EntasyUI{
        Evas_Object *window;
        Evas_Object *emotion;
        Evas_Object *background;
        Evas_Object *box;
        Evas_Object *controls;

        Evas_Object *tracklist;
        Evas_Object *flipper;
        Evas_Object *controlButtons;
        Evas_Object *timeText;
        Evas_Object *timeSlider;
        Evas_Object *volumeSlider;

} EntasyUI;

// GLOBALUS MAXIMUS
EntasyUI entUI;
Elm_Object_Item *curSong;

#endif
