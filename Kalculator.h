/**
*********************************************************************
Kalculator.h
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Header file	for	Kalculator class.


Revision History
	- 01MAY04-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#ifndef KALCULATOR_H
#define KALCULATOR_H

class Kalculator : public wxApp
{
private:
	virtual bool OnInit();
};

DECLARE_APP(Kalculator)

#endif	//KALCULATOR_H