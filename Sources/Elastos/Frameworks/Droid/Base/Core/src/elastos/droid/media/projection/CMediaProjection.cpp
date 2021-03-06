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

#include "Elastos.Droid.Content.h"
#include "Elastos.Droid.Os.h"
#include "elastos/droid/media/projection/CMediaProjection.h"
#include "elastos/droid/media/projection/CMediaProjectionCallback.h"
#include "elastos/droid/utility/CArrayMap.h"
#include "elastos/droid/os/ServiceManager.h"

using Elastos::Droid::Hardware::Display::IDisplayManager;
using Elastos::Utility::IMap;
using Elastos::Droid::Os::ServiceManager;
using Elastos::Droid::Utility::CArrayMap;

namespace Elastos {
namespace Droid {
namespace Media {
namespace Projection {

CAR_INTERFACE_IMPL(CMediaProjection::MediaProjectionCallback, Object, IIMediaProjectionCallback)

ECode CMediaProjection::CallbackRecordRunnable::Run()
{
    return mCallback->OnStop();
}

ECode CMediaProjection::MediaProjectionCallback::OnStop()
{
    Int32 N;
    IMap::Probe(mHost->mCallbacks)->GetSize(&N);
    for (Int32 i = 0; i < N; i++) {
        AutoPtr<IInterface> obj;
        mHost->mCallbacks->GetValueAt(i, (IInterface**)&obj);
        AutoPtr<CallbackRecord> cr = (CallbackRecord*)IObject::Probe(obj);
        cr->OnStop();
    }
    return NOERROR;
}

ECode CMediaProjection::CallbackRecord::OnStop()
{
    AutoPtr<CallbackRecordRunnable> runnable = new CallbackRecordRunnable(mHost, mCallback);
    Boolean b;
    return mHandler->Post(runnable, &b);
}

String CMediaProjection::TAG("MediaProjection");

CAR_INTERFACE_IMPL(CMediaProjection, Object, IMediaProjection)

CAR_OBJECT_IMPL(CMediaProjection)

CMediaProjection::CMediaProjection()
{
}

CMediaProjection::~CMediaProjection()
{
}

ECode CMediaProjection::constructor(
    /* [in] */ IContext * context,
    /* [in] */ IIMediaProjection * impl)
{
    CArrayMap::New((IArrayMap**)&mCallbacks);
    mContext = context;
    mImpl = impl;
    // try {
    AutoPtr<MediaProjectionCallback> cb = new MediaProjectionCallback(this);
    mImpl->Start(IIMediaProjectionCallback::Probe(cb));
    // } catch (RemoteException e) {
    //     throw new RuntimeException("Failed to start media projection", e);
    // }
    return NOERROR;
}

ECode CMediaProjection::RegisterCallback(
    /* [in] */ IMediaProjectionCallback * cb,
    /* [in] */ IHandler * handler)
{
    if (cb == NULL) {
        // throw new IllegalArgumentException("callback should not be null");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }

    AutoPtr<CallbackRecord> cr = new CallbackRecord(this, cb, handler);
    return IMap::Probe(mCallbacks)->Put(cb, (IInterface*)(IObject*)cr);
}

ECode CMediaProjection::UnregisterCallback(
    /* [in] */ IMediaProjectionCallback * cb)
{
    if (cb == NULL) {
        // throw new IllegalArgumentException("callback should not be null");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }

    return IMap::Probe(mCallbacks)->Remove(cb);
}

ECode CMediaProjection::CreateVirtualDisplay(
    /* [in] */ const String& name,
    /* [in] */ Int32 width,
    /* [in] */ Int32 height,
    /* [in] */ Int32 dpi,
    /* [in] */ Boolean isSecure,
    /* [in] */ ISurface * surface,
    /* [in] */ IVirtualDisplayCallback * cb,
    /* [in] */ IHandler * handler,
    /* [out] */ IVirtualDisplay ** result)
{
    AutoPtr<IInterface> service;
    mContext->GetSystemService(IContext::DISPLAY_SERVICE, ((IInterface**)&service));
    AutoPtr<IDisplayManager> dm = IDisplayManager::Probe(service);

    Int32 flags = isSecure ? IDisplayManager::VIRTUAL_DISPLAY_FLAG_SECURE : 0;
    return dm->CreateVirtualDisplay(this, name, width, height, dpi, surface,
                flags | IDisplayManager::VIRTUAL_DISPLAY_FLAG_AUTO_MIRROR |
                IDisplayManager::VIRTUAL_DISPLAY_FLAG_PRESENTATION, cb, handler, result);
}

ECode CMediaProjection::CreateVirtualDisplay(
    /* [in] */ const String& name,
    /* [in] */ Int32 width,
    /* [in] */ Int32 height,
    /* [in] */ Int32 dpi,
    /* [in] */ Int32 flags,
    /* [in] */ ISurface * surface,
    /* [in] */ IVirtualDisplayCallback * cb,
    /* [in] */ IHandler * handler,
    /* [out] */ IVirtualDisplay ** result)
{
    AutoPtr<IInterface> service;
    mContext->GetSystemService(IContext::DISPLAY_SERVICE, ((IInterface**)&service));
    AutoPtr<IDisplayManager> dm = IDisplayManager::Probe(service);

    return dm->CreateVirtualDisplay(
                this, name, width, height, dpi, surface, flags, cb, handler, result);
}

ECode CMediaProjection::CreateAudioRecord(
    /* [in] */ Int32 sampleRateInHz,
    /* [in] */ Int32 channelConfig,
    /* [in] */ Int32 audioFormat,
    /* [in] */ Int32 bufferSizeInBytes,
    /* [out] */ IAudioRecord ** result)
{
    VALIDATE_NOT_NULL(result)
    *result = NULL;
    return NOERROR;
}

ECode CMediaProjection::Stop()
{
    // try {
    return mImpl->Stop();
    // } catch (RemoteException e) {
    //     Log.e(TAG, "Unable to stop projection", e);
    // }
}

ECode CMediaProjection::GetProjection(
    /* [out] */ IIMediaProjection ** result)
{
    VALIDATE_NOT_NULL(result)
    *result = mImpl;
    REFCOUNT_ADD(*result)
    return NOERROR;
}

} // namespace Projection
} // namespace Media
} // namepsace Droid
} // namespace Elastos
