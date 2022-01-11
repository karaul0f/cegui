/***********************************************************************
created:    21/2/2005
author:     Paul D Turner
*************************************************************************/
/***************************************************************************
*   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
*
*   Permission is hereby granted, free of charge, to any person obtaining
*   a copy of this software and associated documentation files (the
*   "Software"), to deal in the Software without restriction, including
*   without limitation the rights to use, copy, modify, merge, publish,
*   distribute, sublicense, and/or sell copies of the Software, and to
*   permit persons to whom the Software is furnished to do so, subject to
*   the following conditions:
*
*   The above copyright notice and this permission notice shall be
*   included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
*   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
*   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
*   OTHER DEALINGS IN THE SOFTWARE.
***************************************************************************/
#include "CEGUI/widgets/Tooltip.h"

namespace CEGUI
{
const String Tooltip::WidgetTypeName("CEGUI/Tooltip");

//----------------------------------------------------------------------------//
TooltipWindowRenderer::TooltipWindowRenderer(const String& name) :
    WindowRenderer(name, "Tooltip")
{
}

//----------------------------------------------------------------------------//
Tooltip::Tooltip(const String& type, const String& name) :
    Window(type, name)
{
}

//----------------------------------------------------------------------------//
void Tooltip::sizeSelf()
{
    if (d_windowRenderer)
    {
        const Sizef textSize = static_cast<TooltipWindowRenderer*>(d_windowRenderer)->getTextSize();
        setSize(USize(cegui_absdim(textSize.d_width), cegui_absdim(textSize.d_height)));
    }
}

//----------------------------------------------------------------------------//
bool Tooltip::validateWindowRenderer(const WindowRenderer* renderer) const
{
    return dynamic_cast<const TooltipWindowRenderer*>(renderer) != nullptr;
}

//----------------------------------------------------------------------------//
void Tooltip::onTextChanged(WindowEventArgs& e)
{
    Window::onTextChanged(e);

    // set size of the tooltip window to consider new text
    sizeSelf();

    // we do not signal we handled it, in case user wants to hear
    // about text changes too.
}

}
