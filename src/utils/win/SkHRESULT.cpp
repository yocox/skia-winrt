/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkTypes.h"

#include "SKHRESULT.h"

void SkTraceHR(const char* file, unsigned long line,
               HRESULT hr, const char* msg) {
    SkDEBUGCODE(if (NULL != msg) SkDEBUGF(("%s\n", msg)));
    SkDEBUGF(("%s(%lu) : error 0x%x: ", file, line, hr));

    CHAR errorText[201];
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL,
                   hr,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   (LPSTR) &errorText,
                   200,
                   NULL
    );

    if (NULL == errorText) {
        SkDEBUGF(("<unknown>\n"));
    } else {
        SkDEBUGF(("%s", errorText));
    }
}
