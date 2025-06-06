/*
 * Copyright (c) 2024, Shannon Booth <shannon@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/AudioParamPrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/WebAudio/AudioParam.h>
#include <LibWeb/WebAudio/BaseAudioContext.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::WebAudio {

GC_DEFINE_ALLOCATOR(AudioParam);

AudioParam::AudioParam(JS::Realm& realm, GC::Ref<BaseAudioContext> context, float default_value, float min_value, float max_value, Bindings::AutomationRate automation_rate, FixedAutomationRate fixed_automation_rate)
    : Bindings::PlatformObject(realm)
    , m_context(context)
    , m_current_value(default_value)
    , m_default_value(default_value)
    , m_min_value(min_value)
    , m_max_value(max_value)
    , m_automation_rate(automation_rate)
    , m_fixed_automation_rate(fixed_automation_rate)
{
}

GC::Ref<AudioParam> AudioParam::create(JS::Realm& realm, GC::Ref<BaseAudioContext> context, float default_value, float min_value, float max_value, Bindings::AutomationRate automation_rate, FixedAutomationRate fixed_automation_rate)
{
    return realm.create<AudioParam>(realm, context, default_value, min_value, max_value, automation_rate, fixed_automation_rate);
}

AudioParam::~AudioParam() = default;

// https://webaudio.github.io/web-audio-api/#dom-audioparam-value
// https://webaudio.github.io/web-audio-api/#simple-nominal-range
float AudioParam::value() const
{
    // Each AudioParam includes minValue and maxValue attributes that together form the simple nominal range
    // for the parameter. In effect, value of the parameter is clamped to the range [minValue, maxValue].
    return clamp(m_current_value, min_value(), max_value());
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-value
void AudioParam::set_value(float value)
{
    m_current_value = value;
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-automationrate
Bindings::AutomationRate AudioParam::automation_rate() const
{
    return m_automation_rate;
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-automationrate
WebIDL::ExceptionOr<void> AudioParam::set_automation_rate(Bindings::AutomationRate automation_rate)
{
    if (automation_rate != m_automation_rate && m_fixed_automation_rate == FixedAutomationRate::Yes)
        return WebIDL::InvalidStateError::create(realm(), "Automation rate cannot be changed"_string);

    m_automation_rate = automation_rate;
    return {};
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-defaultvalue
float AudioParam::default_value() const
{
    return m_default_value;
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-minvalue
float AudioParam::min_value() const
{
    return m_min_value;
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-maxvalue
float AudioParam::max_value() const
{
    return m_max_value;
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-setvalueattime
WebIDL::ExceptionOr<GC::Ref<AudioParam>> AudioParam::set_value_at_time(float value, double start_time)
{
    (void)value;
    (void)start_time;
    dbgln("FIXME: Implement AudioParam::set_value_at_time");
    return GC::Ref { *this };
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-linearramptovalueattime
WebIDL::ExceptionOr<GC::Ref<AudioParam>> AudioParam::linear_ramp_to_value_at_time(float value, double end_time)
{
    (void)value;
    (void)end_time;
    dbgln("FIXME: Implement AudioParam::linear_ramp_to_value_at_time");
    return GC::Ref { *this };
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-exponentialramptovalueattime
WebIDL::ExceptionOr<GC::Ref<AudioParam>> AudioParam::exponential_ramp_to_value_at_time(float value, double end_time)
{
    (void)value;
    (void)end_time;
    dbgln("FIXME: Implement AudioParam::exponential_ramp_to_value_at_time");
    return GC::Ref { *this };
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-settargetattime
WebIDL::ExceptionOr<GC::Ref<AudioParam>> AudioParam::set_target_at_time(float target, double start_time, float time_constant)
{
    (void)target;
    (void)start_time;
    (void)time_constant;
    dbgln("FIXME: Implement AudioParam::set_target_at_time");
    return GC::Ref { *this };
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-setvaluecurveattime
WebIDL::ExceptionOr<GC::Ref<AudioParam>> AudioParam::set_value_curve_at_time(Span<float> values, double start_time, double duration)
{
    (void)values;
    (void)start_time;
    (void)duration;
    dbgln("FIXME: Implement AudioParam::set_value_curve_at_time");
    return GC::Ref { *this };
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-cancelscheduledvalues
WebIDL::ExceptionOr<GC::Ref<AudioParam>> AudioParam::cancel_scheduled_values(double cancel_time)
{
    (void)cancel_time;
    dbgln("FIXME: Implement AudioParam::cancel_scheduled_values");
    return GC::Ref { *this };
}

// https://webaudio.github.io/web-audio-api/#dom-audioparam-cancelandholdattime
WebIDL::ExceptionOr<GC::Ref<AudioParam>> AudioParam::cancel_and_hold_at_time(double cancel_time)
{
    (void)cancel_time;
    dbgln("FIXME: Implement AudioParam::cancel_and_hold_at_time");
    return GC::Ref { *this };
}

void AudioParam::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(AudioParam);
    Base::initialize(realm);
}

void AudioParam::visit_edges(Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_context);
}

}
