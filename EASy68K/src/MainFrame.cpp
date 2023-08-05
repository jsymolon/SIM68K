/*
 * MainFrame.cpp
 *
 *  Created on: Aug 5, 2023
 *      Author: jsymolon
 */
#include "MainFrame.h"

#include <wx/filename.h>
#include <wx/font.h>
#include <wx/log.h>
#include <wx/splitter.h>
#include <wx/stdpaths.h>
#include <wx/toolbar.h>

#include <string>
#include "extern.h"

BEGIN_EVENT_TABLE ( MainFrame, wxFrame ) EVT_MENU(ID_New, MainFrame::OnNew)
EVT_MENU(ID_Open_Data, MainFrame::OnOpenData)
EVT_MENU(ID_Save, MainFrame::OnSave)
EVT_MENU(ID_SaveAs, MainFrame::OnSaveAs)
EVT_MENU(ID_Print, MainFrame::OnPrint)
EVT_MENU(ID_Printer_Setup, MainFrame::OnPrinterSetup)
EVT_MENU(ID_Close, MainFrame::OnClose)
EVT_MENU(ID_Exit, MainFrame::OnExit)

EVT_MENU(ID_Undo, MainFrame::OnUndo)
EVT_MENU(ID_Redo, MainFrame::OnRedo)
EVT_MENU(ID_Cut, MainFrame::OnCut)
EVT_MENU(ID_Copy, MainFrame::OnCopy)
EVT_MENU(ID_Paste, MainFrame::OnPaste)
EVT_MENU(ID_SelectAll, MainFrame::OnSelectAll)
EVT_MENU(ID_Comment, MainFrame::OnComment)
EVT_MENU(ID_Uncomment, MainFrame::OnUnComment)
EVT_MENU(ID_Find, MainFrame::OnFind)
EVT_MENU(ID_FindNext, MainFrame::OnFindNext)
EVT_MENU(ID_Replace, MainFrame::OnReplace)

EVT_MENU(ID_Assemble, MainFrame::OnAssemble)

EVT_MENU(ID_AssemblerOptions, MainFrame::OnAssemblerOptions)
EVT_MENU(ID_EditorOptions, MainFrame::OnEditorOptions)

EVT_MENU(ID_Arrange, MainFrame::OnArrange)
EVT_MENU(ID_Cascade, MainFrame::OnCascade)
EVT_MENU(ID_TileHorz, MainFrame::OnTileHorz)
EVT_MENU(ID_TileVert, MainFrame::OnTileVert)
EVT_MENU(ID_MinimizeAll, MainFrame::OnMinimizeAll)

EVT_MENU(ID_Help, MainFrame::OnHelp)
EVT_MENU(ID_About, MainFrame::OnAbout)
END_EVENT_TABLE()

