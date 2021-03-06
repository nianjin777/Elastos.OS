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

#include "Elastos.Droid.Internal.h"
#include "elastos/droid/internal/telephony/uicc/RuimFileHandler.h"
#include <elastos/utility/logging/Logger.h>

using Elastos::Utility::Logging::Logger;

namespace Elastos {
namespace Droid {
namespace Internal {
namespace Telephony {
namespace Uicc {

//=====================================================================
//                           RuimFileHandler
//=====================================================================
CAR_INTERFACE_IMPL(RuimFileHandler, IccFileHandler, IRuimFileHandler);

const String RuimFileHandler::LOGTAG("RuimFH");

RuimFileHandler::RuimFileHandler()
{
}

ECode RuimFileHandler::constructor(
    /* [in] */ IUiccCardApplication* app,
    /* [in] */ const String& aid,
    /* [in] */ ICommandsInterface* ci)
{
    IccFileHandler::constructor(app, aid, ci);
    return NOERROR;
}

ECode RuimFileHandler::LoadEFImgTransparent(
    /* [in] */ Int32 fileid,
    /* [in] */ Int32 highOffset,
    /* [in] */ Int32 lowOffset,
    /* [in] */ Int32 length,
    /* [in] */ IMessage* onLoaded)
{
    AutoPtr<IMessage> response;
    ObtainMessage(EVENT_READ_ICON_DONE, fileid, 0,
            onLoaded, (IMessage**)&response);

    /* Per TS 31.102, for displaying of Icon, under
     * DF Telecom and DF Graphics , EF instance(s) (4FXX,transparent files)
     * are present. The possible image file identifiers (EF instance) for
     * EF img ( 4F20, linear fixed file) are : 4F01 ... 4F05.
     * It should be MF_SIM + DF_TELECOM + DF_GRAPHICS, same path as EF IMG
     */
    mCi->IccIOForApp(COMMAND_GET_RESPONSE, fileid, GetEFPath(EF_IMG), 0, 0,
            GET_RESPONSE_EF_IMG_SIZE_BYTES, String(NULL), String(NULL),
            mAid, response);
    return NOERROR;
}

String RuimFileHandler::GetEFPath(
    /* [in] */ Int32 efid)
{
    switch(efid) {
    case EF_SMS:
    case EF_CST:
    case EF_RUIM_SPN:
    case EF_RUIM_ID:
    case EF_CSIM_LI:
    case EF_CSIM_MDN:
    case EF_CSIM_IMSIM:
    case EF_CSIM_CDMAHOME:
    case EF_CSIM_EPRL:
    case EF_CSIM_MODEL:
    case EF_MODEL:
    case EF_CSIM_PRL:
        return MF_SIM + DF_CDMA;
    case EF_CSIM_MSPL:
    case EF_CSIM_MLPL:
        return MF_SIM + DF_TELECOM + DF_MMSS;
    }
    return GetCommonIccEFPath(efid);
}

ECode RuimFileHandler::Logd(
    /* [in] */ const String& msg)
{
    Logger::D(LOGTAG, String("[RuimFileHandler] ") + msg);
    return NOERROR;
}

ECode RuimFileHandler::Loge(
    /* [in] */ const String& msg)
{
    Logger::E(LOGTAG, String("[RuimFileHandler] ") + msg);
    return NOERROR;
}

} // namespace Uicc
} // namespace Telephony
} // namespace Internal
} // namespace Droid
} // namespace Elastos
