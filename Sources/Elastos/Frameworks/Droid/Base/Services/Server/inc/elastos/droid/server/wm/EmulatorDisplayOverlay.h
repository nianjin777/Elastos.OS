//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ELASTOS_DROID_SERVER_WM_EMULATORDISPLAYOVERLAY_H__
#define __ELASTOS_DROID_SERVER_WM_EMULATORDISPLAYOVERLAY_H__

#include "_Elastos.Droid.Server.h"
#include <Elastos.Droid.Content.h>
#include "elastos/droid/ext/frameworkext.h"
#include <elastos/core/Object.h>

using Elastos::Droid::Content::IContext;
using Elastos::Droid::Graphics::IPoint;
using Elastos::Droid::Graphics::Drawable::IDrawable;
using Elastos::Droid::View::ISurfaceControl;
using Elastos::Droid::View::ISurface;
using Elastos::Droid::View::IDisplay;
using Elastos::Droid::View::ISurfaceSession;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Wm {

class EmulatorDisplayOverlay : public Object
{
public:
    EmulatorDisplayOverlay(
        /* [in] */ IContext* context,
        /* [in] */ IDisplay* display,
        /* [in] */ ISurfaceSession* session,
        /* [in] */ Int32 zOrder);

    // Note: caller responsible for being inside
    // Surface.openTransaction() / closeTransaction()
    CARAPI_(void) SetVisibility(
        /* [in] */ Boolean on);

    CARAPI_(void) PositionSurface(
        /* [in] */ Int32 dw,
        /* [in] */ Int32 dh,
        /* [in] */ Int32 rotation);

private:
    CARAPI_(void) DrawIfNeeded();

private:
    static const String TAG;

    // Display dimensions
    AutoPtr<IPoint> mScreenSize;

    AutoPtr<ISurfaceControl> mSurfaceControl;
    AutoPtr<ISurface> mSurface;
    Int32 mLastDW;
    Int32 mLastDH;
    Boolean mDrawNeeded;
    AutoPtr<IDrawable> mOverlay;
    Int32 mRotation;
    Boolean mVisible;
};

} // Wm
} // Server
} // Droid
} // Elastos

#endif //__ELASTOS_DROID_SERVER_WM_EMULATORDISPLAYOVERLAY_H__
