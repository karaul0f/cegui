/***********************************************************************
	created:	31/3/2005
	author:		Tomas Lindquist Olsen (based on code by Paul D Turner)
	
	purpose:	Implementation of Menubar widget base class
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
#include "CEGUI/widgets/Menubar.h"
#include "CEGUI/CoordConverter.h"

namespace CEGUI
{
const String Menubar::EventNamespace("Menubar");
const String Menubar::WidgetTypeName("CEGUI/Menubar");

//----------------------------------------------------------------------------//
Menubar::Menubar(const String& type, const String& name)
	: MenuBase(type, name)
{
	d_itemSpacing = 10;
}

//----------------------------------------------------------------------------//
void Menubar::layoutItemWidgets()
{
	float x0 = CoordConverter::alignToPixels(getItemRenderArea().left());
	for (auto item : d_listItems)
	{
		const Sizef optimal = item->getItemPixelSize();

		item->setVerticalAlignment(VerticalAlignment::Centre);

		item->setArea(UVector2(cegui_absdim(x0), cegui_absdim(0)),
            USize(cegui_absdim(CoordConverter::alignToPixels(optimal.d_width)),
                cegui_absdim(CoordConverter::alignToPixels(optimal.d_height))));

		x0 += optimal.d_width + d_itemSpacing;
	}
}

//----------------------------------------------------------------------------//
Sizef Menubar::getContentSize() const
{
	// find the content sizes
	float tallest = 0.f;
	float total_width = 0.f;

	size_t i = 0;
	const size_t max = d_listItems.size();
	while (i < max)
	{
		const Sizef sz = d_listItems[i]->getItemPixelSize();
		if (sz.d_height > tallest)
			tallest = sz.d_height;
		total_width += sz.d_width;

		i++;
	}

	const float count = float(i);

	// horz item spacing
	if (count >= 2)
	{
	    total_width += (count-1)*d_itemSpacing;
	}

	// return the content size
	return Sizef(total_width, tallest);
}

} // End of  CEGUI namespace section