// ------------------------------------------------------------------------------------------------
MainFrame::MainFrame(const wxString &title, const wxPoint &pos,
		const wxSize &size, EASy68K *easy68k) :
		wxFrame(reinterpret_cast<wxFrame*>( NULL), -1, title, pos, size) {
	this->easy68k = easy68k;
	//props->load("");
	// normally we would initialize objects such as buttons and textboxes here
	BuildMenu();
	//BuildFrame();
	BuildToolbar();
	SetMinSize(size);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::AddImageToBar(wxToolBar *toolbar, int toolid, wxString path,
		wxString filename, wxString label) {
	wxString b1 = path.Append(filename);
//	wxBitmap p1(b1, wxBITMAP_TYPE_XPM);
//	toolbar->AddTool(toolid, label, p1);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::BuildToolbar() {
	//wxStandardPathsBase &mp = wxStandardPaths::Get();
	//wxString path = mp.GetDataDir();
//	wxFileName fn;
//	wxString path = wxGetCwd();
//	std::cout << "std data dir:" << path << "\n";
//	path = path.Append("/src/bitmaps/");
//	//wxImage::AddHandler(new wxXPMHandler);
//	wxInitAllImageHandlers();
//	toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
//			wxTB_FLAT | wxTB_NODIVIDER | wxTB_TEXT);
//	toolbar->SetToolBitmapSize(wxSize(ICON_SIZE, ICON_SIZE));
//	//open, run, run2cursor, autotrace, step over, trace into, pause, rewind, reload, log start, log stop
//	AddImageToBar(toolbar, ID_Open, path, "open32x32.xpm", wxT("Open"));
//	AddImageToBar(toolbar, ID_Run, path, "run32x32.xpm", wxT("Run"));
//	AddImageToBar(toolbar, ID_Run_To_Cursor, path, "runto32x32.xpm",
//			wxT("Run To"));
//	AddImageToBar(toolbar, ID_Auto_Trace, path, "trace32x32.xpm", wxT("Trace"));
//	AddImageToBar(toolbar, ID_Step_Over, path, "stepover32x32.xpm",
//			wxT("Over"));
//	AddImageToBar(toolbar, ID_Trace_Into, path, "stepinto32x32.xpm",
//			wxT("Into"));
//	AddImageToBar(toolbar, ID_Pause, path, "pause32x32.xpm", wxT("Pause"));
//	AddImageToBar(toolbar, ID_Rewind_Program, path, "rewind32x32.xpm",
//			wxT("Rewind"));
//	AddImageToBar(toolbar, ID_Reload_Program, path, "reload32x32.xpm",
//			wxT("Reload"));
//	AddImageToBar(toolbar, ID_Log_Start, path, "logon32x32.xpm",
//			wxT("Log Start"));
//	AddImageToBar(toolbar, ID_Log_Stop, path, "logoff32x32.xpm",
//			wxT("Log Stop"));
//
//	toolbar->Realize();
//	SetToolBar (toolbar);
}

// ------------------------------------------------------------------------------------------------
// Build the main menu
void MainFrame::BuildMenu() {
//	mainMenu = new wxMenuBar();
//	fileMenu = new wxMenu();
//	fileMenu->Append(ID_Open, "&Open", "Open");
//	fileMenu->Append(ID_Open_Data, "&Open Data", "Open Data");
//	fileMenu->Append(ID_Close, "&Close", "Close");
//	fileMenu->AppendSeparator();
//	fileMenu->Append(ID_Printer_Setup, "&Open", "Open");
//	fileMenu->AppendSeparator();
//	fileMenu->Append(ID_Exit, "&Exit", "Exit");
//	mainMenu->Append(fileMenu, "&File");
//
//	helpMenu = new wxMenu();
//	helpMenu->Append(ID_Help, "&Help", "");
//	helpMenu->Append(ID_About, "About SIM68K", "");
//	mainMenu->Append(helpMenu, "&Help");
//	SetMenuBar(mainMenu);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnNew(wxCommandEvent &event) {
	// TODO: OnNew
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnOpenData(wxCommandEvent &event) {
	// TODO: OnOpenData
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnSave(wxCommandEvent &event) {
	// TODO: OnSave
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnSaveAs(wxCommandEvent &event) {
	// TODO: OnSaveAs
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnPrint(wxCommandEvent &event) {
	// TODO: OnPrint
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnPrinterSetup(wxCommandEvent &event) {
	// TODO: OnPrinterSetup
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnClose(wxCommandEvent &event) {
	// TODO: OnClose
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnExit(wxCommandEvent &event) {
	// TODO: OnExit
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnUndo(wxCommandEvent &event) {
	// TODO: OnUndo
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnRedo(wxCommandEvent &event) {
	// TODO: OnRedo
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnCut(wxCommandEvent &event) {
	// TODO: OnCut
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnCopy(wxCommandEvent &event) {
	// TODO: OnCopy
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnPaste(wxCommandEvent &event) {
	// TODO: OnPaste
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnSelectAll(wxCommandEvent &event) {
	// TODO: OnSelectAll
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnComment(wxCommandEvent &event) {
	// TODO: OnComment
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnUnComment(wxCommandEvent &event) {
	// TODO: OnUnComment
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnFind(wxCommandEvent &event) {
	// TODO: OnFind
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnFindNext(wxCommandEvent &event) {
	// TODO: OnFindNext
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnReplace(wxCommandEvent &event) {
	// TODO: OnReplace
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnAssemble(wxCommandEvent &event) {
	// TODO: OnAssemble
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnAssemblerOptions(wxCommandEvent &event) {
	// TODO: OnAssemblerOptions
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnEditorOptions(wxCommandEvent &event) {
	// TODO: OnEditorOptions
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnArrange(wxCommandEvent &event) {
	// TODO: OnArrange
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnCascade(wxCommandEvent &event) {
	// TODO: OnCascade
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnTileHorz(wxCommandEvent &event) {
	// TODO: OnTileHorz
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnTileVert(wxCommandEvent &event) {
	// TODO: OnTileVert
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnMinimizeAll(wxCommandEvent &event) {
	// TODO: OnMinimizeAll
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnHelp(wxCommandEvent &event) {
	// TODO: OnHelp
}

// ------------------------------------------------------------------------------------------------
void MainFrame::OnAbout(wxCommandEvent &event) {
	// TODO: OnAbout
}
