#ifndef _ENTASY_H_
#define _ENTASY_H_

#include <Elementary.h>
#include <Emotion.h>
#include <Ecore_Con.h>
#include <math.h>

// Music Library Structs
typedef struct _Ent_Config{
  char* directory;
} Config;


// GUI Structs
typedef struct _Ent_EntasyUI{
        Evas_Object *window;
        Evas_Object *emotion;
        Evas_Object *background;
        Evas_Object *box;
        Evas_Object *controls;

        Evas_Object *preferences;

        Evas_Object *tracklist;
        Evas_Object *flipper;
        Evas_Object *controlButtons;
        Evas_Object *timeText;
        Evas_Object *timeSlider;
        Evas_Object *volumeSlider;
        Evas_Object *directory;

} EntasyUI;

// GLOBALUS MAXIMUS
EntasyUI entUI;
Config config;
Elm_Object_Item *curSong;

#endif
