// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8IDBCursor.h"

#include "bindings/modules/v8/V8IDBRequest.h"
#include "bindings/v8/ExceptionState.h"
#include "bindings/v8/ScriptState.h"
#include "bindings/v8/ScriptValue.h"
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

static void initializeScriptWrappableForInterface(IDBCursor* object)
{
    if (ScriptWrappable::wrapperCanBeStoredInObject(object))
        ScriptWrappable::fromObject(object)->setTypeInfo(&V8IDBCursor::wrapperTypeInfo);
    else
        ASSERT_NOT_REACHED();
}

} // namespace WebCore

void webCoreInitializeScriptWrappableForInterface(WebCore::IDBCursor* object)
{
    WebCore::initializeScriptWrappableForInterface(object);
}

namespace WebCore {
const WrapperTypeInfo V8IDBCursor::wrapperTypeInfo = { gin::kEmbedderBlink, V8IDBCursor::domTemplate, V8IDBCursor::derefObject, 0, 0, 0, V8IDBCursor::installPerContextEnabledMethods, 0, WrapperTypeObjectPrototype, GarbageCollectedObject };

namespace IDBCursorV8Internal {

template <typename T> void V8_USE(T) { }

static void directionAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    IDBCursor* impl = V8IDBCursor::toNative(holder);
    v8SetReturnValueString(info, impl->direction(), info.GetIsolate());
}

static void directionAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    IDBCursorV8Internal::directionAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void keyAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    v8::Handle<v8::String> propertyName = v8AtomicString(info.GetIsolate(), "key");
    IDBCursor* impl = V8IDBCursor::toNative(holder);
    if (!impl->isKeyDirty()) {
        v8::Handle<v8::Value> v8Value = V8HiddenValue::getHiddenValue(info.GetIsolate(), holder, propertyName);
        if (!v8Value.IsEmpty()) {
            v8SetReturnValue(info, v8Value);
            return;
        }
    }
    ScriptState* scriptState = ScriptState::current(info.GetIsolate());
    ScriptValue v8Value = impl->key(scriptState);
    V8HiddenValue::setHiddenValue(info.GetIsolate(), holder, propertyName, v8Value.v8Value());
    v8SetReturnValue(info, v8Value.v8Value());
}

static void keyAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    IDBCursorV8Internal::keyAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void primaryKeyAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    v8::Handle<v8::String> propertyName = v8AtomicString(info.GetIsolate(), "primaryKey");
    IDBCursor* impl = V8IDBCursor::toNative(holder);
    if (!impl->isPrimaryKeyDirty()) {
        v8::Handle<v8::Value> v8Value = V8HiddenValue::getHiddenValue(info.GetIsolate(), holder, propertyName);
        if (!v8Value.IsEmpty()) {
            v8SetReturnValue(info, v8Value);
            return;
        }
    }
    ScriptState* scriptState = ScriptState::current(info.GetIsolate());
    ScriptValue v8Value = impl->primaryKey(scriptState);
    V8HiddenValue::setHiddenValue(info.GetIsolate(), holder, propertyName, v8Value.v8Value());
    v8SetReturnValue(info, v8Value.v8Value());
}

static void primaryKeyAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    IDBCursorV8Internal::primaryKeyAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void sourceAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    IDBCursor* impl = V8IDBCursor::toNative(holder);
    ScriptState* scriptState = ScriptState::current(info.GetIsolate());
    v8SetReturnValue(info, impl->source(scriptState).v8Value());
}

static void sourceAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    IDBCursorV8Internal::sourceAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void updateMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "update", "IDBCursor", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        throwMinimumArityTypeError(exceptionState, 1, info.Length());
        return;
    }
    IDBCursor* impl = V8IDBCursor::toNative(info.Holder());
    ScriptValue value;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_INTERNAL(value, ScriptValue(ScriptState::current(info.GetIsolate()), info[0]));
    }
    ScriptState* scriptState = ScriptState::current(info.GetIsolate());
    RawPtr<IDBRequest> result = impl->update(scriptState, value, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
    v8SetReturnValue(info, result.release());
}

