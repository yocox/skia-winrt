/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkTypeface_android_DEFINED
#define SkTypeface_android_DEFINED

#include "SkTypeface.h"

#ifdef SK_BUILD_FOR_ANDROID

class SkPaintOptionsAndroid;

/**
 *  Get the family name of the font in the fallback font list containing
 *  the specified character. if no font is found, returns false.
 */
SK_API bool SkGetFallbackFamilyNameForChar(SkUnichar uni, SkString* name);

/**
 *  For test only.
 *  Load font config from given xml files, instead of those from Android system.
 */
SK_API void SkUseTestFontConfigFile(const char* mainconf, const char* fallbackconf,
                                    const char* fontsdir);

/**
 *  Given a "current" fontID, return a ref to the next logical typeface
 *  when searching fonts for a given unicode value. Typically the caller
 *  will query a given font, and if a unicode value is not supported, they
 *  will call this, and if 0 is not returned, will search that font, and so
 *  on. This process must be finite, and when the fonthost sees a
 *  font with no logical successor, it must return NULL.
 *
 *  The original fontID is also provided. This is the initial font that was
 *  stored in the typeface of the caller. It is provided as an aid to choose
 *  the best next logical font. e.g. If the original font was bold or serif,
 *  but the 2nd in the logical chain was plain, then a subsequent call to
 *  get the 3rd can still inspect the original, and try to match its
 *  stylistic attributes.
 */
SkTypeface* SkAndroidNextLogicalTypeface(SkFontID currFontID, SkFontID origFontID,
                                         const SkPaintOptionsAndroid& options);

#endif // #ifdef SK_BUILD_FOR_ANDROID
#ifdef SK_BUILD_FOR_ANDROID_FRAMEWORK

#include "SkPaintOptionsAndroid.h"
#include "../harfbuzz/src/harfbuzz-shaper.h"
#include "../harfbuzz_ng/src/hb.h"

/**
 *  Return a new typeface for a fallback script. If the script is
 *  not valid, or can not map to a font, returns null.
 *  @param  script   The harfbuzz script id.
 *  @param  style    The font style, for example bold
 *  @param  elegant  true if we want the web friendly elegant version of the font
 *  @return          reference to the matching typeface. Caller must call
 *                   unref() when they are done.
 */
SK_API SkTypeface* SkCreateTypefaceForScriptNG(hb_script_t script, SkTypeface::Style style,
        SkPaintOptionsAndroid::FontVariant fontVariant = SkPaintOptionsAndroid::kDefault_Variant);

SK_API SkTypeface* SkCreateTypefaceForScript(HB_Script script, SkTypeface::Style style,
        SkPaintOptionsAndroid::FontVariant fontVariant = SkPaintOptionsAndroid::kDefault_Variant);

#endif // #ifdef SK_BUILD_FOR_ANDROID_FRAMEWORK
#endif // #ifndef SkTypeface_android_DEFINED
