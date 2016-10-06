/**
*********************************************************************
Kalculator.cpp
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Imptementation file	for	Kalculator class.


Revision History
	- 01MAY04-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#include "wx/wxprec.h"
#include "Kalculator.h"
#include "KalculatorFrame.h"

IMPLEMENT_APP(Kalculator)

/**
*********************************************************************
Kalculator::OnInit

    Called by the framework when this application is initialized.

    @param  void
    @return bool		True if initialized successfully, false if otherwise. 		
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
bool Kalculator::OnInit()
{
	KalculatorFrame* frame = new KalculatorFrame;
	frame->Show(true);
	SetTopWindow(frame);

	return true;
}