static void updateMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    IDBCursorV8Internal::updateMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void advanceMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "advance", "IDBCursor", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        throwMinimumArityTypeError(exceptionState, 1, info.Length());
        return;
    }
    IDBCursor* impl = V8IDBCursor::toNative(info.Holder());
    unsigned count;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(count, toUInt32(info[0], EnforceRange, exceptionState), exceptionState);
    }
    impl->advance(count, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void advanceMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    IDBCursorV8Internal::advanceMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void continueMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "continue", "IDBCursor", info.Holder(), info.GetIsolate());
    IDBCursor* impl = V8IDBCursor::toNative(info.Holder());
    ScriptValue key;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_INTERNAL(key, ScriptValue(ScriptState::current(info.GetIsolate()), info[0]));
    }
    ScriptState* scriptState = ScriptState::current(info.GetIsolate());
    impl->continueFunction(scriptState, key, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void continueMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    IDBCursorV8Internal::continueMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void continuePrimaryKeyMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "continuePrimaryKey", "IDBCursor", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        throwMinimumArityTypeError(exceptionState, 2, info.Length());
        return;
    }
    IDBCursor* impl = V8IDBCursor::toNative(info.Holder());
    ScriptValue key;
    ScriptValue primaryKey;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_INTERNAL(key, ScriptValue(ScriptState::current(info.GetIsolate()), info[0]));
        TONATIVE_VOID_INTERNAL(primaryKey, ScriptValue(ScriptState::current(info.GetIsolate()), info[1]));
    }
    ScriptState* scriptState = ScriptState::current(info.GetIsolate());
    impl->continuePrimaryKey(scriptState, key, primaryKey, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void continuePrimaryKeyMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    IDBCursorV8Internal::continuePrimaryKeyMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void deleteMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "delete", "IDBCursor", info.Holder(), info.GetIsolate());
    IDBCursor* impl = V8IDBCursor::toNative(info.Holder());
    ScriptState* scriptState = ScriptState::current(info.GetIsolate());
    RawPtr<IDBRequest> result = impl->deleteFunction(scriptState, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
    v8SetReturnValue(info, result.release());
}

static void deleteMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    IDBCursorV8Internal::deleteMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

} // namespace IDBCursorV8Internal

static const V8DOMConfiguration::AttributeConfiguration V8IDBCursorAttributes[] = {
    {"direction", IDBCursorV8Internal::directionAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"key", IDBCursorV8Internal::keyAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"primaryKey", IDBCursorV8Internal::primaryKeyAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"source", IDBCursorV8Internal::sourceAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
};

static const V8DOMConfiguration::MethodConfiguration V8IDBCursorMethods[] = {
    {"update", IDBCursorV8Internal::updateMethodCallback, 0, 1},
    {"advance", IDBCursorV8Internal::advanceMethodCallback, 0, 1},
    {"continue", IDBCursorV8Internal::continueMethodCallback, 0, 0},
    {"delete", IDBCursorV8Internal::deleteMethodCallback, 0, 0},
};

static void configureV8IDBCursorTemplate(v8::Handle<v8::FunctionTemplate> functionTemplate, v8::Isolate* isolate)
{
    functionTemplate->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::installDOMClassTemplate(functionTemplate, "IDBCursor", v8::Local<v8::FunctionTemplate>(), V8IDBCursor::internalFieldCount,
        V8IDBCursorAttributes, WTF_ARRAY_LENGTH(V8IDBCursorAttributes),
        0, 0,
        V8IDBCursorMethods, WTF_ARRAY_LENGTH(V8IDBCursorMethods),
        isolate);
    v8::Local<v8::ObjectTemplate> instanceTemplate ALLOW_UNUSED = functionTemplate->InstanceTemplate();
    v8::Local<v8::ObjectTemplate> prototypeTemplate ALLOW_UNUSED = functionTemplate->PrototypeTemplate();
    if (RuntimeEnabledFeatures::indexedDBExperimentalEnabled()) {
        prototypeTemplate->Set(v8AtomicString(isolate, "continuePrimaryKey"), v8::FunctionTemplate::New(isolate, IDBCursorV8Internal::continuePrimaryKeyMethodCallback, v8Undefined(), defaultSignature, 2));
    }

    // Custom toString template
    functionTemplate->Set(v8AtomicString(isolate, "toString"), V8PerIsolateData::from(isolate)->toStringTemplate());
}

v8::Handle<v8::FunctionTemplate> V8IDBCursor::domTemplate(v8::Isolate* isolate)
{
    return V8DOMConfiguration::domClassTemplate(isolate, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), configureV8IDBCursorTemplate);
}

bool V8IDBCursor::hasInstance(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Handle<v8::Object> V8IDBCursor::findInstanceInPrototypeChain(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

IDBCursor* V8IDBCursor::toNativeWithTypeCheck(v8::Isolate* isolate, v8::Handle<v8::Value> value)
{
    return hasInstance(value, isolate) ? fromInternalPointer(v8::Handle<v8::Object>::Cast(value)->GetAlignedPointerFromInternalField(v8DOMWrapperObjectIndex)) : 0;
}

v8::Handle<v8::Object> wrap(IDBCursor* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl);
    ASSERT(!DOMDataStore::containsWrapper<V8IDBCursor>(impl, isolate));
    return V8IDBCursor::createWrapper(impl, creationContext, isolate);
}

v8::Handle<v8::Object> V8IDBCursor::createWrapper(RawPtr<IDBCursor> impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl);
    ASSERT(!DOMDataStore::containsWrapper<V8IDBCursor>(impl.get(), isolate));
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
    V8DOMWrapper::associateObjectWithWrapper<V8IDBCursor>(impl, &wrapperTypeInfo, wrapper, isolate, WrapperConfiguration::Independent);
    return wrapper;
}

void V8IDBCursor::derefObject(void* object)
{
}

template<>
v8::Handle<v8::Value> toV8NoInline(IDBCursor* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    return toV8(impl, creationContext, isolate);
}

} // namespace WebCore
