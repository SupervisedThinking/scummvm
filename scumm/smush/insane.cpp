/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001-2003 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

#include "stdafx.h"

#include "base/engine.h"

#include "common/file.h"

#include "scumm/scumm.h"
#include "scumm/actor.h"
#include "scumm/sound.h"
#include "scumm/resource.h"
#include "scumm/imuse.h"
#include "scumm/imuse_digi.h"

#include "scumm/smush/smush_player.h"
#include "scumm/smush/insane.h"

#ifdef INSANE

// NOTE:
// san files with IACT chunks:
// minedriv.san
// minefite.san
// toranch.san
// tovista1.san
// tovista2.san

namespace Scumm {

static const int scenePropIdx[58] = {0,  12,  14,  18,  20,  22,  24,  26,  28,  30,  34,
	36,  38,  40,  42,  44,  46,  48,  50,  55,  57,  59,  61,  63,  65,  67,  71,
	73,  75,  77,  79,  81,  83,  85,  89,  93,  95,  97,  99, 101, 103, 105, 107,
	109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 129, 131, 133, 135, 137};

static const int actorAnimationData[21] = {20, 21, 22, 23, 24, 25, 26, 13, 14, 15, 16, 17, 
	18, 19, 6, 7, 8, 9, 10, 11, 12};


Insane::Insane(ScummEngine *scumm) {
	_scumm = scumm;
	
	// Demo has different insane, so disable it now
	if (_scumm->_features & GF_DEMO)
		return;

	initvars();

	readFileToMem("roadrash.rip", &_smush_roadrashRip);
	readFileToMem("roadrsh2.rip", &_smush_roadrsh2Rip);
	readFileToMem("roadrsh3.rip", &_smush_roadrsh3Rip);
	readFileToMem("goglpalt.rip", &_smush_goglpaltRip);
	readFileToMem("tovista1.flu", &_smush_tovista1Flu);
	readFileToMem("tovista2.flu", &_smush_tovista2Flu);
	readFileToMem("toranch.flu", &_smush_toranchFlu);
	readFileToMem("minedriv.flu", &_smush_minedrivFlu);
	readFileToMem("minefite.flu", &_smush_minefiteFlu);

	_smush_iconsNut = new NutRenderer(_scumm);
	_smush_iconsNut->loadFont("icons.nut", _scumm->getGameDataPath());
	_smush_icons2Nut = new NutRenderer(_scumm);
	_smush_icons2Nut->loadFont("icons2.nut", _scumm->getGameDataPath());
	_smush_bensgoggNut = new NutRenderer(_scumm);
	_smush_bensgoggNut->loadFont("bensgogg.nut", _scumm->getGameDataPath());
	_smush_bencutNut = new NutRenderer(_scumm);
	_smush_bencutNut->loadFont("bencut.nut", _scumm->getGameDataPath());

	// FIXME: implement things
	//openManyResource(0, 4, "specfnt.nut", "titlfnt.nut", "techfnt.nut", "scummfnt.nut");
}

Insane::~Insane(void) {
	free(_smush_roadrashRip);
	free(_smush_roadrsh2Rip);
	free(_smush_roadrsh3Rip);
	free(_smush_goglpaltRip);
	free(_smush_tovista1Flu);
	free(_smush_tovista2Flu);
	free(_smush_toranchFlu);
	free(_smush_minedrivFlu);
	free(_smush_minefiteFlu);

	delete _smush_bencutNut;
	delete _smush_bensgoggNut;
	delete _smush_iconsNut;
	delete _smush_icons2Nut;
}

void Insane::setSmushParams(int speed, bool subtitles) {
	_speed = speed;
	_subtitles = subtitles;
}

void Insane::initvars(void) {
	int i, j;

	_speed = 12;
	_subtitles = true;
	_insaneIsRunning = false;

	_numberArray = 0;
	_emulateInterrupt = 0;
	_flag1d = 0;
	_objArray1Idx = 0;
	_objArray1Idx2 = 0;
	_objArray2Idx = 0;
	_objArray2Idx2 = 0;
	_currSceneId = 1;
	_timer6Id = 0;
	_timerSpriteId = 0;
	_temp2SceneId = 0;
	_tempSceneId = 0;
	_currEnemy = -1;
	_currScenePropIdx = 0;
	_currScenePropSubIdx = 0;
	_currTrsMsg = 0;
	_sceneData2Loaded = 0;
	_sceneData1Loaded = 0;
	_keyboardDisable = 0;
	_needSceneSwitch = false;
	_idx2Exceeded = 0;
	_memoryAllocatedNotOK = 0;
	_lastKey = 0;
	_tiresRustle = false;
	_keybOldDx = 0;
	_keybOldDy = 0;
	_velocityX = 0;
	_velocityY = 0;
	_keybX = 0;
	_keybY = 0;
	_firstBattle = false;
	_val11d = 0;
	_val32d = -1;
	_val39_ = true;
	_val51d = 0;
	_val52d = 0;
	_val53d = 0;
	_val54d = 0;
	_val55d = 0;
	_val56d = 0;
	_val57d = 0;
	_val109w = 0x40;
	_val10b = 3;
	_val110w = 0x100;
	_val111w = 0x20;
	_val112w = 0x20;
	_val113d = 1;
	_val115w = 0;
	_val116w = 0;
	_val119_ = false;
	_val120_ = false;
	_val121_ = false;
	_val122_ = false;
	_val123_ = false;
	_val124_ = false;
	_kickingInProgress = false;
	_weaponJustSwitched = false;
	_val130b = 0;
	_val131w = 0;
	_val132w = 0;
	_val133w = 0;
	_val134w = 0;
	_val135w = 0;
	_val136w = 0;
	_val140b = 0;
	_val141w = 0;
	_val142w = 0;
	_val143w = 0;
	_val144w = 0;
	_val145w = 0;
	_val146w = 0;
	_val150b = 0;
	_val151w = 0;
	_val152w = 0;
	_val153w = 0;
	_val154w = 0;
	_val155w = 0;
	_val156w = 0;
	_val160b = 0;
	_val161w = 0;
	_val162w = 0;
	_val163w = 0;
	_val164w = 0;
	_val165w = 0;
	_val166w = 0;
	_val167w = 0;
	_val168w = 0;
	_val170b = 0;
	_val171w = 0;
	_val172w = 0;
	_val173w = 0;
	_val174w = 0;
	_val175w = 0;
	_val176w = 0;
	_val180d = 0;
	_val181b = 0;
	_val182b = 0;
	_val183d = 0;
	_val190d = 0;
	_val191w = 0;
	_val200d = 0;
	_val201d = 0;
	_val202b = 0;
	_beenCheated = 0;
	_val211d = 0;
	_val212_ = 0;
	_val213d = 0;
	_smlayer_room = 0;
	_smlayer_room2 = 0;
	_isBenCut = 0;
	_smush_isPauseImuse = false;
	_continueFrame = 0;
	_continueFrame1 = 0;
	_counter1 = 0;
	_iactSceneId = 0;
	_iactSceneId2 = 0;

	init_enemyStruct(EN_ROTT1, EN_ROTT1, 0, 0, 160, 0, INV_MACE, 90, "wr2_rott.san", 
					 26, 16, 17, 0x1b, 0x0b, 3);
	init_enemyStruct(EN_ROTT2, EN_ROTT2, 1, 0, 250, 0, INV_2X4, 90, "wr2_rott.san", 
					 28, 16, 17, 0x2a, 0x0b, 3);
	init_enemyStruct(EN_ROTT3, EN_ROTT3, 2, 0, 120, 0, INV_HAND, 90, "wr2_rott.san", 
					 15, 16, 17, 0x2b, 0x0b, 3);
	init_enemyStruct(EN_VULTF1, EN_VULTF1, 3, 0, 60, 0, INV_HAND, 91, "wr2_vltp.san", 
					 29, 33, 32, 0x25, 0x0c, 4);
	init_enemyStruct(EN_VULTM1, EN_VULTM1, 4, 0, 100, 0, INV_CHAIN, 91, "wr2_vltc.san", 
					 30, 33, 32, 0x24, 0x0c, 4);
	init_enemyStruct(EN_VULTF2, EN_VULTF2, 5, 0, 250, 0, INV_CHAINSAW, 91, "wr2_vlts.san", 
					 31, 33, 32, 0x23, 0x0c, 4);
	init_enemyStruct(EN_VULTM2, EN_VULTM2, 6, 0, 900, 0, INV_BOOT, 91, "wr2_rott.san", 
					 34, 33, 32, 0x2d, 0x10, 4);
	init_enemyStruct(EN_CAVEFISH, EN_CAVEFISH, 7, 0, 60, 0, INV_DUST, 92, "wr2_cave.san", 
					 39, 0, 0, 0x29, 0x0d, 2);
	init_enemyStruct(EN_TORQUE, EN_TORQUE, 8, 0, 900, 0, INV_HAND, 93, "wr2_vltp.san", 
					 57, 0, 0, 0x25, 0x0c, 1);

	init_fluConfStruct(1, 1, _smush_minedrivFlu, "minedriv.san", 235, 1300);
	init_fluConfStruct(2, 1, _smush_minedrivFlu, "minedriv.san", 355, 1300);
	init_fluConfStruct(3, 1, _smush_minedrivFlu, "minedriv.san", 1255, 1300);
	init_fluConfStruct(4, 1, _smush_minedrivFlu, "minedriv.san", 565, 1300);
	init_fluConfStruct(5, 1, _smush_minedrivFlu, "minedriv.san", 1040, 1300);
	init_fluConfStruct(8, 1, _smush_minedrivFlu, "minedriv.san", 1040, 1300);
	init_fluConfStruct(9, 1, _smush_minedrivFlu, "minedriv.san", 655, 1300);
	init_fluConfStruct(10, 1, _smush_minedrivFlu, "minedriv.san", 115, 1300);
	init_fluConfStruct(11, 1, _smush_minedrivFlu, "minedriv.san", 315, 1300);
	init_fluConfStruct(12, 1, _smush_minedrivFlu, "minedriv.san", 235, 1300);
	init_fluConfStruct(15, 6, _smush_toranchFlu, "toranch.san", 115, 530);
	init_fluConfStruct(16, 5, _smush_tovista2Flu, "tovista2.san", 235, 290);
	init_fluConfStruct(17, 4, _smush_tovista1Flu, "tovista1.san", 175, 230);
	init_fluConfStruct(18, 4, _smush_tovista1Flu, "tovista1.san", 175, 230);
	init_fluConfStruct(19, 6, _smush_toranchFlu, "toranch.san", 115, 530);
	init_fluConfStruct(20, 6, _smush_toranchFlu, "toranch.san", 115, 530);
  
	init_scenePropStruct(  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
	init_scenePropStruct(  1,  0, 1, 128, 2001, 0, 0, 0, 0, 56, 2);
	init_scenePropStruct(  2,  0, 0, 125, 1002, 0, 0, 0, 0, 35, 3);
	init_scenePropStruct(  3,  0, 1, 129, 2002, 0, 0, 0, 0, 23, 4);
	init_scenePropStruct(  4,  0, 1, 130, 2003, 0, 0, 0, 0, 40, 5);
	init_scenePropStruct(  5,  0, 0, 126, 1005, 0, 0, 0, 0, 46, 6);
	init_scenePropStruct(  6,  0, 1, 131, 2004, 0, 0, 0, 0, 39, 7);
	init_scenePropStruct(  7,  0, 1, 132, 2005, 0, 0, 0, 0, 45, 8);
	init_scenePropStruct(  8,  0, 1, 133, 2006, 0, 0, 0, 0, 14, 9);
	init_scenePropStruct(  9,  0, 0, 127, 1009, 0, 0, 0, 0, 15, 10);
	init_scenePropStruct( 10,  0, 1, 134, 501, 0, 0, 0, 0, 25, 11);
	init_scenePropStruct( 11,  0, 1, 135, 502, 0, 0, 0, 0, 15, 0);
	init_scenePropStruct( 12,  1, -1, 0, 0, 0xFF, 0xFF, 0xFF, 0, 0, 1);
	init_scenePropStruct( 13,  1, 0, 291, 135, 0xFF, 0xFF, 0xFF, 0, 25, 0);
	init_scenePropStruct( 14,  2, -1, 0, 0, 0xFC, 0, 0xFC, 0, 0, 1);
	init_scenePropStruct( 15,  2, 1, 277, 17, 0xFC, 0, 0xFC, 0, 56, 2);
	init_scenePropStruct( 16,  2, 0, 288, 18, 0xFF, 0xFF, 0xFF, 0, 56, 3);
	init_scenePropStruct( 17,  2, 1, 278, 19, 0xFC, 0, 0xFC, 0, 56, 0);
	init_scenePropStruct( 18,  3, -1, 0, 0, 0xFC, 0, 0xFC, 0, 0, 1);
	init_scenePropStruct( 19,  3, 1, 282, 23, 0xFC, 0, 0xFC, 0, 56, 0);
	init_scenePropStruct( 20,  4, -1, 0, 0, 0xFC, 0, 0xFC, 0, 0, 1);
	init_scenePropStruct( 21,  4, 1, 283, 24, 0xFC, 0, 0xFC, 0, 56, 0);
	init_scenePropStruct( 22,  5, -1, 0, 0, 0xFC, 0, 0xFC, 0, 0, 1);
	init_scenePropStruct( 23,  5, 1, 284, 25, 0xFC, 0, 0xFC, 0, 56, 0);
	init_scenePropStruct( 24,  6, -1, 0, 0, 0xFC, 0, 0xFC, 0, 0, 1);
	init_scenePropStruct( 25,  6, 1, 285, 26, 0xFC, 0, 0xFC, 0, 56, 0);
	init_scenePropStruct( 26,  7, -1, 0, 0, 0xFC, 0, 0xFC, 0, 0, 1);
	init_scenePropStruct( 27,  7, 1, 286, 27, 0xFC, 0, 0xFC, 0, 56, 0);
	init_scenePropStruct( 28,  8, -1, 0, 0, 0xFC, 0, 0xFC, 0, 0, 1);
	init_scenePropStruct( 29,  8, 1, 287, 28, 0xFC, 0, 0xFC, 0, 56, 0);
	init_scenePropStruct( 30,  9, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 31,  9, 1, 261, 1, 0xFC, 0, 0, 0, 40, 2);
	init_scenePropStruct( 32,  9, 1, 262, 2, 0xFC, 0, 0, 0, 40, 3);
	init_scenePropStruct( 33,  9, 1, 263, 3, 0xFC, 0, 0, 0, 40, 0);
	init_scenePropStruct( 34, 10, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 35, 10, 1, 263, 3, 0xFC, 0, 0, 0, 30, 0);
	init_scenePropStruct( 36, 11, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 37, 11, 1, 264, 4, 0xFC, 0, 0, 0, 30, 0);
	init_scenePropStruct( 38, 12, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 39, 12, 1, 265, 5, 0xFC, 0, 0, 0, 30, 0);
	init_scenePropStruct( 40, 13, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 41, 13, 1, 266, 6, 0xFC, 0, 0, 0, 30, 0);
	init_scenePropStruct( 42, 14, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 43, 14, 1, 267, 7, 0xFC, 0, 0, 0, 30, 0);
	init_scenePropStruct( 44, 15, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 45, 15, 1, 268, 8, 0xFC, 0, 0, 0, 30, 0);
	init_scenePropStruct( 46, 16, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 47, 16, 1, 274, 14, 0xFC, 0, 0, 0, 30, 0);
	init_scenePropStruct( 48, 17, -1, 0, 0, 0xFC, 0, 0, 0, 0, 1);
	init_scenePropStruct( 49, 17, 1, 270, 10, 0xFC, 0, 0, 0, 30, 0);
	init_scenePropStruct( 50, 18, -1, 0, 0, 0xFC, 0xFC, 0x54, 0, 0, 1);
	init_scenePropStruct( 51, 18, 0, 289, 45, 0xFF, 0xFF, 0xFF, 0, 40, 2);
	init_scenePropStruct( 52, 18, 1, 177, 49, 0xFC, 0xFC, 0x54, 0, 40, 3);
	init_scenePropStruct( 53, 18, 1, 178, 50, 0xFC, 0xFC, 0x54, 0, 40, 4);
	init_scenePropStruct( 54, 18, 0, 290, 47, 0xFF, 0xFF, 0xFF, 0, 40, 0);
	init_scenePropStruct( 55, 19, -1, 0, 0, 0xFC, 0xFC, 0x54, 0, 0, 1);
	init_scenePropStruct( 56, 19, 1, 179, 51, 0xFC, 0xFC, 0x54, 0, 40, 0);
	init_scenePropStruct( 57, 20, -1, 0, 0, 0xFC, 0xFC, 0x54, 0, 0, 1);
	init_scenePropStruct( 58, 20, 1, 183, 55, 0xFC, 0xFC, 0x54, 0, 40, 0);
	init_scenePropStruct( 59, 21, -1, 0, 0, 0xFC, 0xFC, 0x54, 0, 0, 1);
	init_scenePropStruct( 60, 21, 1, 184, 56, 0xFC, 0xFC, 0x54, 0, 40, 0);
	init_scenePropStruct( 61, 22, -1, 0, 0, 0xFC, 0xFC, 0x54, 0, 0, 1);
	init_scenePropStruct( 62, 22, 1, 186, 58, 0xFC, 0xFC, 0x54, 0, 40, 0);
	init_scenePropStruct( 63, 23, -1, 0, 0, 0xFC, 0xFC, 0x54, 0, 0, 1);
	init_scenePropStruct( 64, 23, 1, 191, 63, 0xFC, 0xFC, 0x54, 0, 40, 0);
	init_scenePropStruct( 65, 24, -1, 0, 0, 0xFC, 0xFC, 0x54, 0, 0, 1);
	init_scenePropStruct( 66, 24, 1, 192, 64, 0xFC, 0xFC, 0x54, 0, 40, 0);
	init_scenePropStruct( 67, 25, -1, 0, 0, 0xBC, 0x78, 0x48, 0, 0, 1);
	init_scenePropStruct( 68, 25, 1, 220, 93, 0xBC, 0x78, 0x48, 0, 40, 2);
	init_scenePropStruct( 69, 25, 1, 221, 94, 0xBC, 0x78, 0x48, 0, 40, 3);
	init_scenePropStruct( 70, 25, 1, 222, 95, 0xBC, 0x78, 0x48, 0, 40, 0);
	init_scenePropStruct( 71, 26, -1, 0, 0, 0xBC, 0x78, 0x48, 0, 0, 1);
	init_scenePropStruct( 72, 26, 1, 223, 96, 0xBC, 0x78, 0x48, 0, 40, 0);
	init_scenePropStruct( 73, 27, -1, 0, 0, 0xBC, 0x78, 0x48, 0, 0, 1);
	init_scenePropStruct( 74, 27, 1, 224, 97, 0xBC, 0x78, 0x48, 0, 40, 0);
	init_scenePropStruct( 75, 28, -1, 0, 0, 0xBC, 0x78, 0x48, 0, 0, 1);
	init_scenePropStruct( 76, 28, 1, 225, 98, 0xBC, 0x78, 0x48, 0, 40, 0);
	init_scenePropStruct( 77, 29, -1, 0, 0, 0xBC, 0x78, 0x48, 0, 0, 1);
	init_scenePropStruct( 78, 29, 1, 226, 99, 0xBC, 0x78, 0x48, 0, 40, 0);
	init_scenePropStruct( 79, 30, -1, 0, 0, 0xBC, 0x78, 0x48, 0, 0, 1);
	init_scenePropStruct( 80, 30, 1, 228, 101, 0xBC, 0x78, 0x48, 0, 40, 0);
	init_scenePropStruct( 81, 31, -1, 0, 0, 0xBC, 0x78, 0x48, 0, 0, 1);
	init_scenePropStruct( 82, 31, 1, 229, 102, 0xBC, 0x78, 0x48, 0, 40, 0);
	init_scenePropStruct( 83, 32, -1, 0, 0, 0xA8, 0xA8, 0xA8, 0, 0, 1);
	init_scenePropStruct( 84, 32, 1, 233, 106, 0xA8, 0xA8, 0xA8, 0, 40, 2);
	init_scenePropStruct( 85, 32, 1, 234, 107, 0xA8, 0xA8, 0xA8, 0, 40, 0);
	init_scenePropStruct( 86, 33, -1, 0, 0, 0xA8, 0xA8, 0xA8, 0, 0, 1);
	init_scenePropStruct( 87, 33, 1, 241, 114, 0xA8, 0xA8, 0xA8, 0, 40, 2);
	init_scenePropStruct( 88, 33, 1, 242, 115, 0xA8, 0xA8, 0xA8, 0, 40, 0);
	init_scenePropStruct( 89, 34, -1, 0, 0, 0xA8, 0xA8, 0xA8, 0, 0, 1);
	init_scenePropStruct( 90, 34, 1, 237, 110, 0xA8, 0xA8, 0xA8, 0, 40, 2);
	init_scenePropStruct( 91, 34, 1, 238, 111, 0xA8, 0xA8, 0xA8, 0, 40, 3);
	init_scenePropStruct( 92, 34, 1, 239, 112, 0xA8, 0xA8, 0xA8, 0, 40, 0);
	init_scenePropStruct( 93, 35, -1, 0, 0, 0xA8, 0xA8, 0xA8, 0, 0, 1);
	init_scenePropStruct( 94, 35, 1, 258, 131, 0xA8, 0xA8, 0xA8, 0, 40, 0);
	init_scenePropStruct( 95, 36, -1, 0, 0, 0xA8, 0xA8, 0xA8, 0, 0, 1);
	init_scenePropStruct( 96, 36, 1, 260, 133, 0xA8, 0xA8, 0xA8, 0, 40, 0);
	init_scenePropStruct( 97, 37, -1, 0, 0, 0xA8, 0xA8, 0xA8, 0, 0, 1);
	init_scenePropStruct( 98, 37, 1, 252, 125, 0xA8, 0xA8, 0xA8, 0, 40, 0);
	init_scenePropStruct( 99, 38, -1, 0, 0, 0xA8, 0xA8, 0xA8, 0, 0, 1);
	init_scenePropStruct(100, 38, 1, 254, 127, 0xA8, 0xA8, 0xA8, 0, 40, 0);
	init_scenePropStruct(101, 39, -1, 0, 0, 0xA8, 0xA8, 0xA8, 0, 0, 1);
	init_scenePropStruct(102, 39, 1, 236, 109, 0xA8, 0xA8, 0xA8, 0, 40, 0);
	init_scenePropStruct(103, 40, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(104, 40, 1, 174, 42, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(105, 41, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(106, 41, 1, 167, 36, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(107, 42, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(108, 42, 1, 160, 29, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(109, 43, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(110, 43, 1, 161, 30, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(111, 44, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(112, 44, 1, 163, 32, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(113, 45, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(114, 45, 1, 164, 33, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(115, 46, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(116, 46, 1, 170, 39, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(117, 47, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(118, 47, 1, 166, 35, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(119, 48, -1, 0, 0, 4, 0xBC, 0, 0, 0, 1);
	init_scenePropStruct(120, 48, 1, 175, 43, 4, 0xBC, 0, 0, 40, 0);
	init_scenePropStruct(121, 49, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(122, 49, 1, 203, 75, 0x40, 0x40, 0xFC, 0, 40, 0);
	init_scenePropStruct(123, 50, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(124, 50, 1, 194, 66, 0x40, 0x40, 0xFC, 0, 40, 0);
	init_scenePropStruct(125, 51, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(126, 51, 1, 195, 67, 0x40, 0x40, 0xFC, 0, 40, 0);
	init_scenePropStruct(127, 52, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(128, 52, 1, 199, 71, 0x40, 0x40, 0xFC, 0, 40, 0);
	init_scenePropStruct(129, 53, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(130, 53, 1, 205, 77, 0x40, 0x40, 0xFC, 0, 40, 0);
	init_scenePropStruct(131, 54, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(132, 54, 1, 212, 85, 0x40, 0x40, 0xFC, 0, 40, 0);
	init_scenePropStruct(133, 55, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(134, 55, 1, 201, 73, 0x40, 0x40, 0xFC, 0, 40, 0);
	init_scenePropStruct(135, 56, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(136, 56, 1, 198, 70, 0x40, 0x40, 0xFC, 0, 40, 0);
	init_scenePropStruct(137, 57, -1, 0, 0, 0x40, 0x40, 0xFC, 0, 0, 1);
	init_scenePropStruct(138, 57, 0, 59, 134, 0xFF, 0xFF, 0xFF, 0, 30, 0);

	_actor[0].damage = 0;
	_actor[0].maxdamage = 80;
	_actor[0].field_8 = 1;
	_actor[0].field_C = 0;
	_actor[0].speed = 0;
	_actor[0].field_14 = 0;
	_actor[0].field_18 = 0;
	_actor[0].x = 160;
	_actor[0].y = 0;
	_actor[0].y1 = -1;
	_actor[0].x1 = -1;
	_actor[0].field_2C = 2;
	_actor[0].field_30 = 0;
	_actor[0].field_34 = 2;
	_actor[0].field_38 = 0;
	_actor[0].lost = 0;
	_actor[0].kicking = 0;
	_actor[0].field_44 = 0;
	_actor[0].field_48 = 0;
	_actor[0].field_4C = 0;
	_actor[0].scenePropSubIdx = 0;
	_actor[0].field_54 = 0;
	_actor[0].runningSound = 0;
	_actor[0].weapon = INV_HAND;
	_actor[0].inventory[INV_CHAIN] = 0;
	_actor[0].inventory[INV_CHAINSAW] = 0;
	_actor[0].inventory[INV_MACE] = 0;
	_actor[0].inventory[INV_2X4] = 0;
	_actor[0].inventory[INV_WRENCH] = 1;
	_actor[0].inventory[INV_BOOT] = 1;
	_actor[0].inventory[INV_HAND] = 1;
	_actor[0].inventory[INV_DUST] = 0;
	_actor[0].probability = 5;
	_actor[0].enemyHandler = EN_BEN;
	init_actStruct(0, 0, 11, 1, 1, 0, 0, 0);
	init_actStruct(0, 1, 12, 1, 1, 0, 0, 0);
	init_actStruct(0, 2, 1,  1, 1, 0, 0, 0);
	init_actStruct(0, 3, 1,  1, 1, 0, 0, 0);

	_actor[1].damage = 0;
	_actor[1].maxdamage = -1;
	_actor[1].field_8 = 1;
	_actor[1].field_C = 0;
	_actor[1].speed = 0;
	_actor[1].field_14 = 0;
	_actor[1].field_18 = 0;
	_actor[1].x = 160;
	_actor[1].y = 0;
	_actor[1].y1 = -1;
	_actor[1].x1 = -1;
	_actor[1].field_2C = 2;
	_actor[1].field_30 = 0;
	_actor[1].field_34 = 0;
	_actor[1].field_38 = 0;
	_actor[1].lost = 0;
	_actor[1].kicking = 0;
	_actor[1].field_44 = 0;
	_actor[1].field_48 = 0;
	_actor[1].field_4C = 0;
	_actor[1].scenePropSubIdx = 0;
	_actor[1].field_54 = 0;
	_actor[1].runningSound = 0;
	_actor[1].weapon = INV_HAND;
	_actor[1].inventory[INV_CHAIN] = 0;
	_actor[1].inventory[INV_CHAINSAW] = 0;
	_actor[1].inventory[INV_MACE] = 1;
	_actor[1].inventory[INV_2X4] = 0;
	_actor[1].inventory[INV_WRENCH] = 0;
	_actor[1].inventory[INV_BOOT] = 0;
	_actor[1].inventory[INV_HAND] = 0;
	_actor[1].inventory[INV_DUST] = 0;
	_actor[1].probability = 5;
	_actor[1].enemyHandler = -1;

	init_actStruct(1, 0, 14, 1, 1, 0, 0, 0);
	init_actStruct(1, 1, 15, 1, 1, 0, 0, 0);
	init_actStruct(1, 2, 13, 1, 1, 0, 0, 0);
	init_actStruct(1, 3, 13, 1, 1, 0, 0, 0);

	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
			_enemyState[i][j] = 0;
}

void Insane::init_actStruct(int actornum, int actnum, int32 actorval, byte state, 
								  int32 room, int32 facing, int32 speedX, int32 frame) {
	_actor[actornum].act[actnum].actor = actorval;
	_actor[actornum].act[actnum].state = state;
	_actor[actornum].act[actnum].room = room;
	_actor[actornum].act[actnum].facing = facing;
	_actor[actornum].act[actnum].speedX = speedX;
	_actor[actornum].act[actnum].frame = frame;
}

void Insane::init_enemyStruct(int n, int32 handler, int32 initializer,
								   int32 field_8, int32 maxdamage, int32 field_10,
								   int32 weapon, int32 sound, const char *filename,
								   int32 costume4, int32 costume6, int32 costume5,
								   int16 field_2C, int32 field_30, int32 field_34) {
	assert(strlen(filename) < 20);

	_enemy[n].handler = handler;
	_enemy[n].initializer = initializer;
	_enemy[n].field_8 = field_8;
	_enemy[n].maxdamage = maxdamage;
	_enemy[n].field_10 = field_10;
	_enemy[n].weapon = weapon;
	_enemy[n].sound = sound;
	strncpy(_enemy[n].filename, filename, 20);
	_enemy[n].costume4 = costume4;
	_enemy[n].costume6 = costume6;
	_enemy[n].costume5 = costume5;
	_enemy[n].field_2C = field_2C;
	_enemy[n].field_30 = field_30;
	_enemy[n].field_34 = field_34;
}

void Insane::init_fluConfStruct(int n, int sceneId, byte *fluPtr, 
					const char *filenamePtr, int startFrame, int numFrames) {
	_fluConf[n].sceneId = sceneId;
	_fluConf[n].fluPtr = fluPtr;
	_fluConf[n].filenamePtr = filenamePtr;
	_fluConf[n].startFrame = startFrame;
	_fluConf[n].numFrames = numFrames;
}

void Insane::init_scenePropStruct(int32 n, int32 n1, int32 actornum, int32 sound, int32 trsId,
					  byte r, byte g, byte b, int32 counter, int32 maxCounter,
					  int32 index) {
	_sceneProp[n].actor = actornum; // main actor number, -1 if not applicable
	_sceneProp[n].sound = sound;
	_sceneProp[n].trsId = trsId;
	_sceneProp[n].r = r;
	_sceneProp[n].g = g;
	_sceneProp[n].b = b;
	_sceneProp[n].counter = counter;
	_sceneProp[n].maxCounter = maxCounter;
	_sceneProp[n].index = index;
}

int32 Insane::enemyInitializer(int num, int32 actor1, int32 actor2, int32 probability) {
	switch (num) {
	case EN_ROTT1:
		return enemy0initializer(actor1, actor2, probability);
		break;
	case EN_ROTT2:
		return enemy1initializer(actor1, actor2, probability);
		break;
	case EN_ROTT3:
		return enemy2initializer(actor1, actor2, probability);
		break;
	case EN_VULTF1:
		return enemy3initializer(actor1, actor2, probability);
		break;
	case EN_VULTM1:
		return enemy4initializer(actor1, actor2, probability);
		break;
	case EN_VULTF2:
		return enemy5initializer(actor1, actor2, probability);
		break;
	case EN_VULTM2:
		return enemy6initializer(actor1, actor2, probability);
		break;
	case EN_CAVEFISH:
		return enemy7initializer(actor1, actor2, probability);
		break;
	case EN_TORQUE:
		return enemy8initializer(actor1, actor2, probability);
		break;
	case -1:
		// nothing
		break;
	}

	return 0;
}


int32 Insane::enemyHandler(int num, int32 actor1, int32 actor2, int32 probability) {
	switch (num) {
	case EN_ROTT1:
		return enemy0handler(actor1, actor2, probability);
		break;
	case EN_ROTT2:
		return enemy1handler(actor1, actor2, probability);
		break;
	case EN_ROTT3:
		return enemy2handler(actor1, actor2, probability);
		break;
	case EN_VULTF1:
		return enemy3handler(actor1, actor2, probability);
		break;
	case EN_VULTM1:
		return enemy4handler(actor1, actor2, probability);
		break;
	case EN_VULTF2:
		return enemy5handler(actor1, actor2, probability);
		break;
	case EN_VULTM2:
		return enemy6handler(actor1, actor2, probability);
		break;
	case EN_CAVEFISH:
		return enemy7handler(actor1, actor2, probability);
		break;
	case EN_TORQUE:
		return enemy8handler(actor1, actor2, probability);
		break;
	case EN_BEN:
		return enemyBenHandler(actor1, actor2, probability);
		break;
	case -1:
		// nothing
		break;
	}
	return 0;
}

int32 Insane::enemy0handler(int32 actor1, int32 actor2, int32 probability) {
	int32 act1damage, act2damage, act1x, act2x, retval;
	int32 dist;

	retval = 0;
	act1damage = _actor[actor1].damage; // ebx
	act2damage = _actor[actor2].damage; // ebp
	act1x = _actor[actor1].x; // esi
	act2x = _actor[actor2].x; // edi

	if (!_actor[actor1].field_4C) {
		if (_val131w > _val132w) {
			if (act1damage - act2damage >= 30) {
				if (rand() % probability != 1)
					_val130b = 0;
				else
					_val130b = 1;
			}
			_val131w = 0;
			_val132w = rand() % (probability * 2);
		}

		dist = ABS(act1x - act2x);

		if (_val133w > _val134w) {
			if (_val130b == 1) {
				if (weaponMaxRange(actor1) < dist) {
					if (act2x < act1x)
						_actor[1].field_14 = -101;
					else
						_actor[1].field_14 = 101;
				} else {
					if (weaponMinRange(actor1) > dist) {
						if (act2x < act1x)
							_actor[1].field_14 = 101;
						else
							_actor[1].field_14 = -101;
					} else {
						_actor[1].field_14 = 0;
					}
				}
			} else {
				if (weaponMaxRange(actor2) < dist) {
					if (act2x < act1x)
						_actor[1].field_14 = 101;
					else
						_actor[1].field_14 = -101;
				} else {
					_actor[1].field_14 = 0;
				}
			}
			_val133w = 0;
			_val134w = rand() % probability;
		}
		if (_val135w < _val136w) {
			if (weaponMaxRange(actor2) + 40 >= dist) {
				if (rand() % probability == 1)
					retval = 1;
			}
			if (_actor[actor1].kicking) {
				if (weaponMaxRange(actor2) <= dist)
					if (rand() % (probability * 2) <= 1)
						retval = 1;
			}
			_val135w = 0;
			_val136w = ABS(rand() % probability) * 2;
		}

		if (_actor[actor1].weapon == -1)
			retval = 2;

		if ((_actor[actor1].field_54 == 0) &&
			(_actor[actor1].lost == 0) &&
			(_actor[actor2].lost == 0)) {
			if (_actor[actor2].act[3].state == 54) {
				switch (rand() % 10) {
				case 3:
					if (!_enemyState[EN_ROTT1][6]) {
						_enemyState[EN_ROTT1][6] = 1;
						prepareScenePropScene(scenePropIdx[54], 0, 0);
					}
					break;
				case 8:
					if (!_enemyState[EN_ROTT1][4]) {
						_enemyState[EN_ROTT1][4] = 1;
						prepareScenePropScene(scenePropIdx[52], 0, 0);
					}
					break;
				}
			} else {
				switch(rand() % 15) {
				case 2:
					if (!_enemyState[EN_ROTT1][2]) {
						_enemyState[EN_ROTT1][2] = 1;
						prepareScenePropScene(scenePropIdx[50], 0, 0);
					}
					break;
				case 4:
					if (!_enemyState[EN_ROTT1][3]) {
						_enemyState[EN_ROTT1][3] = 1;
						prepareScenePropScene(scenePropIdx[51], 0, 0);
					}
					break;
				case 6:
					if (!_enemyState[EN_ROTT1][7]) {
						_enemyState[EN_ROTT1][7] = 1;
						if (_enemy[EN_ROTT1].field_8)
							prepareScenePropScene(scenePropIdx[55], 0, 0);
					}
					break;
				case 9:
					if (!_enemyState[EN_ROTT1][5]) {
						_enemyState[EN_ROTT1][5] = 1;
						prepareScenePropScene(scenePropIdx[53], 0, 0);
					}
					break;
				case 11:
					if (!_enemyState[EN_ROTT1][8]) {
						_enemyState[EN_ROTT1][8] = 1;
						prepareScenePropScene(scenePropIdx[56], 0, 0);
					}
					break;
				default:
					break;
				}
			}
		}
		_val131w++;
		_val133w++;
		_val135w++;
	}

	if (act1x > 310)
		_actor[1].field_14 = -320;
	else if (act1x < 10)
		_actor[1].field_14 = 320;
	else if (act1x > 280)
		_actor[1].field_14 = -160;

	// Shift+V cheat to win the battle
	if (_scumm->getKeyState(0x56) && !_beenCheated &&
		!_actor[0].lost && !_actor[1].lost) {
		_beenCheated = 1;
		_actor[1].damage = _actor[1].maxdamage + 10;
	}

	return retval;
}

int32 Insane::enemy0initializer(int32 actor1, int32 actor2, int32 probability) {
	int i;

	for (i = 0; i < 9; i++)
		_enemyState[EN_ROTT1][i] = 0;

	_val130b = 0;
	_val131w = 0;
	_val132w = 0;
	_val133w = 0;
	_val134w = 0;
	_val135w = 0;
	_val136w = 0;
	_beenCheated = 0;

	return 1;
}

int32 Insane::enemy1handler(int32 actor1, int32 actor2, int32 probability) {
	// FIXME: implement
	warning("stub Insane::enemy1handler(%d, %d, %d)", actor1, actor2, probability);
	return 0;
}

int32 Insane::enemy1initializer(int32 actor1, int32 actor2, int32 probability) {
	int i;

	for (i = 0; i < 9; i++)
		_enemyState[EN_ROTT2][i] = 0;

	_val140b = 0;
	_val141w = 0;
	_val142w = 0;
	_val143w = 0;
	_val144w = 0;
	_val145w = 0;
	_val146w = 0;
	_beenCheated = 0;

	return 1;
}

int32 Insane::enemy2handler(int32 actor1, int32 actor2, int32 probability) {
	int32 act1damage, act2damage, act1x, act2x, retval;
	int32 dist;

	debug(0, "enemy2handler()");

	retval = 0;
	act1damage = _actor[actor1].damage; // ebx
	act2damage = _actor[actor2].damage; // ebp
	act1x = _actor[actor1].x; // esi
	act2x = _actor[actor2].x; // edi

	if (!_actor[actor1].field_4C) {
		if (_val151w > _val152w) {
			if (act1damage - act2damage >= 30) {
				if (rand() % probability != 1)
					_val150b = 0;
				else
					_val150b = 1;
			}
			_val151w = 0;
			_val152w = rand() % (probability * 2);
		}

		dist = ABS(act1x - act2x);

		if (_val153w > _val154w) {
			if (_val150b == 1) {
				if (weaponMaxRange(actor1) < dist) {
					if (act2x < act1x)
						_actor[1].field_14 = -101;
					else
						_actor[1].field_14 = 101;
				} else {
					if (weaponMinRange(actor1) > dist) {
						if (act2x < act1x)
							_actor[1].field_14 = 101;
						else
							_actor[1].field_14 = -101;
					} else {
						_actor[1].field_14 = 0;
					}
				}
			} else {
				if (weaponMaxRange(actor2) < dist) {
					if (act2x < act1x)
						_actor[1].field_14 = 101;
					else
						_actor[1].field_14 = -101;
				} else {
					_actor[1].field_14 = 0;
				}
			}
			_val153w = 0;
			_val154w = rand() % probability;
		}
		if (_val155w < _val156w) {
			if (weaponMaxRange(actor2) + 40 >= dist) {
				if (rand() % probability == 1)
					retval = 1;
			}
			if (_actor[actor1].kicking) {
				if (weaponMaxRange(actor2) <= dist)
					if (rand() % (probability * 2) <= 1)
						retval = 1;
			}
			_val155w = 0;
			_val156w = ABS(rand() % probability) * 2;
		}

		if (_actor[actor1].weapon == -1)
			retval = 2;

		if ((_actor[actor1].field_54 == 0) &&
			(_actor[actor1].lost == 0) &&
			(_actor[actor2].lost == 0)) {
			if (_actor[actor2].act[3].state == 54) {
				switch (rand() % 10) {
				case 3:
					if (!_enemyState[EN_ROTT3][1]) {
						_enemyState[EN_ROTT3][1] = 1;
						prepareScenePropScene(scenePropIdx[26], 0, 0);
					}
					break;
				case 5:
					if (!_enemyState[EN_ROTT3][3]) {
						_enemyState[EN_ROTT3][3] = 1;
						prepareScenePropScene(scenePropIdx[28], 0, 0);
					}
					break;
				case 8:
					if (!_enemyState[EN_ROTT3][2]) {
						_enemyState[EN_ROTT3][2] = 1;
						prepareScenePropScene(scenePropIdx[27], 0, 0);
					}
					break;
				}
			} else {
				if (_actor[1].kicking) {
					if (rand() % 10 == 9) {
						if (!_enemyState[EN_ROTT3][6]) {
							_enemyState[EN_ROTT3][6] = 1;
							prepareScenePropScene(scenePropIdx[31], 0, 0);
						}
					}
				} else {
					if (rand() % 15 == 7) {
						if (!_enemyState[EN_ROTT3][5]) {
							_enemyState[EN_ROTT3][5] = 1;
							prepareScenePropScene(scenePropIdx[30], 0, 0);
						}
					}
				}
			}
		}
		_val151w++;
		_val153w++;
		_val155w++;
	}

	if (act1x > 310)
		_actor[1].field_14 = -320;
	else if (act1x < 10)
		_actor[1].field_14 = 320;
	else if (act1x > 280)
		_actor[1].field_14 = -160;

	// Shift+V cheat to win the battle
	if (_scumm->getKeyState(0x56) && !_beenCheated &&
		!_actor[0].lost && !_actor[1].lost) {
		_beenCheated = 1;
		_actor[1].damage = _actor[1].maxdamage + 10;
	}

	return retval;
}

int32 Insane::enemy2initializer(int32 actor1, int32 actor2, int32 probability) {
	int i;

	debug(0, "enemy2initializer()");

	for (i = 0; i < 7; i++)
		_enemyState[EN_ROTT3][i] = 0;

	_val150b = 0;
	_val151w = 0;
	_val152w = 0;
	_val153w = 0;
	_val154w = 0;
	_val155w = 0;
	_val156w = 0;
	_beenCheated = 0;

	return 1;
}

int32 Insane::enemy3handler(int32 actor1, int32 actor2, int32 probability) {
	// FIXME: implement
	warning("stub Insane::enemy3handler(%d, %d, %d)", actor1, actor2, probability);
	return 0;
}

int32 Insane::enemy3initializer(int32 actor1, int32 actor2, int32 probability) {
	int i;

	for (i = 0; i < 6; i++)
		_enemyState[EN_VULTF1][i] = 0;

	_val160b = 0;
	_val161w = 0;
	_val162w = 0;
	_val163w = 0;
	_val164w = 0;
	_val165w = 0;
	_val166w = 0;
	_val167w = 0;
	_val168w = 0;
	_beenCheated = 0;

	return 1;
}

int32 Insane::enemy4handler(int32 actor1, int32 actor2, int32 probability) {
	// FIXME: implement
	warning("stub Insane::enemy4handler(%d, %d, %d)", actor1, actor2, probability);
	return 0;
}

int32 Insane::enemy4initializer(int32 actor1, int32 actor2, int32 probability) {
	int i;

	for (i = 0; i < 10; i++)
		_enemyState[EN_VULTM1][i] = 0;

	_val170b = 0;
	_val171w = 0;
	_val172w = 0;
	_val173w = 0;
	_val174w = 0;
	_val175w = 0;
	_val176w = 0;
	_beenCheated = 0;

	return 1;
}

int32 Insane::enemy5handler(int32 actor1, int32 actor2, int32 probability) {
	// FIXME: implement
	warning("stub Insane::enemy5handler(%d, %d, %d)", actor1, actor2, probability);
	return 0;
}

int32 Insane::enemy5initializer(int32 actor1, int32 actor2, int32 probability) {
	int i;

	for (i = 0; i < 9; i++)
		_enemyState[EN_VULTF2][i] = 0;

	_val181b = 0;
	_val182b = 0;
	_val183d = 0;
	_val180d = 0;
	_beenCheated = 0;

	return 1;
}

int32 Insane::enemy6handler(int32 actor1, int32 actor2, int32 probability) {
	// FIXME: implement
	warning("stub Insane::enemy6handler(%d, %d, %d)", actor1, actor2, probability);
	return 0;
}

int32 Insane::enemy6initializer(int32 actor1, int32 actor2, int32 probability) {
	int i;

	for (i = 0; i < 7; i++)
		_enemyState[EN_VULTM2][i] = 0;

	_val190d = 0;
	_val191w = 0;
	_beenCheated = 0;

	return 1;
}

int32 Insane::enemy7handler(int32 actor1, int32 actor2, int32 probability) {
	// FIXME: implement
	warning("stub Insane::enemy7handler(%d, %d, %d)", actor1, actor2, probability);
	return 0;
}

int32 Insane::enemy7initializer(int32 actor1, int32 actor2, int32 probability) {
	_val202b = 0;
	_val200d = 0;
	_val201d = 0;
	_beenCheated = 0;

	return 1;
}

int32 Insane::enemy8handler(int32 actor1, int32 actor2, int32 probability) {
	_actor[actor1].field_14 = 0;
	return 0;
}

int32 Insane::enemy8initializer(int32 actor1, int32 actor2, int32 probability) {
	return 1;
}

int32 Insane::enemyBenHandler(int32 actor1, int32 actor2, int32 probability) {
	int32 retval;
	int32 tmp;

	retval = func75();
	
	// Joystick support
	// if (func77())
	//	retval |= func78();

	retval |= processKeyboard();

	tmp = _enemyState[EN_BEN][0] - 160;
	if (tmp < -160)
		tmp = -160;

	if (tmp > 160)
		tmp = 160;

	_actor[actor1].field_14 = tmp;

	smush_setupSomething(_enemyState[EN_BEN][0], _enemyState[EN_BEN][1], -1);
	
	return retval & 3;
}

int32 Insane::func75(void) {
	// FIXME: implement
	return 0;
}

int32 Insane::processKeyboard(void) {
	int32 retval = 0;
	int dx = 0, dy = 0;
	int tmpx, tmpy;

	if (_scumm->getKeyState(0x14f) || _scumm->getKeyState(0x14b) || _scumm->getKeyState(0x147))
		dx--;

	if (_scumm->getKeyState(0x151) || _scumm->getKeyState(0x14d) || _scumm->getKeyState(0x149))
		dx++;

	if (_scumm->getKeyState(0x147) || _scumm->getKeyState(0x148) || _scumm->getKeyState(0x149))
		dy--;

	if (_scumm->getKeyState(0x14f) || _scumm->getKeyState(0x150) || _scumm->getKeyState(0x151))
		dy++;

	if (dx == _keybOldDx)
		_velocityX += 4;
	else
		_velocityX = 3;

	if (dy == _keybOldDy)
		_velocityY += 4;
	else
		_velocityY = 2;

	_keybOldDx = dx;
	_keybOldDy = dy;

	if (_velocityX > 48)
		_velocityX = 48;

	if (_velocityY > 32)
		_velocityY = 32;

	_keybX += dx * _velocityX;
	_keybY += dy * _velocityY;

	tmpx = _keybX / 4;
	tmpy = _keybY / 4;

	_keybX -= tmpx * 4;
	_keybY -= tmpy * 4;

	if (tmpx || tmpy) {
		_enemyState[EN_BEN][0] += tmpx;
		_enemyState[EN_BEN][1] += tmpy;
	}

	if (_scumm->getKeyState(0x0d))
		retval |= 1;

	if (_scumm->getKeyState(0x09))
		retval |= 2;

	return retval;
}

void Insane::readFileToMem(const char *name, byte **buf) {
	File *in;
	uint32 len;

	in = new File();
	in->open(name, _scumm->getGameDataPath());
	len = in->size();
	*buf = (byte *)malloc(len);
	in->read(*buf, len);
	in->close();
}

void Insane::runScene(int arraynum) {
	//	  procPtr5 = &procPtr5Body;
	//	  procPtr6 = &procPtr6Body;
	//	  procIact = &handleIact;
	//	  ptrMainLoop = &ptrMainLoopBody;

	_insaneIsRunning = true;
	_player = new SmushPlayer(_scumm, _speed, _subtitles);
	_player->insanity(true);

	_numberArray = arraynum;

	// set4Values()
	_val109w = 114;
	_val110w = 256;
	_val111w = 4;
	_val112w = 256;
	// set1Value()
	_val113d = 0;
	// zeroValues1()
	_objArray2Idx = 0;
	_objArray2Idx2 = 0;
	// zeroValues2()
	_objArray1Idx = 0;
	_objArray1Idx2 = 0;
	// zeroValues3()
	_currScenePropIdx = 0;
	_currScenePropSubIdx = 0;
	_currTrsMsg = 0;

	smush_proc41();
	smush_setupSomething(160, 100, -1);
	putActors();
	readState();
	_val10b = _val50d; // FIXME: seems to be unused
	setTrsFile(_trsFilePtr); // FIXME: we don't need it

	debug(0, "INSANE Arg: %d", readArray(_numberArray, 0));

	switch (readArray(_numberArray, 0)) {
	case 1:
		initScene(1);
		setupValues();
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 10));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		startVideo("minedriv.san", 1, 32, 12, 0);
		break;
	case 2:
		setupValues();
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 11));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		_val8d = readArray(_numberArray, 2);
		if (_val55d) {
			initScene(5);
			startVideo("tovista2.san", 1, 32, 12, 0);
		} else {
			if (_val56d) {
				initScene(5);
				startVideo1("tovista2.san", 1, 32, 12, 0, _smush_tovista2Flu, 60);
			} else {
				initScene(4);
				startVideo("tovista1.san", 1, 32, 12, 0);
			}
		}
		break;
	case 3:
		setupValues();
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 11));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		_val8d = readArray(_numberArray, 2);
		if (_val55d) {
			initScene(6);
			startVideo1("toranch.san", 1, 32, 12, 0, _smush_toranchFlu, 300);
		} else {
			if (_val56d) {
				initScene(6);
				startVideo1("toranch.san", 1, 32, 12, 0, _smush_toranchFlu, 240);
			} else {
				initScene(6);
				startVideo("toranch.san", 1, 32, 12, 0);
			}
		}
		break;
	case 4:
		_firstBattle = true;
		_currEnemy = EN_ROTT1;
		initScene(13);
		startVideo("minefite.san", 1, 32, 12, 0);
		break;
	case 5:
		setWordInString(_numberArray, 1, _val54d);
		initScene(24);
		startVideo("rottopen.san", 1, 32, 12, 0);
		break;
	case 6:
		initScene(1);
		setupValues();
		smlayer_setFluPalette(_smush_roadrashRip, 1);
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 10));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		startVideo1("minedriv.san", 1, 32, 12, 0, _smush_minedrivFlu, 420);
		break;
	case 7:
	case 8:
	case 9:
		break;
	case 10:
		initScene(26);
		setWordInString(_numberArray, 1, _val54d);
		startVideo("credits.san", 1, 32, 12, 0);
	default:
		warning("Unknown FT_INSANE mode %d", readArray(_numberArray, 0));
		break;
	}

	resetTrsFilePtr(); // FIXME: we don't need it
	smush_proc39();
	putActors();
	smush_proc40();
	_scumm->_sound->pauseSounds(0); // IMUSE_Resume();
	_enemy[EN_ROTT3].maxdamage = 120;

	_insaneIsRunning = false;

	setWordInString(_numberArray, 50, _actor[0].inventory[INV_CHAIN]);
	setWordInString(_numberArray, 51, _actor[0].inventory[INV_CHAINSAW]);
	setWordInString(_numberArray, 52, _actor[0].inventory[INV_MACE]);
	setWordInString(_numberArray, 53, _actor[0].inventory[INV_2X4]);
	setWordInString(_numberArray, 54, _actor[0].inventory[INV_WRENCH]);
	setWordInString(_numberArray, 55, _actor[0].inventory[INV_DUST]);
	setWordInString(_numberArray, 337, _enemy[EN_TORQUE].field_8);
	setWordInString(_numberArray, 329, _enemy[EN_ROTT1].field_8);
	setWordInString(_numberArray, 330, _enemy[EN_ROTT2].field_8);
	setWordInString(_numberArray, 331, _enemy[EN_ROTT3].field_8);
	setWordInString(_numberArray, 332, _enemy[EN_VULTF1].field_8);
	setWordInString(_numberArray, 333, _enemy[EN_VULTM1].field_8);
	setWordInString(_numberArray, 334, _enemy[EN_VULTF2].field_8);
	setWordInString(_numberArray, 335, _enemy[EN_VULTM2].field_8);
	setWordInString(_numberArray, 336, _enemy[EN_CAVEFISH].field_8);
	setWordInString(_numberArray, 339, _enemy[EN_VULTF2].field_10);
	setWordInString(_numberArray, 56, _enemy[EN_CAVEFISH].field_10);
	setWordInString(_numberArray, 340, _enemy[EN_VULTM2].field_10);
	// insane_unlock(); // FIXME
	_scumm->_sound->stopAllSounds(); // IMUSE_StopAllSounds();
	if (_memoryAllocatedNotOK) {
		error("Memory Alloc Error in Mineroad (Heap Size?)");
	}
	
	delete _player;
}

void Insane::startVideo(const char *filename, int num, int argC, int frameRate, 
						int doMainLoop) {
	startVideo1(filename, num, argC, frameRate, doMainLoop, 0, 0);
}

void Insane::blah(void) {
	Actor *a = _scumm->derefActor(1, "smlayer_setActorCostume");

	_scumm->_currentRoom = _smlayer_room;
	a->setActorCostume(readArray(_numberArray, _enemy[8].costume4));
	a->setDirection(180);
	a->startAnimActor(1);
	a->putActor(100, 100, _smlayer_room);

	while (true) {
		if (!smlayer_isSoundRunning(87))
			smlayer_startSound1(87);

		_scumm->_sound->processSoundQues();

		_scumm->parseEvents();
		_scumm->processKbd();

		_scumm->setActorRedrawFlags();
		_scumm->resetActorBgs();
		_scumm->processActors();

		_scumm->drawDirtyScreenParts();
		_scumm->_system->update_screen();
		if (_scumm->_quit)
			break;
		_scumm->_system->delay_msecs(500);
	}
}


void Insane::startVideo1(const char *filename, int num, int argC, int frameRate, 
						 int doMainLoop, byte *fluPtr, int32 numFrames) {

	// Demo has different insane, so disable it now
	if (_scumm->_features & GF_DEMO)
		return;

	_smush_curFrame = 0;
	_smush_isSanFileSetup = 0;
	_smush_setupsan4 = 0;
	_smush_smushState = 0;
	_smush_setupsan1 = 0;
	_smush_setupsan17 = 0;


	if (fluPtr) {
		smush_setupSanWithFlu(filename, 0, -1, -1, 0, fluPtr, numFrames);
	} else {
		smush_setupSanFromStart(filename, 0, -1, -1, 0);
	}

	// Everything below is a temporary and wrong implementation
	// FIXME: implement

	// blah();
	
	_player->play(filename, _scumm->getGameDataPath());

	return;

	_scumm->_videoFinished = false;

	while (true) {
		procPreRendering();

		smlayer_mainLoop(); // we avoid calling ptrs here

		_scumm->parseEvents();
		_scumm->processKbd();
		_scumm->processActors();
		_scumm->_sound->processSoundQues();
	
		if (1) {
			uint32 end_time, start_time;
		
			start_time = _scumm->_system->get_msecs();

		   _scumm->drawDirtyScreenParts(); // FIXME: remove

			_scumm->_system->update_screen();
			end_time = _scumm->_system->get_msecs();
		}

		procPostRendering(_player->_dst, 0, 0, 0, _smush_curFrame, _smush_numFrames);

		_smush_curFrame++;

		debug(0, "Frame: %d %d", _smush_curFrame, _smush_numFrames);

		if (_scumm->_quit || _scumm->_videoFinished)
			break;
		_scumm->_system->delay_msecs(100);
	}
}

int Insane::smlayer_mainLoop(void) {
	// FIXME: implement
	warning("stub Insane::smlayer_mainLoop");
	mainLoop();
	return 1;
}

void Insane::smush_proc39(void) {
	// FIXME: implement
	warning("stub Insane::smush_proc39");
}

void Insane::smush_proc40(void) {
	// FIXME: implement
	warning("stub Insane::smush_proc40");
}

void Insane::smush_proc41(void) {
	// FIXME: implement
	warning("stub Insane::smush_proc41");
}

void Insane::smush_setupSomething(int x, int y, int flag) {
	// FIXME: implement
}

void Insane::putActors(void) {
	smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1, _smlayer_room);
	smlayer_putActor(0, 0, _actor[0].x, _actor[0].y1, _smlayer_room);
	smlayer_putActor(0, 1, _actor[0].x, _actor[0].y1, _smlayer_room);
	smlayer_putActor(1, 2, _actor[0].x, _actor[0].y1, _smlayer_room);
	smlayer_putActor(1, 0, _actor[0].x, _actor[0].y1, _smlayer_room);
	smlayer_putActor(1, 1, _actor[0].x, _actor[0].y1, _smlayer_room);
}

void Insane::readState(void) {
	_actor[0].inventory[INV_CHAIN] = readArray(_numberArray, 50) != 0; // Chain
	_actor[0].inventory[INV_CHAINSAW] = readArray(_numberArray, 51) != 0; // Chainsaw
	_actor[0].inventory[INV_MACE] = readArray(_numberArray, 52) != 0; // Mace
	_actor[0].inventory[INV_2X4] = readArray(_numberArray, 53) != 0; // 2x4
	_actor[0].inventory[INV_WRENCH] = readArray(_numberArray, 54) != 0; // Wrench
	_actor[0].inventory[INV_DUST] = readArray(_numberArray, 55) != 0; // Dust
	_actor[0].inventory[INV_HAND] = 1; // Boot
	_actor[0].inventory[INV_BOOT] = 1; // Hand

	_smlayer_room = readArray(_numberArray, 320);
	_smlayer_room2 = readArray(_numberArray, 321);
	_val55d = readArray(_numberArray, 322);
	_val53d = readArray(_numberArray, 323);
	_val57d = readArray(_numberArray, 324);
	_val52d = readArray(_numberArray, 325);
	_val56d = readArray(_numberArray, 326);
	_val54d = readArray(_numberArray, 327);
	_val51d = readArray(_numberArray, 328);
	_enemy[EN_TORQUE].field_8 = readArray(_numberArray, 337);
	_enemy[EN_ROTT1].field_8 = readArray(_numberArray, 329);
	_enemy[EN_ROTT2].field_8 = readArray(_numberArray, 330);
	_enemy[EN_ROTT3].field_8 = readArray(_numberArray, 331);
	_enemy[EN_VULTF1].field_8 = readArray(_numberArray, 332);
	_enemy[EN_VULTM1].field_8 = readArray(_numberArray, 333);
	_enemy[EN_VULTF2].field_8 = readArray(_numberArray, 334);
	_enemy[EN_VULTM2].field_8 = readArray(_numberArray, 335);
	_enemy[EN_CAVEFISH].field_8 = readArray(_numberArray, 336);
	_enemy[EN_VULTM2].field_10 = readArray(_numberArray, 340);
	_enemy[EN_CAVEFISH].field_10 = readArray(_numberArray, 56);
	_enemy[EN_VULTF2].field_10 = readArray(_numberArray, 339);
}

void Insane::setTrsFile(int file) {
	// FIXME: we don't need it
}

void Insane::resetTrsFilePtr(void) {
	// FIXME: we don't need it
}

int Insane::initScene(int sceneId) {
	debug(0, "initScene(%d)", sceneId);

	if (_needSceneSwitch)
		return 1;

	stopSceneSounds(_currSceneId); // do it for previous scene
	loadSceneData(sceneId, 0, 1);
	if (loadSceneData(sceneId, 0, 2)) {
		setSceneCostumes(sceneId);
		_sceneData2Loaded = 0;
		_sceneData1Loaded = 0;
	} else
		_sceneData2Loaded = 1;

	_currSceneId = sceneId;
	return 1;
}

void Insane::stopSceneSounds(int sceneId) {
	int flag = 0;

	debug(0, "stopSceneSounds(%d)", sceneId);

	switch (sceneId) {
	case 1:
		smlayer_stopSound(88);
		smlayer_stopSound(86);
		smlayer_stopSound(87);
		flag = 1;
		break;
	case 18:
	case 19:
		smlayer_stopSound(88);
		flag = 1;
		break;
	case 17:
		smlayer_stopSound(88);
		smlayer_stopSound(94);
		flag = 1;
		break;
	case 2:
	case 7:
	case 8:
		flag = 1;
		break;
	case 3:
	case 21:
		flag = 1;
		// break is omittted intentionally
	case 13:
		if (_actor[0].runningSound != 0)
			smlayer_stopSound(_actor[0].runningSound);
		_actor[0].runningSound = 0;
	
		if (_actor[1].runningSound != 0)
			smlayer_stopSound(_actor[1].runningSound);
		_actor[1].runningSound = 0;
	
		if (_currScenePropIdx != 0)
			shutCurrentScene();
	
		_currScenePropSubIdx = 0;
		_currTrsMsg = 0;
		_actor[0].field_4C = 0;
		_actor[0].scenePropSubIdx = 0;
		_actor[0].field_54 = 0;
		_actor[1].field_4C = 0;
		_actor[1].scenePropSubIdx = 0;
		_actor[1].field_54 = 0;
		smlayer_stopSound(89);
		smlayer_stopSound(90);
		smlayer_stopSound(91);
		smlayer_stopSound(92);
		smlayer_stopSound(93);
		smlayer_stopSound(95);
		smlayer_stopSound(87);
		break;
	case 4:
	case 5:
	case 6:
		smlayer_stopSound(88);
		smlayer_stopSound(86);
		flag = 1;
		break;
	case 24:
		smlayer_stopSound(90);
		break;
	case 9:
	case 10:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 20:
	case 22:
	case 23:
		break;
	default:
		error("Insane::stopSceneSounds(%d): default case %d", 
			  sceneId, sceneId);
	}
	smush_proc39();
	if (!flag)
		return;

	smlayer_setActorCostume(0, 2, 0);
	smlayer_setActorCostume(0, 0, 0);
	smlayer_setActorCostume(0, 1, 0);
	smlayer_setActorCostume(1, 2, 0);
	smlayer_setActorCostume(1, 0, 0);
	smlayer_setActorCostume(1, 1, 0);
	
	return;
}

void Insane::shutCurrentScene(void) {
	debug(0, "shutCurrentScene()");

	_currScenePropIdx = 0;
	_currTrsMsg = 0;
	_currScenePropSubIdx = 0;
	_actor[1].scenePropSubIdx = 0;
	_actor[1].field_4C = 0;
	
	if (_actor[1].runningSound != 0) {
		smlayer_stopSound(_actor[1].runningSound);
		_actor[1].runningSound = 0;
	}

	_actor[0].scenePropSubIdx = 0;
	_actor[0].field_4C = 0;

	if (_actor[0].runningSound != 0) {
		smlayer_stopSound(_actor[0].runningSound);
		_actor[0].runningSound = 0;
	}

	_val39_ = true;
}


// insane_loadSceneData1 & insane_loadSceneData2
int Insane::loadSceneData(int scene, int flag, int phase) {
	int retvalue = 1;

	debug(0, "Insane::loadSceneData(%d, %d, %d)", scene, flag, phase);
	//if (phase == 1) /// FIXME
	//	insane_unlock();
	switch (scene) {
	case 1:
		smlayer_loadSound(88, flag, phase);
		smlayer_loadSound(86, flag, phase);
		smlayer_loadSound(87, flag, phase);
		smlayer_loadCostume(10, phase);
		break;
	case 4:
	case 5:
	case 6:
		smlayer_loadSound(88, flag, phase);
		smlayer_loadCostume(11, phase);
		break;
	case 3:
	case 13:
		switch(_currEnemy) {
		case EN_TORQUE:
			smlayer_loadSound(59, flag, phase);
			smlayer_loadSound(93, flag, phase);
			smlayer_loadCostume(57, phase);
			smlayer_loadCostume(37, phase);
			break;
		case EN_ROTT1:
			smlayer_loadSound(201, flag, phase);
			smlayer_loadSound(194, flag, phase);
			smlayer_loadSound(195, flag, phase);
			smlayer_loadSound(199, flag, phase);
			smlayer_loadSound(205, flag, phase);
			smlayer_loadSound(212, flag, phase);
			smlayer_loadSound(198, flag, phase);
			smlayer_loadSound(203, flag, phase);
			smlayer_loadSound(213, flag, phase);
			smlayer_loadSound(215, flag, phase);
			smlayer_loadSound(216, flag, phase);
			smlayer_loadSound(217, flag, phase);
			smlayer_loadSound(218, flag, phase);
			smlayer_loadSound(90, flag, phase);
			smlayer_loadCostume(26, phase);
			smlayer_loadCostume(16, phase);
			smlayer_loadCostume(17, phase);
			smlayer_loadCostume(27, phase);
			break;
		case EN_ROTT2:
			smlayer_loadSound(242, flag, phase);
			smlayer_loadSound(244, flag, phase);
			smlayer_loadSound(236, flag, phase);
			smlayer_loadSound(238, flag, phase);
			smlayer_loadSound(239, flag, phase);
			smlayer_loadSound(240, flag, phase);
			smlayer_loadSound(258, flag, phase);
			smlayer_loadSound(259, flag, phase);
			smlayer_loadSound(260, flag, phase);
			smlayer_loadSound(243, flag, phase);
			smlayer_loadSound(244, flag, phase);
			smlayer_loadSound(245, flag, phase);
			smlayer_loadSound(246, flag, phase);
			smlayer_loadSound(233, flag, phase);
			smlayer_loadSound(234, flag, phase);
			smlayer_loadSound(241, flag, phase);
			smlayer_loadSound(242, flag, phase);
			smlayer_loadSound(90, flag, phase);
			smlayer_loadCostume(28, phase);
			smlayer_loadCostume(16, phase);
			smlayer_loadCostume(17, phase);
			smlayer_loadCostume(42, phase);
			break;
		case EN_ROTT3:
			smlayer_loadSound(223, flag, phase);
			smlayer_loadSound(224, flag, phase);
			smlayer_loadSound(225, flag, phase);
			smlayer_loadSound(226, flag, phase);
			smlayer_loadSound(228, flag, phase);
			smlayer_loadSound(229, flag, phase);
			smlayer_loadSound(230, flag, phase);
			smlayer_loadSound(232, flag, phase);
			smlayer_loadSound(220, flag, phase);
			smlayer_loadSound(221, flag, phase);
			smlayer_loadSound(222, flag, phase);
			smlayer_loadSound(90, flag, phase);
			smlayer_loadCostume(15, phase);
			smlayer_loadCostume(16, phase);
			smlayer_loadCostume(17, phase);
			smlayer_loadCostume(43, phase);
			smlayer_loadCostume(47, phase);
			break;
		case EN_VULTF1:
			smlayer_loadSound(282, flag, phase);
			smlayer_loadSound(283, flag, phase);
			smlayer_loadSound(284, flag, phase);
			smlayer_loadSound(285, flag, phase);
			smlayer_loadSound(286, flag, phase);
			smlayer_loadSound(287, flag, phase);
			smlayer_loadSound(279, flag, phase);
			smlayer_loadSound(280, flag, phase);
			smlayer_loadSound(281, flag, phase);
			smlayer_loadSound(277, flag, phase);
			smlayer_loadSound(288, flag, phase);
			smlayer_loadSound(278, flag, phase);
			smlayer_loadSound(91, flag, phase);
			smlayer_loadCostume(29, phase);
			smlayer_loadCostume(33, phase);
			smlayer_loadCostume(32, phase);
			smlayer_loadCostume(37, phase);
			break;
		case EN_VULTM1:
			smlayer_loadSound(160, flag, phase);
			smlayer_loadSound(161, flag, phase);
			smlayer_loadSound(174, flag, phase);
			smlayer_loadSound(167, flag, phase);
			smlayer_loadSound(163, flag, phase);
			smlayer_loadSound(164, flag, phase);
			smlayer_loadSound(170, flag, phase);
			smlayer_loadSound(166, flag, phase);
			smlayer_loadSound(175, flag, phase);
			smlayer_loadSound(162, flag, phase);
			smlayer_loadSound(91, flag, phase);
			smlayer_loadCostume(30, phase);
			smlayer_loadCostume(33, phase);
			smlayer_loadCostume(32, phase);
			smlayer_loadCostume(36, phase);
			break;
		case EN_VULTF2:
			smlayer_loadSound(263, flag, phase);
			smlayer_loadSound(264, flag, phase);
			smlayer_loadSound(265, flag, phase);
			smlayer_loadSound(266, flag, phase);
			smlayer_loadSound(267, flag, phase);
			smlayer_loadSound(268, flag, phase);
			smlayer_loadSound(270, flag, phase);
			smlayer_loadSound(271, flag, phase);
			smlayer_loadSound(275, flag, phase);
			smlayer_loadSound(276, flag, phase);
			smlayer_loadSound(261, flag, phase);
			smlayer_loadSound(262, flag, phase);
			smlayer_loadSound(263, flag, phase);
			smlayer_loadSound(274, flag, phase);
			smlayer_loadSound(91, flag, phase);
			smlayer_loadCostume(31, phase);
			smlayer_loadCostume(33, phase);
			smlayer_loadCostume(32, phase);
			smlayer_loadCostume(35, phase);
			smlayer_loadCostume(46, phase);
			break;
		case EN_VULTM2:
			smlayer_loadSound(179, flag, phase);
			smlayer_loadSound(183, flag, phase);
			smlayer_loadSound(184, flag, phase);
			smlayer_loadSound(186, flag, phase);
			smlayer_loadSound(191, flag, phase);
			smlayer_loadSound(192, flag, phase);
			smlayer_loadSound(180, flag, phase);
			smlayer_loadSound(101, flag, phase);
			smlayer_loadSound(289, flag, phase);
			smlayer_loadSound(177, flag, phase);
			smlayer_loadSound(178, flag, phase);
			smlayer_loadSound(290, flag, phase);
			smlayer_loadSound(102, flag, phase);
			smlayer_loadSound(91, flag, phase);
			smlayer_loadCostume(34, phase);
			smlayer_loadCostume(33, phase);
			smlayer_loadCostume(32, phase);
			smlayer_loadCostume(44, phase);
			smlayer_loadCostume(45, phase);
			break;
		case EN_CAVEFISH:
			smlayer_loadSound(291, flag, phase);
			smlayer_loadSound(100, flag, phase);
			smlayer_loadSound(92, flag, phase);
			smlayer_loadCostume(39, phase);
			smlayer_loadCostume(40, phase);
			smlayer_loadCostume(41, phase);
			break;
		default:
			error("Insane::loadSceneData(%d, %d): default case[2] %d", 
				  scene, phase, _currEnemy);
			retvalue = 0;
			break;
		}
		smlayer_loadSound(64, flag, phase);
		smlayer_loadSound(65, flag, phase);
		smlayer_loadSound(66, flag, phase);
		smlayer_loadSound(67, flag, phase);
		smlayer_loadSound(68, flag, phase);
		smlayer_loadSound(69, flag, phase);
		smlayer_loadSound(70, flag, phase);
		smlayer_loadSound(71, flag, phase);
		smlayer_loadSound(72, flag, phase);
		smlayer_loadSound(73, flag, phase);
		smlayer_loadSound(74, flag, phase);
		smlayer_loadSound(75, flag, phase);
		smlayer_loadSound(76, flag, phase);
		smlayer_loadSound(77, flag, phase);
		smlayer_loadSound(78, flag, phase);
		smlayer_loadSound(79, flag, phase);
		smlayer_loadSound(80, flag, phase);
		smlayer_loadSound(81, flag, phase);
		smlayer_loadSound(82, flag, phase);
		smlayer_loadSound(83, flag, phase);
		smlayer_loadSound(84, flag, phase);
		smlayer_loadSound(85, flag, phase);
		smlayer_loadSound(86, flag, phase);
		smlayer_loadSound(87, flag, phase);
		smlayer_loadSound(62, flag, phase);
		smlayer_loadSound(63, flag, phase);
		smlayer_loadSound(60, flag, phase);
		smlayer_loadSound(61, flag, phase);
		smlayer_loadSound(315, flag, phase);
		smlayer_loadSound(316, flag, phase);
		smlayer_loadSound(317, flag, phase);
		smlayer_loadSound(98, flag, phase);
		smlayer_loadSound(318, flag, phase);
		smlayer_loadSound(96, flag, phase);
		smlayer_loadSound(97, flag, phase);
		smlayer_loadSound(95, flag, phase);
		smlayer_loadSound(89, flag, phase);
		smlayer_loadCostume(12, phase);
		smlayer_loadCostume(13, phase);
		smlayer_loadCostume(14, phase);
		smlayer_loadCostume(18, phase);
		smlayer_loadCostume(22, phase);
		smlayer_loadCostume(19, phase);
		smlayer_loadCostume(38, phase);
		smlayer_loadCostume(20, phase);
		smlayer_loadCostume(21, phase);
		smlayer_loadCostume(23, phase);
		smlayer_loadCostume(24, phase);
		smlayer_loadCostume(25, phase);
		break;
	case 21:
	case 24:
	case 25:
		smlayer_loadSound(223, flag, phase);
		smlayer_loadSound(224, flag, phase);
		smlayer_loadSound(225, flag, phase);
		smlayer_loadSound(226, flag, phase);
		smlayer_loadSound(228, flag, phase);
		smlayer_loadSound(229, flag, phase);
		smlayer_loadSound(230, flag, phase);
		smlayer_loadSound(232, flag, phase);
		smlayer_loadSound(90, flag, phase);
		smlayer_loadCostume(15, phase);
		smlayer_loadCostume(16, phase);
		smlayer_loadCostume(17, phase);
		smlayer_loadCostume(43, phase);
		smlayer_loadSound(62, flag, phase);
		smlayer_loadSound(63, flag, phase);
		smlayer_loadSound(60, flag, phase);
		smlayer_loadSound(61, flag, phase);
		smlayer_loadSound(315, flag, phase);
		smlayer_loadSound(316, flag, phase);
		smlayer_loadSound(317, flag, phase);
		smlayer_loadSound(98, flag, phase);
		smlayer_loadSound(318, flag, phase);
		smlayer_loadSound(96, flag, phase);
		smlayer_loadSound(97, flag, phase);
		smlayer_loadSound(95, flag, phase);
		smlayer_loadSound(89, flag, phase);
		smlayer_loadCostume(12, phase);
		smlayer_loadCostume(13, phase);
		smlayer_loadCostume(14, phase);
		smlayer_loadCostume(18, phase);
		smlayer_loadCostume(22, phase);
		break;
	case 17:
		smlayer_loadSound(88, flag, phase);
		smlayer_loadSound(94, flag, phase);
		break;
	case 2:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 18:
	case 19:
	case 20:
	case 22:
	case 23:
		break;
	default:
		error("Insane::loadSceneData(%d, %d): default case %d", 
			  scene, phase, scene);
		retvalue = 0;
	}
	if (phase == 1) {
		_sceneData1Loaded = 1;
		_val11d = 0;
	}
	return retvalue;
}

void Insane::setSceneCostumes(int sceneId) {
	debug(0, "Insane::setSceneCostumes(%d)", sceneId);

	switch (sceneId) {
	case 1:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 10));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		smlayer_setFluPalette(_smush_roadrashRip, 0);
		setupValues();
		return;
		break;
	case 17:
		smlayer_setFluPalette(_smush_goglpaltRip, 0);
		setupValues();
		return;
		break;
	case 2:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 10));
		setupValues();
		return;
		break;
	case 13:
		setEnemyCostumes();
		smlayer_setFluPalette(_smush_roadrashRip, 0);
		return;
		break;
	case 21:
		_currEnemy = EN_ROTT3;
		setEnemyCostumes();
		_actor[1].y = 200;
		smlayer_setFluPalette(_smush_roadrashRip, 0);
		return;
		break;
	case 4:
	case 5:
	case 6:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 11));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		setupValues();
		return;
		break;
	case 7:
	case 8:
		setWordInString(_numberArray, 4, 0);
		return;
	case 3:
	case 9:
	case 10:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 18:
	case 19:
	case 20:
	case 22:
	case 23:
	case 24:
	case 25:
		break;
	default:
		error("Insane::setSceneCostumes: default case %d", sceneId);
	}
}

void Insane::setupValues(void) {
	_actor[0].x = 160;
	_actor[0].y = 200;
	_actor[0].speed = 0;
	_actor[0].field_8 = 1;
	_actor[0].field_C = 0;
	_actor[0].act[2].state = 1;
	_actor[0].act[0].state = 1;
	_actor[0].act[1].state = 0;
	_actor[0].act[2].room = 1;
	_actor[0].act[1].room = 0;
	_actor[0].act[0].room = 0;
	_actor[0].field_14 = 0;
	_actor[0].lost = 0;
	_currEnemy = -1;
	_val32d = -1;
	smush_setupSomething(160, 100, -1);
}

void Insane::setEnemyCostumes (void) {
	debug(0, "setEnemyCostumes()");

	smlayer_setActorCostume(0, 2, readArray(_numberArray, 12));
	smlayer_setActorCostume(0, 0, readArray(_numberArray, 14));
	smlayer_setActorCostume(0, 1, readArray(_numberArray, 13));
	smlayer_setActorLayer(0, 1, 1);
	smlayer_setActorLayer(0, 2, 5);
	smlayer_setActorLayer(0, 0, 10);
	smlayer_putActor(0, 2, _actor[0].x+11, _actor[0].y1+102, _smlayer_room2);
	smlayer_putActor(0, 1, _actor[0].x, _actor[0].y1+200, _smlayer_room2);
	smlayer_putActor(0, 0, _actor[0].x, _actor[0].y1+200, _smlayer_room2);
	
	if (_currEnemy == EN_CAVEFISH) {
		smlayer_setActorCostume(1, 2, readArray(_numberArray, _enemy[_currEnemy].costume4));
		_actor[1].act[2].room = 1;
		_actor[1].act[1].room = 0;
		_actor[1].act[0].room = 0;
		_actor[1].act[2].facing = 1;
		_actor[1].field_8 = 98;
		_actor[1].act[2].state = 98;
		_actor[1].act[0].state = 98;
		_actor[1].act[1].state = 98;
	
		smlayer_putActor(1, 2, _actor[1].x + _actor[1].act[2].speedX - 17, 
						 _actor[1].y + _actor[1].y1 - 98, _smlayer_room2);
	} else if (_currEnemy == EN_TORQUE) {
		smlayer_setActorCostume(1, 2, readArray(_numberArray, _enemy[_currEnemy].costume4));
		_actor[1].act[2].room = 1;
		_actor[1].act[1].room = 0;
		_actor[1].act[0].room = 0;
		_actor[1].field_8 = 1;
		_actor[1].act[2].state = 1;
		_actor[1].act[0].state = 1;
		_actor[1].act[1].state = 1;
		smlayer_putActor(1, 2, _actor[1].x + _actor[1].act[2].speedX - 17, 
						 _actor[1].y + _actor[1].y1 - 98, _smlayer_room2);
	} else {
		_actor[1].act[2].room = 1;
		_actor[1].act[1].room = 1;
		_actor[1].act[0].room = 1;
	
		if (_enemy[_currEnemy].costume4)
			smlayer_setActorCostume(1, 2, readArray(_numberArray, _enemy[_currEnemy].costume4));
	
		if (_enemy[_currEnemy].costume5)
			smlayer_setActorCostume(1, 0, readArray(_numberArray, _enemy[_currEnemy].costume5));
	
		if (_enemy[_currEnemy].costume6)
			smlayer_setActorCostume(1, 1, readArray(_numberArray, _enemy[_currEnemy].costume6));
	
		_actor[1].field_8 = 1;
		_actor[1].act[2].state = 1;
		_actor[1].act[0].state = 1;
		_actor[1].act[1].state = 1;
	
		if (_actor[1].act[2].room != 0)
			smlayer_putActor(1, 2, _actor[1].x + _actor[1].act[2].speedX - 17, 
							 _actor[1].y + _actor[1].y1 - 98, 
							 _smlayer_room2);
	}
	
	if (_actor[1].act[1].room != 0)
		smlayer_putActor(1, 1, _actor[1].x, _actor[1].y + _actor[1].y1,
						 _smlayer_room2);
	
	if (_actor[1].act[0].room != 0)
		smlayer_putActor(1, 0, _actor[1].x, _actor[1].y + _actor[1].y1, 
						 _smlayer_room2);
	
	smlayer_setActorLayer(1, 1, 1);
	smlayer_setActorLayer(1, 2, 5);
	smlayer_setActorLayer(1, 0, 10);
	
	_actor[1].damage = 0;
	_actor[1].x = 250;
	_actor[1].y = 300;
	_actor[1].field_14 = 0;
	_actor[1].speed = 0;
	_actor[1].weapon = -1;
	_actor[1].field_2C = 2;
	_enemy[_currEnemy].field_8++;
	_actor[1].maxdamage = _enemy[_currEnemy].maxdamage;
	_actor[1].enemyHandler = _enemy[_currEnemy].handler;
	_actor[1].field_30 = 0;
	memset (_actor[1].inventory, 8, 0);
	_actor[0].damage = 0;
	_actor[0].x = 100;
	_actor[0].y = 200;
	_actor[0].weapon = INV_HAND;
	_actor[0].field_2C = 2;
	_actor[0].field_30 = 0;
	_actor[0].field_34 = 2;
	_actor[0].field_38 = 0;
	_actor[0].speed = 0;
	_actor[0].field_8 = 1;
	_actor[0].act[2].state = 1;
	_actor[0].act[2].facing = 1;
	_actor[0].act[0].state = 0;
	_actor[0].act[1].state = 1;
	_actor[0].act[2].room = 1;
	_actor[0].act[1].room = 1;
	_actor[0].act[0].room = 1;
	_actor[0].field_14 = 0;
	_actor[0].field_4C = 0;
	_actor[0].scenePropSubIdx = 0;
	_actor[0].field_54 = 0;
	_actor[0].runningSound = 0;
	_actor[0].lost = 0;
	_actor[0].kicking = 0;
	_actor[0].field_44 = 0;
	_actor[1].inventory[_enemy[_currEnemy].weapon] = 1;
	_actor[0].field_44 = 0;
	_actor[0].field_48 = 0;
	_actor[1].field_4C = 0;
	_actor[1].scenePropSubIdx = 0;
	_actor[1].field_54 = 0;
	_actor[1].runningSound = 0;
	_actor[1].lost = 0;
	_actor[1].kicking = 0;
	_actor[1].field_44 = 0;
	_actor[1].field_48 = 0;
	if (_enemy[_currEnemy].initializer != -1)
		enemyInitializer(_enemy[_currEnemy].initializer, _actor[1].damage, 
							 _actor[0].damage, _actor[1].probability);

	smush_setupSomething(160, 100, -1);
}

void Insane::mainLoop(void) {
	int32 resid;

	_val11d++;

	while (!idx2Compare()) {
		if(!(resid = idx2Tweak()))
			continue;
	  
		_scumm->ensureResourceLoaded(rtSound, resid);
		_scumm->setResourceCounter(rtSound, resid, 1);
	}
	_scumm->increaseResourceCounter();
	
	while (!idx1Compare()) {
		resid = idx1Tweak();
		_scumm->ensureResourceLoaded(rtCostume, resid);
		_scumm->setResourceCounter(rtCostume, resid, 1);
		// smlayer_lock (rtCostume, resid);
	}
	
	if (loadSceneData(_currSceneId, 0, 2)) {
		_sceneData1Loaded = 0;
		_objArray2[0] = 0;
		return;
	}
	_sceneData1Loaded = 1;
	if (idx1Compare() || idx2Compare()) {
		_objArray2[0] = 0;
		return;
	}
	_objArray2[0]++;
	if (_objArray2[0] <= 5) {
		_objArray2[0] = 0;
		return;
	}
	
	smush_setToFinish();
	loadSceneData(_currSceneId, 1, 2);
	_memoryAllocatedNotOK = 1;
}

bool Insane::idx1Compare(void) {
	return _objArray1Idx == _objArray1Idx2;
}

bool Insane::idx2Compare(void) {
	return _objArray2Idx == _objArray2Idx2;
}

int32 Insane::idx1Tweak(void) {
	_objArray1Idx++;
	if (_objArray1Idx > 100)
		_objArray1Idx = 0;
	
	return _objArray1[_objArray1Idx];
}

int32 Insane::idx2Tweak(void) {
	if (!_idx2Exceeded)
		if (_objArray2Idx >= _objArray2Idx2)
			return false;
	
	_objArray2Idx++;
	if (_objArray2Idx > 100) {
		_idx2Exceeded = 0;
		_objArray2Idx = 0;
	}
	return _objArray2[_objArray2Idx];
}

void Insane::smush_setToFinish(void) {
	debug(0, "Video is set to finish");
	_scumm->_videoFinished = 1;
}

// smlayer_stopSound
void Insane::smlayer_stopSound(int idx) {
	_scumm->_sound->stopSound(readArray(_numberArray, idx));
}

void Insane::procPreRendering(void) {
	_smush_isSanFileSetup = 0; // FIXME: This shouldn't be here

	switchSceneIfNeeded();

	if (_sceneData1Loaded) {
		if (!_keyboardDisable) {
			smush_changeState(1);
			_smush_isPauseImuse = true;
			IMUSE_shutVolume();
			_keyboardDisable = 1;
		}
	} else {
		_val115w = 0;
		if (_keyboardDisable) {
			if (!_val116w) {
				smush_changeState(0);
				_smush_isPauseImuse = false;
				IMUSE_restoreVolume();
			}
			_keyboardDisable = 0;
		}
	}

	_lastKey = getLastKey(1);
}

void Insane::switchSceneIfNeeded(void) {
	if (_needSceneSwitch && !_smush_isSanFileSetup) {
		putActors();
		stopSceneSounds(_currSceneId);
		_tempSceneId = _currSceneId;
		_currSceneId = _temp2SceneId;
		_needSceneSwitch = false;
		loadSceneData(_temp2SceneId, 0, 1);
		if(loadSceneData(_temp2SceneId, 0, 2)) {
			setSceneCostumes(_temp2SceneId);
			_sceneData2Loaded = 0;
			_sceneData1Loaded = 0;
			return;
		}
		_sceneData2Loaded = 1;
		if (_temp2SceneId == 13 || _temp2SceneId == 3)
			_isBenCut = 1;
	}
	if (_sceneData2Loaded && !_sceneData1Loaded) {
		setSceneCostumes(_currSceneId);
		_sceneData2Loaded = 0;
	}
}

int Insane::smush_changeState(int state) {
	if (state == 2) {
		if (_smush_smushState == 0)
			_smush_smushState = 1;
		else
			_smush_smushState = 0;
	} else if (state == 4) {
		if (_smush_smushState)
			_smush_smushState = 3;
	} else if (state != 5) {
		_smush_smushState = state;
	}
	return _smush_smushState;
}

// FIXME: in SmushPlayer object
// renderBitmap = _dst
// curFrame = _frame
// maxFrame = _nbframes
// setupsan12 = 0??
// setupsan13 = 0??
// <_sev> codecparam is the last one...
// <aquadran> yes, but it's from FOBJ chunk that is from handleFrameObject
void Insane::procPostRendering(byte *renderBitmap, int32 codecparam, int32 setupsan12,
							   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	int32 tmpSnd;
	bool needMore = false;

	if(!_keyboardDisable && !_val116w) {
		switch (_currSceneId) {
		case 12:
			postCase11(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 1:
			postCase0(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSound1(88);
			smlayer_soundSetPan(88, ((_actor[0].x+160)>>2)+64);
			if(_tiresRustle) {
				if (!smlayer_isSoundRunning(87))
					smlayer_startSound1(87);
			} else {
				smlayer_stopSound(87);
			}
			break;
		case 18:
		case 19:
			postCase17(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			smlayer_stopSound(95);
			smlayer_stopSound(87);
			smlayer_stopSound(88);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSound1(88);
			break;
		case 17:
			postCase16(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSound1(88);
			break;
		case 2:
			postCase1(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 3:
			postCase2(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			needMore = true;
			if(!smlayer_isSoundRunning(89)) {
				smlayer_startSound1(89);
				smlayer_soundSetPriority(89, 100);
			}
			tmpSnd = _enemy[_currEnemy].sound;
			if(!smlayer_isSoundRunning(tmpSnd)) {
				smlayer_startSound1(tmpSnd);
				smlayer_soundSetPriority(tmpSnd, 100);
			}
			smlayer_soundSetPan(89, ((_actor[0].x+160)>>2)+64);
			smlayer_soundSetPan(tmpSnd, ((_actor[1].x+160)>>2)+64);
			if(!_tiresRustle) {
				smlayer_stopSound(87);
			} else {
				if (!smlayer_isSoundRunning(87))
					smlayer_startSound1(87);
			}
			break;
		case 21:
			postCase20(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			needMore = true;
			if(!smlayer_isSoundRunning(89)) {
				smlayer_startSound1(89);
				smlayer_soundSetPriority(89, 100);
			}
			tmpSnd = _enemy[_currEnemy].sound;
			if(!smlayer_isSoundRunning(tmpSnd)) {
				smlayer_startSound1(tmpSnd);
				smlayer_soundSetPriority(tmpSnd, 100);
			}
			smlayer_soundSetPan(89, ((_actor[0].x+160)>>2)+64);
			smlayer_soundSetPan(tmpSnd, ((_actor[1].x+160)>>2)+64);
			break;
		case 4:
		case 5:
			postCase3(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSound1(88);
			smlayer_soundSetPan(88, ((_actor[0].x+160)>>2)+64);
			break;
		case 6:
			postCase5(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSound1(88);
			smlayer_soundSetPan(88, ((_actor[0].x+160)>>2)+64);
			break;
		case 7:
		case 8:
			postCase6(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 9:
		case 23:
			postCase8(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 10:
			postCase9(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 11:
		case 20:
		case 22:
			postCase10(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 13:
			postCase12(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			needMore = true;
			if(!smlayer_isSoundRunning(89)) {
				smlayer_startSound1(89);
				smlayer_soundSetPriority(89, 100);
			}
			tmpSnd = _enemy[_currEnemy].sound;
			if(!smlayer_isSoundRunning(tmpSnd)) {
				smlayer_startSound1(tmpSnd);
				smlayer_soundSetPriority(tmpSnd, 100);
			}
			smlayer_soundSetPan(89, ((_actor[0].x+160)>>2)+64);
			smlayer_soundSetPan(tmpSnd, ((_actor[1].x+160)>>2)+64);
			break;
		case 24:
			if(!smlayer_isSoundRunning(90)) {
				smlayer_startSound1(90);
				smlayer_soundSetPriority(90, 100);
			}
			postCase23(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 15:
		case 16:
			postCase14(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 25:
		case 26:
			break;
		default:
			error("Insane::procPostRendering: default case %d", _currSceneId);
			break;
		}

		if (_currScenePropIdx)
			postCaseAll(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
	
		_actor[0].field_C++;
		_actor[0].act[3].frame++;
		_actor[0].act[2].frame++;
		_actor[0].act[1].frame++;
		_actor[0].act[0].frame++;
		_actor[1].act[3].frame++;
		_actor[1].field_C++;
		_actor[1].act[2].frame++;
		_actor[1].act[1].frame++;
		_actor[1].act[0].frame++;
	}
	
	if (!_val115w) {
		smlayer_overrideDrawActorAt(&renderBitmap[0], renderBitmap[2], renderBitmap[3]);
		_isBenCut = 0;
	}
	
	if (_isBenCut)
		smlayer_drawSomething(renderBitmap, codecparam, 89, 56, 1, _smush_bencutNut, 0, 0, 0);
	
	if (!_keyboardDisable && !_val116w)
		_scumm->processActors();
	
	if (needMore)
		postCaseMore(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
	
	_lastKey = 0;
	_tiresRustle = false;
}

void Insane::postCase11(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame && !_needSceneSwitch) {
		if (_firstBattle) {
			smush_setToFinish();
		} else {
			queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0, 
							 _continueFrame, 1300);
		}
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase0(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	actorsReaction(true);
	
	if (!curFrame || curFrame == 420)
		smlayer_setFluPalette(_smush_roadrashRip, 0);
	
	if (curFrame >= maxFrame)
		smush_rewindCurrentSan(1088, -1, -1);
	
	_val121_ = false;
	_val119_ = false;
	_val120_ = false;
	_val122_ = false;
	_val123_ = false;
	_continueFrame1 = curFrame;
}

void Insane::postCase17(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame && !_needSceneSwitch) {
		if (_currSceneId == 18) {
			queueSceneSwitch(17, _smush_minedrivFlu, "minedriv.san", 64, 0, 
							 _continueFrame1, 1300);
			setWordInString(_numberArray, 9, 1);
		} else {
			queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0,
							 _continueFrame1, 1300);
			setWordInString(_numberArray, 9, 0);
		}
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase16(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	char buf[12];
	int32 tmp;
	
	actorsReaction(true);
	sprintf(buf, "^f01%02o", curFrame & 0x3f);
	smlayer_showStatusMsg(-1, renderBitmap, codecparam, 180, 168, 1, 2, 0, "%s", buf);
	tmp = 400-curFrame;
	
	if (tmp < 0)
		tmp += 1300;
	
	sprintf(buf, "^f01%04d", tmp);
	smlayer_showStatusMsg(-1, renderBitmap, codecparam, 202, 168, 1, 2, 0, "%s", buf);
	
	sprintf(buf, "^f01%02o", curFrame & 0xff);
	smlayer_showStatusMsg(-1, renderBitmap, codecparam, 140, 168, 1, 2, 0, "%s", buf);
	smlayer_showStatusMsg(-1, renderBitmap, codecparam, 170, 43, 1, 2, 0, "%s", buf);
	
	smlayer_drawSomething(renderBitmap, codecparam, 0, 0, 1, _smush_bensgoggNut, 0, 0, 0);
	
	if (!_val124_)
		smlayer_drawSomething(renderBitmap, codecparam, 24, 170, 1, 
							  _smush_iconsNut, 23, 0, 0);
	
	if (!curFrame)
		smlayer_setFluPalette(_smush_goglpaltRip, 0);
	
	if (curFrame >= maxFrame) {
		smush_rewindCurrentSan(1088, -1, -1);
		smlayer_setFluPalette(_smush_goglpaltRip, 0);
	}
	_val121_ = false;
	_val123_ = false;
	_val119_ = false;
	_val120_ = false;
	_val124_ = false;
	_counter1++;
	_continueFrame1 = curFrame;
	if (_counter1 >= 10)
		_counter1 = 0;
}

void Insane::postCase1(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	struct fluConf *flu;

	if ((curFrame >= maxFrame) && !_needSceneSwitch) {
		flu = &_fluConf[14 + _iactSceneId2];
		queueSceneSwitch(flu->sceneId, flu->fluPtr, flu->filenamePtr, 64, 0, 
						 flu->startFrame, flu->numFrames);
	}
	_val119_ = 0;
	_val120_ = 0;
}

void Insane::postCase2(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	actorsReaction(_val39_);
	checkEnemyLoose(1);
	
	if (!curFrame)
		smlayer_setFluPalette(_smush_roadrashRip, 0);

	if (curFrame >= maxFrame)
		smush_rewindCurrentSan(1088, -1, -1);

	_val121_ = 0;
	_val119_ = 0;
	_val120_ = 0;
	_continueFrame = curFrame;
}

void Insane::postCase20(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	actorsReaction(true);
	checkEnemyLoose(1);
	
	if (curFrame >= maxFrame)
		smush_rewindCurrentSan(1088, -1, -1);
	
	_val121_ = false;
	_val119_ = false;
	_val120_ = false;
	_continueFrame = curFrame;
}

void Insane::postCase3(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	// FIXME: implement
	warning("stub Insane::postCase3(...)");
}

void Insane::postCase5(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	// FIXME: implement
	warning("stub Insane::postCase5(...)");
}

void Insane::postCase6(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	struct fluConf *flu;

	if ((curFrame >= maxFrame) && !_needSceneSwitch) {
		if (_currSceneId == 8)
			flu = &_fluConf[7 + _iactSceneId2];
		else
			flu = &_fluConf[0 + _iactSceneId2];
		queueSceneSwitch(flu->sceneId, flu->fluPtr, flu->filenamePtr, 64, 0, 
						 flu->startFrame, flu->numFrames);
	}
	_val119_ = 0;
	_val120_ = 0;
}

void Insane::postCase8(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame && !_needSceneSwitch) {
		_actor[0].damage = 0;

		if (_firstBattle) {
			queueSceneSwitch(13, _smush_minefiteFlu, "minefite.san", 64, 0,
							 _continueFrame, 1300);
		} else {
			if (_currSceneId == 23) {
				queueSceneSwitch(21, 0, "rottfite.san", 64, 0, 0, 0);
			} else {
				queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0,
							 _continueFrame, 1300);
			}
		}
 	}
	
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase9(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	// FIXME: implement
	warning("stub Insane::postCase9(...)");
}

void Insane::postCase10(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	// FIXME: implement
	warning("stub Insane::postCase10(...)");
}

void Insane::postCase12(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (_actor[1].y <= 200) {
		initScene(3);
		_actor[1].y = 200;

		switch (_currEnemy) {
		case EN_ROTT2:
			actorsReaction(true);

			if (_enemy[1].field_8 <= 1)
				prepareScenePropScene(scenePropIdx[32], 0, 1);
			else
				prepareScenePropScene(scenePropIdx[33], 0, 1);
			break;
		case EN_ROTT3:
			actorsReaction(true);

			if (_enemy[1].field_8 <= 1)
				prepareScenePropScene(scenePropIdx[25], 0, 1);
			break;
		case EN_VULTF1:
			actorsReaction(true);

			if (_enemy[1].field_8 <= 1)
				prepareScenePropScene(scenePropIdx[2], 0, 1);
			break;
		case EN_VULTF2:
			actorsReaction(true);

			if (_enemy[1].field_8 <= 1)
				prepareScenePropScene(scenePropIdx[9], 0, 1);
			else
				prepareScenePropScene(scenePropIdx[16], 0, 1);
			break;
		case EN_VULTM2:
			actorsReaction(true);

			prepareScenePropScene(scenePropIdx[18], 0, 1);
			_val39_ = false;
			break;
		case EN_TORQUE:
			actorsReaction(false);
			setWordInString(_numberArray, 1, _val51d);
			smush_setToFinish();
			break;
		case EN_ROTT1:
		case EN_VULTM1:
		case EN_CAVEFISH:
		default:
			actorsReaction(true);
			break;
		}
	} else {
		switch (_currEnemy) {
		case EN_VULTM2:
			if (_enemy[EN_VULTM2].field_8 <= 1)
				actorsReaction(false);
			else
				actorsReaction(true);
			break;
		case EN_TORQUE:
			actorsReaction(false);
			if (_actor[1].y != 300)
				prepareScenePropScene(scenePropIdx[57], 1, 0);
			break;
		default:
			actorsReaction(true);
		}
		_actor[1].y -= (_actor[1].y - 200) / 20 + 1;
	}

	checkEnemyLoose(false);

	if (curFrame == 0)
		smlayer_setFluPalette(_smush_roadrashRip, 0);

	if (curFrame >= maxFrame)
		smush_rewindCurrentSan(1088, -1, -1);

	_val119_ = 0;
	_val120_ = 0;
	_continueFrame = curFrame;
}

void Insane::postCase23(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame) {
		if (_currSceneId == 24)
			queueSceneSwitch(21, 0, "rottfite.san", 64, 0, 0, 0);
	
		if (readArray(_numberArray, 6) && readArray(_numberArray, 4))
			queueSceneSwitch(16, 0, "limocrsh.san", 64, 0, 0, 0);
	
		queueSceneSwitch(5, 0, "tovista2.san", 64, 0, 0, 290);
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase14(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	// FIXME: implement
	warning("stub Insane::postCase14(...)");
}

void Insane::postCaseAll(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						 int32 setupsan13, int32 curFrame, int32 maxFrame) {
	struct sceneProp *tsceneProp;

	tsceneProp = &_sceneProp[_currScenePropIdx + _currScenePropSubIdx];
	if (tsceneProp->actor != -1) {
		if (_actor[tsceneProp->actor].field_54) {
			tsceneProp->counter++;
			if (!_actor[tsceneProp->actor].runningSound || !_scumm->_noSubtitles) {
				if (_actor[tsceneProp->actor].act[3].state == 72 &&
					_currTrsMsg) {
					smush_setPaletteValue(1, tsceneProp->r, tsceneProp->g, tsceneProp->b);
					smush_setPaletteValue(2, 0, 0, 0);
					smlayer_showStatusMsg(-1, renderBitmap, codecparam, 160, 20, 1, 2, 5,
										  "^f00%s", _currTrsMsg);
				}
			}
		} else {
			_currScenePropSubIdx = tsceneProp->index;
			if (_currScenePropSubIdx && _currScenePropIdx) {
				tsceneProp = &_sceneProp[_currScenePropIdx + _currScenePropSubIdx];
				tsceneProp->counter = 0;
				if (tsceneProp->trsId)
					_currTrsMsg = handleTrsTag(_trsFilePtr, tsceneProp->trsId);
				else
					_currTrsMsg = 0;

				if (tsceneProp->actor != -1) {
					_actor[tsceneProp->actor].field_54 = 1;
					_actor[tsceneProp->actor].act[3].state = 117;
					_actor[tsceneProp->actor].field_54 = _currScenePropSubIdx;
				}
			} else {
				_currScenePropIdx = 0;
				_currTrsMsg = 0;
				_currScenePropSubIdx = 0;
				_actor[0].field_4C = 0;
				_actor[1].field_4C = 0;
				_val39_ = true;
			}
		}
	}
	_val119_ = 0;
	_val120_ = 0;
	_continueFrame = curFrame;
}

void Insane::postCaseMore(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						  int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (_actor[0].weapon <= 7) {
		smlayer_drawSomething(renderBitmap, codecparam, 5, 160, 1, _smush_iconsNut,
							  _actor[0].weapon + 11, 0, 0);
	}
}

void Insane::queueSceneSwitch(int32 sceneId, byte *fluPtr, const char *filename, 
							  int32 arg_C, int32 arg_10, int32 startFrame, int32 numFrames) {
	int32 tmp;
	
	if (_needSceneSwitch || _sceneData1Loaded)
		return;
	
	debug(0, "Enqueued scene switch to %d", sceneId);
	if (fluPtr) {
		tmp = ((int)startFrame/30+1)*30;
		if (tmp >= numFrames)
			tmp = 0;
	
		smush_setupSanWithFlu(filename, arg_C|32, -1, -1, 0, fluPtr, tmp);
	} else {
		smush_setupSanFromStart(filename, arg_C|32, -1, -1, 0);
	}
	_needSceneSwitch = true;
	_temp2SceneId = sceneId;
}

void Insane::actorsReaction(bool flag) {
	int32 buttons;
	
	switch (_currSceneId) {
	case 21:
	case 25:
	case 3:
	case 13:
		if (_actor[0].damage < _actor[0].maxdamage) {
			_actor[0].lost = 0;
		} else {
			if (!_actor[0].lost && !_actor[1].lost) {
				_actor[0].lost = 1;
				_actor[0].act[2].state = 36;
				_actor[0].act[1].state = 36;
				_actor[0].act[1].room = 0;
				_actor[0].act[0].state = 36;
				_actor[0].act[0].room = 0;
		
				if (smlayer_isSoundRunning(95))
					smlayer_stopSound(95);
			}
		}
		buttons = 0;
		if (!_actor[0].lost && flag) {
			buttons = processBattle();
			if (_currSceneId == 13)
				buttons &= 2;
			if (_currEnemy == EN_TORQUE)
				buttons = 0;
		}
		debug(1, "00:%d 01:%d 02:%d 03:%d", _actor[0].act[0].state, 
				_actor[0].act[1].state, _actor[0].act[2].state, _actor[0].act[3].state);
		actor01Reaction(buttons);
		actor02Reaction(buttons);
		actor03Reaction(buttons);
		actor00Reaction(buttons);
		break;
	case 17:
		func11(func10(false));
		break;
	default:
		if (_actor[0].damage < _actor[0].maxdamage) {
			_actor[0].lost = 0;
		} else {
			if (!_actor[0].lost && !_actor[1].lost) {
				queueSceneSwitch(10, 0, "wr2_ben.san", 64, 0, 0, 0);
				_actor[0].lost = 1;
				_actor[0].act[2].state = 36;
				_actor[0].act[2].room = 0;
				_actor[0].act[0].state = 36;
				_actor[0].act[0].room = 0;
				_actor[0].act[1].state = 36;
				_actor[0].act[1].room = 0;
				func11(0);
				return;
			}
		}
		if (!_actor[0].lost && !flag)
			func11(func10(true));
		else
			func11(0);
		break;
	}
}

int32 Insane::processBattle(void) {
	int32 buttons, tmp;
	bool doDamage = false;

	if (_actor[0].enemyHandler != -1)
		buttons = enemyHandler(_actor[0].enemyHandler, 0, 1, _actor[0].probability);
	else
		buttons = enemyHandler(EN_TORQUE, 0, 1, _actor[0].probability);

	if (_actor[0].speed) {
		_actor[0].field_18 += _actor[0].field_14 / 40;
	} else {
		if (_actor[0].field_18 < 0)
			_actor[0].field_18++;
		else
			_actor[0].field_18--;
	}

	if (_actor[0].field_18 > 8)
		_actor[0].field_18 = 8;

	if (_actor[0].field_18 < -8)
		_actor[0].field_18 = -8;

	_actor[0].x += _actor[0].field_18;

	if (_actor[0].x > 100)
		_actor[0].x--;
	else
		if (_actor[0].x < 100)
			_actor[0].x++;

	if (_actor[0].x >= 0) {
		if (_actor[1].x - 90 <= _actor[0].x && !_actor[0].lost && !_actor[1].lost) {
			_val213d++;
			_actor[0].x = _actor[1].x - 90;

			tmp = _actor[1].field_18;
			_actor[1].field_18 = _actor[0].field_18;
			_actor[0].field_18 = tmp;

			if (_val213d > 50) {
				_actor[0].field_14 = -320;
				_val213d = 0;
			}

			if (!smlayer_isSoundRunning(95))
				smlayer_startSound1(95);
		} else {
			if (smlayer_isSoundRunning(95))
				smlayer_stopSound(95);
			
			_val213d = 0;
		}
	} else {
		_actor[0].x = 0;
		_actor[0].damage++; // FIXME: apparently it is a bug in original
							// and damage is doubled
		doDamage = true;
	}

	if (_actor[0].x > 320) {
		_actor[0].x = 320;
		doDamage = true;
	}

	if (_actor[0].x < 10 || _actor[0].x > 310 || doDamage) {
		_tiresRustle = 1;
		_actor[0].x1 = -_actor[0].x1;
		_actor[0].damage++; // PATCH
	}

	return buttons;
}

int32 Insane::func10(bool flag) {
	// FIXME: implement
	warning("stub Insane::func10(%d)", flag);
	return 0;
}

// FIXME: give a proper name
void Insane::func11(int32 arg_0) {
	int16 tmp;

	if (_actor[0].field_8 < 1)
		return;

	if (_actor[0].field_8 == 112) {
		if (_actor[0].field_C < 18 || !_needSceneSwitch)
			return;

		queueSceneSwitch(18, 0, "fishgogg.san", 64, 0, 0, 0);
	} else if (_actor[0].field_8 == 1) {
		tmp = _actor[0].field_14 / 22;
		switch (_currSceneId) {
		case 17:
			if (arg_0 != 1) {
				if (_val123_) {
					setWordInString(_numberArray, 1, _val52d);
					smush_setToFinish();
				}

				if (_val119_ && !_needSceneSwitch) {
					_iactSceneId2 = _iactSceneId;
					queueSceneSwitch(2, 0, "mineexit.san", 64, 0, 0, 0);
				}
			}
			
			if (arg_0 == 2 || _needSceneSwitch)
				return;

			queueSceneSwitch(19, 0, "fishgog2.san", 64, 0, 0, 0);
			break;
		case 1:
			_actor[0].speed = tmp;

			if (tmp < -7)
				_actor[0].speed = -7;
			if (tmp > 7)
				_actor[0].speed = 7;

			drawSpeedyActor(arg_0);

			if (arg_0 != 1 && _currSceneId == 1 && _val119_ && !_needSceneSwitch) {
				_iactSceneId2 = _iactSceneId;
				queueSceneSwitch(2, 0, "mineexit.san", 64, 0, 0, 0);
			}

			if (arg_0 == 2 || !_val122_)
				return;

			_actor[0].field_C = 0;
			_actor[0].field_8 = 112;
			smlayer_setActorFacing(0, 2, 26, 180);
			break;
		case 5:
			_actor[0].speed = tmp;

			if (tmp < -7)
				_actor[0].speed = -7;
			if (tmp > 7)
				_actor[0].speed = 7;
			
			drawSpeedyActor(arg_0);
			
			if (_val119_ && !_needSceneSwitch) {
				_iactSceneId2 = _iactSceneId;

				if (readArray(_numberArray, 4) && _val211d < 3) {
					_val211d++;
					queueSceneSwitch(8, 0, "fishfear.san", 64, 0, 0, 0);
				} else {
					queueSceneSwitch(8, 0, "tomine.san", 64, 0, 0, 0);
				}
			}
			
			if (_val120_) {
				setWordInString(_numberArray, 1, _val55d);
				setWordInString(_numberArray, 3, _val57d);
				smush_setToFinish();
			}

			if (!_val212_)
				return;

			setWordInString(_numberArray, 1, _val56d);
			setWordInString(_numberArray, 3, _val57d);
			smush_setToFinish();
			break;
		case 6:
			_actor[0].speed = tmp;

			if (tmp < -7)
				_actor[0].speed = -7;
			if (tmp > 7)
				_actor[0].speed = 7;

			drawSpeedyActor(arg_0);
			
			if (arg_0 == 1)
				return;

			if (_val119_ && !_needSceneSwitch) {
				_iactSceneId2 = _iactSceneId;

				if (readArray(_numberArray, 4) && _val211d < 3) {
					_val211d++;
					queueSceneSwitch(7, 0, "fishfear.san", 64, 0, 0, 0);
				} else {
					queueSceneSwitch(7, 0, "tomine.san", 64, 0, 0, 0);
				}
			}
			
			if (_val120_) {
				setWordInString(_numberArray, 1, _val55d);
				setWordInString(_numberArray, 3, _val53d);
				smush_setToFinish();
			}

			if (!_val212_)
				return;

			setWordInString(_numberArray, 1, _val56d);
			setWordInString(_numberArray, 3, _val53d);
			smush_setToFinish();
			break;
		default:
			break;
		}
	}
}

void Insane::drawSpeedyActor(int32 arg_0) {
	switch (_actor[0].speed) {
	case -7:
		if (_actor[0].act[2].state != 47) {
			smlayer_setActorFacing(0, 2, 13, 180);
			_actor[0].act[2].state = 47;
		}
		break;
	case -6:
		if (_actor[0].act[2].state != 44) {
			smlayer_setActorFacing(0, 2, 11, 180);
			_actor[0].act[2].state = 44;
		}
		break;
	case -5:
		if (_actor[0].act[2].state != 43) {
			smlayer_setActorFacing(0, 2, 10, 180);
			_actor[0].act[2].state = 43;
		}
		break;
	case -4:
		if (_actor[0].act[2].state != 42) {
			smlayer_setActorFacing(0, 2, 9, 180);
			_actor[0].act[2].state = 42;
		}
		break;
	case -3:
		if (_actor[0].act[2].state != 41) {
			smlayer_setActorFacing(0, 2, 8, 180);
			_actor[0].act[2].state = 41;
		}
		break;
	case -2:
		if (_actor[0].act[2].state != 40) {
			smlayer_setActorFacing(0, 2, 7, 180);
			_actor[0].act[2].state = 40;
		}
		break;
	case -1:
		if (_actor[0].act[2].state != 39) {
			smlayer_setActorFacing(0, 2, 6, 180);
			_actor[0].act[2].state = 39;
		}
		break;
	case 0:
		if (_actor[0].act[2].state != 1) {
			smlayer_setActorFacing(0, 2, 22, 180);
			_actor[0].act[2].state = 1;
		}
		break;
	case 1:
		if (_actor[0].act[2].state != 55) {
			smlayer_setActorFacing(0, 2, 14, 180);
			_actor[0].act[2].state = 55;
		}
		break;
	case 2:
		if (_actor[0].act[2].state != 56) {
			smlayer_setActorFacing(0, 2, 15, 180);
			_actor[0].act[2].state = 56;
		}
		break;
	case 3:
		if (_actor[0].act[2].state != 57) {
			smlayer_setActorFacing(0, 2, 16, 180);
			_actor[0].act[2].state = 57;
		}
		break;
	case 4:
		if (_actor[0].act[2].state != 58) {
			smlayer_setActorFacing(0, 2, 17, 180);
			_actor[0].act[2].state = 58;
		}
		break;
	case 5:
		if (_actor[0].act[2].state != 59) {
			smlayer_setActorFacing(0, 2, 18, 180);
			_actor[0].act[2].state = 59;
		}
		break;
	case 6:
		if (_actor[0].act[2].state != 60) {
			smlayer_setActorFacing(0, 2, 19, 180);
			_actor[0].act[2].state = 60;
		}
		break;
	case 7:
		if (_actor[0].act[2].state != 50) {
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 50;
		}
		break;
	default:
		break;
	}

	if (!_actor[0].act[2].room)
		return;

	smlayer_putActor(0, 2, _actor[0].x + _actor[0].x1, _actor[0].y + _actor[0].y1,
					 _smlayer_room2);
}

void Insane::smush_rewindCurrentSan(int arg_0, int arg_4, int arg_8) {
	debug(0, "smush_rewindCurrentSan(%d, %d, %d)", arg_0, arg_4, arg_8);
	_smush_setupsan2 = arg_0;
	
	smush_setupSanFile(0, 8);
	_smush_isSanFileSetup = 1;
	smush_setFrameSteps(arg_4, arg_8);

	_smush_curFrame = 0; // HACK
}

void Insane::actor02Reaction(int32 buttons) {
	int32 tmp, tmp2;
	
	switch(_actor[0].act[2].state) {
	case 106:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		smlayer_setActorFacing(0, 2, 29, 180);
		_actor[0].act[2].state = 107;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 107:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 9) {
			_actor[0].act[2].state = 1;
			_actor[0].inventory[INV_MACE] = 0;
			smlayer_startSound2(318);
			switchWeapon();
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 104:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		smlayer_setActorFacing(0, 2, 28, 180);
		_actor[0].act[2].state = 105;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 105:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 5) {
			_actor[0].act[2].state = 1;
			_actor[0].inventory[INV_MACE] = 0; // Mace
			smlayer_startSound2(318);
			switchWeapon();
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 108:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		smlayer_setActorFacing(0, 2, 28, 180);
		_actor[0].act[2].state = 109;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 109:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 5) {
			_actor[0].act[2].state = 1;
			_actor[0].inventory[INV_CHAIN] = 0; // Chain
			smlayer_startSound2(318);
			switchWeapon();
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 73:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 1;
		if (_actor[0].act[2].frame >= 2 && !_kickingInProgress) {
			smlayer_setActorFacing(0, 2, 19, 180);
			_actor[0].act[2].state = 74;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 74:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 0;
		if (_actor[0].act[2].frame >= 2) {
			smlayer_setActorFacing(0, 2, 9, 180);
			_actor[0].act[2].state = 1;
			_actor[0].field_2C = 2;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 79:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 1;
		if (_actor[0].act[2].frame >= 2) {
			smlayer_setActorFacing(0, 2, 23, 180);
			_actor[0].act[2].state = 80;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 80:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 0;
		if (_actor[0].act[2].frame >= 6) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 63;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 81:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 1;
		if (_actor[0].act[2].frame >= 2 && !_kickingInProgress) {
			smlayer_setActorFacing(0, 2, 23, 180);
			_actor[0].act[2].state = 82;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 82:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 0;
		if (_actor[0].act[2].frame >= 3) {
			smlayer_setActorFacing(0, 2, 26, 180);
			_actor[0].act[2].state = 64;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 77:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 1;
		if (_actor[0].act[2].frame >= 2) {
			smlayer_setActorFacing(0, 2, 23, 180);
			_actor[0].act[2].state = 78;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 78:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 0;
		if (_actor[0].act[2].frame >= 5) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 65;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 83:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 0;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 1;
		if (_actor[0].act[2].frame >= 2 && !_kickingInProgress) {
			smlayer_setActorFacing(0, 2, 23, 180);
			_actor[0].act[2].state = 84;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 84:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 0;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 0;
		if (_actor[0].act[2].frame >= 5) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 66;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 75:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 1;
		if (_actor[0].act[2].frame >= 4 && !_kickingInProgress) {
			smlayer_setActorFacing(0, 2, 23, 180);
			_actor[0].act[2].state = 76;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
		break;
	case 76:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].field_44 = 0;
		if (_actor[0].act[2].frame >= 4) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 62;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 2:
		smlayer_setActorLayer(0, 2, 4);
		smlayer_setActorFacing(0, 2, 17, 180);
		_actor[0].kicking = 1;
		_actor[0].field_2C = 1;
		_actor[0].act[2].state = 3;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		smlayer_startSound1(63);
		break;
	case 3:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		if (_actor[0].act[2].frame == 2) {
			if (_currEnemy != EN_CAVEFISH) {
				tmp = calcDamage(1, 1);
				if (tmp == 1)
					smlayer_startSound1(60);
				if (tmp == 1000)
					smlayer_startSound1(62);
			} else {
				if ((_actor[1].x - _actor[0].x <= weaponMaxRange(0)) &&
					(_actor[1].x - _actor[0].x >= weaponMinRange(0)) &&
					!_actor[0].field_54)
					prepareScenePropScene(scenePropIdx[1], 0, 0);
			}
		}
		if (_actor[0].act[2].frame >= 4) {
			smlayer_setActorFacing(0, 2, 20, 180);
			_actor[0].act[2].state = 4;
		}
	
		_actor[0].kicking = 1;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 4:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 2) {
			smlayer_setActorFacing(0, 2, 9, 180);
			_actor[0].act[2].state = 1;
			_actor[0].act[2].facing = -1000;
			_actor[0].field_2C = 2;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 5:
		smlayer_setActorLayer(0, 2, 5);
		break;
	case 10:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		smlayer_setActorFacing(0, 2, 19, 180);
		_actor[0].act[2].state = 11;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		smlayer_startSound1(75);
		break;
	case 11:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 2) {
			if (_currEnemy == EN_VULTM2) {
				if ((_actor[1].x - _actor[0].x <= weaponMaxRange(0)) &&
					(_actor[1].x - _actor[0].x >= weaponMinRange(0)) &&
					calcDamage(0, 0)) {
					smlayer_setActorFacing(0, 2, 20, 180);
					_actor[0].act[2].state = 97;
					_actor[0].act[2].room = 0;
					_actor[0].act[1].room = 0;
					_actor[0].act[0].room = 0;
					smlayer_setActorLayer(0, 2, 25);
					smlayer_setActorCostume(1, 2, readArray(_numberArray, 45));
					smlayer_setActorFacing(1, 2, 6, 180);
					smlayer_startSound1(101);
					_actor[1].act[2].state = 97;
					_actor[1].lost = 1;
					_actor[1].act[2].room = 1;
					_actor[1].act[1].room = 0;
					_actor[1].act[0].room = 0;
				} else {
					smlayer_setActorFacing(0, 2, 20, 180);
					_actor[0].act[2].state = 12;
				}
			} else {
				smlayer_setActorFacing(0, 2, 20, 180);
				_actor[0].act[2].state = 12;
			}
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 97:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 5) {
			_actor[0].act[2].room = 1;
			_actor[0].act[1].room = 1;
			_actor[0].act[0].room = 1;
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 13;
			_actor[0].x = _actor[1].x - 116;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 12:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 1) {
			if (_currEnemy != EN_CAVEFISH) {
				if ((_actor[1].weapon >= 0 && _actor[1].weapon < 5) || 
					_actor[1].weapon == INV_DUST) {
					tmp = calcDamage(1, 1);
					if (tmp == 1)
						smlayer_startSound1(73);
					if (tmp == 1000)
						smlayer_startSound1(74);
				} else {
					if(calcDamage(1, 0) == 1)
						smlayer_startSound1(73);
				}
			} else {
				if ((_actor[1].x - _actor[0].x <= weaponMaxRange(0)) &&
					(_actor[1].x - _actor[0].x >= weaponMinRange(0)) &&
					!_actor[0].field_54)
					prepareScenePropScene(scenePropIdx[1], 0, 0);
		
			}
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 13;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 13:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 3) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 63;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 6:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 2;
		_actor[0].field_34 = 1;
		_actor[0].kicking = 0;
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 22));
		smlayer_setActorFacing(0, 2, 19, 180);
		_actor[0].act[2].state = 7;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		smlayer_startSound1(66);
		break;
	case 7:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 2;
		_actor[0].field_34 = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 1) {
			smlayer_setActorFacing(0, 2, 20, 180);
			_actor[0].act[2].state = 8;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 8:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 2;
		_actor[0].field_34 = 1;
		_actor[0].kicking = 0;
		if ((_actor[0].act[2].frame == 3) && (calcDamage(0, 0) == 1)) {
			_actor[1].damage = weaponDamage(0);
			smlayer_startSound1(64);
			_actor[1].field_14 = 320;
		}
		if (_actor[0].act[2].frame >= 5) {
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 9;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 9:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 2;
		_actor[0].field_34 = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 3) {
			smlayer_setActorCostume(0, 2, readArray(_numberArray, 12));
			_actor[0].field_34 = 2;
			_actor[0].act[2].state = 1;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 14:
		smlayer_setActorLayer(0, 2, 8);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		smlayer_setActorFacing(0, 2, 19, 180);
		_actor[0].act[2].state = 15;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		smlayer_startSound1(78);
		break;
	case 15:
		smlayer_setActorLayer(0, 2, 8);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 2) {
			switch (_actor[1].weapon) {
			case INV_CHAIN:
			case INV_CHAINSAW:
				if (weaponEffective()) {
					smlayer_setActorFacing(0, 2, 22, 180);
					_actor[0].act[2].state = 81;
				} else {
					smlayer_setActorFacing(0, 2, 20, 180);
					_actor[0].act[2].state = 16;
				}
				break;	
			case INV_MACE:
				if (!_actor[1].kicking || _actor[1].field_44)
					if (actor1StateFlags(_actor[1].act[2].state)) {
						smlayer_setActorFacing(0, 2, 20, 180);
						_actor[0].act[2].state = 106;
						break;
					}
			default:
				smlayer_setActorFacing(0, 2, 20, 180);
				_actor[0].act[2].state = 16;
				break;
			}
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 16:
		smlayer_setActorLayer(0, 2, 8);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 1) {
			switch (_actor[1].weapon) {
			case INV_CHAIN:
			case INV_CHAINSAW:
				tmp = calcDamage(1, 1);
				if (tmp == 1)
					smlayer_startSound1(76);
				if (tmp == 1000)
					smlayer_startSound1(77);
				break;
			case INV_BOOT:
				calcDamage(0, 1);
				break;
			case INV_DUST:
				if ((_actor[1].x - _actor[0].x <= weaponMaxRange(0)) &&
					(_actor[1].x - _actor[0].x >= weaponMinRange(0))) {
					smlayer_startSound1(76);
					_actor[1].damage = weaponDamage(0);
				}
				break;
			default:
				if (calcDamage(1, 0))
					smlayer_startSound1(76);
				break;
			}
			smlayer_setActorFacing(0, 2, 21,180);
			_actor[0].act[2].state = 17;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 17:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 2) {
			smlayer_setActorFacing(0, 2, 26, 180);
			_actor[0].act[2].state = 64;
			smlayer_stopSound(76);
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 18:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		smlayer_setActorFacing(0, 2, 19, 180);
		_actor[0].act[2].state = 19;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		smlayer_startSound1(69);
		break;
	case 19:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 1) {
			switch (_actor[1].weapon) {
			case INV_CHAIN:
				if (_actor[1].kicking) {
					_actor[1].act[2].state = 108;
					_actor[0].act[2].state = 110;
				} else {
					smlayer_setActorFacing(0, 2, 20, 180);
					_actor[0].act[2].state = 20;
				}
				break;
			case INV_CHAINSAW:
				if (!_actor[1].kicking || !_actor[1].field_44)
					_actor[0].act[2].state = 106;
				else {
					smlayer_setActorFacing(0, 2, 20, 180);
					_actor[0].act[2].state = 20;
				}
				break;
			case INV_MACE:
			case INV_2X4:
				if (weaponEffective()) {
					smlayer_setActorFacing(0, 2, 22, 180);
					_actor[0].act[2].state = 77;
					break;
				}
			default:
				smlayer_setActorFacing(0, 2, 19, 180);
				_actor[0].act[2].state = 19;
				break;
			}
			smlayer_setActorFacing(0, 2, 20, 180);
			_actor[0].act[2].state = 20;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 20:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 1) {
			if (_currEnemy != EN_CAVEFISH) {
				switch (_actor[1].weapon) {
				case INV_CHAINSAW:
				case INV_MACE:
				case INV_2X4:
				case INV_BOOT:
					tmp = calcDamage(1, 1);
					if (tmp == 1)
						smlayer_startSound1(67);
					if (tmp == 1000)
						smlayer_startSound1(68);
					break;
				default:
					smlayer_setActorFacing(0, 2, 19, 180);
					_actor[0].act[2].state = 19;
					break;
				}
			} else {
				if ((_actor[1].x - _actor[0].x <= weaponMaxRange(0)) &&
					(_actor[1].x - _actor[0].x >= weaponMinRange(0)) &&
					!_actor[0].field_54)
					prepareScenePropScene(scenePropIdx[1], 0, 0);
			}
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 21;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 21:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 6) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 65;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 110:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		smlayer_setActorFacing(0, 2, 30, 180);
		_actor[0].act[2].state = 111;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 111:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 7) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 65;
			_actor[0].inventory[INV_CHAIN] = 1; // Chain
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 22:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 0;
		_actor[0].kicking = 1;
		smlayer_setActorFacing(0, 2, 19, 180);
		_actor[0].act[2].state = 23;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		smlayer_startSound1(81);
		break;
	case 23:
		smlayer_setActorLayer(0, 2, 6);
		_actor[0].field_2C = 0;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 4) {
			switch (_actor[1].weapon) {
			case INV_CHAIN:
			case INV_CHAINSAW:
			case INV_MACE:
			case INV_2X4:
			case INV_BOOT:
			case INV_DUST:
				if (weaponEffective()) {
					smlayer_setActorFacing(0, 2, 22, 180);
					_actor[0].act[2].state = 83;
				}
				break;
			default:
				smlayer_setActorFacing(0, 2, 20, 180);
				_actor[0].act[2].state = 24;
				break;
			}
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 21;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 24:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 0;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 1) {
			switch (_actor[1].weapon) {
			case INV_CHAIN:
			case INV_CHAINSAW:
			case INV_MACE:
			case INV_2X4:
			case INV_BOOT:
			case INV_DUST:
				tmp = calcDamage(1, 1);
				if (tmp == 1) {
					if (_currEnemy == EN_CAVEFISH) {
						_actor[1].lost = 1;
						_actor[1].act[2].state = 102;
						_actor[1].damage = _actor[1].maxdamage + 10;
					}
					smlayer_startSound1(79);
				}
				if (tmp == 1000)
					smlayer_startSound1(80);
				break;
			default:
				if (!calcDamage(1, 0))
					smlayer_startSound1(79);
				break;
			}
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 25;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 25:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 0;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 6) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 66;
			_actor[0].field_2C = 1;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 26:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		smlayer_setActorFacing(0, 2, 19, 180);
		_actor[0].act[2].state = 27;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		smlayer_startSound1(72);
		break;
	case 27:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 1) {
			switch (_actor[1].weapon) {
			case INV_HAND:
				smlayer_setActorFacing(0, 2, 20, 180);
				_actor[0].act[2].state = 28;
				break;
			case INV_CHAIN:
			case INV_CHAINSAW:
			case INV_MACE:
			case INV_2X4:
			case INV_BOOT:
			case INV_DUST:
				if (weaponEffective()) {
					smlayer_setActorFacing(0, 2, 22, 180);
					_actor[0].act[2].state = 75;
					break;
				}
			default:
				smlayer_setActorFacing(0, 2, 20, 180);
				_actor[0].act[2].state = 28;
				break;
			}
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 28:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 1;
		if (_actor[0].act[2].frame >= 3) {
			if (_currEnemy != EN_CAVEFISH) {
				switch (_actor[1].weapon) {
				case INV_CHAIN:
				case INV_CHAINSAW:
				case INV_MACE:
				case INV_2X4:
				case INV_BOOT:
				case INV_DUST:
					tmp = calcDamage(1, 1);
					if (tmp == 1)
						smlayer_startSound1(70);
					if (tmp == 1000)
						smlayer_startSound1(71);
					break;
				case 6:
					if (!calcDamage(0, 1))
						smlayer_startSound1(70);
					break;
				default:
					break;
				}
			} else {
				if ((_actor[1].x - _actor[0].x <= weaponMaxRange(0)) &&
					(_actor[1].x - _actor[0].x >= weaponMinRange(0)) &&
					!_actor[0].field_54)
					prepareScenePropScene(scenePropIdx[1], 0, 0);
			}
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 29;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 29:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 6) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].state = 62;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 30:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 21));
		smlayer_setActorFacing(0, 2, 18, 180);
		_actor[0].act[2].state = 31;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		smlayer_startSound1(84);
		break;
	case 31:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		if (_actor[0].act[2].frame >= 6) {
			smlayer_setActorFacing(0, 2, 20, 180);
			_actor[0].act[2].state = 32;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 32:
		smlayer_setActorLayer(0, 2, 4);
		_actor[0].field_2C = 1;
		if (_actor[0].act[2].frame >= 5) {
			switch (_currEnemy) {
			case EN_ROTT3:
				if (calcDamage(0, 0))
					_actor[1].act[2].state = 115;
				break;
			case EN_VULTF2:
				if (calcDamage(0, 0))
					_actor[1].act[2].state = 113;
				break;
			default:
				tmp = calcDamage(1, 1);
				if (tmp == 1)
					smlayer_startSound1(82);
				if (tmp == 1000)
					smlayer_startSound1(83);
				break;
			}
			smlayer_setActorFacing(0, 2, 21, 180);
			_actor[0].act[2].state = 33;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 33:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 5) {
			smlayer_setActorCostume(0, 2, readArray(_numberArray, 12));
			_actor[0].act[2].state = 1;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 36:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].kicking = 0;
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 18));
		smlayer_setActorFacing(0, 2, 6, 180);
		smlayer_startSound1(96);
		switch (_currEnemy) {
		case EN_ROTT1:
			prepareScenePropScene(scenePropIdx[33], 0, 0);
			break;
		case EN_ROTT2:
			tmp = rand() % 5;
			if (!tmp)
				prepareScenePropScene(scenePropIdx[35], 0, 0);
			if (tmp == 3)
				prepareScenePropScene(scenePropIdx[36], 0, 0);
			break;
		case EN_VULTF1:
			prepareScenePropScene(scenePropIdx[6], 0, 0);
			break;
		case EN_VULTM1:
			tmp = rand() % 5;
			if (!tmp)
				prepareScenePropScene(scenePropIdx[40], 0, 0);
			if (tmp == 3)
				prepareScenePropScene(scenePropIdx[41], 0, 0);
			break;
		default:
			break;
		}
		_actor[0].act[2].state = 37;
		break;
	case 37:
		smlayer_setActorLayer(0, 2, 25);
		_actor[0].field_14 = 0;
		_actor[0].kicking = 0;
		if (_actor[0].act[2].frame >= 18 || 
			(_actor[0].x < 50 && _actor[0].act[2].frame >= 10) ||
			 (_actor[0].x > 270 && _actor[0].act[2].frame >= 10)) {
			if (_currSceneId == 21) {
				queueSceneSwitch(23, 0, "benflip.san", 64, 0, 0, 0);
			} else {
				switch (_currEnemy) {
				case EN_ROTT1:
				case EN_ROTT2:
				case EN_ROTT3:
					queueSceneSwitch(9, 0, "wr2_benr.san", 64, 0, 0, 0);
					break;
				case EN_VULTF1:
				case EN_VULTM1:
				case EN_VULTF2:
				case EN_VULTM2:
					queueSceneSwitch(9, 0, "wr2_benv.san", 64, 0, 0, 0);
					break;
				case EN_CAVEFISH:
					queueSceneSwitch(9, 0, "wr2_benc.san", 64, 0, 0, 0);
					break;
				default:
					queueSceneSwitch(9, 0, "wr2_ben.san", 64, 0, 0, 0);
					break;
				}
			}
			_actor[0].act[2].state = 38;
		}
		break;
	case 38:
		if (_actor[0].act[2].frame >= 36) {
			_actor[0].act[2].frame = 0;
			if (_currSceneId == 21) {
				queueSceneSwitch(23, 0, "benflip.san", 64, 0, 0, 0);
			} else {
				switch (_currEnemy) {
				case EN_ROTT1:
				case EN_ROTT2:
				case EN_ROTT3:
					queueSceneSwitch(9, 0, "wr2_benr.san", 64, 0, 0, 0);
					break;
				case EN_VULTF1:
				case EN_VULTM1:
				case EN_VULTF2:
				case EN_VULTM2:
					queueSceneSwitch(9, 0, "wr2_benv.san", 64, 0, 0, 0);
					break;
				case EN_CAVEFISH:
					queueSceneSwitch(9, 0, "wr2_benc.san", 64, 0, 0, 0);
					break;
				default:
					queueSceneSwitch(9, 0, "wr2_ben.san", 64, 0, 0, 0);
					break;
				}
			}
			_actor[0].act[2].state = 38;
		}
		break;
	case 34:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].kicking = 0;
		
		if (!smlayer_actorNeedRedraw(0, 2)) {
			setProperActorState();
			_actor[0].act[2].speedX = 0;
			// heh, for some reason there is no break at this
			// place, so speedX gets overriden on next line
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 35:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].kicking = 0;
		
		if (!smlayer_actorNeedRedraw(0, 2)) {
			switchWeapon();
			_actor[0].act[2].speedX = 0;
		}
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 63:
		smlayer_setActorLayer(0, 2, 5);
		if (_actor[0].act[2].facing) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].facing = 0;
		}
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 64:
		smlayer_setActorLayer(0, 2, 5);
		if (_actor[0].act[2].facing) {
			smlayer_setActorFacing(0, 2, 26, 180);
			_actor[0].act[2].facing = 0;
		}
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 65:
		smlayer_setActorLayer(0, 2, 5);
		if (_actor[0].act[2].facing) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].facing = 0;
		}
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 66:
		smlayer_setActorLayer(0, 2, 5);
		if (_actor[0].act[2].facing) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].facing = 0;
		}
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 62:
		smlayer_setActorLayer(0, 2, 5);
		if (_actor[0].act[2].facing) {
			smlayer_setActorFacing(0, 2, 25, 180);
			_actor[0].act[2].facing = 0;
		}
		_actor[0].field_2C = 1;
		_actor[0].kicking = 0;
		_actor[0].act[2].speedX = speedTranslator(_actor[0].speed);
		break;
	case 1:
		smlayer_setActorLayer(0, 2, 5);
		_actor[0].field_2C = 2;
		_actor[0].kicking = 0;

		switch (_actor[0].speed) {
		case -3:
			if (_actor[0].act[2].facing != -3) {
				smlayer_setActorFacing(0, 2, 6, 180);
				_actor[0].act[2].facing = -3;
			}
			break;
		case -2:
			if (_actor[0].field_8 == 48)
				smlayer_setActorFacing(0, 2, 7, 180);
			_actor[0].act[2].facing = -2;
			break;
		case -1:
			if (_actor[0].field_8 == 46)
				smlayer_setActorFacing(0, 2, 8, 180);
			_actor[0].act[2].facing = -1;
			break;
		case 0:
			if (_actor[0].act[2].facing) {
				smlayer_setActorFacing(0, 2, 9, 180);
				_actor[0].act[2].facing = 0;
			}
			break;
		case 1:
			if (_actor[0].field_8 == 49)
				smlayer_setActorFacing(0, 2, 10, 180);
			_actor[0].act[2].facing = 1;
			break;
		case 2:
			if (_actor[0].field_8 == 51)
				smlayer_setActorFacing(0, 2, 11, 180);
			_actor[0].act[2].facing = 2;
			break;
		case 3:
			if (_actor[0].act[2].facing != 3) {
				smlayer_setActorFacing(0, 2, 12, 180);
				_actor[0].act[2].facing = 3;
			}
			break;
		default:
			break;
		}
		_actor[0].act[2].speedX = 0;
		break;
	default:
		break;
	}
	tmp = _actor[0].x + _actor[0].act[2].speedX + 17 + _actor[0].x1;
	tmp2 = _actor[0].y + _actor[0].y1 - 98;
	
	if (_actor[0].act[2].room)
		smlayer_putActor(0, 2, tmp, tmp2, _smlayer_room2);
	else
		smlayer_putActor(0, 2, tmp, tmp2, _smlayer_room);
	
}

void Insane::actor00Reaction(int32 buttons) {
	int32 tmpx, tmpy;

	switch (_actor[0].speed) {
	case -3:
		if (_actor[0].act[0].state != 41) {
			smlayer_setActorFacing(0, 0, 6, 180);
			_actor[0].act[0].state = 41;
		}
		break;
	case -2:
		if (_actor[0].act[0].state != 40) {
			smlayer_setActorFacing(0, 0, 7, 180);
			_actor[0].act[0].state = 40;
		}
		break;
	case -1:
		if (_actor[0].act[0].state != 39) {
			smlayer_setActorFacing(0, 0, 8, 180);
			_actor[0].act[0].state = 39;
		}
		break;
	case 0:
		if (_actor[0].act[0].state != 1) {
			smlayer_setActorFacing(0, 0, 9, 180);
			_actor[0].act[0].state = 1;
		}
		break;
	case 1:
		if (_actor[0].act[0].state != 55) {
			smlayer_setActorFacing(0, 0, 10, 180);
			_actor[0].act[0].state = 55;
		}
		break;
	case 2:
		if (_actor[0].act[0].state != 56) {
			smlayer_setActorFacing(0, 0, 11, 180);
			_actor[0].act[0].state = 56;
		}
		break;
	case 3:
		if (_actor[0].act[0].state != 57) {
			smlayer_setActorFacing(0, 0, 12, 180);
			_actor[0].act[0].state = 57;
		}
		break;
	default:
		break;
	}
	tmpx = _actor[0].x + _actor[0].x1;
	tmpy = _actor[0].y + _actor[0].y1;

	if (_actor[0].act[0].room)
		smlayer_putActor(0, 0, tmpx, tmpy, _smlayer_room2);
	else
		smlayer_putActor(0, 0, tmpx, tmpy, _smlayer_room);
}

void Insane::actor01Reaction(int32 buttons) {
	int32 tmpx, tmpy;

	chooseWeaponAnim(buttons);

	switch (_actor[0].speed) {
	case -3:
		if (_actor[0].act[1].state != 41 || _actor[0].field_2C != _actor[0].field_30) {
			setEnemyAnimation(0, 6);
			_actor[0].act[1].state = 41;
		}
	
		if (_actor[0].field_14 >= -100) {
			setEnemyAnimation(0, 7);
			_actor[0].act[1].state = 40;
			_actor[0].field_8 = 48;
			_actor[0].speed = -2;
		}
		break;
	case -2:
		if (_actor[0].act[1].state != 40 || _actor[0].field_2C != _actor[0].field_30) {
			setEnemyAnimation(0, 7);
			_actor[0].act[1].state = 40;
		}
		if (_actor[0].field_8 == 48)
			_actor[0].speed = -1;
		else
			_actor[0].speed = -3;
		break;
	case -1:
		if (_actor[0].act[1].state != 39 || _actor[0].field_2C != _actor[0].field_30) {
			setEnemyAnimation(0, 8);
			_actor[0].act[1].state = 39;
		}
	
		if (_actor[0].field_8 == 48)
			_actor[0].speed = 0;
		else
			_actor[0].speed = -2;
		break;
	case 0:
		if (_actor[0].act[1].state != 1 || _actor[0].field_2C != _actor[0].field_30) {
			setEnemyAnimation(0, 9);
			_actor[0].act[1].state = 1;
		}
		_actor[0].field_8 = 1;
		if (_actor[0].field_14 < -100) {
			setEnemyAnimation(0, 8);
			_actor[0].act[1].state = 39;
			_actor[0].field_8 = 46;
			_actor[0].speed = -1;
		} else {
			if (_actor[0].field_14 > 100) {
				setEnemyAnimation(0, 10);
				_actor[0].act[1].state = 55;
				_actor[0].field_8 = 49;
				_actor[0].speed = 1;
			}
		}
		break;
	case 1:
		if (_actor[0].act[1].state != 55 || _actor[0].field_2C != _actor[0].field_30) {
			setEnemyAnimation(0, 10);
			_actor[0].act[1].state = 55;
		}
		if (_actor[0].field_8 == 51)
			_actor[0].speed = 0;
		else
			_actor[0].speed = 2;
		break;
	case 2:
		if (_actor[0].act[1].state != 56 || _actor[0].field_2C != _actor[0].field_30) {
			setEnemyAnimation(0, 11);
			_actor[0].act[1].state = 56;
		}
		if (_actor[0].field_8 == 51)
			_actor[0].speed = 1;
		else
			_actor[0].speed = 3;
		break;
	case 3:
		if (_actor[0].act[1].state != 57 || _actor[0].field_2C != _actor[0].field_30) {
			setEnemyAnimation(0, 12);
			_actor[0].act[1].state = 57;
		}
	
		if (_actor[0].field_14 <= 100) {
			setEnemyAnimation(0, 11);
			_actor[0].act[1].state = 56;
			_actor[0].field_8 = 51;
			_actor[0].speed = 2;
		}
		break;
	}
	
	if (_actor[0].field_38 != _actor[0].field_34) {
		if (_actor[0].field_34 == 2)
			smlayer_setActorFacing(0, 1, 28, 180);
		else
			smlayer_setActorFacing(0, 1, 27, 180);
	}

	tmpx = _actor[0].x + _actor[0].x1;
	tmpy = _actor[0].y + _actor[0].y1;
	if (_actor[0].act[1].room)
		smlayer_putActor(0, 1, tmpx, tmpy, _smlayer_room2);
	else 
		smlayer_putActor(0, 1, tmpx, tmpy, _smlayer_room);
	
	_actor[0].field_30 = _actor[0].field_2C;
	_actor[0].field_38 = _actor[0].field_34;
}

void Insane::actor03Reaction(int32 buttons) {
	int32 tmp;

	switch (_actor[0].act[3].state) {
	case 117:
		reinitActors();
		smlayer_setActorFacing(0, 3, 13, 180);
		_actor[0].act[3].state = 69;
		break;
	case 69:
		if (_actor[0].act[3].frame >= 2)
			_actor[0].act[3].state = 70;
		break;
	case 70:
		if (_actor[0].scenePropSubIdx) {
			smlayer_setActorFacing(0, 3, 4, 180);
			tmp = _currScenePropIdx + _actor[0].scenePropSubIdx;
			if (!smlayer_startSound2(_sceneProp[tmp].sound))
				_actor[0].runningSound = 0;
			else
				_actor[0].runningSound = _sceneProp[tmp].sound;
			_actor[0].act[3].state = 72;
		} else {
			_actor[0].act[3].state = 118;
		}
		break;
	case 72:
		if (_actor[0].runningSound) {
			if (!smlayer_isSoundRunning(_actor[0].runningSound)) {
				smlayer_setActorFacing(0, 3, 5, 180);
				_actor[0].act[3].state = 70;
				_actor[0].scenePropSubIdx = 0;
			}
		} else {
			tmp = _currScenePropIdx + _actor[0].scenePropSubIdx;
			if (_sceneProp[tmp].counter >= _sceneProp[tmp].maxCounter) {
				smlayer_setActorFacing(0, 3, 5, 180);
				_actor[0].act[3].state = 70;
				_actor[0].scenePropSubIdx = 0;
				_actor[0].runningSound = 0;
			}
		}
		break;
	case 118:
		smlayer_setActorFacing(0, 3, 14, 180);
		_actor[0].act[3].state = 71;
		break;
	case 71:
		_actor[0].field_54 = 0;
		if (_actor[0].act[3].frame >= 2)
			_actor[0].act[3].state = 1;
		break;
	case 52:
		if (_actor[0].runningSound)
			smlayer_stopSound(_actor[0].runningSound);
		
		if (_currScenePropIdx)
			shutCurrentScene();

		_actor[0].runningSound = 0;
		_actor[0].field_4C = 0;
		_actor[0].field_54 = 0;
		smlayer_setActorFacing(0, 3, 15, 180);
		_actor[0].act[3].state = 53;
		break;
	case 53:
		if (_actor[0].act[3].frame >= 2) {
			smlayer_setActorFacing(0, 3, 16, 180);
			_actor[0].act[3].state = 54;
		}
		break;
	case 54:
		break;
	case 1:
		_actor[0].field_54 = 0;
		break;
	default:
		break;
	}
}

void Insane::chooseWeaponAnim(int buttons) {
	// kick
	if ((buttons & 1) && (_currEnemy != EN_TORQUE)) {
		if (!_kickingInProgress && actor0StateFlags2(_actor[0].act[2].state + _actor[0].weapon * 238)) {
			switch (_actor[0].weapon) {
			case INV_CHAIN:
				_actor[0].act[2].state = 10;
				break;
			case INV_CHAINSAW:
				_actor[0].act[2].state = 14;
				break;
			case INV_MACE:
				_actor[0].act[2].state = 18;
				break;
			case INV_2X4:
				_actor[0].act[2].state = 22;
				break;
			case INV_WRENCH:
				_actor[0].act[2].state = 26;
				break;
			case INV_BOOT:
				_actor[0].act[2].state = 6;
				break;
			case INV_HAND:
				_actor[0].act[2].state = 2;
				break;
			case INV_DUST:
				_actor[0].act[2].state = 30;
				break;
			default:
				break;
			}
			_actor[0].kicking = 1;
			_kickingInProgress = true;
		}
	} else {
		_kickingInProgress = false;
	}

	// switch weapon
	if ((buttons & 2) && (_currEnemy != EN_TORQUE)) {
		if (_weaponJustSwitched)
			return;

		if (!actor0StateFlags1(_actor[0].act[2].state))
			return;

		switch (_actor[0].weapon) {
		case INV_CHAIN:
		case INV_CHAINSAW:
		case INV_MACE:
		case INV_2X4:
		case INV_WRENCH:
			_actor[0].act[2].state = 35;
			smlayer_setActorFacing(0, 2, 24, 180);
			break;
		case INV_BOOT:
		case INV_HAND:
		case INV_DUST:
			_actor[0].act[2].state = 0;
			switchWeapon();
		}
		
		_weaponJustSwitched = true;
	} else {
		_weaponJustSwitched = false;
	}
}

void Insane::setEnemyAnimation(int32 actornum, int32 arg_4) {
	if (arg_4 <= 12)
		smlayer_setActorFacing(actornum, 1, 
			  actorAnimationData[_actor[actornum].field_2C * 7 + arg_4 - 6], 180);
}

void Insane::switchWeapon(void) {
	do {
		_actor[0].weapon++;
		if (_actor[0].weapon > 7)
			_actor[0].weapon = 0;

	} while (!_actor[0].inventory[_actor[0].weapon]);

	switch (_actor[0].weapon) {
	case INV_CHAIN:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 20));
		smlayer_setActorFacing(0, 2, 18, 180);
		_actor[0].field_2C = 0;
		_actor[0].act[2].state = 34;
		break;
	case INV_CHAINSAW:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 24));
		smlayer_setActorFacing(0, 2, 18, 180);
		_actor[0].field_2C = 0;
		_actor[0].act[2].state = 34;
		break;
	case INV_MACE:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 23));
		smlayer_setActorFacing(0, 2, 18, 180);
		_actor[0].field_2C = 0;
		_actor[0].act[2].state = 34;
		break;
	case INV_2X4:
		if (_currEnemy == EN_CAVEFISH)
			smlayer_setActorCostume(0, 2, readArray(_numberArray, 38));
		else
			smlayer_setActorCostume(0, 2, readArray(_numberArray, 19));

		smlayer_setActorFacing(0, 2, 18, 180);
		_actor[0].field_2C = 0;
		_actor[0].act[2].state = 34;
		break;
	case INV_WRENCH:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 25));
		smlayer_setActorFacing(0, 2, 18, 180);
		_actor[0].field_2C = 0;
		_actor[0].act[2].state = 34;
		break;
	case INV_BOOT:
	case INV_HAND:
	case INV_DUST:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 12));
		_actor[0].field_2C = 2;
		_actor[0].act[2].state = 1;
		break;
	default:
		break;
	}
}

int32 Insane::weaponMaxRange(int32 actornum) {
	static int map[8] = {135, 125, 130, 125, 120, 104, 104, 104};

	if (_actor[actornum].weapon == -1)
		return 104;
	
	return map[_actor[actornum].weapon];
}

int32 Insane::weaponMinRange(int32 actornum) {
	static int map[8] = {80, 40, 80, 40, 80, 80, 40, 50};

	if (_actor[actornum].weapon == -1)
		return 40;
	
	return map[_actor[actornum].weapon];
}

int32 Insane::weaponDamage(int32 actornum) {
	static int map[8] = {20, 300, 25, 40, 15, 10, 10, 5};

	if (_actor[actornum].weapon == -1)
		return 10;
	
	return map[_actor[actornum].weapon];
}

bool Insane::weaponEffective(void) {
	if ((_actor[1].x - _actor[0].x > weaponMaxRange(0)) ||
		(_actor[1].x - _actor[0].x < weaponMinRange(0)) ||
		!_actor[1].kicking)
		return false;

	return true;
}

void Insane::prepareScenePropScene(int32 scenePropNum, bool arg_4, bool arg_8) {
	int tmp;

	if (!loadScenePropSounds(scenePropNum))
		return;

	_actor[0].field_4C = arg_4;
	_actor[1].field_4C = arg_8;
	_currScenePropIdx = scenePropNum;
	_sceneProp[scenePropNum + 1].counter = 0;
	_currScenePropSubIdx = 1;
	if (_sceneProp[scenePropNum + 1].trsId)
		_currTrsMsg = handleTrsTag(_trsFilePtr, _sceneProp[scenePropNum + 1].trsId);
	else
		_currTrsMsg = 0;

	tmp = _sceneProp[scenePropNum + 1].actor;
	if (tmp != -1) {
		_actor[tmp].field_54 = 1;
		_actor[tmp].act[3].state = 117;
		_actor[tmp].scenePropSubIdx = scenePropNum;
	}
}

int32 Insane::calcDamage(bool arg_0, bool arg_4) {
	if ((_actor[1].x - _actor[0].x > weaponMaxRange(0)) ||
		(_actor[1].x - _actor[0].x < weaponMinRange(0)))
		return 0;

	if (_actor[1].field_44 && arg_4)
		return 1000;

	if (!actor1StateFlags(_actor[1].act[2].state))
		return 0;

	if (arg_0) {
		enemyOuchSound();
		_actor[1].damage += weaponDamage(0);
	}

	return 1;
}

void Insane::enemyOuchSound(void) {
	int32 tmp;

	_actor[1].act[3].state = 52;

	switch (_currEnemy) {
	case EN_VULTF1:
		if (_actor[0].weapon == INV_DUST) {
			smlayer_startSound2(287);
		} else {
			if (rand() % 2) {
				smlayer_startSound2(279);
			} else {
				smlayer_startSound2(280);
			}
		}
		break;
	case EN_VULTF2:
		smlayer_startSound2(271);
		break;
	case EN_VULTM1:
		smlayer_startSound2(162);
		break;
	case EN_ROTT1:
		tmp = rand() % 3;

		if (!tmp) {
			smlayer_startSound2(216);
		} else if (tmp == 1) {
			smlayer_startSound2(217);
		} else {
			smlayer_startSound2(218);
		}
		break;
	case EN_ROTT2:
		tmp = rand() % 3;

		if (!tmp) {
			smlayer_startSound2(243);
		} else if (tmp == 1) {
			smlayer_startSound2(244);
		} else {
			smlayer_startSound2(245);
		}
		break;
	case EN_VULTM2:
		smlayer_startSound2(180);
		break;
	default:
		smlayer_startSound2(99);
		break;
	}
}

bool Insane::loadScenePropSounds(int32 scenePropNum) {
	int32 num = 0;
	int32 res = 1;

	if (_sceneProp[scenePropNum + num].index != 1) {
		while (num < 12) {
			res &= smlayer_loadSound(_sceneProp[scenePropNum + num].sound, 0, 2);
			num = _sceneProp[scenePropNum + num].index;

			if (!num)
				break;
		}
	}

	return res != 0;
}

int32 Insane::setProperActorState(void) {
	_actor[0].act[2].facing = -1000;
	switch (_actor[0].weapon) {
	case INV_CHAIN:
		_actor[0].field_2C = 1;
		_actor[0].act[2].state = 63;
		break;
	case INV_CHAINSAW:
		_actor[0].field_2C = 1;
		_actor[0].act[2].state = 64;
		break;
	case INV_MACE:
		_actor[0].field_2C = 1;
		_actor[0].act[2].state = 65;
		break;
	case INV_2X4:
		_actor[0].field_2C = 1;
		_actor[0].act[2].state = 66;
		break;
	case INV_WRENCH:
		_actor[0].field_2C = 1;
		_actor[0].act[2].state = 62;
		break;
	case INV_BOOT:
	case INV_HAND:
	case INV_DUST:
		_actor[0].field_2C = 2;
		_actor[0].act[2].state = 1;
		break;
	default:
		break;
	}
	return _actor[0].act[2].state;
}

void Insane::reinitActors(void) {
	smlayer_setActorCostume(0, 2, readArray(_numberArray, 12));
	smlayer_setActorCostume(0, 0, readArray(_numberArray, 14));
	smlayer_setActorCostume(0, 1, readArray(_numberArray, 13));
	smlayer_setActorLayer(0, 1, 1);
	smlayer_setActorLayer(0, 2, 5);
	smlayer_setActorLayer(0, 0, 10);
	_actor[0].weapon = INV_HAND;
	_actor[0].field_2C = 2;
	_actor[0].field_30 = 0;
	_actor[0].field_34 = 2;
	_actor[0].field_38 = 0;
	_actor[0].speed = 0;
	_actor[0].field_8 = 1;
	_actor[0].act[2].state = 1;
	_actor[0].act[2].facing = 1;
	_actor[0].act[0].state = 0;
	_actor[0].act[1].state = 1;
	_actor[0].act[2].room = 1;
	_actor[0].act[1].room = 1;
	_actor[0].act[0].room = 1;
	_actor[0].field_14 = 0;
}

int Insane::speedTranslator(int value) {
	const int a[7] = {-5, -4, -2, 0, 2, 4, 5};
	if (value+3 > 6)
		return 0;
	
	return a[value+3];
}

bool Insane::actor1StateFlags(int state) {
	// This is compressed table. It contains indexes where state
	// changes. I.e. 0-33: true, 34-38: false 39-72: true, etc.
	const int spans[] = {0, 34, 39, 73, 89, 90, 92, 93, 99, 100, 117};
	bool retvalue = 0;
	unsigned int i;
	
	for (i = 0; i < sizeof(spans); i++) {
		retvalue = !retvalue;
		if (spans[i] <= state)
			break;
	}
	return retvalue;
}

void Insane::escapeKeyHandler(void) {
	struct fluConf *flu;

	//if (!_ptrMainLoop) { } // We don't need it
 	// Demo has different insane, so disable it now
	if (!_insaneIsRunning || _scumm->_features & GF_DEMO) {
		smush_setToFinish();
		return;
	}

	if (_needSceneSwitch || _keyboardDisable)
		return;

	debug(0, "scene: %d", _currSceneId);
	switch (_currSceneId) {
	case 1:
		queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0, _continueFrame1, 1300);
		setWordInString(_numberArray, 9, 0);
		break;
	case 18:
		queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0, _continueFrame1, 1300);
		setWordInString(_numberArray, 9, 1);
		break;
	case 2:
		flu = &_fluConf[14 + _iactSceneId2];
		queueSceneSwitch(flu->sceneId, flu->fluPtr, flu->filenamePtr, 64, 0, 
						 flu->startFrame, flu->numFrames);
		break;
	case 3:
		queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0, _continueFrame1, 1300);
		break;
	case 4:
		if (_needSceneSwitch)
			return;
		
		if (readArray(_numberArray, 6)) {
			if (readArray(_numberArray, 4)) {
				queueSceneSwitch(14, 0, "hitdust2.san", 64, 0, 0, 0);
			} else {
				queueSceneSwitch(14, 0, "hitdust4.san", 64, 0, 0, 0);
			}
		} else {
			if (readArray(_numberArray, 4)) {
				queueSceneSwitch(14, 0, "hitdust1.san", 64, 0, 0, 0);
			} else {
				queueSceneSwitch(14, 0, "hitdust3.san", 64, 0, 0, 0);
			}
		}
		break;
	case 5:
		if (readArray(_numberArray, 4)) {
			if (_needSceneSwitch)
				return;
			queueSceneSwitch(15, 0, "vistthru.san", 64, 0, 0, 0);
		} else {
			setWordInString(_numberArray, 1, _val53d);
			smush_setToFinish();
		}
		break;
	case 6:
		if (readArray(_numberArray, 4)) {
			if (_needSceneSwitch)
				return;
			queueSceneSwitch(15, 0, "chasthru.san", 64, 0, 0, 0);
		} else {
			if (readArray(_numberArray, 5)) {
				setWordInString(_numberArray, 1, _val57d);
				smush_setToFinish();
			} else {
				setWordInString(_numberArray, 4, 1);
				queueSceneSwitch(15, 0, "chasout.san", 64, 0, 0, 0);
			}
		}
		break;
	case 8:
		flu = &_fluConf[7 + _iactSceneId2];
		queueSceneSwitch(flu->sceneId, flu->fluPtr, flu->filenamePtr, 64, 0, 
						 flu->startFrame, flu->numFrames);
		break;
	case 7:
		flu = &_fluConf[0 + _iactSceneId2];
		queueSceneSwitch(flu->sceneId, flu->fluPtr, flu->filenamePtr, 64, 0, 
						 flu->startFrame, flu->numFrames);
		break;
	case 23:
		_actor[0].damage = 0;
		queueSceneSwitch(21, 0, "rottfite.san", 64, 0, 0, 0);
		break;
	case 9:
		_actor[0].damage = 0;
		queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0, _continueFrame, 1300);
		break;
	case 10:
		_actor[0].damage = 0;
		queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0, _continueFrame1, 1300);
		break;
	case 13:
		queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0, _continueFrame, 1300);
		break;
	case 24:
		queueSceneSwitch(21, 0, "rottfite.san", 64, 0, 0, 0);
		break;
	case 16:
		setWordInString(_numberArray, 4, 0);
		setWordInString(_numberArray, 5, 1);
		setWordInString(_numberArray, 1, _val56d);
		setWordInString(_numberArray, 3, _val55d);
		smush_setToFinish();
		break;
	case 15:
		switch (_tempSceneId) {
		case 5:
			queueSceneSwitch(6, 0, "toranch.san", 64, 0, 0, 530);
			break;
		case 6:
			queueSceneSwitch(4, 0, "tovista1.san", 64, 0, 0, 230);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

bool Insane::actor0StateFlags1(int state) {
	const int spans[] = {0, 2, 34, 35, 39, 69, 98, 100, 117};
	bool retvalue = 0;
	unsigned int i;
	
	for (i = 0; i < sizeof(spans); i++) {
		retvalue = !retvalue;
		if (spans[i] <= state)
			break;
	}
	return retvalue;
}

bool Insane::actor0StateFlags2(int state) {
	const int spans[] = {0, 10, 14, 34, 39, 73, 75, 79, 81, 90, 93, 94,
		 98, 100, 117, 133, 136, 153, 158, 200, 202, 209, 212, 213, 217,
		 219, 236, 256, 259, 272, 277, 311, 312, 315, 317, 328, 331, 332,
		 336, 338, 355, 379, 382, 391, 396, 440, 441, 447, 450, 451, 455,
		 457, 474, 502, 505, 510, 515, 549, 553, 566, 569, 570, 574, 576,
		 593, 601, 604, 629, 634, 680, 682, 685, 688, 689, 693, 695, 712,
		 716, 718, 748, 753, 787, 788, 804, 807, 808, 812, 814, 831, 863,
		 866, 867, 872, 920, 922, 923, 926, 927, 931, 933, 950};
	bool retvalue = 0;
	unsigned int i;
	
	for (i = 0; i < sizeof(spans); i++) {
		retvalue = !retvalue;
		if (spans[i] <= state)
			break;
	}
	return retvalue;
}

// smlayer_loadSound1 && smlayer_loadSound2
int Insane::smlayer_loadSound(int id, int flag, int phase) {
	int resid;
	
	if (phase == 1) {
		if (_idx2Exceeded != 0)
			if (_objArray2Idx >= _objArray2Idx2)
				return 0;
	}
	resid = readArray(_numberArray, id);
	
	if (!resid && phase == 2)
		return 0;
	
	if (phase == 2)
		_scumm->ensureResourceLoaded(rtSound, resid);
	
	_scumm->setResourceCounter(rtSound, resid, 1);
	
	if (phase == 1) {
		_objArray2Idx2++;
		_objArray2[_objArray2Idx2] = id;
		if (_objArray2Idx2 > 100) {
			_idx2Exceeded = 1;
			_objArray2Idx2 = 0;
		}
	}
	return resid;
}

void Insane::IMUSE_shutVolume(void) {
	debug(0, "***************************************************");
	_scumm->_imuse->pause(true);
}

void Insane::IMUSE_restoreVolume(void) {
	debug(0, "***************************************************");
	_scumm->_imuse->pause(false);
}

// smlayer_loadCostume1 && smlayer_loadCostume2
int Insane::smlayer_loadCostume(int id, int phase) {
	int resid;
	resid = readArray(_numberArray, id);
	
	if (!resid)
		return 0;
	
	_scumm->ensureResourceLoaded(rtCostume, resid);
	_scumm->setResourceCounter(rtCostume, resid, 1);
	
	// smlayer_lock(rtCostume, resid); // FIXME
	
	if (phase == 1) {
		_objArray1Idx2++;
		_objArray1[_objArray1Idx2] = id;
		if (_objArray1Idx2 == 100)
			_objArray1Idx2 = 0;
	}
	
	return resid;
}

void Insane::smlayer_setActorCostume(int actornum, int actnum, int costume) {
	Actor *a = _scumm->derefActor(_actor[actornum].act[actnum].actor, "smlayer_setActorCostume");
	a->setActorCostume(costume);
	a->setDirection(180);
	a->startAnimActor(1);
	_actor[actornum].act[actnum].frame = 0;
}

void Insane::smlayer_putActor(int actornum, int actnum, int x, int y, byte room) {
	Actor *a = _scumm->derefActor(_actor[actornum].act[actnum].actor, "smlayer_putActor");
	a->putActor(x, y, room);
}

void Insane::smlayer_setActorLayer(int actornum, int actnum, int layer) {
	Actor *a = _scumm->derefActor(_actor[actornum].act[actnum].actor, "smlayer_setActorLayer");
	a->layer = layer;
}

void Insane::smlayer_setFluPalette(byte *pal, int shut_flag) {
	// FIXME. We can't run it without SmushPlayer object
	//	  if (shut_flag)
	//		// FIXME: shut colors and make picture appear smoothly
	//		SmushPlayer::setPalette(pal);
	//	  else
	_player->setPalette(pal);
}

bool Insane::smlayer_isSoundRunning(int32 sound) {
	return _scumm->_sound->isSoundRunning(readArray(_numberArray, sound)) != 0;
}

bool Insane::smlayer_startSound1(int32 sound) {
	// FIXME: original startSound parameters:
	// startSound(id, 40, 1);
	// second param is priority in imuse, 
	// third param set sound to group volume in imuse
	//		(0 - master, 1-sfx, 2-voice, 3 - music, 
	//		 4 - background music)
	// there are no equivalents in scummvm
	if (smlayer_loadSound(sound, 0, 2)) {
		_scumm->_sound->addSoundToQueue(readArray(_numberArray, sound));
		return true;
	} else
		return false;
}

bool Insane::smlayer_startSound2(int32 sound) {
	// FIXME: original startSound parameters:
	// startSound(id, 126, 2);
	// second param is priority in imuse, 
	// third param set sound to group volume in imuse
	//		(0 - master, 1-sfx, 2-voice, 3 - music, 
	//		 4 - background music)
	// there are no equivalents in scummvm
	if (smlayer_loadSound(sound, 0, 2)) {
		_scumm->_sound->addSoundToQueue(readArray(_numberArray, sound));
		return true;
	} else
		return false;
}

void Insane::smlayer_soundSetPan(int32 soundid, int32 pan) {
	_scumm->_imuseDigital->doCommand(12, soundid, 0x700, pan, 0, 0, 0, 0);
}

void Insane::smlayer_soundSetPriority(int32 sound, int32 priority) {
	// FIXME: waits for complete iMUSE digital
	warning("stub Insane::smlayer_soundSetPriority(%d, %d)", sound, priority);
}

void Insane::smlayer_drawSomething(byte *renderBitmap, int32 codecparam, 
			   int32 x, int32 y, int32 arg_10, NutRenderer *nutfile, 
			   int32 c, int32 arg_1C, int32 arg_20) {
	nutfile->drawFrame(renderBitmap, c, x, y);
}

void Insane::smlayer_overrideDrawActorAt(byte *arg_0, byte arg_4, byte arg_8) {
	// FIXME: doublecheck

	// noop in current implementation
}

void Insane::smlayer_showStatusMsg(int32 arg_0, byte *renderBitmap, int32 codecparam, 
					   int32 x, int32 y, int32 arg_14, int32 arg_18, 
					   int32 arg_1C, const char *formatString, char *str) {
	// FIXME: implement
	// SmushPlayer::handleTextResource does the thing
	warning("stub Insane::smlayer_showStatusMsg(...)");
}

void Insane::checkEnemyLoose(int arg_0) {
	int tmp;

	if (_actor[1].damage < _actor[1].maxdamage) {
		_actor[1].lost = 0;
	} else {
		if (!_actor[1].lost && !_actor[1].lost) {
			_actor[1].lost = 1;
			_actor[1].act[2].state = 36;
			_actor[1].act[1].state = 36;
			_actor[1].act[0].state = 36;
			_actor[1].act[1].room = 0;
			_actor[1].act[0].room = 0;
		}
	}

	tmp = 0;

	if (_actor[1].lost == 0) {
		if (arg_0)
			tmp = func60();
	}

	debug(1, "11:%d 12:%d 13:%d 10:%d", _actor[1].act[1].state, 
				_actor[1].act[2].state, _actor[1].act[3].state, _actor[1].act[0].state);
	proc59(1, 1, tmp);
	proc51(1, 2, tmp);
	proc54(1, 3, tmp);
	proc55(1, 0, tmp);
}

void Insane::proc59(int32 actornum, int32 actnum, int32 arg_8) {
	// FIXME: implement
}

void Insane::proc51(int32 actornum, int32 actnum, int32 arg_8) {
	// FIXME: implement
}

void Insane::proc54(int32 actornum, int32 actnum, int32 arg_8) {
	// FIXME: implement
}

void Insane::proc55(int32 actornum, int32 actnum, int32 arg_8) {
	// FIXME: implement
}

int32 Insane::func60(void) {
	// FIXME: implement
	return 0;
}

void Insane::smlayer_setActorFacing(int actornum, int actnum, int frame, int direction) {
	if (_actor[actornum].act[actnum].room) {
		Actor *a = _scumm->derefActor(_actor[actornum].act[actnum].actor, "smlayer_setActorFacing");
		a->setDirection(direction);
		a->startAnimActor(frame);
		_actor[actornum].act[actnum].frame = 0;
	}
}

char *Insane::handleTrsTag(int32 trsFilePtr, int32 trsId) {
	// FIXME: implement
	warning("stub Insane::handleTrsTag(0, %d)", trsId);

	return 0;
}

bool Insane::smush_eitherNotStartNewFrame(void) {
	if (_smush_setupsan17)
		return false;
	
	if (_smush_isSanFileSetup) {
		if (_smush_frameStep < 0)
			return false;
	
		if (_smush_curFrame > _smush_frameStep + _smush_frameNum2)
			return true;
		else
			return false;
	} else {
		if (_smush_frameNum1 < 0)
			return false;
	
		if (_smush_curFrame >= _smush_frameNum1) {
			_smush_frameNum1 = -1;
			return false;
		} else
			return true;
	}
}

int32 Insane::getLastKey(bool arg_0) {
	return _scumm->_lastKeyHit;
}

bool Insane::smlayer_actorNeedRedraw(int actornum, int actnum) {
	Actor *a = _scumm->derefActor(_actor[actornum].act[actnum].actor, "smlayer_actorNeedRedraw");

	return a->needRedraw;
}

void Insane::smush_setPaletteValue(int where, int r, int g, int b) {
	// FIXME: implement
	warning("stub Insane::smlayer_setPaletteValue(%d, %d, %d, %d)", where, r, g, b);
}

int32 Insane::readArray (int number, int item) {
	return _scumm->readArray (number, 0, item);
}

void Insane::setWordInString(int number, int item, int value) {
	_scumm->writeArray(number, 0, item, value);
}

void Insane::smush_setupSanWithFlu(const char *filename, int32 setupsan2, int32 step1, 
								   int32 step2, int32 setupsan1, byte *fluPtr, 
								   int32 numFrames) {
	byte *tmp = fluPtr;
	int32 offset;
	
	_smush_setupsan1 = setupsan1;
	
	/* skip FLUP marker */
	if (READ_BE_UINT32(fluPtr) == 'FLUP')
		tmp += 8;

	_smush_setupsan2 = setupsan2;
	
	if (tmp[2] <= 1) {
		/* 0x300 -- palette, 0x8 -- header */
		offset = READ_LE_UINT32(tmp + 0x308 + numFrames*4);
		smush_setupSanFile(filename, offset);
		memcpy(_smush_earlyFluContents, tmp+2, 0x306);
		_smush_earlyFluContents[0x30e] = 0;
		_smush_earlyFluContents[0x30f] = 0;
		_smush_earlyFluContents[0x310] = 0;
		_smush_earlyFluContents[0x311] = 0;
		_smush_earlyFluContents[0x306] = 0;
		_smush_earlyFluContents[0x307] = 0;
	} else {
		offset = READ_LE_UINT32(tmp + 0x31c + numFrames*4);
		smush_setupSanFile(filename, offset);
		memcpy(_smush_earlyFluContents, tmp+2, 0x31a);
	}
	_smush_isSanFileSetup = 1;
	_smush_setupsan4 = 1;
	_smush_numFrames = numFrames;
	smush_setFrameSteps(step1, step2);
}

void Insane::smush_setupSanFromStart(const char *filename, int32 setupsan2, int32 step1, 
									 int32 step2, int32 setupsan1) {
	_smush_setupsan1 = setupsan1;
	_smush_setupsan2 = setupsan2;
	smush_setupSanFile(filename, 8);
	_smush_isSanFileSetup = 1;
	smush_setFrameSteps(step1, step2);

	_smush_curFrame = 0; // HACK
}

void Insane::smush_setFrameSteps(int32 step1, int32 step2) {
	_smush_frameNum2 = _smush_curFrame;
	_smush_frameNum1 = step2;
	_smush_frameStep = step1;
}

void Insane::smush_setupSanFile(const char *filename, int32 offset) {
	debug(0, "smush_setupSanFile(%s, %d)", filename, offset);

	_player->seekSan(filename, _scumm->getGameDataPath(), offset);

	_scumm->_imuseDigital->pause(false);
	_scumm->_sound->pauseBundleMusic(false);
}

}
#endif // INSANE
