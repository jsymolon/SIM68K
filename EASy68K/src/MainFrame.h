/*
 * MainFrame.h
 *
 *  Created on: Aug 5, 2023
 *      Author: jsymolon
 */

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//#include <wx/file.h>
//#include <wx/filename.h>
//#include <wx/gdicmn.h>
//#include <wx/menu.h>
//#include <wx/menuitem.h>
//#include <wx/sizer.h>
//#include <wx/textctrl.h>
#include <wx/toolbar.h>

#include <memory>
#include <string>

#include "SourceEditCtrl.h"
#include "LogCtrl.h"
#include "Properties.h"
#include "Options.h"

const int16_t ICON_SIZE = 32;

class EASy68K;
class MainFrame: public wxFrame {
public:

	MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
			EASy68K *easy68k);

	void AddImageToBar(wxToolBar *toolbar, int toolid, wxString path,
			wxString filename, wxString label);

	void BuildToolbar();
	void BuildMenu();
	void BuildFrame();
	void ChangeFont(wxPanel *panel, const Properties *const props);

	void OnNew(wxCommandEvent &event);
	void OnOpen(wxCommandEvent &event);
	void OnSave(wxCommandEvent &event);
	void OnSaveAs(wxCommandEvent &event);
	void OnPrint(wxCommandEvent &event);
	void OnPrinterSetup(wxCommandEvent &event);
	void OnClose(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	void OnUndo(wxCommandEvent &event);
	void OnRedo(wxCommandEvent &event);
	void OnCut(wxCommandEvent &event);
	void OnCopy(wxCommandEvent &event);
	void OnPaste(wxCommandEvent &event);
	void OnSelectAll(wxCommandEvent &event);
	void OnComment(wxCommandEvent &event);
	void OnUnComment(wxCommandEvent &event);
	void OnFind(wxCommandEvent &event);
	void OnFindNext(wxCommandEvent &event);
	void OnReplace(wxCommandEvent &event);
	void OnAssemble(wxCommandEvent &event);
	void OnAssemblerOptions(wxCommandEvent &event);
	void OnEditorOptions(wxCommandEvent &event);
	void OnArrange(wxCommandEvent &event);
	void OnCascade(wxCommandEvent &event);
	void OnTileHorz(wxCommandEvent &event);
	void OnTileVert(wxCommandEvent &event);
	void OnMinimizeAll(wxCommandEvent &event);
	void OnHelp(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);

protected:
	EASy68K *easy68k;
	SourceEditCtrl *sourceCodeCtrl;
	LogCtrl *logCtrl;
	std::unique_ptr<Options> options;

//	wxMenuBar *mainMenu;
//	wxMenu *fileMenu;
//	wxMenu *editMenu;
//	wxMenu *projectMenu;
//	wxMenu *optionsMenu;
//	wxMenu *windowMenu;
//	wxMenu *helpMenu;
//
//	wxToolBar *toolbar;
//
//	wxStatusBar *statusBar;
//	Properties *props = new Properties();
//	wxString srcFilePath;
//	wxFile *tempFile = nullptr;

DECLARE_EVENT_TABLE()

private:
	static inline const std::string menu_file = "File";
	static inline const std::string menu_new = "New X68 Source FIle";
	static inline const std::string menu_open_file = "Open File";
	static inline const std::string menu_save = "Save";
	static inline const std::string menu_save_as = "Save As";
	static inline const std::string menu_print = "Print";
	static inline const std::string menu_printer_setup = "Printer Setup";
	static inline const std::string menu_close = "Close File";
	static inline const std::string menu_exit = "Exit";

	static inline const std::string menu_edit = "Edit";
	static inline const std::string menu_undo = "Undo";
	static inline const std::string menu_redo = "Redo";
	static inline const std::string menu_cut = "Cut";
	static inline const std::string menu_copy = "Copy";
	static inline const std::string menu_paste = "Paste";
	static inline const std::string menu_select_all = "Select All";
	static inline const std::string menu_comment = "Comment Section";
	static inline const std::string menu_uncomment = "Uncomment Section";
	static inline const std::string menu_find = "Find";
	static inline const std::string menu_find_next = "Find Next";
	static inline const std::string menu_replace = "Find And Replace";

	static inline const std::string menu_project = "Project";
	static inline const std::string menu_assemble = "Assemble Source";

	static inline const std::string menu_options = "Options";
	static inline const std::string menu_assembler_options = "Assembler Options";
	static inline const std::string menu_editor_options = "Editor Options";

	static inline const std::string menu_window = "Window";
	static inline const std::string menu_arrange = "Arrange";
	static inline const std::string menu_cascade = "Cascade";
	static inline const std::string menu_tile_horz = "Tile Horizontally";
	static inline const std::string menu_tile_vert = "Tile Vertically";
	static inline const std::string menu_minimize = "Minimize All";

	static inline const std::string menu_help = "Help";
	static inline const std::string menu_help_easy68k = "Help";
	static inline const std::string menu_about = "About";
};

enum {
	// File
	ID_Open = wxID_HIGHEST + 1,
	ID_New,
	ID_Save,
	ID_SaveAs,
	ID_Print,
	ID_Printer_Setup,
	ID_Close,
	ID_Exit,
	ID_Undo,
	ID_Redo,
	ID_Cut,
	ID_Copy,
	ID_Paste,
	ID_SelectAll,
	ID_Comment,
	ID_Uncomment,
	ID_Find,
	ID_FindNext,
	ID_Replace,
	ID_Assemble,
	ID_AssemblerOptions,
	ID_EditorOptions,
	ID_Arrange,
	ID_Cascade,
	ID_TileHorz,
	ID_TileVert,
	ID_MinimizeAll,
	ID_Help,
	ID_About,

// -- --
	ID_TEST_FRAME = 200,
	ID_WINDOW_TOP,
	ID_WINDOW_BOTTOM,
};

#endif /* MAINFRAME_H_ */
