#ifndef __ELASTOS_DROID_GOOGLE_MMS_PDU_GENERICPDU_H__
#define __ELASTOS_DROID_GOOGLE_MMS_PDU_GENERICPDU_H__

#include "elastos/droid/google/mms/pdu/EncodedStringValue.h"
#include "elastos/droid/ext/frameworkext.h"
#include "elastos/core/Object.h"

// package com.google.android.mms.pdu;
// import com.google.android.mms.InvalidHeaderValueException;

namespace Elastos {
namespace Droid {
namespace Google {
namespace Mms {
namespace Pdu {

class GenericPdu
    : public Object
    , public IGenericPdu
{
public:
    CAR_INTERFACE_DECL();

    /**
      * Constructor.
      */
    GenericPdu();

    /**
      * Constructor.
      *
      * @param headers Headers for this PDU.
      */
    GenericPdu(
        /* [in] */ IPduHeaders* headers);

    /**
      * Get the headers of this PDU.
      *
      * @return A PduHeaders of this PDU.
      */
    virtual CARAPI GetPduHeaders(
        /* [out] */ IPduHeaders** result);

    /**
      * Get X-Mms-Message-Type field value.
      *
      * @return the X-Mms-Report-Allowed value
      */
    virtual CARAPI GetMessageType(
        /* [out] */ Int32* result);

    /**
      * Set X-Mms-Message-Type field value.
      *
      * @param value the value
      * @throws InvalidHeaderValueException if the value is invalid.
      *         RuntimeException if field's value is not Octet.
      */
    virtual CARAPI SetMessageType(
        /* [in] */ Int32 value);

    /**
      * Get X-Mms-MMS-Version field value.
      *
      * @return the X-Mms-MMS-Version value
      */
    virtual CARAPI GetMmsVersion(
        /* [out] */ Int32* result);

    /**
      * Set X-Mms-MMS-Version field value.
      *
      * @param value the value
      * @throws InvalidHeaderValueException if the value is invalid.
      *         RuntimeException if field's value is not Octet.
      */
    virtual CARAPI SetMmsVersion(
        /* [in] */ Int32 value);

    /**
      * Get From value.
      * From-value = Value-length
      *      (Address-present-token Encoded-string-value | Insert-address-token)
      *
      * @return the value
      */
    virtual CARAPI GetFrom(
        /* [out] */ EncodedStringValue** result);

    /**
      * Set From value.
      *
      * @param value the value
      * @throws NullPointerException if the value is null.
      */
    virtual CARAPI SetFrom(
        /* [in] */ EncodedStringValue* value);

public:
    /**
      * The headers of pdu.
      */
    AutoPtr<IPduHeaders> mPduHeaders;
};

} // namespace Pdu
} // namespace Mms
} // namespace Google
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_GOOGLE_MMS_PDU_GENERICPDU_H__

