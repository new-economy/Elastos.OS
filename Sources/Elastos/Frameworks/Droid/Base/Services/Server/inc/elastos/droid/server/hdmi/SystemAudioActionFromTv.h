/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.server.hdmi;

using Elastos::Droid::Hardware::Hdmi::IHdmiDeviceInfo;
using Elastos::Droid::Hardware::Hdmi::IIHdmiControlCallback;


/**
 * Feature action that handles System Audio initiated by TV devices.
 */
final class SystemAudioActionFromTv extends SystemAudioAction {

    /**
     * Constructor
     *
     * @param sourceAddress {@link HdmiCecLocalDevice} instance
     * @param avrAddress logical address of AVR device
     * @param targetStatus Whether to enable the system audio mode or not
     * @param callback callback interface to be notified when it's done
     * @throw IllegalArugmentException if device type of tvAddress is invalid
     */
    SystemAudioActionFromTv(HdmiCecLocalDevice sourceAddress, Int32 avrAddress,
            Boolean targetStatus, IHdmiControlCallback callback) {
        Super(sourceAddress, avrAddress, targetStatus, callback);
        HdmiUtils->VerifyAddressType(GetSourceAddress(), HdmiDeviceInfo.DEVICE_TV);
    }

    //@Override
    Boolean Start() {
        RemoveSystemAudioActionInProgress();
        SendSystemAudioModeRequest();
        return TRUE;
    }
}
