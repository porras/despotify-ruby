/*
 * $Id: main.c 350 2009-06-15 16:43:37Z chripppa $
 */

#include <ruby.h>
#include <despotify.h>

#include "main.h"
#include "album.h"
#include "album_browse.h"
#include "artist.h"
#include "artist_browse.h"
#include "playlist.h"
#include "search.h"
#include "session.h"
#include "track.h"

/* We can't define these in main.h because it leads to conflicting symbols
   when linking because everyone includes main.h. Move them here and slap
   extern on the references in main.h to cover this. - rjp */
VALUE cAlbum;
VALUE cAlbumBrowse;
VALUE cArtist;
VALUE cArtistBrowse;
VALUE cPlaylist;
VALUE cSearch;
VALUE cSession;
VALUE cTrack;

VALUE eDespotifyError;

static VALUE
rb_despotify_id2uri (VALUE self, VALUE idv)
{
	char *id;
	char buf[128];

	id = StringValuePtr(idv);

	despotify_id2uri(id, buf);

	return rb_str_new2(buf);
}

static VALUE
rb_despotify_uri2id (VALUE self, VALUE uriv)
{
	char *uri;
	char buf[128];

	uri = StringValuePtr(uriv);

	despotify_uri2id(uri, buf);

	return rb_str_new2(buf);
}

/* dunno when this changed but this works for old and new libdespotify
   - rjp */
#ifndef DESPOTIFY_TRACK_CHANGE
#define DESPOTIFY_TRACK_CHANGE DESPOTIFY_NEW_TRACK
#endif

void
Init_despotify (void)
{
	if (!despotify_init()) {
		printf("despotify_init() failed\n");
		return;
	}

	VALUE mDespotify = rb_define_module("Despotify");

	rb_define_singleton_method(mDespotify, "id2uri", rb_despotify_id2uri, 1);
	rb_define_singleton_method(mDespotify, "uri2id", rb_despotify_uri2id, 1);
	rb_define_const(mDespotify, "TRACK_CHANGE", INT2FIX(DESPOTIFY_TRACK_CHANGE));
	rb_define_const(mDespotify, "MAX_SEARCH_RESULTS", INT2FIX(MAX_SEARCH_RESULTS));

	cAlbum        = Init_Album(mDespotify);
	cAlbumBrowse  = Init_AlbumBrowse(mDespotify);
	cArtist       = Init_Artist(mDespotify);
	cArtistBrowse = Init_ArtistBrowse(mDespotify);
	cPlaylist     = Init_Playlist(mDespotify);
	cSearch       = Init_Search(mDespotify);
	cSession      = Init_Session(mDespotify);
	cTrack        = Init_Track(mDespotify);

	eDespotifyError = rb_define_class_under(mDespotify, "DespotifyError", rb_eException);
}
