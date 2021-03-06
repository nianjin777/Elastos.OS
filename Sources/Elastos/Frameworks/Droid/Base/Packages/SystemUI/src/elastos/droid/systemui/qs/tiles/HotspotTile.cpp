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

#include "elastos/droid/systemui/qs/tiles/HotspotTile.h"
#include "../R.h"

using Elastos::Droid::SystemUI::StatusBar::Policy::EIID_IHotspotControllerCallback;

namespace Elastos {
namespace Droid {
namespace SystemUI {
namespace Qs {
namespace Tiles {

CAR_INTERFACE_IMPL(HotspotTile::Callback, Object, IHotspotControllerCallback)
HotspotTile::Callback::Callback(
    /* [in] */ HotspotTile* host)
    : mHost(host)
{}

ECode HotspotTile::Callback::OnHotspotChanged(
    /* [in] */ Boolean enabled)
{
    mHost->RefreshState();
    return NOERROR;
}

HotspotTile::HotspotTile(
    /* [in] */ IQSTileHost* host)
{
    QSTile::constructor(host);
    mCallback = new Callback(this);
    host->GetHotspotController((IHotspotController**)&mController);
    AutoPtr<IContext> ctx;
    host->GetContext((IContext**)&ctx);
    mUsageTracker = new UsageTracker(ctx, this/*HotspotTile.class*/);
    mUsageTracker->SetListening(TRUE);
}

void HotspotTile::HandleDestroy()
{
    QSTile::HandleDestroy();
    mUsageTracker->SetListening(FALSE);
}

AutoPtr<QSTile::State> HotspotTile::NewTileState()
{
    return new BooleanState();
}

ECode HotspotTile::SetListening(
    /* [in] */ Boolean listening)
{
    if (listening) {
        mController->AddCallback(mCallback);
    }
    else {
        mController->RemoveCallback(mCallback);
    }
    return NOERROR;
}

void HotspotTile::HandleClick()
{
    const Boolean isEnabled = ((BooleanState*)mState.Get())->mValue;
    mController->SetHotspotEnabled(!isEnabled);
}

void HotspotTile::HandleUpdateState(
    /* [in] */ State* state,
    /* [in] */ IInterface* arg)
{
    Boolean tmp = FALSE;
    state->mVisible = (mController->IsHotspotSupported(&tmp), tmp) && mUsageTracker->IsRecentlyUsed()
            && (mController->IsProvisioningNeeded(&tmp), !tmp);
    mContext->GetString(R::string::quick_settings_hotspot_label, &state->mLabel);

    mController->IsHotspotEnabled(&((BooleanState*)state)->mValue);
    state->mIconId = state->mVisible && ((BooleanState*)state)->mValue ? R::drawable::ic_qs_hotspot_on
            : R::drawable::ic_qs_hotspot_off;
}

String HotspotTile::ComposeChangeAnnouncement()
{
    String v;
    if (((BooleanState*)mState.Get())->mValue) {
        mContext->GetString(R::string::accessibility_quick_settings_hotspot_changed_on, &v);
    }
    else {
        mContext->GetString(R::string::accessibility_quick_settings_hotspot_changed_off, &v);
    }
    return v;
}

String HotspotTile::GetSimpleName()
{
    return String("HotspotTile");
}

} // namespace Tiles
} // namespace Qs
} // namespace SystemUI
} // namespace Droid
} // namespace Elastos
