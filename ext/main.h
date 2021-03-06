/*
 * $Id: main.h 350 2009-06-15 16:43:37Z chripppa $
 */

#ifndef __RB_DESPOTIFY_H
#define __RB_DESPOTIFY_H

extern VALUE cAlbum;
extern VALUE cAlbumBrowse;
extern VALUE cArtist;
extern VALUE cArtistBrowse;
extern VALUE cPlaylist;
extern VALUE cSearch;
extern VALUE cSession;
extern VALUE cTrack;

extern VALUE eDespotifyError;

typedef struct album ds_album_t;
typedef struct album_browse ds_album_browse_t;
typedef struct artist ds_artist_t;
typedef struct artist_browse ds_artist_browse_t;
typedef struct playlist ds_playlist_t;
typedef struct link ds_link_t;
typedef struct search_result ds_search_t;
typedef struct despotify_session ds_session_t;
typedef struct track ds_track_t;
typedef struct user_info ds_user_info_t;
typedef struct external_id ds_external_id_t;

#define BOOL2VALUE(exp) exp ? Qtrue : Qfalse
#define RB_DESPOTIFYERR(session) \
	rb_raise(eDespotifyError, (session)->real->last_error)

#define HASH_VALUE_ADD(hash, key, val) \
	rb_hash_aset(hash, rb_str_new2((key)), (val))

#endif
