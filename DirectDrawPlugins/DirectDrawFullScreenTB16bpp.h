// DirectDrawFullScreenTB16bpp.h
//
//	Class that implements a DirectDraw FullScreen 16bpp mode using triple buffer
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _DIRECT_DRAW_FULLSCREEN_TB_16BPP_H_
#define _DIRECT_DRAW_FULLSCREEN_TB_16BPP_H_


#include "DirectDrawFullScreen.h"
#include "util/INotificationSuscriber.h"

class DirectDrawFullScreenTB16bpp : public DirectDrawFullScreen, public INotificationSuscriber<IPalette>
{
// fields
protected:
	LPDIRECTDRAWSURFACE _backBuf;
	IPalette *_originalPalette;
	UINT16 *_palette;

// inherited methods
public:
	// initialization and cleanup
	DirectDrawFullScreenTB16bpp(Win32Settings *settings);
	virtual ~DirectDrawFullScreenTB16bpp();
	virtual bool init(const VideoInfo *vi, IPalette *pal);
	virtual void end();

	// drawing functions
	virtual void render(bool throttle);

	virtual void setPixel(int x, int y, int color);

	virtual void drawGfx(GfxElement *gfx, int code, int color, int x, int y, int attr);
	virtual void drawGfxClip(GfxElement *gfx, int code, int color, int x, int y, int attr);
	virtual void drawGfxTrans(GfxElement *gfx, int code, int color, int x, int y, int attr, int transData);
	virtual void drawGfxClipTrans(GfxElement *gfx, int code, int color, int x, int y, int attr, int transData);

protected:
	// palette changed notification
	virtual void update(IPalette *palette, int data);
	void updateFullPalette(IPalette *palette);
};


#endif // _DIRECT_DRAW_FULLSCREEN_TB_16BPP_H
