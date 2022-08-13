/*
 * MainFrame.cpp
 *
 *  Created on: May 17, 2021
 *      Author: jsymolon
 */

#include "MainFrame.h"

#include "FileHandling.h"
#include "Memory.h"
#include "SourceCtrl.h"

#include <wx/filename.h>
#include <wx/log.h>
#include <wx/splitter.h>
#include <wx/stdpaths.h>
#include <wx/toolbar.h>

#include "extern.h"
#include "PROTO.H"
#include <string>

#include "MemoryDialog.h"
#include "UTILS.h"

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
EVT_MENU(ID_Open, MainFrame::OnOpen)
EVT_MENU(ID_Open_Data, MainFrame::OnOpenData)
EVT_MENU(ID_Close, MainFrame::OnClose)
EVT_MENU(ID_Printer_Setup, MainFrame::OnPrinterSetup)
EVT_MENU(ID_Exit, MainFrame::OnExit)
EVT_MENU(ID_Find, MainFrame::OnFind)
EVT_MENU(ID_GoToPC, MainFrame::OnGoToPC)
EVT_MENU(ID_Run, MainFrame::OnRun)
EVT_MENU(ID_Run_To_Cursor, MainFrame::OnRunToCursor)
EVT_MENU(ID_Auto_Trace, MainFrame::OnAutoTrace)
EVT_MENU(ID_Step_Over, MainFrame::OnStepOver)
EVT_MENU(ID_Trace_Into, MainFrame::OnTraceInto)
EVT_MENU(ID_Pause, MainFrame::OnPause)
EVT_MENU(ID_Rewind_Program, MainFrame::OnRewindProgram)
EVT_MENU(ID_Reload_Program, MainFrame::OnReloadProgram)
EVT_MENU(ID_Log_Start, MainFrame::OnLogStart)
EVT_MENU(ID_Log_Stop, MainFrame::OnLogStop)
EVT_MENU(ID_Output_Window, MainFrame::OnOutputWindow)
EVT_MENU(ID_Memory_Window, MainFrame::OnMemoryWindow)
EVT_MENU(ID_Stack_Window, MainFrame::OnStackWindow)
EVT_MENU(ID_Hardware_Window, MainFrame::OnHardwareWindow)
EVT_MENU(ID_Breakpoints_Window, MainFrame::OnBreakpointsWindow)
EVT_MENU(ID_EASyBIN_Window, MainFrame::OnEASyBINWindow)
EVT_MENU(ID_Source_Window_Font, MainFrame::OnSourceWindowFont)
EVT_MENU(ID_Output_Window_Font, MainFrame::OnOutputWindowFont)
EVT_MENU(ID_Printer_Font, MainFrame::OnPrinterFont)
EVT_MENU(ID_Log_Output, MainFrame::OnLogOutput)
EVT_MENU(ID_Auto_Trace_Output, MainFrame::OnAutoTraceOutput)
EVT_MENU(ID_Fullscreen_Options, MainFrame::OnFullscreenOptions)
EVT_MENU(ID_Enable_Bit_Field_Options, MainFrame::OnEnableBitFieldOptions)
EVT_MENU(ID_Output_Window_Size, MainFrame::OnOutputWindowSize)
EVT_MENU(ID_Output_Window_Text_Wrap, MainFrame::OnOutputWindowTextWrap)
EVT_MENU(ID_Help, MainFrame::OnHelp)
EVT_MENU(ID_About, MainFrame::OnAbout)
END_EVENT_TABLE() // The button is pressed

// ------------------------------------------------------------------------------------------------
MainFrame::~MainFrame() {
	if (memoryDialog != nullptr) {
		memoryDialog->Destroy();
	}
}

// ------------------------------------------------------------------------------------------------
MainFrame::MainFrame(const wxString &title, const wxPoint &pos,
		const wxSize &size, SIM68K *sim68k) :
		wxFrame((wxFrame*) NULL, -1, title, pos, size) {
	this->sim68k = sim68k;
	// normally we would initialize objects such as buttons and textboxes here
	BuildMenu();
	BuildFrame();
	BuildToolbar();
	SetMinSize(size);
	initSim();
}

