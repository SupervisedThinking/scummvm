/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "common/scummsys.h"
#include "engines/util.h"
#include "graphics/palette.h"
#include "mads/mads.h"
#include "mads/msurface.h"
#include "mads/staticres.h"

namespace MADS {

#define VGA_COLOR_TRANS(x) ((x) * 255 / 63)

void RGB6::load(Common::SeekableReadStream *f) {
	r = VGA_COLOR_TRANS(f->readByte());
	g = VGA_COLOR_TRANS(f->readByte());
	b = VGA_COLOR_TRANS(f->readByte());
	_palIndex = f->readByte();
	_u2 = f->readByte();
	_flags = f->readByte();
}

/*------------------------------------------------------------------------*/

PaletteUsage::PaletteUsage(MADSEngine *vm) {
	_vm = vm;
}

void PaletteUsage::load(int count, ...) {
	va_list va;
	va_start(va, count);

	_data.clear();
	for (int i = 0; i < count; ++i)
		_data.push_back(UsageEntry(va_arg(va, int)));

	va_end(va);
}


void PaletteUsage::getKeyEntries(Common::Array<RGB6> &palette) {
	_data.clear();

	 for (uint i = 0; i < palette.size(); ++i) {
		 byte *uPtr = &palette[i]._flags;
		 if ((*uPtr & 0x10) && _data.size() < 3) {
			 _data.push_back(UsageEntry(i));
		 }
	 }
}

static bool sortHelper(const PaletteUsage::UsageEntry &ue1, const PaletteUsage::UsageEntry &ue2) {
	return ue1._sortValue < ue2._sortValue;
}

void PaletteUsage::prioritize(Common::Array<RGB6> &palette) {
	for (uint i = 0; i < _data.size(); ++i) {
		RGB6 &palEntry = palette[_data[i]._palIndex];
		_data[i]._sortValue = rgbMerge(palEntry);
	}
	
	Common::sort(_data.begin(), _data.end(), sortHelper);
}

static bool rangeSorter(const PaletteUsage::UsageRange &ur1, const PaletteUsage::UsageRange &ur2) {
	return ur1._v2 < ur2._v2;
}

int PaletteUsage::process(Common::Array<RGB6> &palette, uint flags) {
	int palLow;
	int palHigh = (flags & 0x800) ? 0x100 : 0xFC;
	int palIdx;

	if (flags & 0x4000) {
		palLow = 0;
		palIdx = palHigh;
	} else {
		palLow = _vm->_palette->_lowRange;
		if ((PALETTE_COUNT - _vm->_palette->_highRange) > palHigh) {
			palIdx = palHigh;
		} else {
			palIdx = PALETTE_COUNT - _vm->_palette->_highRange;
		}
	}

	int rgbIndex = _vm->_palette->_rgbList.scan();
	uint32 rgbMask = 1 << rgbIndex;
	int varA = flags & 0x8000;
	bool hasUsage = !_vm->_palette->_paletteUsage.empty();
	bool flag1 = false;

	if (hasUsage) {
		if (varA || _vm->_palette->_paletteUsage.empty())
			hasUsage = false;

		if (varA && !_vm->_palette->_paletteUsage.empty())
			flag1 = true;
	}

	if (hasUsage) {
		getKeyEntries(palette);
		prioritize(palette);
	}

	int freeIndex;
	int palCount = getGamePalFreeIndex(&freeIndex);
	Common::Array<UsageRange> palRange;

	for (uint palIndex = 0; palIndex < palette.size(); ++palIndex) {
		byte pal2 = palIndex;
		byte pal1 = 0;

		if (!(palette[palIndex]._flags & 0x80)) {
			pal1 = 0x40;
		}
		if (palette[palIndex]._flags & 0x60) {
			pal1 |= 0x20;
		}

		palRange.push_back(UsageRange(pal1, pal2));
	}

	Common::sort(palRange.begin(), palRange.end(), rangeSorter);
	
	int var3A = (flags & 0x4000) ? 0xffff : 0xfffe;

	for (uint palIndex = 0; palIndex < palette.size(); ++palIndex) {
		bool var48 = false;
		int var4 = 0xffff;
		int v1 = palRange[palIndex]._v2;

		if (palette[v1]._flags & 8) {
			var48 = true;
			var4 = 0xFD;
		}

		if (hasUsage && palette[v1]._flags & 0x10) {
			for (uint usageIndex = 0; usageIndex < _data.size() && !var48; ++usageIndex) {
				if (_data[usageIndex]._palIndex == palIndex) {
					var48 = true;
					int dataIndex = MIN(usageIndex, _data.size() - 1);
					var4 = _data[dataIndex]._palIndex;
				}
			}
		}

		if (flag1 && palette[palIndex]._flags & 0x10) {
			for (uint usageIndex = 0; usageIndex < _data.size() && !var48; ++usageIndex) {
				if (_data[usageIndex]._palIndex == palIndex) {
					var48 = true;
					var4 = 0xF0 + usageIndex;

					// Copy data into the high end of the main palette
					RGB6 &pSrc = palette[palIndex];
					byte *pDest = &_vm->_palette->_mainPalette[var4 * 3];
					pDest[0] = pSrc.r;
					pDest[1] = pSrc.g;
					pDest[2] = pSrc.b;
				}
			}
		}

		if (!var48 && !varA) {
			int var2 = (palette[palIndex]._flags & 0x20) ||
				(((flags & 0x2000) || (palette[palIndex]._flags & 0x4000)) &&
				((flags & 0x1000) || (palCount == 0))) ? 0x7fff : 1;
			int var36 = (palette[palIndex]._flags & 0x80) ? 0 : 2;
			
			for (int idx = palLow; idx < palIdx; ++idx) {
				uint32 v = _vm->_palette->_palFlags[idx];
				if ((v & var3A) && !(v & var36)) {
					int var10;

					if (var2 > 1) {
						var10 = rgbFactor(&_vm->_palette->_mainPalette[idx * 3], palette[palIndex]);
					}
					else if (_vm->_palette->_mainPalette[idx * 3] != palette[palIndex].r ||
							_vm->_palette->_mainPalette[idx * 3 + 1] != palette[palIndex].g ||
							_vm->_palette->_mainPalette[idx * 3 + 2] != palette[palIndex].b) {
						var10 = 1;
					} else {
						var10 = 0;
					}

					if (var2 > var10) {
						var48 = true;
						var4 = idx;
						var2 = var10;
					}
				}
			}
		}

		if (!var48 && (!(flags & 0x1000) || (!(palette[palIndex]._flags & 0x60) && !(flags & 0x2000)))) {
			for (int idx = freeIndex; idx < palIdx && !var48; ++idx) {
				if (!_vm->_palette->_palFlags[idx]) {
					--palCount;
					++freeIndex;
					var48 = true;
					var4 = idx;

					RGB6 &pSrc = palette[palIndex];
					byte *pDest = &_vm->_palette->_mainPalette[idx * 3];
					pDest[0] = pSrc.r;
					pDest[1] = pSrc.g;
					pDest[2] = pSrc.b;
				}
			}
		}
		
		assert(var48);
		int var52 = (varA && palette[palIndex]._u2) ? 2 : 0;

		_vm->_palette->_palFlags[var4] |= var52 | rgbMask;
		palette[palIndex]._palIndex = var4;
	}

	_vm->_palette->_rgbList[rgbIndex] = true;

	return rgbIndex;
}


int PaletteUsage::rgbMerge(RGB6 &palEntry) {
	return ((palEntry.r + 1) / 4 - 1) * 38 + ((palEntry.g + 1) / 4 - 1) * 76 + 
		((palEntry.b + 1) / 4 - 1) * 14;
}

void PaletteUsage::transform(Common::Array<RGB6> &palette) {
	if (!empty()) {
		for (uint i = 0; i < _data.size(); ++i) {
			int palIndex = _data[i]._palIndex;
			_data[i]._palIndex = palette[palIndex]._palIndex;
		}
	}
}

void PaletteUsage::updateUsage(Common::Array<int> &usageList, int sceneUsageIndex) {
	uint32 mask1 = 0xFFFFFFFF;
	uint32 mask2 = 0;

	for (uint idx = 0; idx < usageList.size(); ++idx) {
		uint32 bitMask = 1 << usageList[idx];
		mask1 ^= bitMask;
		mask2 |= bitMask;
		_vm->_palette->_rgbList[usageList[idx]] = false;
	}

	uint32 mask3 = 1 << sceneUsageIndex;

	for (uint idx = 0; idx < PALETTE_COUNT; ++idx) {
		uint32 mask = mask2 & _vm->_palette->_palFlags[idx];
		if (mask) {
			_vm->_palette->_palFlags[idx] = (_vm->_palette->_palFlags[idx] &
				mask1) | mask3;
		}
	}

	_vm->_palette->_rgbList[sceneUsageIndex] = true;
}

int PaletteUsage::getGamePalFreeIndex(int *palIndex) {
	*palIndex = -1;
	int count = 0;

	for (int i = 0; i < PALETTE_COUNT; ++i) {
		if (!_vm->_palette->_palFlags[i]) {
			++count;
			if (*palIndex < 0)
				*palIndex = i;
		}
	}

	return count;
}

int PaletteUsage::rgbFactor(byte *palEntry, RGB6 &pal6) {
	int total = 0;
	total += (palEntry[0] - pal6.r) * (palEntry[0] - pal6.r);
	total += (palEntry[1] - pal6.g) * (palEntry[1] - pal6.g);
	total += (palEntry[2] - pal6.b) * (palEntry[2] - pal6.b);

	return total;
}

/*------------------------------------------------------------------------*/

void RGBList::clear() {
	for (int i = 0; i < 32; i++)
		_data[i] = false;
}

void RGBList::reset() {
	for (int i = 2; i < 32; i++)
		_data[i] = false;
}

int RGBList::scan() {
	for (int i = 0; i < 32; ++i) {
		if (!_data[i])
			return i;
	}

	error("RGBList was full");
}

/*------------------------------------------------------------------------*/

Palette::Palette(MADSEngine *vm) : _vm(vm), _paletteUsage(vm) {
	reset();

	_lockFl = false;
	_lowRange = 0;
	_highRange = 0;
	Common::fill(&_mainPalette[0], &_mainPalette[PALETTE_SIZE], 0);
}

void Palette::setPalette(const byte *colors, uint start, uint num) {
	g_system->getPaletteManager()->setPalette(colors, start, num);
	reset();
}

void Palette::setEntry(byte palIndex, byte r, byte g, byte b) {
	_mainPalette[palIndex * 3] = VGA_COLOR_TRANS(r);
	_mainPalette[palIndex * 3 + 1] = VGA_COLOR_TRANS(g);
	_mainPalette[palIndex * 3 + 2] = VGA_COLOR_TRANS(b);

	setPalette((const byte *)&_mainPalette[palIndex * 3], palIndex, 1);
}


void Palette::grabPalette(byte *colors, uint start, uint num) {
	g_system->getPaletteManager()->grabPalette(colors, start, num);
	reset();
}

uint8 Palette::palIndexFromRgb(byte r, byte g, byte b, byte *paletteData) {
	byte index = 0;
	int32 minDist = 0x7fffffff;
	byte palData[PALETTE_SIZE];
	int Rdiff, Gdiff, Bdiff;

	if (paletteData == NULL) {
		g_system->getPaletteManager()->grabPalette(palData, 0, PALETTE_COUNT);
		paletteData = &palData[0];
	}

	for (int palIndex = 0; palIndex < PALETTE_COUNT; ++palIndex) {
		Rdiff = r - paletteData[palIndex * 3];
		Gdiff = g - paletteData[palIndex * 3 + 1];
		Bdiff = b - paletteData[palIndex * 3 + 2];

		if (Rdiff * Rdiff + Gdiff * Gdiff + Bdiff * Bdiff < minDist) {
			minDist = Rdiff * Rdiff + Gdiff * Gdiff + Bdiff * Bdiff;
			index = (uint8)palIndex;
		}
	}

	return (uint8)index;
}

void Palette::reset() {
}

void Palette::setGradient(byte *palette, int start, int count, int rgbValue1, int rgbValue2) {
	int rgbCtr = 0;
	int rgbCurrent = rgbValue2;
	int rgbDiff = -(rgbValue2 - rgbValue1);

	if (count >  0) {
		byte *pDest = palette + start * 3;
		int endVal = count - 1;
		int numLeft = count;

		do {
			pDest[0] = pDest[1] = pDest[2] = rgbCurrent;

			if (numLeft > 1) {
				rgbCtr += rgbDiff;
				if (rgbCtr >= endVal) {
					do {
						++rgbCurrent;
						rgbCtr += 1 - numLeft;
					} while (rgbCtr >= endVal);
				}
			}

			pDest += 3;
		} while (--numLeft > 0);
	}
}

void Palette::setSystemPalette() {
	byte palData[4 * 3];
	palData[0 * 3] = palData[0 * 3 + 1] = palData[0 * 3 + 2] = 0;
	palData[1 * 3] = palData[1 * 3 + 1] = palData[1 * 3 + 2] = 0x54;
	palData[2 * 3] = palData[2 * 3 + 1] = palData[2 * 3 + 2] = 0xb4;
	palData[3 * 3] = palData[3 * 3 + 1] = palData[3 * 3 + 2] = 0xff;
	
	setPalette(palData, 0, 4);
}

void Palette::resetGamePalette(int lowRange, int highRange) {
	Common::fill((byte *)&_palFlags[0], (byte *)&_palFlags[PALETTE_COUNT], 0);
	initVGAPalette(_mainPalette);

	// Init low range to common RGB values
	if (lowRange) {
		Common::fill(&_palFlags[0], &_palFlags[lowRange], 1);
	}

	// Init high range to common RGB values
	if (highRange) {
		_palFlags[255] = 1;

		Common::fill(&_palFlags[255 - highRange], &_palFlags[254], _palFlags[255]);
	}

	_rgbList.clear();
	_rgbList[0] = _rgbList[1] = true;

	_lockFl = false;
	_lowRange = lowRange;
	_highRange = highRange;
}

void Palette::initPalette() {
	RGB4 rgb;
	uint32 palMask = 1;

	if (_vm->_game->_player._spritesLoaded && _vm->_game->_player._numSprites) {

		for (int idx = 0; idx < _vm->_game->_player._numSprites; ++idx) {
			SpriteAsset *asset = _vm->_game->_scene._sprites[
				_vm->_game->_player._spritesStart + idx];
			
			uint32 mask = 1;
			if (asset->_usageIndex)
				mask <<= asset->_usageIndex;
			
			palMask = mask;
		}
	}

	for (int idx = 0; idx < PALETTE_COUNT; ++idx)
		_palFlags[idx] = palMask;

	_lockFl = false;
	_rgbList.reset();
}

void Palette::initVGAPalette(byte *palette) {
	byte *destP = palette;
	for (int palIndex = 0; palIndex < 16; ++palIndex) {
		for (int byteCtr = 2; byteCtr >= 0; --byteCtr)
			*destP++ = ((DEFAULT_VGA_PALETTE[palIndex] >> (8 * byteCtr)) & 0xff) >> 2;
	}
}

void Palette::setLowRange() {
	_mainPalette[0] = _mainPalette[1] = _mainPalette[2] = VGA_COLOR_TRANS(0);
	_mainPalette[3] = _mainPalette[4] = _mainPalette[5] = VGA_COLOR_TRANS(0x15);
	_mainPalette[6] = _mainPalette[7] = _mainPalette[8] = VGA_COLOR_TRANS(0x2A);
	_mainPalette[9] = _mainPalette[10] = _mainPalette[11] = VGA_COLOR_TRANS(0x3F);
	_vm->_palette->setPalette(_mainPalette, 0, 4);
}

void Palette::fadeOut(byte palette[PALETTE_SIZE], int v1, int v2, int v3, int v4, int v5, int v6) {
}

void Palette::lock() {
	if (_rgbList[31] && !_lockFl)
		error("Palette Lock - Unexpected values");

	_lockFl = true;
	_rgbList[31] = true;

	for (int i = 0; i < 256; i++) {
		if (_palFlags[i])
			_palFlags[i] |= 0x80000000;
	}
}

void Palette::unlock() {
	if (!_lockFl)
		return;

	for (int i = 0; i < 256; i++)
		_palFlags[i] &= 0x7FFFFFFF;

	_rgbList[31] = false;
	_lockFl = false;
}
} // End of namespace MADS
