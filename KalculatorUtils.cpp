/**
*********************************************************************
KalculatorUtils.cpp
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Implementation file	for	KalculatorUtils class.


Revision History
	- 05APR05-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#include <sstream>
#include "KalculatorUtils.h"
#include "KalculatorException.h"

/**
*********************************************************************
KalculatorUtils::GetCodeLocation

    Creates a string with the specified code location and returns it.

    @param  const std::string&		Name of the source file.
    @param  const std::string&		Line of source code.
	@return std::string				String that includes the code location.
    @throw  N/A


Revision History
	- 01FEB05-BCC	Initial	creation
	- 05APR05-BCC	Returns the string regardless of the debug mode
*********************************************************************/
std::string KalculatorUtils::GetCodeLocation(const std::string& fileName, const int& lineNumber)
{
	std::string message = ">>> Exception at... \nFile: \t";
	message.append(fileName);
	message.append("\nLine: \t");

	std::stringstream strm;
	strm << lineNumber;

	message.append( strm.str() );

	return message;
}


/**
*********************************************************************
KalculatorUtils::ErrorOut

    If in debug mode, displays the specified error message.

    @param  const std::string&		Error message to display.
	@return void
    @throw  N/A


Revision History
	- 01FEB05-BCC	Initial	creation
	- 05APR05-BCC	Now passing a wxString to ShowDialog function
*********************************************************************/
void KalculatorUtils::ErrorOut(const std::string& errorMessage)
{
	if(IS_DEBUGGING)
	{
		wxString errorMessage_( errorMessage.c_str() );		//ShowDialog takes wxString only!

		ShowDialog(	(wxWindow*) NULL,
					errorMessage_,
					"Kalculator", 
					wxOK | wxICON_ERROR | wxCENTRE);
	}
}


/**
*********************************************************************
KalculatorUtils::CheckPointer

    Checks if the specified pointer is null or not.

	@param  const void*			Pointer to test.
    @param  const wxString&		Name of the source file.
	@param  const int&			Line of the source code.
    @return bool				False if it is null, true if otherwise.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
bool KalculatorUtils::CheckPointer(	const void* pointer, 
									const std::string& fileName, 
									const int& lineNumber)
{
	if(pointer == NULL)
	{
		try
		{
			throw KalculatorException(fileName, lineNumber);
		}
		catch(...)
		{
			//define an exception catch policy?
			
			return false;
		}			
	}
	else
	{
		return true;
	}
}


/**
*********************************************************************
KalculatorUtils::IsFloating

    Determines if the specified parameter is a floating number or not.

    @param  const wxString&		String to determine it has a '.' or not.
    @return bool				True if floating, false of otherwise.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
bool KalculatorUtils::IsFloating(const wxString& string)
{
	if(string.Find('.') == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}


void KalculatorUtils::ShowDialog(	wxWindow* parent, 
									const wxString& message, 
									const wxString& title, 
									const long& style) 
{
	wxMessageDialog* msgDialog = new wxMessageDialog(parent, message, title, style);
	msgDialog->ShowModal();
	msgDialog->Destroy();	
}