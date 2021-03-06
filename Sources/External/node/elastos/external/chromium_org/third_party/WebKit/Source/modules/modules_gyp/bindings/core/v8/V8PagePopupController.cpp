// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8PagePopupController.h"

#include "bindings/v8/ExceptionState.h"
#include "bindings/v8/V8DOMConfiguration.h"
#include "bindings/v8/V8HiddenValue.h"
#include "bindings/v8/V8ObjectConstructor.h"
#include "core/dom/ContextFeatures.h"
#include "core/dom/Document.h"
#include "platform/RuntimeEnabledFeatures.h"
#include "platform/TraceEvent.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace WebCore {

static void initializeScriptWrappableForInterface(PagePopupController* object)
{
    if (ScriptWrappable::wrapperCanBeStoredInObject(object))
        ScriptWrappable::fromObject(object)->setTypeInfo(&V8PagePopupController::wrapperTypeInfo);
    else
        ASSERT_NOT_REACHED();
}

} // namespace WebCore

void webCoreInitializeScriptWrappableForInterface(WebCore::PagePopupController* object)
{
    WebCore::initializeScriptWrappableForInterface(object);
}

namespace WebCore {
const WrapperTypeInfo V8PagePopupController::wrapperTypeInfo = { gin::kEmbedderBlink, V8PagePopupController::domTemplate, V8PagePopupController::derefObject, 0, 0, 0, V8PagePopupController::installPerContextEnabledMethods, 0, WrapperTypeObjectPrototype, WillBeGarbageCollectedObject };

namespace PagePopupControllerV8Internal {

template <typename T> void V8_USE(T) { }

static void setValueAndClosePopupMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setValueAndClosePopup", "PagePopupController", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        throwMinimumArityTypeError(exceptionState, 2, info.Length());
        return;
    }
    PagePopupController* impl = V8PagePopupController::toNative(info.Holder());
    int numberValue;
    V8StringResource<> stringValue;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(numberValue, toInt32(info[0], exceptionState), exceptionState);
        TOSTRING_VOID_INTERNAL(stringValue, info[1]);
    }
    impl->setValueAndClosePopup(numberValue, stringValue);
}

static void setValueAndClosePopupMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    PagePopupControllerV8Internal::setValueAndClosePopupMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void setValueMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        throwMinimumArityTypeErrorForMethod("setValue", "PagePopupController", 1, info.Length(), info.GetIsolate());
        return;
    }
    PagePopupController* impl = V8PagePopupController::toNative(info.Holder());
    V8StringResource<> value;
    {
        TOSTRING_VOID_INTERNAL(value, info[0]);
    }
    impl->setValue(value);
}

static void setValueMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    PagePopupControllerV8Internal::setValueMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void closePopupMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    PagePopupController* impl = V8PagePopupController::toNative(info.Holder());
    impl->closePopup();
}

static void closePopupMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    PagePopupControllerV8Internal::closePopupMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void localizeNumberStringMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        throwMinimumArityTypeErrorForMethod("localizeNumberString", "PagePopupController", 1, info.Length(), info.GetIsolate());
        return;
    }
    PagePopupController* impl = V8PagePopupController::toNative(info.Holder());
    V8StringResource<> numberString;
    {
        TOSTRING_VOID_INTERNAL(numberString, info[0]);
    }
    v8SetReturnValueString(info, impl->localizeNumberString(numberString), info.GetIsolate());
}

static void localizeNumberStringMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    PagePopupControllerV8Internal::localizeNumberStringMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void formatMonthMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "formatMonth", "PagePopupController", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        throwMinimumArityTypeError(exceptionState, 2, info.Length());
        return;
    }
    PagePopupController* impl = V8PagePopupController::toNative(info.Holder());
    int year;
    int zeroBaseMonth;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(year, toInt32(info[0], exceptionState), exceptionState);
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(zeroBaseMonth, toInt32(info[1], exceptionState), exceptionState);
    }
    v8SetReturnValueString(info, impl->formatMonth(year, zeroBaseMonth), info.GetIsolate());
}

static void formatMonthMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    PagePopupControllerV8Internal::formatMonthMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void formatShortMonthMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "formatShortMonth", "PagePopupController", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        throwMinimumArityTypeError(exceptionState, 2, info.Length());
        return;
    }
    PagePopupController* impl = V8PagePopupController::toNative(info.Holder());
    int year;
    int zeroBaseMonth;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(year, toInt32(info[0], exceptionState), exceptionState);
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(zeroBaseMonth, toInt32(info[1], exceptionState), exceptionState);
    }
    v8SetReturnValueString(info, impl->formatShortMonth(year, zeroBaseMonth), info.GetIsolate());
}

static void formatShortMonthMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    PagePopupControllerV8Internal::formatShortMonthMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void histogramEnumerationMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "histogramEnumeration", "PagePopupController", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 3)) {
        throwMinimumArityTypeError(exceptionState, 3, info.Length());
        return;
    }
    PagePopupController* impl = V8PagePopupController::toNative(info.Holder());
    V8StringResource<> name;
    int sample;
    int boundaryValue;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TOSTRING_VOID_INTERNAL(name, info[0]);
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(sample, toInt32(info[1], exceptionState), exceptionState);
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(boundaryValue, toInt32(info[2], exceptionState), exceptionState);
    }
    impl->histogramEnumeration(name, sample, boundaryValue);
}

