/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/HTMLDListElementPrototype.h>
#include <LibWeb/HTML/HTMLDListElement.h>
#include <LibWeb/HTML/Window.h>

namespace Web::HTML {

GC_DEFINE_ALLOCATOR(HTMLDListElement);

HTMLDListElement::HTMLDListElement(DOM::Document& document, DOM::QualifiedName qualified_name)
    : HTMLElement(document, move(qualified_name))
{
}

HTMLDListElement::~HTMLDListElement() = default;

void HTMLDListElement::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(HTMLDListElement);
    Base::initialize(realm);
}

}
