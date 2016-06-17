
#include "elastos/droid/phone/CallGatewayManager.h"

namespace Elastos {
namespace Droid {
namespace Phone {

String CallGatewayManager::RawGatewayInfo::GetFormattedGatewayNumber()
{
    return CallGatewayManager::FormatProviderUri(gatewayUri);
}

Boolean CallGatewayManager::RawGatewayInfo::IsEmpty()
{
    return TextUtils::IsEmpty(packageName) || gatewayUri == NULL;
}

const String CallGatewayManager::EXTRA_GATEWAY_PROVIDER_PACKAGE("com.android.phone.extra.GATEWAY_PROVIDER_PACKAGE");

const String CallGatewayManager::EXTRA_GATEWAY_URI("com.android.phone.extra.GATEWAY_URI");

AutoPtr<RawGatewayInfo> CallGatewayManager::EMPTY_INFO = new RawGatewayInfo(NULL, NULL, NULL);

const String CallGatewayManager::LOG_TAG("CallGatewayManager");// = CallGatewayManager.class.getSimpleName();

AutoPtr<CallGatewayManager> CallGatewayManager::sSingleton;

AutoPtr<CallGatewayManager> CallGatewayManager::GetInstance()
{
    {
        AutoLock syncLock(this);
        if (sSingleton == NULL) {
            sSingleton = new CallGatewayManager();
        }
    }
    return sSingleton;
}

CallGatewayManager::CallGatewayManager()
{
    CConcurrentHashMap::New(4, 0.9f, 1, (IConcurrentHashMap**)&mMap);
}

AutoPtr<RawGatewayInfo> CallGatewayManager::GetRawGatewayInfo(
    /* [in] */ IIntent* intent,
    /* [in] */ const String& number)
{
    if (HasPhoneProviderExtras(intent)) {
        String extra;
        intent->GetStringExtra(EXTRA_GATEWAY_PROVIDER_PACKAGE, &extra);
        AutoPtr<IUri> uri = GetProviderGatewayUri(intent);
        AutoPtr<RawGatewayInfo> info = new RawGatewayInfo(extra, uri, number);
        return info;
    }
    return EMPTY_INFO;
}

ECode CallGatewayManager::SetGatewayInfoForConnection(
    /* [in] */ IConnection* connection,
    /* [in] */ RawGatewayInfo* gatewayInfo)
{
    if (!gatewayInfo->IsEmpty()) {
        mMap->Put(TO_IINTERFACE(connection), TO_IINTERFACE(gatewayInfo));
    }
    else {
        mMap->Remove(TO_IINTERFACE(connection));
    }
    return NOERROR;
}

ECode CallGatewayManager::ClearGatewayData(
    /* [in] */ IConnection* connection)
{
    SetGatewayInfoForConnection(connection, EMPTY_INFO);
}

CARAPI_(AutoPtr<RawGatewayInfo>) CallGatewayManager::GetGatewayInfo(
    /* [in] */ IConnection* connection)
{
    AutoPtr<IInterface> obj;
    mMap->Get(TO_IINTERFACE(connection), (IInterface**)&obj);
    AutoPtr<RawGatewayInfo> info = (RawGatewayInfo*)IObject::Probe(obj);
    if (info != NULL) {
        return info;
    }

    return EMPTY_INFO;
}

Boolean CallGatewayManager::HasPhoneProviderExtras(
    /* [in] */ IIntent* intent)
{
    if (NULL == intent) {
        return FALSE;
    }
    String name;
    intent->GetStringExtra(EXTRA_GATEWAY_PROVIDER_PACKAGE, &name);
    String gatewayUri;
    intent->GetStringExtra(EXTRA_GATEWAY_URI, &gatewayUri);

    return !TextUtils::IsEmpty(name) && !TextUtils::IsEmpty(gatewayUri);
}

ECode CallGatewayManager::CheckAndCopyPhoneProviderExtras(
    /* [in] */ IIntent* src,
    /* [in] */ IIntent* dst)
{
    if (!HasPhoneProviderExtras(src)) {
        Logger::D(LOG_TAG, "checkAndCopyPhoneProviderExtras: some or all extras are missing.");
        return NOERROR;
    }

    String extra;
    src->GetStringExtra(EXTRA_GATEWAY_PROVIDER_PACKAGE, &extra);
    dst->PutExtra(EXTRA_GATEWAY_PROVIDER_PACKAGE, extra);

    String extra2;
    src->GetStringExtra(EXTRA_GATEWAY_URI, &extra2);
    return dst->PutExtra(EXTRA_GATEWAY_URI, extra2);
}

AutoPtr<IUri> CallGatewayManager::GetProviderGatewayUri(
    /* [in] */ IIntent* intent)
{
    String uri;
    intent->GetStringExtra(EXTRA_GATEWAY_URI, &uri);

    if(TextUtils::IsEmpty(uri)){
        return NULL;
    }
    else {
        AutoPtr<IUri> _uri;
        AutoPtr<IUriHelper> helper;
        CUriHelper::AcquireSingleton((IUriHelper**)&helper);
        helper->Parse(uri, (IUri**)&_uri);
        return _uri;
    }
    return NULL;
}

String CallGatewayManager::FormatProviderUri(
    /* [in] */ IUri* uri)
{
    if (uri != NULL) {
        String schem;
        uri->GetScheme(&schem);
        if (PhoneAccount::SCHEME_TEL.Equals(schem)) {
            String schemeSpecific;
            uri->GetSchemeSpecificPart(&schemeSpecific);
            return PhoneNumberUtils::FormatNumber(schemeSpecific);
        }
        else {
            String str;
            uri->ToString(&str);
            return str;
        }
    }
    return String(NULL);
}

} // namespace Phone
} // namespace Droid
} // namespace Elastos