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

#ifndef __ELASTOS_DROID_SERVER_WIFI_WIFIAPCONFIGSTORE_H__
#define __ELASTOS_DROID_SERVER_WIFI_WIFIAPCONFIGSTORE_H__

#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/internal/utility/AsyncChannel.h"
#include "elastos/droid/internal/utility/State.h"
#include "elastos/droid/internal/utility/StateMachine.h"
#include <elastos/core/Runnable.h>

using Elastos::Droid::Content::IContext;
using Elastos::Droid::Os::IHandler;
using Elastos::Droid::Os::IMessenger;
using Elastos::Core::Runnable;
using Elastos::Droid::Internal::Utility::AsyncChannel;
using Elastos::Droid::Internal::Utility::State;
using Elastos::Droid::Internal::Utility::StateMachine;
using Elastos::Droid::Wifi::IWifiConfiguration;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Wifi {

/**
 * Provides API to the WifiStateMachine for doing read/write access
 * to soft access point configuration
 */
class WifiApConfigStore : public StateMachine
{
public:
    WifiApConfigStore(
        /* [in] */ IContext* context,
        /* [in] */ IHandler* target);

    static CARAPI_(AutoPtr<WifiApConfigStore>) MakeWifiApConfigStore(
        /* [in] */ IContext* context,
        /* [in] */ IHandler* target);

    CARAPI_(void) LoadApConfiguration();

    CARAPI GetMessenger(
        /* [out] */ IMessenger** msg);

private:
    class DefaultState : public State
    {
    public:
        DefaultState(
            /* [in] */ WifiApConfigStore* owner) : mOwner(owner)
        {}

        // @Override
        CARAPI ProcessMessage(
            /* [in] */ IMessage* msg,
            /* [out] */ Boolean* result);

        CARAPI_(String) GetName()
        {
            return String("DefaultState");
        }

    private:
        WifiApConfigStore* mOwner;
    };

    class InactiveState : public State
    {
    public:
        InactiveState(
            /* [in] */ WifiApConfigStore* owner) : mOwner(owner)
        {}

        // @Override
        CARAPI ProcessMessage(
            /* [in] */ IMessage* msg,
            /* [out] */ Boolean* result);

        CARAPI_(String) GetName()
        {
            return String("InactiveState");
        }

    private:
        WifiApConfigStore* mOwner;
    };

    class ActiveStateRunnable : public Runnable
    {
    public:
        ActiveStateRunnable(
            /* [in] */ WifiApConfigStore* owner) : mOwner(owner)
        {}

        CARAPI Run();

    private:
        WifiApConfigStore* mOwner;
    };

    class ActiveState : public State
    {
    public:
        ActiveState(
            /* [in] */ WifiApConfigStore* owner) : mOwner(owner)
        {}

        CARAPI Enter();

        // @Override
        CARAPI ProcessMessage(
            /* [in] */ IMessage* msg,
            /* [out] */ Boolean* result);

        CARAPI_(String) GetName()
        {
            return String("ActiveState");
        }

    private:
        WifiApConfigStore* mOwner;
    };

private:
    CARAPI_(void) WriteApConfiguration(
        /* [in] */ IWifiConfiguration* config);

    /* Generate a default WPA2 based configuration with a random password.
       We are changing the Wifi Ap configuration storage from secure settings to a
       flat file accessible only by the system. A WPA2 based default configuration
       will keep the device secure after the update */
    CARAPI_(void) SetDefaultApConfiguration();

private:
    AutoPtr<IContext> mContext;
    static String TAG;
    static String AP_CONFIG_FILE;
    static const Int32 AP_CONFIG_FILE_VERSION;

    AutoPtr<State> mDefaultState;
    AutoPtr<State> mInactiveState;
    AutoPtr<State> mActiveState;

    AutoPtr<IWifiConfiguration> mWifiApConfig;
    AutoPtr<AsyncChannel> mReplyChannel;
};

} // namespace Wifi
} // namespace Server
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SERVER_WIFI_WIFIAPCONFIGSTORE_H__