// ------------------------------------------------------------------------------------------------
void MainFrame::AddImageToBar(wxToolBar* toolbar, int toolid, wxString path, wxString filename, wxString label) {
	wxString b1 = path.Append(filename);
	wxBitmap p1(b1, wxBITMAP_TYPE_XPM);
	toolbar->AddTool(toolid, label, p1);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::BuildToolbar() {
	//wxStandardPathsBase &mp = wxStandardPaths::Get();
	//wxString path = mp.GetDataDir();
	wxFileName fn;
	wxString path = wxGetCwd();
	std::cout << "std data dir:" << path << "\n";
	path = path.Append("/src/bitmaps/");
	//wxImage::AddHandler(new wxXPMHandler);
	wxInitAllImageHandlers();
	toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
			wxTB_FLAT | wxTB_NODIVIDER | wxTB_TEXT);
	toolbar->SetToolBitmapSize(wxSize(32, 32));
	//open, run, run2cursor, autotrace, step over, trace into, pause, rewind, reload, log start, log stop
	AddImageToBar(toolbar, ID_Open, path, "icon32x32.xpm", wxT("Open"));
	AddImageToBar(toolbar, ID_Run, path, "icon32x32.xpm", wxT("Run"));
	AddImageToBar(toolbar, ID_Run_To_Cursor, path, "icon32x32.xpm", wxT("Run To"));
	AddImageToBar(toolbar, ID_Auto_Trace, path, "icon32x32.xpm", wxT("Trace"));
	AddImageToBar(toolbar, ID_Step_Over, path, "icon32x32.xpm", wxT("Over"));
	AddImageToBar(toolbar, ID_Trace_Into, path, "stepinto32x32.xpm", wxT("Into"));
	AddImageToBar(toolbar, ID_Pause, path, "icon32x32.xpm", wxT("Pause"));
	AddImageToBar(toolbar, ID_Rewind_Program, path, "icon32x32.xpm", wxT("Rewind"));
	AddImageToBar(toolbar, ID_Reload_Program, path, "icon32x32.xpm", wxT("Reload"));
	AddImageToBar(toolbar, ID_Log_Start, path, "icon32x32.xpm", wxT("Log Start"));
	AddImageToBar(toolbar, ID_Log_Stop, path, "icon32x32.xpm", wxT("Log Stop"));

	toolbar->Realize();
	SetToolBar(toolbar);
}

