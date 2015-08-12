#ifndef _ENTASY_H_
#define _ENTASY_H_

#include <Elementary.h>
#include <Emotion.h>
#include <Ecore_Con.h>
#include <math.h>


typedef struct _Ent_PlayerState {
  char* base_directory;
  char* current_directory;

  char hasCoverOn; // if a cover is loaded its != 0
} PlayerState;


// GUI Structs
typedef struct _Ent_EntasyUI{
        Evas_Object *window;
        Evas_Object *emotion;
        Evas_Object *background;
        Evas_Object *box;
        Evas_Object *controls;

        Evas_Object *preferences_window;
        Evas_Object *preferences;

        Evas_Object *tracklist;
        Evas_Object *controlButtons;
        Evas_Object *timeText;
        Evas_Object *timeSlider;
        Evas_Object *volumeSlider;
        Evas_Object *directory;

        Evas_Object *flipper;
        Evas_Object *flipperCover;
        Evas_Object *flipperLyrics;
} EntasyUI;

// GLOBALUS MAXIMUS
EntasyUI entUI;
PlayerState entState;
Elm_Object_Item *curSong;
//Config config;

#endif
