/*
 * MainFrame.h
 *
 *  Created on: May 17, 2021
 *      Author: jsymolon
 */

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include <wx/wx.h>
#include <wx/gdicmn.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/toolbar.h>

#include <string>
#include "SourceCtrl.h"
#include "LogCtrl.h"
#include "Properties.h"

class SIM68K;
class MemoryDialog;

const uint16_t SR_TRACE = 0b1000000000000000;
const uint16_t SR_SUPER = 0b0010000000000000;
const uint16_t SR_MINT = 0b0001000000000000;
const uint16_t SR_INTPM1 = 0b0000010000000000;
const uint16_t SR_INTPM2 = 0b0000001000000000;
const uint16_t SR_INTPM3 = 0b0000000100000000;
const uint16_t SR_EXT = 0b0000000000010000;
const uint16_t SR_NEG = 0b0000000000001000;
const uint16_t SR_ZERO = 0b0000000000000100;
const uint16_t SR_OVER = 0b0000000000000010;
const uint16_t SR_CARRY = 0b0000000000000001;

const int16_t ICON_SIZE = 32;

class MainFrame: public wxFrame {
public:

	MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size, SIM68K *sim68k);
	virtual ~MainFrame();

	void BuildToolbar();
	void BuildMenu();
	void CreateBoxTxtEntry(std::string label, wxBoxSizer *rgrid, wxTextCtrl *tc);
	void CreateLabTxtEntry(std::string label, wxFlexGridSizer *rgrid, wxTextCtrl *tc);
	void BuildRegisterFrame(wxBoxSizer *topsizer);
	void BuildFrame();

	void ChangeFont(wxControl *control, const Properties *const props);
	void ChangeFont(wxPanel *panel, const Properties *const props);
	void ChangeFont(wxPanel *panel, wxFont font);

	void EnableDisableFunctions(bool flag); // no source / source loaded

	// File
	void OnOpen(wxCommandEvent &event);
	void OnOpenData(wxCommandEvent &event);
	void OnClose(wxCommandEvent &event);
	void OnPrinterSetup(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);

	// Search
	void OnFind(wxCommandEvent &event);
	void OnGoToPC(wxCommandEvent &event);

	// Run
	void OnRun(wxCommandEvent &event);
	void OnRunToCursor(wxCommandEvent &event);
	void OnAutoTrace(wxCommandEvent &event);
	void OnStepOver(wxCommandEvent &event);
	void OnTraceInto(wxCommandEvent &event);
	void OnPause(wxCommandEvent &event);
	void OnRewindProgram(wxCommandEvent &event);
	void OnReloadProgram(wxCommandEvent &event);
	void OnLogStart(wxCommandEvent &event);
	void OnLogStop(wxCommandEvent &event);

	// View
	void OnOutputWindow(wxCommandEvent &event);
	void OnMemoryWindow(wxCommandEvent &event);
	void OnStackWindow(wxCommandEvent &event);
	void OnHardwareWindow(wxCommandEvent &event);
	void OnBreakpointsWindow(wxCommandEvent &event);
	void OnEASyBINWindow(wxCommandEvent &event);

	// Options
	void OnSourceWindowFont(wxCommandEvent &event);
	void OnOutputWindowFont(wxCommandEvent &event);
	void OnPrinterFont(wxCommandEvent &event);
	void OnLogOutput(wxCommandEvent &event);
	void OnAutoTraceOutput(wxCommandEvent &event);
	void OnFullscreenOptions(wxCommandEvent &event);
	void OnEnableBitFieldOptions(wxCommandEvent &event);
	void OnOutputWindowSize(wxCommandEvent &event);
	void OnOutputWindowTextWrap(wxCommandEvent &event);

	// Help
	void OnHelp(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);

	void updateRegisters(void); // move the data from .. to the display
	void updateSource(void);
	void updateUI(void);

	void logMsg(const std::string &msg);
	void logMsg(const char *msg);
	void setStatusMsg(const std::string &msg);

	bool isTracing(void);

protected:
	SIM68K *sim68k;
	SourceCtrl *sourceCodeCtrl;
	LogCtrl *logCtrl;

	wxMenuBar *mainMenu;
	wxMenu *fileMenu;
	wxMenu *searchMenu;
	wxMenu *runMenu;
	wxMenu *viewMenu;
	wxMenu *optionsMenu;
	wxMenu *helpMenu;

	wxToolBar *toolbar;

	wxStatusBar *statusBar;
	Properties *props = new Properties();

	wxTextCtrl *tcD0;
	wxTextCtrl *tcD1;
	wxTextCtrl *tcD2;
	wxTextCtrl *tcD3;
	wxTextCtrl *tcD4;
	wxTextCtrl *tcD5;
	wxTextCtrl *tcD6;
	wxTextCtrl *tcD7;

	wxTextCtrl *tcA0;
	wxTextCtrl *tcA1;
	wxTextCtrl *tcA2;
	wxTextCtrl *tcA3;
	wxTextCtrl *tcA4;
	wxTextCtrl *tcA5;
	wxTextCtrl *tcA6;
	wxTextCtrl *tcA7;

	wxTextCtrl *tcUS;
	wxTextCtrl *tcSS;
	wxTextCtrl *tcPC;
	wxTextCtrl *tcFlags;

	wxTextCtrl *tcCycles;
	wxButton *bCycles;

	void AddImageToBar(wxToolBar *toolbar, int toolid, wxString path, wxString filename, wxString label);

	MemoryDialog *memoryDialog = nullptr;

