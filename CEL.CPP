/**
*********************************************************************
CEL.cpp
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Imptementation file	for	CEL class. 


Revision History
	- 01MAY04-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#include "CEL.h"
#include <sstream>

using namespace std;

/**
*********************************************************************
CEL::CEL

    CEL default constructor.

    @param  void
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
CEL::CEL() : 
	m_buffer("")
{

}

/**
*********************************************************************
CEL::~CEL

    CEL destructor.

    @param  void
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
CEL::~CEL()
{

}

/**
*********************************************************************
CEL::GetCEL

    Returns the buffer (actual logged data) of CEL.

    @param  void
    @return wxString
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
wxString CEL::GetCEL() const
{
	return m_buffer;
}

/**
*********************************************************************
CEL::AddLogNewLine

    Adds a new line to CEL's buffer.

    @param  const wxString&		New line of string to be added.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL::AddLogNewLine(const wxString& text)
{
	m_buffer += ("\n" + text);
}

/**
*********************************************************************
CEL::AddLogNewLine

    Adds a new line to CEL's buffer. Specified numeric value will be converted to a string, then it
	will be added to buffer.

    @param  const long double&		New long double number to be added.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL::AddLogNewLine(const long double& number)
{
	ostringstream oStream;
	oStream << "\n";
	oStream << number;

	m_buffer += wxString( oStream.str().c_str() );
	oStream.flush();
}

/**
*********************************************************************
CEL::AddLogSameLine

    Adds data CEL's buffer without advancing the line.

    @param  const wxString&		New line of string to be added.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL::AddLogSameLine(const wxString& text)
{
	m_buffer += text;	
}

/**
*********************************************************************
CEL::AddLogSameLine

    Adds data CEL's buffer without advancing the line. Specified numeric value will be converted to a string, then it
	will be added to buffer.

    @param  const long double&		New long double number to be added.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL::AddLogSameLine(const long double& number)
{
	ostringstream oStream;
	oStream << number;

	m_buffer += wxString( oStream.str().c_str() );
	oStream.flush();
}

/**
*********************************************************************
CEL::ClearCEL

    Clears CEL's buffer

    @param  void
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL::ClearCEL()
{
	m_buffer = "";
}