// ------------------------------------------------------------------------------------------------
// Build the main menu
void MainFrame::BuildMenu() {
	mainMenu = new wxMenuBar();
	fileMenu = new wxMenu();
	fileMenu->Append(ID_Open, "&Open", "Open");
	fileMenu->Append(ID_Open_Data, "&Open Data", "Open Data");
	fileMenu->Append(ID_Close, "&Close", "Close");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Printer_Setup, "&Open", "Open");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Exit, "&Exit", "Exit");
	mainMenu->Append(fileMenu, "&File");

	searchMenu = new wxMenu();
	searchMenu->Append(ID_Find, "Find", "Find");
	searchMenu->AppendSeparator();
	searchMenu->Append(ID_GoToPC, "Go To PC", "Go To PC");
	mainMenu->Append(searchMenu, "&Search");

	runMenu = new wxMenu();
	runMenu->Append(ID_Run, "Run", "Run"); //f9
	runMenu->AppendSeparator();
	runMenu->Append(ID_Run_To_Cursor, "Run To Cursor", "Run To Curso"); // ctrl-f9
	runMenu->Append(ID_Auto_Trace, "Auto Trace", ""); // f10
	runMenu->Append(ID_Step_Over, "Step Over", ""); // f8
	runMenu->Append(ID_Trace_Into, "Trace Into", ""); //f7
	runMenu->Append(ID_Pause, "Pause", ""); // f6
	runMenu->AppendSeparator();
	runMenu->Append(ID_Rewind_Program, "Rewind Program", ""); // ctrl-f2
	runMenu->Append(ID_Reload_Program, "Reload Program", ""); // ctrl-f3
	runMenu->AppendSeparator();
	runMenu->Append(ID_Log_Start, "Log Start", ""); // ctrl-f4
	runMenu->Append(ID_Log_Stop, "Log Stop", ""); // ctrl-f5
	mainMenu->Append(runMenu, "&Run");

	viewMenu = new wxMenu();
	viewMenu->Append(ID_Output_Window, "Output", "");
	viewMenu->Append(ID_Memory_Window, "Memory", "");
	viewMenu->Append(ID_Stack_Window, "Stack", "");
	viewMenu->Append(ID_Hardware_Window, "Hardware", "");
	viewMenu->Append(ID_Breakpoints_Window, "Breakpoints", "");
	viewMenu->Append(ID_EASyBIN_Window, "EASyBIN", "");
	mainMenu->Append(viewMenu, "&View");

	optionsMenu = new wxMenu();
	optionsMenu->Append(ID_Source_Window_Font, "Source Window Font", "");
	optionsMenu->Append(ID_Output_Window_Font, "Output Window Font", "");
	optionsMenu->Append(ID_Printer_Font, "Printer Font", "");
	optionsMenu->AppendSeparator();
	optionsMenu->Append(ID_Log_Output, "Log Output", "");
	optionsMenu->AppendSeparator();
	optionsMenu->Append(ID_Auto_Trace_Output, "Auto Trace Output", "");
	optionsMenu->AppendSeparator();
	optionsMenu->Append(ID_Fullscreen_Options, "Fullscreen Options", "");
	optionsMenu->AppendSeparator();
	optionsMenu->Append(ID_Enable_Bit_Field_Options,
			"Enable Bit Field Instructions", "");
	optionsMenu->AppendSeparator();
	optionsMenu->Append(ID_Output_Window_Size, "Output Window Font Size", "");
	optionsMenu->Append(ID_Output_Window_Text_Wrap, "Output Window Text Wrap",
			"");
	mainMenu->Append(optionsMenu, "&Options");

	helpMenu = new wxMenu();
	helpMenu->Append(ID_Help, "&Help", "");
	helpMenu->Append(ID_About, "About SIM68K", "");
	mainMenu->Append(helpMenu, "&Help");
	SetMenuBar(mainMenu);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::CreateBoxTxtEntry(std::string label, wxBoxSizer *rgrid,
		wxTextCtrl *tc) {
	wxBoxSizer *rd0sz = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *rd0p = new wxPanel(this, wxID_ANY, wxDefaultPosition,
			wxDefaultSize);
	if (label.length() > 0) {
		new wxStaticText(rd0p, wxID_ANY, label.c_str(), wxDefaultPosition,
				wxDefaultSize, wxALIGN_LEFT);
		rd0sz->Add(rd0p);
	}
	rd0sz->Add(tc, wxEXPAND, 0);
	rgrid->Add(rd0sz, wxEXPAND);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::CreateLabTxtEntry(std::string label, wxFlexGridSizer *rgrid,
		wxTextCtrl *tc) {
	wxBoxSizer *rd0sz = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *rd0p = new wxPanel(this, wxID_ANY, wxDefaultPosition,
			wxDefaultSize);
	if (label.length() > 0) {
		new wxStaticText(rd0p, wxID_ANY, label.c_str(), wxDefaultPosition,
				wxDefaultSize, wxALIGN_LEFT);
		rd0sz->Add(rd0p);
	}
	rd0sz->Add(tc, wxEXPAND, 0);
	rgrid->Add(rd0sz, wxEXPAND);
}

// ------------------------------------------------------------------------------------------------
// Build the Register group
void MainFrame::BuildRegisterFrame(wxBoxSizer *topsizer) {
	// add the register group (static box)
	wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition,
			wxDefaultSize, wxTAB_TRAVERSAL);
	wxStaticBoxSizer *registerbox = new wxStaticBoxSizer(wxVERTICAL, panel,
			wxT("")); // TODO: fix registers - "reg" only shows

	wxBoxSizer *bx = new wxBoxSizer(wxVERTICAL);

	topsizer->Add(bx, 0, wxEXPAND | wxALL, 5);
	bx->Add(registerbox, 0, wxEXPAND | wxALL, 5);

	// add the 8 x 4 grid
	wxFlexGridSizer *rgrid = new wxFlexGridSizer(4, 8, 1, 1); //row, col, v/h gaps
	registerbox->Add(rgrid, 0, wxEXPAND);

	// add the small sizer, label and textbox
	tcD0 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcD1 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcD2 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcD3 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcD4 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcD5 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcD6 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcD7 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	CreateLabTxtEntry("D0", rgrid, tcD0);
	CreateLabTxtEntry("D1", rgrid, tcD1);
	CreateLabTxtEntry("D2", rgrid, tcD2);
	CreateLabTxtEntry("D3", rgrid, tcD3);
	CreateLabTxtEntry("D4", rgrid, tcD4);
	CreateLabTxtEntry("D5", rgrid, tcD5);
	CreateLabTxtEntry("D6", rgrid, tcD6);
	CreateLabTxtEntry("D7", rgrid, tcD7);

	tcA0 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcA1 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcA2 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcA3 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcA4 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcA5 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcA6 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcA7 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	CreateLabTxtEntry("A0", rgrid, tcA0);
	CreateLabTxtEntry("A1", rgrid, tcA1);
	CreateLabTxtEntry("A2", rgrid, tcA2);
	CreateLabTxtEntry("A3", rgrid, tcA3);
	CreateLabTxtEntry("A4", rgrid, tcA4);
	CreateLabTxtEntry("A5", rgrid, tcA5);
	CreateLabTxtEntry("A6", rgrid, tcA6);
	CreateLabTxtEntry("A7", rgrid, tcA7);

	wxBoxSizer *rd0sz = new wxBoxSizer(wxHORIZONTAL);
	rgrid->Add(rd0sz, 0, wxEXPAND);

	// US, SS, PC, Flags
	tcUS = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcSS = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	tcPC = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
			wxHSCROLL);
	CreateLabTxtEntry("US", rgrid, tcUS);
	CreateLabTxtEntry("SS", rgrid, tcSS);
	CreateLabTxtEntry("PC", rgrid, tcPC);
	rd0sz = new wxBoxSizer(wxHORIZONTAL);
	rgrid->Add(rd0sz, 0, wxEXPAND);

	wxBoxSizer *othersz = new wxBoxSizer(wxHORIZONTAL);

	tcFlags = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
			wxSize(125, -1), wxHSCROLL);
	wxBoxSizer *fsz = new wxBoxSizer(wxHORIZONTAL);
	CreateBoxTxtEntry("Flags", fsz, tcFlags);
	othersz->Add(fsz, 0, wxEXPAND);

	// cycles,cycles button
	tcCycles = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
			wxSize(125, -1), wxHSCROLL);
	wxBoxSizer *csz = new wxBoxSizer(wxHORIZONTAL);
	CreateBoxTxtEntry("Cycles", csz, tcCycles);
	othersz->Add(csz, 0, wxEXPAND);

	bCycles = new wxButton(this, wxID_ANY, _T("Clear Cycles"),
			wxDefaultPosition, wxDefaultSize, 0);
	othersz->Add(bCycles, 0, wxEXPAND);

	bx->Add(othersz, 0, wxEXPAND);
}

