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

#ifndef __ORG_APACHE_HTTP_IMPL_DEFAULTHTTPSERVERCONNECTION_H__
#define __ORG_APACHE_HTTP_IMPL_DEFAULTHTTPSERVERCONNECTION_H__

#include "org/apache/http/impl/SocketHttpServerConnection.h"

namespace Org {
namespace Apache {
namespace Http {
namespace Impl {

/**
 * Default implementation of a server-side HTTP connection.
 *
 * @author <a href="mailto:oleg at ural.ru">Oleg Kalnichevski</a>
 *
 * @version $Revision: 561083 $
 *
 * @since 4.0
 */
class DefaultHttpServerConnection : public SocketHttpServerConnection
{
public:
    DefaultHttpServerConnection();

    CARAPI Bind(
        /* [in] */ ISocket* socket,
        /* [in] */ IHttpParams* params);

    CARAPI ToString(
        /* [out] */ String* str);
};

} // namespace Impl
} // namespace Http
} // namespace Apache
} // namespace Org

#endif // __ORG_APACHE_HTTP_IMPL_DEFAULTHTTPSERVERCONNECTION_H__
