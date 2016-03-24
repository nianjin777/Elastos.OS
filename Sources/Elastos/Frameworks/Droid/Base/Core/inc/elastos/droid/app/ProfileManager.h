#ifndef __ELASTOS_DROID_APP_PROFILE_MANAGER_H__
#define __ELASTOS_DROID_APP_PROFILE_MANAGER_H__

#include "elastos/droid/ext/frameworkext.h"
#include "elastos/core/Object.h"
#include "Elastos.Droid.App.h"
#include "Elastos.Droid.Content.h"

using Elastos::Droid::App::INotificationGroup;
using Elastos::Droid::App::IProfile;
using Elastos::Droid::App::IIProfileManager;
using Elastos::Droid::Content::IContext;
using Elastos::Droid::Os::IHandler;
using Elastos::Utility::IUUID;

namespace Elastos {
namespace Droid {
namespace App {

/**
 * @hide
 */
class ProfileManager
    : public Object
    , public IProfileManager
{
public:
    CAR_INTERFACE_DECL()

    ProfileManager()
        : mContext(NULL)
    {
    }

    virtual ~ProfileManager()
    {
    }

    /** @hide */
    static AutoPtr<IIProfileManager> GetService();

    CARAPI ToString(
        /* [out] */ String* str);

    CARAPI constructor(
        /* [in] */ IContext* context,
        /* [in] */ IHandler* handler);

    // @Deprecated
    CARAPI SetActiveProfile(
        /* [in] */ const String& profileName);

    CARAPI SetActiveProfile(
        /* [in] */ IUUID* profileUuid);

    CARAPI GetActiveProfile(
        /* [out] */ IProfile** profile);

    /** @hide */
    CARAPI AddProfile(
        /* [in] */ IProfile* profile);

    /** @hide */
    CARAPI RemoveProfile(
        /* [in] */ IProfile* profile);

    /** @hide */
    CARAPI UpdateProfile(
        /* [in] */ IProfile* profile);

    // @Deprecated
    CARAPI GetProfile(
        /* [in] */ const String& profileName,
        /* [out] */ IProfile** profile);

    CARAPI GetProfile(
        /* [in] */ IUUID* profileUuid,
        /* [out] */ IProfile** profile);

    CARAPI GetProfileNames(
        /* [out, callee] */ ArrayOf<String>** names);

    CARAPI GetProfiles(
        /* [out, callee] */ ArrayOf<IProfile*>** profiles);

    CARAPI ProfileExists(
        /* [in] */ const String& profileName,
        /* [out] */ Boolean* isExisted);

    CARAPI ProfileExists(
        /* [in] */ IUUID* profileUuid,
        /* [out] */ Boolean* isExisted);

    CARAPI NotificationGroupExists(
        /* [in] */ const String& notificationGroupName,
        /* [out] */ Boolean* isExisted);

    /** @hide */
    CARAPI GetNotificationGroups(
        /* [out, callee] */ ArrayOf<INotificationGroup*>** groups);

    /** @hide */
    CARAPI AddNotificationGroup(
        /* [in] */ INotificationGroup* group);

    /** @hide */
    CARAPI RemoveNotificationGroup(
        /* [in] */ INotificationGroup* group);

    /** @hide */
    CARAPI UpdateNotificationGroup(
        /* [in] */ INotificationGroup* group);

    /** @hide */
    CARAPI GetNotificationGroupForPackage(
        /* [in] */ const String& pkg,
        /* [out] */ INotificationGroup** group);

    /** @hide */
    CARAPI GetNotificationGroup(
        /* [in] */ IUUID* groupParcelUuid,
        /* [out] */ INotificationGroup** group);

    /** @hide */
    CARAPI GetActiveProfileGroup(
        /* [in] */ const String& packageName,
        /* [out] */ IProfileGroup** group);

    /** @hide */
    CARAPI ResetAll();

public:
    /**
     * @hide
     */
    static AutoPtr<IUUID> NO_PROFILE; // = UUID.fromString("00000000-0000-0000-0000-000000000000");

private:
    static AutoPtr<IIProfileManager> sService;

    static const String TAG; // = "ProfileManager";

    static const String SYSTEM_PROFILES_ENABLED; // = "system_profiles_enabled";

    // A blank profile that is created to be returned if profiles disabled
    static AutoPtr<IProfile> sEmptyProfile;

    AutoPtr<IContext> mContext;

};

} // namespace App
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_APP_PROFILE_MANAGER_H__
