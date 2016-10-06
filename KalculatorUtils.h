/**
*********************************************************************
KalculatorUtils.h
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Header file	for	KalculatorUtils class.


Revision History
	- 05APR05-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#ifndef KALCULATOR_UTILS_H
#define KALCULATOR_UTILS_H
#include "wx/wxprec.h"
#include <string>

//messages to be displayed in dialog boxes
const wxString CEL_SAVE_SUCCESS_MSG	= "CEL saved successfully.";
const wxString CEL_SAVE_FAILURE_MSG	= "Saving CEL failed.\nPlease try again.";
const wxString DIVIDE_BY_ZERO_MSG	= "Invalid action. Cannot divide by 0.";
const wxString SQRT_MSG				= "Invalid action. Square root of negative numbers cannot be taken.";
const wxString EXCEPTION_MSG		= "Unhandled Exception.\nSaved data in is this application may be lost.\n"
										"Click 'OK' to go back to Kalculator then click 'Clear' to continue normal operation.";
const wxString ABOUT_MSG			= "Designed & Developed by Berk Can Celebisoy.";
//Debug mode flag
const bool IS_DEBUGGING				= true;

class KalculatorUtils
{
public:
	static inline std::string GetCodeLocation(	const std::string& fileName, 
												const int& lineNumber);
	
	static inline void ErrorOut(const std::string& errorMessage);
	
	static inline bool CheckPointer(const void* pointer, 
									const std::string& fileName, 
									const int& lineNumber);
	
	static inline bool IsFloating(const wxString& string);
	
	static inline void ShowDialog(	wxWindow* parent, 
									const wxString& message, 
									const wxString& title, 
									const long& style);

private:
	KalculatorUtils() = 0;										//not implemented as per design
	KalculatorUtils(const KalculatorUtils& kalcUtils) = 0;		//not implemented as per design
	virtual ~KalculatorUtils() = 0;								//not implemented as per design
};

#endif	//KALCULATOR_UTILS_H