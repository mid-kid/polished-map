#ifndef PALETTE_WINDOW_H
#define PALETTE_WINDOW_H

#pragma warning(push, 0)
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#pragma warning(pop)

#include "tileset.h"
#include "map-buttons.h"
#include "palette-map.h"
#include "metatile.h"
#include "widgets.h"

class Swatch_Window : public Fl_Double_Window {
public:
	Swatch_Window(int x, int y, int w, int h, const char *l = NULL);
	int handle(int event);
};

class Abstract_Palette_Window {
protected:
	int _dx, _dy;
	Palettes _current_palettes;
	bool _canceled;
	Swatch_Window *_window;
	Color_Button *_selected, *_chosen;
	Default_Spinner *_red_spinner, *_green_spinner, *_blue_spinner;
	Default_Button *_ok_button;
	OS_Button *_cancel_button;
	friend class Swatch_Window;
	bool _copied;
	uchar _clipboard[NUM_CHANNELS];
	bool _debounce;
public:
	Abstract_Palette_Window(int x, int y);
	virtual ~Abstract_Palette_Window();
protected:
	void initialize(void);
	virtual void initial_setup(void) = 0;
	virtual void refresh(void) = 0;
public:
	inline void current_palettes(Palettes l) { _current_palettes = l; }
	inline bool canceled(void) const { return _canceled; }
	inline void canceled(bool c) { _canceled = c; }
	void show(const Fl_Widget *p);
	virtual void apply_modifications(void) = 0;
	void select(Color_Button *cb);
protected:
	static void close_cb(Fl_Widget *w, Abstract_Palette_Window *alw);
	static void cancel_cb(Fl_Widget *w, Abstract_Palette_Window *alw);
	static void select_color_cb(Color_Button *cb, Abstract_Palette_Window *alw);
	static void change_red_cb(Default_Spinner *sp, Abstract_Palette_Window *alw);
	static void change_green_cb(Default_Spinner *sp, Abstract_Palette_Window *alw);
	static void change_blue_cb(Default_Spinner *sp, Abstract_Palette_Window *alw);
	static void copy_color_cb(Fl_Widget *w, Abstract_Palette_Window *alw);
	static void paste_color_cb(Fl_Widget *w, Abstract_Palette_Window *alw);
	static void swap_colors_cb(Fl_Widget *w, Abstract_Palette_Window *alw);
};

class Palette_Window : public Abstract_Palette_Window {
private:
	Fl_Group *_palette_heading_group, *_color_group;
	Color_Button *_color_buttons[NUM_GAME_PALETTES][NUM_HUES];
public:
	Palette_Window(int x, int y);
	~Palette_Window();
private:
	void initial_setup(void);
	void refresh(void);
public:
	void apply_modifications(void);
};

class Monochrome_Palette_Window : public Abstract_Palette_Window {
private:
	Label *_palette_heading;
	Fl_Group *_color_group;
	Color_Button *_color_buttons[NUM_HUES];
public:
	Monochrome_Palette_Window(int x, int y);
	~Monochrome_Palette_Window();
private:
	void initial_setup(void);
	void refresh(void);
public:
	void apply_modifications(void);
};

#endif
