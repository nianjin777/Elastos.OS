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

#include "elastos/droid/internal/utility/CDumpUtils.h"
#include "elastos/droid/internal/utility/DumpUtils.h"

namespace Elastos {
namespace Droid {
namespace Internal {
namespace Utility {

CAR_INTERFACE_IMPL(CDumpUtils, Singleton, IDumpUtils)

CAR_SINGLETON_IMPL(CDumpUtils)

ECode CDumpUtils::DumpAsync(
    /* [in] */ IHandler* handler,
    /* [in] */ IDump* dump,
    /* [in] */ IPrintWriter* pw,
    /* [in] */ Int64 timeout)
{
    return DumpUtils::DumpAsync(handler, dump, pw, timeout);
}

} // namespace Utility
} // namespace Internal
} // namespace Droid
} // namespace Elastos
