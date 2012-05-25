#ifndef _ENTASY_H_
#define _ENTASY_H_

#include <Emotion.h>
#include <Elementary.h>
#include <Ecore_Con.h>
#include <math.h>

// Structs

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

// Global variables

Evas_Object *ent_player;
Elm_List_Item *curSong;

#endif
