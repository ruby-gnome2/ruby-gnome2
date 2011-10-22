/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2006  Kouhei Sutou
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include "rbgprivate.h"
#include "rbglib.h"
#include <glib/gwin32.h>

#ifdef G_OS_WIN32
static VALUE
rbglib_m_win32_error_message(VALUE self, VALUE error)
{
    return CSTR2RVAL_FREE(g_win32_error_message(NUM2INT(error)));
}

static VALUE
rbglib_m_win32_locale(VALUE self)
{
    return CSTR2RVAL_FREE(g_win32_getlocale());
}

static VALUE
rbglib_m_win32_locale_deprecated(VALUE self)
{
	rb_warn("GLib.win32_locale() is deprecated. Use GLib::Win32.locale instead");
	return rbglib_m_win32_locale(self);
}

static VALUE
rbglib_m_win32_get_package_installation_directory(VALUE self, VALUE package, VALUE dll_name)
{
	return CSTR2RVAL_FREE(g_win32_get_package_installation_directory(RVAL2CSTR(package), 
	                                                            RVAL2CSTR(dll_name)));
}

static VALUE
rbglib_m_get_package_installation_subdirectory(VALUE self, VALUE package, VALUE dll_name, VALUE subdir)
{
	return CSTR2RVAL_FREE(g_win32_get_package_installation_subdirectory(RVAL2CSTR(package), 
	                                                                RVAL2CSTR(dll_name),
	                                                                RVAL2CSTR(subdir)));
}

#if GLIB_CHECK_VERSION(2,6,0)
static VALUE
rbglib_m_get_windows_version(VALUE self)
{
	return UINT2NUM(g_win32_get_windows_version());
}
#endif

#if GLIB_CHECK_VERSION(2,8,0)
static VALUE
rbglib_m_win32_locale_filename_from_utf8(VALUE self, VALUE utf8_filename)
{
    return CSTR2RVAL_FREE(g_win32_locale_filename_from_utf8(RVAL2CSTR(utf8_filename)));
}

static VALUE
rbglib_m_win32_locale_filename_from_utf8_deprecated(VALUE self,
                                                    VALUE utf8_filename)
{
	rb_warn("GLib.win32_locale_filename_from_utf8() is deprecated. Use GLib::Win32.locale_filename_from_utf8 instead");
	return rbglib_m_win32_locale_filename_from_utf8(self, utf8_filename);
}

#endif

#  if GLIB_CHECK_VERSION(2, 16, 0)
static VALUE
rbglib_m_win32_get_package_installation_directory_of_module(int argc,
							    VALUE *argv,
							    VALUE self)
{
    VALUE rb_module;
    gchar *directory;
    gpointer hmodule;

    rb_scan_args(argc, argv, "01", &rb_module);
    if (NIL_P(rb_module))
	hmodule = NULL;
    else
	hmodule = GINT_TO_POINTER(NUM2INT(rb_module));

    directory = g_win32_get_package_installation_directory_of_module(hmodule);
    return CSTR2RVAL_FREE(directory);
}
#  endif
#endif

void
Init_glib_win32(void)
{
#ifdef G_OS_WIN32
    /* glib/gwin32.h */
    VALUE mWin32 = rb_define_module_under(mGLib, "Win32");

    rb_define_module_function(mWin32, "error_message", rbglib_m_win32_error_message, 1);
    rb_define_module_function(mWin32, "locale", rbglib_m_win32_locale, 0);
    rb_define_module_function(mWin32, "get_package_installation_directory", rbglib_m_win32_get_package_installation_directory, 2);
    rb_define_module_function(mWin32, "get_package_installation_subdirectory", rbglib_m_get_package_installation_subdirectory, 3);
    rb_define_module_function(mWin32, "version", rbglib_m_get_windows_version, 0);
    /* Deprecated */
    rb_define_module_function(mGLib, "win32_locale", rbglib_m_win32_locale_deprecated, 0);

#  if GLIB_CHECK_VERSION(2,8,0)
    rb_define_module_function(mWin32, "locale_filename_from_utf8",
                              rbglib_m_win32_locale_filename_from_utf8, 1);
    /* Deprecated */
    rb_define_module_function(mGLib, "win32_locale_filename_from_utf8",
                              rbglib_m_win32_locale_filename_from_utf8_deprecated, 1);
#  endif

#  if GLIB_CHECK_VERSION(2, 16, 0)
    rb_define_module_function(mWin32,
			      "get_package_installation_directory_of_module",
			      rbglib_m_win32_get_package_installation_directory_of_module,
			      -1);
#  endif
#endif
}
