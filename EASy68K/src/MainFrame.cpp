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
	props->load("");
	BuildMenu();
	BuildFrame();
	BuildToolbar();
	SetMinSize(size);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::AddImageToBar(wxToolBar *toolbar, int toolid, wxString path,
		wxString filename, wxString label) {
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
	toolbar->SetToolBitmapSize(wxSize(ICON_SIZE, ICON_SIZE));

	AddImageToBar(toolbar, ID_New, path, "new.png", wxT("New"));
	AddImageToBar(toolbar, ID_Open, path, "folder.png", wxT("Open"));
	AddImageToBar(toolbar, ID_Save, path, "save.png", wxT("Save"));
	AddImageToBar(toolbar, ID_Print, path, "print.png", wxT("Print"));
	AddImageToBar(toolbar, ID_Find, path, "search.png", wxT("Find"));
	AddImageToBar(toolbar, ID_Cut, path, "scissors.png", wxT("Cut"));
	AddImageToBar(toolbar, ID_Copy, path, "copy.png", wxT("Copy"));
	AddImageToBar(toolbar, ID_Paste, path, "paste.png", wxT("Paste"));
	AddImageToBar(toolbar, ID_Undo, path, "undo_blue.png", wxT("Undo"));
	AddImageToBar(toolbar, ID_Redo, path, "redo_blue.png", wxT("Redo"));
	AddImageToBar(toolbar, ID_Comment, path, "comment.png", wxT("Comment"));
	AddImageToBar(toolbar, ID_Uncomment, path, "uncomment.png",
			wxT("Uncomment"));
	AddImageToBar(toolbar, ID_Assemble, path, "run32x32.png", wxT("Assemble"));

	toolbar->Realize();
	SetToolBar(toolbar);
}

// ------------------------------------------------------------------------------------------------
// Build the main menu
void MainFrame::BuildMenu() {
	mainMenu = new wxMenuBar();

	fileMenu = new wxMenu();
	fileMenu->Append(ID_New, "&New X68 Source File", "New X68 Source File");
	fileMenu->Append(ID_Open, "&Open", "Open");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Save, "&Save", "Save");
	fileMenu->Append(ID_SaveAs, "&Save As", "Save As");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Print, "&Print", "Print");
	fileMenu->Append(ID_Printer_Setup, "&Printer Setup", "Printer Setup");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Close, "&Close File", "Close File");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Exit, "&Exit", "Exit");
	mainMenu->Append(fileMenu, "&File");

	editMenu = new wxMenu();
	editMenu->Append(ID_Undo, "&Undo", "Undo");
	editMenu->Append(ID_Redo, "&Redo", "Redo");
	editMenu->AppendSeparator();
	editMenu->Append(ID_Cut, "&Cut", "Cut");
	editMenu->Append(ID_Copy, "&Copy", "Copy");
	editMenu->Append(ID_Paste, "&Paste", "Paste");
	editMenu->Append(ID_SelectAll, "&Select All", "Select All");
	editMenu->AppendSeparator();
	editMenu->Append(ID_Comment, "&Comment Selection", "Comment Selection");
	editMenu->Append(ID_Uncomment, "&Uncomment Selection",
			"Uncomment Selection");
	editMenu->AppendSeparator();
	editMenu->Append(ID_Find, "&Find", "Find");
	editMenu->Append(ID_FindNext, "&Find Next", "Find Next");
	editMenu->Append(ID_Replace, "&Replace", "Replace");
	mainMenu->Append(editMenu, "&Edit");

	projectMenu = new wxMenu();
	projectMenu->Append(ID_Assemble, "&Assemble Source ...", "Assemble Source");
	mainMenu->Append(projectMenu, "&Project");

	optionsMenu = new wxMenu();
	optionsMenu->Append(ID_AssemblerOptions, "&Assembler Options",
			"Assembler Options ...");
	optionsMenu->AppendSeparator();
	optionsMenu->Append(ID_EditorOptions, "&Editor Options",
			"Editor Options ...");
	mainMenu->Append(optionsMenu, "&Options");

	windowMenu = new wxMenu();
	windowMenu->Append(ID_Arrange, "&Arrange", "Arrange");
	windowMenu->Append(ID_Cascade, "&Cascade", "Cascade");
	windowMenu->Append(ID_TileHorz, "&Tile Horzontally", "Tile Horizontally");
	windowMenu->Append(ID_TileVert, "&Tile Vertically", "Tile Vertically");
	windowMenu->Append(ID_MinimizeAll, "&Minimize", "Minimize All");
	windowMenu->AppendSeparator();
	mainMenu->Append(windowMenu, "&Window");

	helpMenu = new wxMenu();
	helpMenu->Append(ID_Help, "&Help", "Help");
	helpMenu->AppendSeparator();
	helpMenu->Append(ID_About, "About SIM68K", "");
	mainMenu->Append(helpMenu, "&Help");
	SetMenuBar(mainMenu);
}

// ------------------------------------------------------------------------------------------------
// Build the main frame w/ register layout
void MainFrame::BuildFrame() {
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	sourceCodeCtrl = new SourceCtrl(this);
	topsizer->Add(sourceCodeCtrl, 1, wxEXPAND | wxALL);
	SetSizer(topsizer);

	statusBar = new wxStatusBar(this, wxID_ANY, wxST_SIZEGRIP);
	this->SetStatusBar(statusBar);
	//int widths[] = { 60, 60, -1 };
	//statusBar->SetFieldWidths(WXSIZEOF(widths), widths);
	statusBar->SetStatusText(wxT("Ready"), 0);
}

// ------------------------------------------------------------------------------------------------
void MainFrame::ChangeFont(wxPanel *panel, const Properties *const props) {
	wxFont font(wxFontInfo(12).FaceName("Liberation Mono").Italic());
	panel->SetFont(font);
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