static void histogramEnumerationMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    PagePopupControllerV8Internal::histogramEnumerationMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

} // namespace PagePopupControllerV8Internal

static const V8DOMConfiguration::MethodConfiguration V8PagePopupControllerMethods[] = {
    {"setValueAndClosePopup", PagePopupControllerV8Internal::setValueAndClosePopupMethodCallback, 0, 2},
    {"setValue", PagePopupControllerV8Internal::setValueMethodCallback, 0, 1},
    {"closePopup", PagePopupControllerV8Internal::closePopupMethodCallback, 0, 0},
    {"localizeNumberString", PagePopupControllerV8Internal::localizeNumberStringMethodCallback, 0, 1},
    {"formatMonth", PagePopupControllerV8Internal::formatMonthMethodCallback, 0, 2},
    {"formatShortMonth", PagePopupControllerV8Internal::formatShortMonthMethodCallback, 0, 2},
    {"histogramEnumeration", PagePopupControllerV8Internal::histogramEnumerationMethodCallback, 0, 3},
};

static void configureV8PagePopupControllerTemplate(v8::Handle<v8::FunctionTemplate> functionTemplate, v8::Isolate* isolate)
{
    functionTemplate->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    if (!RuntimeEnabledFeatures::pagePopupEnabled())
        defaultSignature = V8DOMConfiguration::installDOMClassTemplate(functionTemplate, "", v8::Local<v8::FunctionTemplate>(), V8PagePopupController::internalFieldCount, 0, 0, 0, 0, 0, 0, isolate);
    else
        defaultSignature = V8DOMConfiguration::installDOMClassTemplate(functionTemplate, "PagePopupController", v8::Local<v8::FunctionTemplate>(), V8PagePopupController::internalFieldCount,
            0, 0,
            0, 0,
            V8PagePopupControllerMethods, WTF_ARRAY_LENGTH(V8PagePopupControllerMethods),
            isolate);
    v8::Local<v8::ObjectTemplate> instanceTemplate ALLOW_UNUSED = functionTemplate->InstanceTemplate();
    v8::Local<v8::ObjectTemplate> prototypeTemplate ALLOW_UNUSED = functionTemplate->PrototypeTemplate();

    // Custom toString template
    functionTemplate->Set(v8AtomicString(isolate, "toString"), V8PerIsolateData::from(isolate)->toStringTemplate());
}

v8::Handle<v8::FunctionTemplate> V8PagePopupController::domTemplate(v8::Isolate* isolate)
{
    return V8DOMConfiguration::domClassTemplate(isolate, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), configureV8PagePopupControllerTemplate);
}

bool V8PagePopupController::hasInstance(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Handle<v8::Object> V8PagePopupController::findInstanceInPrototypeChain(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

PagePopupController* V8PagePopupController::toNativeWithTypeCheck(v8::Isolate* isolate, v8::Handle<v8::Value> value)
{
    return hasInstance(value, isolate) ? fromInternalPointer(v8::Handle<v8::Object>::Cast(value)->GetAlignedPointerFromInternalField(v8DOMWrapperObjectIndex)) : 0;
}

v8::Handle<v8::Object> wrap(PagePopupController* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl);
    ASSERT(!DOMDataStore::containsWrapper<V8PagePopupController>(impl, isolate));
    return V8PagePopupController::createWrapper(impl, creationContext, isolate);
}

v8::Handle<v8::Object> V8PagePopupController::createWrapper(PassRefPtrWillBeRawPtr<PagePopupController> impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl);
    ASSERT(!DOMDataStore::containsWrapper<V8PagePopupController>(impl.get(), isolate));
    if (ScriptWrappable::wrapperCanBeStoredInObject(impl.get())) {
        const WrapperTypeInfo* actualInfo = ScriptWrappable::fromObject(impl.get())->typeInfo();
        // Might be a XXXConstructor::wrapperTypeInfo instead of an XXX::wrapperTypeInfo. These will both have
        // the same object de-ref functions, though, so use that as the basis of the check.
        RELEASE_ASSERT_WITH_SECURITY_IMPLICATION(actualInfo->derefObjectFunction == wrapperTypeInfo.derefObjectFunction);
    }

    v8::Handle<v8::Object> wrapper = V8DOMWrapper::createWrapper(creationContext, &wrapperTypeInfo, toInternalPointer(impl.get()), isolate);
    if (UNLIKELY(wrapper.IsEmpty()))
        return wrapper;

    installPerContextEnabledProperties(wrapper, impl.get(), isolate);
    V8DOMWrapper::associateObjectWithWrapper<V8PagePopupController>(impl, &wrapperTypeInfo, wrapper, isolate, WrapperConfiguration::Independent);
    return wrapper;
}

void V8PagePopupController::derefObject(void* object)
{
#if !ENABLE(OILPAN)
    fromInternalPointer(object)->deref();
#endif // !ENABLE(OILPAN)
}

template<>
v8::Handle<v8::Value> toV8NoInline(PagePopupController* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    return toV8(impl, creationContext, isolate);
}

} // namespace WebCore
