#include "Graphics.h"

namespace ooe
{
	bool Graphics::instance_flag_;
	Graphics* Graphics::instance_;
	uint16 Graphics::width_ = 0;
	uint16 Graphics::height_ = 0;

	Graphics& Graphics::getInstance()
	{
		if(!instance_flag_) {
			instance_ = new Graphics;
			instance_flag_ = true;
		}

		return *instance_;
	}

	Graphics::Graphics() : pntr2screen_(nullptr)
	{
	}

	Graphics::Graphics(const Graphics& copy)
	{
		copyGraphics(copy);
	}

	Graphics::~Graphics()
	{
		pntr2screen_ = nullptr;
	}

	void Graphics::clearColour(HAPI_TColour colour)
	{
		uint32 buffer_size = gfx.width_ * gfx.height_ * 4;

		//Fast Clear if RGB channels are all the same -> Colour's either black, grey or white
		if (colour.blue & colour.green & colour.red ||
			(colour.blue == colour.green == colour.red == 0))
		{
			memset(pntr2screen_.get(), colour.red, buffer_size);
			return;
		}

		//Clear screen to colour passed in
		uchar* pntr2screen = pntr2screen_.get();
		uint32 col = (colour.alpha << 24 | colour.red << 16 | colour.green << 8 | colour.blue);
		uint32* screenPtr = (uint32*)pntr2screen_.get();

		for (uint32 idx = 0; idx < buffer_size; idx += 4) {
			memcpy(screenPtr, &col, 4);
			++screenPtr;
		}
	}

	void Graphics::draw(vec2 position, uint16 id, Rectangle frame_dimen, uint16 frame)
	{
		if (id < 0) {
			return;
		}

		auto screen = Rectangle(0, 0, width_, height_);
		position = vec2(roundToInt(position.i), roundToInt(position.j));
		sprites_[id].blit(position, pntr2screen_.get(), width_, height_, screen, frame_dimen, frame);
	}

	void Graphics::quickdraw(vec2 position, uint16 id)
	{
		if (id < 0) {
			return;
		}

		auto screen = Rectangle(0, 0, width_, height_);
		position = vec2(roundToInt(position.i), roundToInt(position.j));
		sprites_[id].quickBlit(position, pntr2screen_.get(), width_, height_, screen);
	}

	bool Graphics::init(uint16 width, uint16 height, bool fullscreen)
	{
		int w = (int)width;
		int h = (int)height; 

		if (fullscreen && !HAPI->Initialise(&w, &h, HAPI_INIT_FULLSCREEN)) {
			return false;
		} else if (!HAPI->Initialise(&w, &h)) {
			return false;
		}

		height_ = h;
		width_ = w;
		pntr2screen_ = std::unique_ptr<uchar>(HAPI->GetScreenPointer());

		return true;
	}

	bool Graphics::load(const std::string& name, uint16& id)
	{
		id = sprites_.size();
		Sprite newsprite;

		HAPI_UserResponse response;

		if (!newsprite.loadSprite(name)) {

			HAPI->UserMessage("Failed to load texture: "+name, "Error!", eButtonTypeOkCancel, &response);

			while(response)	{
				if (eUserResponseOk) {
					return false;
				}
				HAPI->Close();
				return false;
			}
		}
		sprites_.push_back(newsprite);

		return true;
	}

	const Rectangle& Graphics::spriteDimensions(const uint16 id) const
	{
		return sprites_[id].dimensions();
	}

	Star& Graphics::star()
	{
		return star_;
	}

	uint32 Graphics::spriteFrames(const uint16 id) const
	{
		return sprites_[id].frames();
	}

	const Graphics& Graphics::operator=(const Graphics& copy)
	{
		if (this != &copy)
		{
			copyGraphics(copy);
		}

		return *this;
	} 

	void Graphics::copyGraphics(const Graphics& copy)
	{	
		height_ = copy.height_;
		width_ = copy.width_;

		sprites_ = copy.sprites_;
		star_ = copy.star_;

		pntr2screen_.reset(copy.pntr2screen_.get());
	}
}