// ------------------------------------------------------------------------------------------------
// Build the main frame w/ register layout
void MainFrame::BuildFrame() {
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
	BuildRegisterFrame(topsizer);

	wxSplitterWindow *splittermain = new wxSplitterWindow(this, wxID_ANY);
	splittermain->SetSashGravity(0.5);
	splittermain->SetMinimumPaneSize(20); // Smallest size the

	wxPanel *pnl1 = new wxPanel(splittermain, wxID_ANY);
	pnl1->SetBackgroundColour(wxColour("WHITE"));

	logWindow = new wxTextCtrl(pnl1, wxID_ANY);
	//std::unique_ptr<wxTextCtrl>logWindow = std::make_unique<wxTextCtrl>(pnl1, wxID_ANY);
	wxBoxSizer *txt1sizer = new wxBoxSizer(wxVERTICAL);
	txt1sizer->Add(logWindow, 1, wxEXPAND | wxALL, 2);
	//txt1sizer->Add(logWindow.get(), 1, wxEXPAND | wxALL, 2);
	pnl1->SetSizerAndFit(txt1sizer);

	sourceCodeCtrl = new SourceCtrl(splittermain);

	splittermain->SplitVertically(sourceCodeCtrl, pnl1);
	splittermain->SetSashPosition(200);
	topsizer->Add(splittermain, 1, wxEXPAND);
	SetSizerAndFit(topsizer);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::EnableDisableFunctions(bool flag) { // no source / source loaded
	// TODO:: Enable/Disable
	// see https://forums.wxwidgets.org/viewtopic.php?t=1594
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void MainFrame::OnOpen(wxCommandEvent &event) {
	//TODO: why everything vs only S68
	wxFileDialog openDialog = new wxFileDialog(this, _("Choose a file to open"),
			"", "", _("Code Files (*.S68)|*.S68"),
			wxFD_MULTIPLE);
	if (openDialog.ShowModal() == wxID_CANCEL) {
		return;
	}
	std::string filePath = std::string(openDialog.GetPath());
	fileHandling->loadProgramFile(filePath, memory);
	sourceCodeCtrl->SetScrollAndSize(memory->getNumberOfSourceLines());
	sourceCodeCtrl->Refresh();
	updateRegisters();
	std::string msg("Loaded " + filePath);
	logMsg(msg);
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnOpenData(wxCommandEvent &event) {
	// TODO: OnOpenData
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnClose(wxCommandEvent &event) {
	// TODO: OnClose
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnPrinterSetup(wxCommandEvent &event) {
	// TODO: OnPrinterSetup
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnExit(wxCommandEvent &event) {
	Close();
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnFind(wxCommandEvent &event) {
	// TODO: OnFind
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnGoToPC(wxCommandEvent &event) {
	// TODO: OnGoToPC
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnRun(wxCommandEvent &event) {
	// TODO: OnRun
	runprog();
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnRunToCursor(wxCommandEvent &event) {
	// TODO: OnRunToCursor
	runprog();
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnAutoTrace(wxCommandEvent &event) {
	// TODO: OnAutoTrace
	runprog();
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnStepOver(wxCommandEvent &event) {
	runprog();
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnTraceInto(wxCommandEvent &event) {
	runprog();
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnPause(wxCommandEvent &event) {
	// TODO: OnPause
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnRewindProgram(wxCommandEvent &event) {
	// TODO: OnRewindProgram
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnReloadProgram(wxCommandEvent &event) {
	// TODO: OnReloadProgram
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnLogStart(wxCommandEvent &event) {
	// TODO: OnLogStart
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnLogStop(wxCommandEvent &event) {
	// TODO: OnLogStop
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnOutputWindow(wxCommandEvent &event) {
	// TODO: OnOutputWindow
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnMemoryWindow(wxCommandEvent &event) {
	if (memoryDialog == nullptr) {
		memoryDialog = new MemoryDialog("68000 Memory", wxPoint(1,1), wxSize(350, 250), sim68k);
	}
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnStackWindow(wxCommandEvent &event) {
	// TODO: OnStackWindow
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnHardwareWindow(wxCommandEvent &event) {
	// TODO: OnHardwareWindow
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnBreakpointsWindow(wxCommandEvent &event) {
	// TODO: OnBreakpointsWindow
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnEASyBINWindow(wxCommandEvent &event) {
	// TODO: OnEASyBINWindow
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnSourceWindowFont(wxCommandEvent &event) {
	// TODO: OnSourceWindowFont
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnOutputWindowFont(wxCommandEvent &event) {
	// TODO: OnOutputWindowFont
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnPrinterFont(wxCommandEvent &event) {
	// TODO: OnPrinterFont
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnLogOutput(wxCommandEvent &event) {
	// TODO: OnLogOutput
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnAutoTraceOutput(wxCommandEvent &event) {
	// TODO: OnAutoTraceOutput
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnFullscreenOptions(wxCommandEvent &event) {
	// TODO: OnFullscreenOptions
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnEnableBitFieldOptions(wxCommandEvent &event) {
	// TODO: OnEnableBitFieldOptions
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnOutputWindowSize(wxCommandEvent &event) {
	// TODO: OnOutputWindowSize
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnOutputWindowTextWrap(wxCommandEvent &event) {
	// TODO: OnOutputWindowTextWrap
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnHelp(wxCommandEvent &event) {
	// TODO: OnHelp
}
// ------------------------------------------------------------------------------------------------
void MainFrame::OnAbout(wxCommandEvent &event) {
	// TODO: OnAbout
}

// ------------------------------------------------------------------------------------------------
void MainFrame::updateRegisters(void) {
	UTILS u;
	tcD0->SetValue(u.vformat("%08lX", D[0]));
	tcD1->SetValue(u.vformat("%08lX", D[1]));
	tcD2->SetValue(u.vformat("%08lX", D[2]));
	tcD3->SetValue(u.vformat("%08lX", D[3]));
	tcD4->SetValue(u.vformat("%08lX", D[4]));
	tcD5->SetValue(u.vformat("%08lX", D[5]));
	tcD6->SetValue(u.vformat("%08lX", D[6]));
	tcD7->SetValue(u.vformat("%08lX", D[7]));

	tcA0->SetValue(u.vformat("%08lX", A[0]));
	tcA1->SetValue(u.vformat("%08lX", A[1]));
	tcA2->SetValue(u.vformat("%08lX", A[2]));
	tcA3->SetValue(u.vformat("%08lX", A[3]));
	tcA4->SetValue(u.vformat("%08lX", A[4]));
	tcA5->SetValue(u.vformat("%08lX", A[5]));
	tcA6->SetValue(u.vformat("%08lX", A[6]));
	tcA7->SetValue(u.vformat("%08lX", A[7])); //TODO: fill based on sup or user mode

	tcUS->SetValue(u.vformat("%08lX", A[7]));
	tcSS->SetValue(u.vformat("%08lX", A[8])); // SUP is stored in 8
	tcPC->SetValue(u.vformat("%08lX", PC));

	if (cycles > 0xFFFFFFFFFFFF)
		tcCycles->SetValue("Overflow");
	else
		tcCycles->SetValue(u.vformat("%u", cycles));

	// print each bit of SR
	std::string str = "";
	if (SR & 0x1000000000000000)
		str += "T";
	else
		str += "t";
	str += "0"; //t0 is 0 < 68020
	//         ttsm0iii000xnzvc
	if (SR & 0x0010000000000000)
		str += "S";
	else
		str += "s";
	//         ttsm0iii000xnzvc
	if (SR & 0x0001000000000000)
		str += "M";
	else
		str += "m";
	str += "0";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000010000000000)
		str += "I";
	else
		str += "i";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000001000000000)
		str += "I";
	else
		str += "i";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000000100000000)
		str += "I";
	else
		str += "i";
	str += "000";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000000000010000)
		str += "X";
	else
		str += "x";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000000000010000)
		str += "X";
	else
		str += "x";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000000000001000)
		str += "N";
	else
		str += "n";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000000000000100)
		str += "Z";
	else
		str += "z";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000000000000010)
		str += "V";
	else
		str += "v";
	//         ttsm0iii000xnzvc
	if (SR & 0x0000000000010001)
		str += "C";
	else
		str += "c";

	tcFlags->SetValue(str);
	// If NOT (auto trace AND display is disabled)
	//TODO: fix
//	if (!(autoTraceInProgress && AutoTraceOptions->DisableDisplay->Checked)) {
//		Form1->highlight();              // highlight the instruction
//		Form1->ListBox1->Repaint();
//		StackFrm->updateDisplay();
//		MemoryFrm->Repaint();
//	}

}

// ------------------------------------------------------------------------------------------------
void MainFrame::updateSource(void) {
	wxRect r = sourceCodeCtrl->GetClientRect();
	sourceCodeCtrl->Refresh(true, &r);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::updateUI(void) {
	updateRegisters();
	updateSource();
}

// ------------------------------------------------------------------------------------------------
void MainFrame::logMsg(const std::string& msg) {
	logWindow->SetInsertionPointEnd();
	logWindow->AppendText(msg);
	logWindow->SetInsertionPointEnd();
	logWindow->AppendText(wxT("\n"));
}

// ------------------------------------------------------------------------------------------------
void MainFrame::logMsg(const char* msg) {
	logWindow->SetInsertionPointEnd();
	std::string msgr;
	msgr.append(msg);
	msgr.append("\n");
	logWindow->AppendText(msgr);
}

// ------------------------------------------------------------------------------------------------
bool MainFrame::isTracing(void) {
	return (trace || sstep || stepToAddr != 0 || runToAddr != 0);
}
