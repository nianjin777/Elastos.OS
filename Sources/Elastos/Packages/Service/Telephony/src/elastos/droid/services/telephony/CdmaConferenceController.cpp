
#include "elastos/droid/services/telephony/CdmaConferenceController.h"

namespace Elastos {
namespace Droid {
namespace Services {
namespace Telephony {

ECode CdmaConferenceController::MyConnectionListener::OnStateChanged(
    /* [in] */ IConnection* c,
    /* [in] */ Int32 state)
{
    mHost->RecalculateConference();
    return NOERROR;
}

ECode CdmaConferenceController::MyConnectionListener::OnDisconnected(
    /* [in] */ IConnection* c,
    /* [in] */ IDisconnectCause* disconnectCause)
{
    mHost->RecalculateConference();
    return NOERROR;
}

ECode CdmaConferenceController::MyConnectionListener::OnDestroyed(
    /* [in] */ IConnection* c)
{
    AutoPtr<CdmaConnection> c = (CdmaConnection*)IObject::Probe(c);
    mHost->Remove(TO_IINTERFACE(c));
    return NOERROR;
}

ECode MyRunnable::Run()
{
    mConnection->ForceAsDialing(FALSE);
    mHost->AddInternal(mConnection);

    Int32 size;
    mConnectionsToReset->GetSize(&size);
    for (Int32 i = 0; i < size; i++) {
        AutoPtr<IInterface> obj;
        mConnectionsToReset->Get(i, (IInterface**)&obj);
        AutoPtr<CdmaConnection> current = (CdmaConnection*)IObject::Probe(obj);

        current->ResetStateForConference();
    }
    return NOERROR;
}

const Int32 CdmaConferenceController::ADD_OUTGOING_CONNECTION_DELAY_MILLIS = 6000;

CdmaConferenceController::CdmaConferenceController(
    /* [in] */ ITelephonyConnectionService* connectionService)
    : mConnectionService(connectionService)
{
    mConnectionListener = new MyConnectionListener(this);

    CArrayList::New((IArrayList**)&mCdmaConnections);

    CArrayList::New((IArrayList**)&mPendingOutgoingConnections);

    CHandler::New((Handler**)&mHandler);
}

ECode CdmaConferenceController::Add(
    /* [in] */ CdmaConnection* connection)
{
    Boolean res1,res2;
    if ((mCdmaConnections->IsEmpty(&res1), !res1) &&
        (connection->IsOutgoing(&res2), res2)) {
        // There already exists a connection, so this will probably result in a conference once
        // it is added. For outgoing connections which are added while another connection
        // exists, we mark them as "dialing" for a set amount of time to give the user time to
        // see their new call as "Dialing" before it turns into a conference call.
        // During that time, we also mark the other calls as "held" or else it can cause issues
        // due to having an ACTIVE and a DIALING call simultaneously.
        connection->ForceAsDialing(TRUE);
        Int32 size;
        mCdmaConnections->GetSize(&size);
        AutoPtr<IList> connectionsToReset;
        CArrayList::New(size, (IArrayList**)&connectionsToReset);

        for (Int32 i = 0; i < size; i++) {
            AutoPtr<IInterface> obj;
            mCdmaConnections->Get(i, (IInterface**)&obj);
            AutoPtr<CdmaConnection> current = (CdmaConnection*)IObject::Probe(obj);

            Boolean res;
            if (current->SetHoldingForConference(&res), res) {
                connectionsToReset->Add(TO_IINTERFACE(current));
            }
        }

        AutoPtr<IRunnable> r = new MyRunnable(this, connection, connectionsToReset);
        mHandler->PostDelayed(r, ADD_OUTGOING_CONNECTION_DELAY_MILLIS);
    }
    else {
        // This is the first connection, or it is incoming, so let it flow through.
        AddInternal(connection);
    }
    return NOERROR;
}

void CdmaConferenceController::AddInternal(
    /* [in] */ CdmaConnection* connection)
{
    mCdmaConnections->Add(TO_IINTERFACE(connection));
    connection->AddConnectionListener(mConnectionListener);
    RecalculateConference();
}

void CdmaConferenceController::Remove(
    /* [in] */ CdmaConnection* connection)
{
    connection->removeConnectionListener(mConnectionListener);
    mCdmaConnections->remove(TO_IINTERFACE(connection));
    RecalculateConference();
}

void CdmaConferenceController::RecalculateConference()
{
    Int32 size;
    mCdmaConnections->GetSize(&size);
    AutoPtr<IList> conferenceConnections;
    CArrayList::New(size, (IArrayList**)&conferenceConnections);
    for (Int32 i = 0; i < size; i++) {
            AutoPtr<IInterface> obj;
            mCdmaConnections->Get(i, (IInterface**)&obj);
            AutoPtr<CdmaConnection> connection = (CdmaConnection*)IObject::Probe(obj);

             // We do not include call-waiting calls in conferences.
            Boolean res;
            State stete;
            if ((connection->IsCallWaiting(&res), !res) &&
                    (connection->GetState(&stete), stete) != IConnection::STATE_DISCONNECTED) {
                conferenceConnections->Add(TO_IINTERFACE(connection));
            }
    }

    Logger::D("CdmaConferenceController", "recalculating conference calls %d",
            (conferenceConnections->GetSize(&size), size));
    Boolean tmp;
    if ((conferenceConnections->GetSize(&size), size) >= 2) {
        Boolean isNewlyCreated = FALSE;

        // There are two or more CDMA connections. Do the following:
        // 1) Create a new conference connection if it doesn't exist.
        if (mConference == NULL) {
            Logger::I("CdmaConferenceController", "Creating new Cdma conference call");
            AutoPtr<IInterface> obj;
            Int32 _size;
            mCdmaConnections->Get((mCdmaConnections->GetSize(&_size), _size) - 1, (IInterface**)&obj);
            AutoPtr<CdmaConnection> newConnection = (CdmaConnection*)IObject::Probe(obj);

            Boolean res;
            if (newConnection->IsOutgoing(&res), res) {
                // Only an outgoing call can be merged with an ongoing call.
                mConference = new CdmaConference(NULL, IPhoneCapabilities::MERGE_CONFERENCE);
            }
            else {
                // If the most recently added connection was an incoming call, enable
                // swap instead of merge.
                mConference = new CdmaConference(NULL, IPhoneCapabilities::SWAP_CONFERENCE);
            }
            isNewlyCreated = TRUE;
        }

        // 2) Add any new connections to the conference
        mConference->GetSize(&size);
        AutoPtr<IList> existingChildConnections;
        CArrayList::New(size, (IList**)&existingChildConnections);

        conferenceConnections->GetSize(&size);
        for (Int32 = 0; i < size; i++) {
            AutoPtr<IInterface> obj;
            conferenceConnections->Get(i, (IInterface**)&obj);
            AutoPtr<CdmaConnection> connection = (CdmaConnection*)IObject::Probe(obj);

            Boolean res;
            if (existingChildConnections->Contains(TO_IINTERFACE(connection), &res), !res) {
                Logger::I("CdmaConferenceController", "Adding connection to conference call: %s", TO_CSTR(connection));
                mConference->AddConnection(TO_IINTERFACE(connection));
            }
            existingChildConnections->Remove(TO_IINTERFACE(connection));
        }

        // 3) Remove any lingering old/disconnected/destroyed connections
        existingChildConnections->GetSize(&size);
        for (Int32 = 0; i < size; i++) {
            AutoPtr<IInterface> obj;
            existingChildConnections->Get(i, (IInterface**)&obj);
            AutoPtr<IConnection> oldConnection = IConnection::Probe(obj);

            mConference->RemoveConnection(TO_IINTERFACE(oldConnection));
            Logger::I("CdmaConferenceController", "Removing connection from conference call: %s", TO_CSTR(oldConnection));
        }

        // 4) Add the conference to the connection service if it is new.
        if (isNewlyCreated) {
            Logger::D("CdmaConferenceController", "Adding the conference call");
            mConnectionService->AddConference(mConference);
        }
    }
    else if (conferenceConnections->IsEmpty(&tmp), tmp) {
        // There are no more connection so if we still have a conference, lets remove it.
        if (mConference != NULL) {
            Logger::I("CdmaConferenceController", "Destroying the CDMA conference connection.");
            mConference->Destroy();
        }
    }
}

} // namespace Telephony
} // namespace Services
} // namespace Droid
} // namespace Elastos