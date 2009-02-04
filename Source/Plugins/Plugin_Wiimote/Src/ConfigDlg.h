// Copyright (C) 2003-2008 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef __CONFIGDIALOG_h__
#define __CONFIGDIALOG_h__

#include <iostream>
#include <vector>

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>

class ConfigDialog : public wxDialog
{
	public:
		ConfigDialog(wxWindow *parent, wxWindowID id = 1,
			const wxString &title = wxT("Wii Remote Plugin Configuration"),
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
			long style = wxDEFAULT_DIALOG_STYLE);
		virtual ~ConfigDialog();

		// General open, close and event functions
		void CloseClick(wxCommandEvent& event);
		void UpdateGUI();
		void OnKeyDown(wxKeyEvent& event);
		void LoadFile(); void SaveFile();
		
		// General status
		wxStaticText * m_TextUpdateRate;

		// Wiimote status
		wxGauge *m_GaugeBattery, *m_GaugeRoll[2], *m_GaugeGForce[3], *m_GaugeAccel[3];
		wxStaticText *m_TextIR, *m_TextAccNeutralCurrent;
		bool m_bWaitForRecording, m_bRecording, m_bAllowA;
		int m_iRecordTo;
		void RecordMovement(wxCommandEvent& event);
		void DoRecordMovement(u8 _x, u8 _y, u8 _z, const u8 *_IR, int IRBytes);
		void DoRecordA(bool Pressed);
		void ConvertToString();
		wxTimer *m_TimeoutTimer, *m_ShutDownTimer, *m_TimeoutATimer;
		void Update(wxTimerEvent& WXUNUSED(event));
		void ShutDown(wxTimerEvent& WXUNUSED(event));
		void UpdateA(wxTimerEvent& WXUNUSED(event));

	private:
		DECLARE_EVENT_TABLE();

		bool ControlsCreated; int Page, BoxW, BoxH;

		wxNotebook *m_Notebook;
		wxPanel *m_Controller[4], *m_PageRecording;
		wxButton *m_About, *m_Close, *m_Apply;
		wxBoxSizer *m_MainSizer, *m_sMain[4], *m_SizePadding[4],*m_SizeExtensionsPadding[4], *m_SizeBasicGeneral[4], *sRecordingMain, *m_HorizControllers[4], *m_TiltHoriz[4];
		wxStaticBoxSizer *m_SizeBasic[4], *m_SizeExtensions[4], *m_gTilt[4], *m_gJoyname[4];

		wxCheckBox *m_SidewaysDPad[4], *m_Joyattach[4]; // Emulated Wiimote settings
		wxCheckBox *m_WideScreen[4];
		wxCheckBox *m_NunchuckConnected[4], *m_ClassicControllerConnected[4];
		wxComboBox *m_TiltCombo[4], *m_TiltComboRange[4], *m_Joyname[4];
		wxStaticText *m_TiltText[4];

		wxCheckBox *m_ConnectRealWiimote[4], *m_UseRealWiimote[4], *m_UpdateMeters; // Real Wiimote settings
		wxChoice *m_AccNeutralChoice[3], *m_AccNunNeutralChoice[3];

		wxPanel *m_pInStatus[4], *m_pRightStatus[4];
		wxStaticBitmap *m_bmpDot[4], *m_bmpSquare[4], *m_bmpDotRight[4], *m_bmpSquareRight[4];
		wxStaticBoxSizer *m_gAnalogLeft[4], *m_gAnalogRight[4];
		wxBitmap CreateBitmapDot(), CreateBitmap();		

		wxButton * m_RecordButton[RECORDING_ROWS + 1];
		wxChoice * m_RecordHotKey[RECORDING_ROWS + 1];
		wxTextCtrl * m_RecordText[RECORDING_ROWS + 1];
		wxTextCtrl * m_RecordGameText[RECORDING_ROWS + 1];
		wxTextCtrl * m_RecordIRBytesText[RECORDING_ROWS + 1];
		wxTextCtrl * m_RecordSpeed[RECORDING_ROWS + 1];
		wxChoice * m_RecordPlayBackSpeed[RECORDING_ROWS + 1];

		/*
		struct m_sRecording
		{
			u8 x;
			u8 y;
			u8 z;
			double Time;
		};
		*/
		std::vector<SRecording> m_vRecording;
		int IRBytes;

		enum
		{
			ID_CLOSE = 1000,
			ID_APPLY,
			ID_ABOUTOGL,
			IDTM_EXIT, IDTM_UPDATE, IDTM_SHUTDOWN, IDTM_UPDATEA, // Timer

			ID_NOTEBOOK, ID_CONTROLLERPAGE1, ID_CONTROLLERPAGE2, ID_CONTROLLERPAGE3, ID_CONTROLLERPAGE4, ID_PAGE_RECORDING,

			ID_SIDEWAYSDPAD, // Emulated
			ID_WIDESCREEN,
			ID_NUNCHUCKCONNECTED, ID_CLASSICCONTROLLERCONNECTED,
			IDC_JOYNAME, IDC_JOYATTACH, ID_TILT_COMBO, ID_TILT_CHECK, 

			// Real
			ID_CONNECT_REAL, ID_USE_REAL, ID_UPDATE_REAL, IDT_STATUS, ID_NEUTRAL_CHOICE,
			IDB_RECORD = 2000,
			IDC_RECORD = 3000,
			IDT_RECORD_TEXT, IDT_RECORD_GAMETEXT, IDT_RECORD_IRBYTESTEXT, IDT_RECORD_SPEED, IDT_RECORD_PLAYSPEED
		};

		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		void CreateGUIControlsRecording();
		void AboutClick(wxCommandEvent& event);

		void DoConnectReal(); // Real

		void DoExtensionConnectedDisconnected(); // Emulated

		void GeneralSettingsChanged(wxCommandEvent& event);		
};

extern ConfigDialog *frame;

#endif