DECLARE_EVENT_TABLE()

private:
	static inline const std::string menu_file = "File";
	static inline const std::string menu_open = "Open";
	static inline const std::string menu_open_data = "Open Data";
	static inline const std::string menu_close = "Close";
	static inline const std::string menu_printer_setup = "Printer Setup";
	static inline const std::string menu_exit = "Exit";
	static inline const std::string menu_search = "Search";
	static inline const std::string menu_find = "Find";
	static inline const std::string menu_gotopc = "GoToPC";
	static inline const std::string menu_run = "Run";  // menu AND item
	static inline const std::string menu_run_to_cursor = "Run To Cursor";
	static inline const std::string menu_auto_trace = "Auto Trace";
	static inline const std::string menu_step_over = "Step Over";
	static inline const std::string menu_trace_into = "Trace Into";
	static inline const std::string menu_pause = "Pause";
	static inline const std::string menu_rewind_program = "Rewind Program";
	static inline const std::string menu_reload_program = "Reload Program";
	static inline const std::string menu_log_start = "Log_Start";
	static inline const std::string menu_log_stop = "Log_Stop";
	static inline const std::string menu_view = "View";
	static inline const std::string menu_output_window = "Output";
	static inline const std::string menu_memory_window = "Memory";
	static inline const std::string menu_stack_window = "Stack";
	static inline const std::string menu_hardware_window = "Hardware";
	static inline const std::string menu_breakpoints_window = "Breakpoints";
	static inline const std::string menu_easybin = "EASyBIN";
	static inline const std::string menu_options = "Options";
	static inline const std::string menu_source_window_font = "Source Window Font";
	static inline const std::string menu_output_window_font = "Output Window Font";
	static inline const std::string menu_printer_font = "Printer Font";
	static inline const std::string menu_log_output = "Log Output";
	static inline const std::string menu_auto_trace_output = "Auto Trace Output";
	static inline const std::string menu_fullscreen_options = "Fullscreen Options";
	static inline const std::string menu_enable_bit_field = "Enable Bit Field Options";
	static inline const std::string menu_output_window_text_size = "Output Window Size";
	static inline const std::string menu_output_window_text_wrap = "Output Window Text Wrap";
	static inline const std::string menu_help = "Help";
	static inline const std::string menu_help_sim68k = "Help SIM68K";
	static inline const std::string menu_about = "About";
};

enum {
	// File
	ID_Open = wxID_HIGHEST + 1,
	ID_Open_Data,
	ID_Close,
	// --
	ID_Printer_Setup,
	// --
	ID_Exit,

	// Search
	ID_Find,
	// --
	ID_GoToPC,
	// Run
	ID_Run, //f9
	// --
	ID_Run_To_Cursor, // ctrl-f9
	ID_Auto_Trace, // f10
	ID_Step_Over, // f8
	ID_Trace_Into, //f7
	ID_Pause, // f6
	// --
	ID_Rewind_Program, // ctrl-f2
	ID_Reload_Program, // ctrl-f3
	// --
	ID_Log_Start, // ctrl-f4
	ID_Log_Stop, // ctrl-f5

	// View
	ID_Output_Window,
	ID_Memory_Window,
	ID_Stack_Window,
	ID_Hardware_Window,
	ID_Breakpoints_Window,
	ID_EASyBIN_Window,

	// Options
	ID_Source_Window_Font,
	ID_Output_Window_Font,
	ID_Printer_Font,
	// --
	ID_Log_Output,
	// --
	ID_Auto_Trace_Output,
	// --
	ID_Fullscreen_Options,
	// --
	ID_Enable_Bit_Field_Options,
	// --
	ID_Output_Window_Size,
	ID_Output_Window_Text_Wrap,
	// Help
	ID_Help,
	ID_About,

	// -- Registers --
	ID_RD0 = 100,
	ID_RD1,
	ID_RD2,
	ID_RD3,
	ID_RD4,
	ID_RD5,
	ID_RD6,
	ID_RD7,
	ID_RA0,
	ID_RA1,
	ID_RA2,
	ID_RA3,
	ID_RA4,
	ID_RA5,
	ID_RA6,
	ID_RA7,
	ID_RUS,
	ID_RSS,
	ID_RPC,
	ID_Cycles,
	ID_B_Cycles,

	// -- --
	ID_TEST_FRAME = 200,
	ID_WINDOW_TOP,
	ID_WINDOW_BOTTOM,

};

#endif /* MAINFRAME_H_ */
