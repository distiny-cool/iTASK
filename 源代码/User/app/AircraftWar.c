/**************************************************************************************
* 因为emWin显示只支持UTF-8编码格式的中文，如果希望直接显示在Keil直接输入的中文，      *
*            比如使用：GUI_DispStringHCenterAt("流水灯",110,120);                     *
* 该文件必须以UTF-8编码格式，不然中文无法正常显示。                                   *
*                                                                                     *
* 如果只是个别例程出现中文显示乱码（如果所有例程都无法显示中文可能是字库问题），      *
* 把对应的例程文件(比如LEDapp.c)用电脑的记事本软件打开，然后选择另存为，在弹出对      *
* 话框中“保存(S)"按钮的左边有个"编码(E)"选项，选择"UTF-8",然后同样保存为同名称的      *
* C语言文件(覆盖原来文件)，再编译。                                                   *
*                                                                                     *
* 如果编译工程时出现下面类似错误也是该文件编码格式问题,必须把文件保存为UTF-8格式      *
* 再编译                                                                              *
* ..\..\User\app\LEDapp.c(275): error:  #8: missing closing quote                     *
*        GUI_DispStringHCenterAt("娴?姘?鐏?",110,120);                                *
* ..\..\User\app\LEDapp.c(276): error:  #165: too few arguments in function call      *
*        GUI_DispStringHCenterAt("瑙?鎽?鍋?宸?澶?鎵?闇€瑕?瑙?鎽?鏍?鍑?",110,215);     *
* ..\..\User\app\LEDapp.c(276): error:  #18: expected a ")"                           *
*        GUI_DispStringHCenterAt("瑙?鎽?鍋?宸?澶?鎵?闇€瑕?瑙?鎽?鏍?鍑?",110,215);     *
*                                                                                     *
* 修改文件后编译就出错这是Keil5软件问题(Keil4没这问题)，推荐使用其他程序编辑工具，    *
* 只用Keil5完成编译和下载工作。                                                       *
***************************************************************************************
*                      实验平台: 野火STM32 ISO 开发板                                 *
*                      论    坛: http://www.chuxue123.com                             *
*                      淘    宝: http://firestm32.taobao.com                          *
*                      邮    箱: wildfireteam@163.com                                 *
***************************************************************************************
*/
/**************************************************************************************
*                                                                                     *
*                SEGGER Microcontroller GmbH & Co. KG                                 *
*        Solutions for real time microcontroller applications                         *
*                                                                                     *
***************************************************************************************
*                                                                                     *
* C-file generated by:                                                                *
*                                                                                     *
*        GUI_Builder for emWin version 5.22                                           *
*        Compiled Jul  4 2013, 15:16:01                                               *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG                                *
*                                                                                     *
***************************************************************************************
*                                                                                     *
*        Internet: www.segger.com  Support: support@segger.com                        *
*                                                                                     *
***************************************************************************************
*/
// USER START (Optionally insert additional includes)
#include "includes.h"
#include  "app.h"
#include "GUI.h"
#include "GUI_Private.h"
#include "WM.h"

#include "stdlib.h"

/*********************************************************************
*
*       External dependencies
*
**********************************************************************
*/
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipTop_Small;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipLeft_Small;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipRight_Small;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipBottom_Small;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShip;
extern GUI_CONST_STORAGE GUI_BITMAP bmAsteroid;
extern GUI_CONST_STORAGE GUI_BITMAP bmBang;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define XSIZE_DISPLAY LCD_GetXSize()
#define YSIZE_DISPLAY LCD_GetYSize()

#define PERIOD_GAME  20000
#define PERIOD_INTRO  2000

#define YSIZE_BAR 12

#define DIR_NONE   0
#define DIR_LEFT   1
#define DIR_RIGHT  2

#define CONTROL_TYPE_PID 0
#define CONTROL_TYPE_JOY 1
#define CONTROL_TYPE     CONTROL_TYPE_PID

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  int xPos;
  int yPos;
  GUI_CONST_STORAGE GUI_BITMAP * pBitmap;
} SHIP;

typedef struct {
  int xPos;
  int yPos;
} ASTEROID;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetDirection()
*
*  Function description:
*    This function returns the direction the space ship should fly.
*    It might be necessary to adapt this function depending on the
*    hardware used.
*
*    CONTROL_TYPE_PID:
*      Use the PID input to move the ship left or right. The ship
*      will move to the left if clicked left of the ship and to the
*      right if clicked right of it.
*
*    CONTROL_TYPE_JOY:
*      Use this if the pid buffer gets filled by a joystick.
*      If State.x is bigger than 0 the stick is pushed to the right.
*      If State.x is smaler than 0 the stick is pushed to the left.
*      This was originally for the SEGGER emPower evaluation board.
*/
static int _GetDirection(SHIP * pShip) {
#if (CONTROL_TYPE == CONTROL_TYPE_PID)
  //
  // CONTROL_TYPE_PID
  //
  GUI_PID_STATE State;
  int           Direction;
  int           Center;
  
  GUI_PID_GetState(&State);                              // Get the current PID state
  Direction = DIR_NONE;
  if (pShip) {                                           // If we have a ship
    if (State.Pressed) {                                 // Check if it is pressed
      Center = pShip->xPos + pShip->pBitmap->XSize / 2;  // If pressed get the center of the ship
      if (State.x > Center) {                            // Pressed right of the ship
        Direction = DIR_RIGHT;
      } else if (State.x < Center) {                     // Pressed left of the ship
        Direction = DIR_LEFT;
      }
    }
  } else {                                               // We have no ship
    if (State.Pressed == 1) {                            // Anyway, if pressed return a value
      Direction = DIR_LEFT;
    }
  }
  return Direction;
#elif (CONTROL_TYPE == CONTROL_TYPE_JOY)
  //
  // CONTROL_TYPE_KEY
  //
  GUI_PID_STATE State;
  int           Direction;
  
  GUI_PID_GetState(&State);    // Get the current PID state
  if (pShip) {                 // If we have a ship
    if (State.x > 0) {         // Pressed right of the ship
      Direction = DIR_RIGHT;
    } else if (State.x < 0) {  // Pressed left of the ship
      Direction = DIR_LEFT;
    } else {
      Direction = DIR_NONE;    // No pressed state
    }
  } else {                     // We have no ship
    if (State.x != 0) {        // Anyway, if pressed return a value
      Direction = DIR_LEFT;
    } else {
      Direction = DIR_NONE;
    }
  }
  return Direction;
#endif
}

/*********************************************************************
*
*       _Game()
*/
static void _Game(SHIP * pShip) {
  int Direction;
  //
  // Clear previous shape
  //
  GUI_ClearRect(pShip->xPos, pShip->yPos, pShip->xPos + pShip->pBitmap->XSize - 1, pShip->yPos + pShip->pBitmap->YSize - 1);
  //
  // Check which direction
  //
  Direction = _GetDirection(pShip);
  switch (Direction) {
  case DIR_RIGHT:
    //
    // Set the proper bitmap
    //
    pShip->pBitmap = &bmSpaceShipRight_Small;
    //
    // Clear a rectangle left of the bitmap
    //
    GUI_ClearRect(pShip->xPos,     pShip->yPos,
                  pShip->xPos + 5, pShip->yPos + bmSpaceShipTop_Small.YSize);
    //
    // Set new x-position
    //
    pShip->xPos += (pShip->xPos + 5 < LCD_GetXSize() - bmSpaceShipTop_Small.XSize) ? 5 : 0;
    break;
  case DIR_LEFT:
    //
    // Set the proper bitmap
    //
    pShip->pBitmap = &bmSpaceShipLeft_Small;
    //
    // Clear a rectangle left of the bitmap
    //
    GUI_ClearRect(pShip->xPos + bmSpaceShipTop_Small.XSize - 5, pShip->yPos,
                  pShip->xPos + bmSpaceShipTop_Small.XSize,     pShip->yPos + bmSpaceShipTop_Small.YSize);
    //
    // Set new x-position
    //
    pShip->xPos -= (pShip->xPos - 5 > 0) ? 5 : 0;
    break;
  default:
    //
    // No button is pressed, set the default bitmap
    //
    pShip->pBitmap = &bmSpaceShipTop_Small;
    break;
  }
  //
  // Draw bitmap
  //
  GUI_DrawBitmap(pShip->pBitmap, pShip->xPos, pShip->yPos);
}

/*********************************************************************
*
*       _Asteroid()
*/
static void _Asteroid(ASTEROID * pAsteroid) {
  //
  // Clear a rectangle above the bitmap
  //
  GUI_ClearRect(pAsteroid->xPos,                    pAsteroid->yPos,
                pAsteroid->xPos + bmAsteroid.XSize, pAsteroid->yPos + 10);
  //
  // Set a new y-position
  //
  pAsteroid->yPos += 5;
  //
  // Draw the bitmap
  //
  GUI_DrawBitmap(&bmAsteroid, pAsteroid->xPos, pAsteroid->yPos);
  //
  // If the bitmap is no longer visible, set a new x- and y-position
  //
  if (pAsteroid->yPos >= LCD_GetYSize()) {
    pAsteroid->xPos = rand() % (XSIZE_DISPLAY - bmAsteroid.XSize);
    pAsteroid->yPos = -((int)bmAsteroid.YSize);
  }
}

/*********************************************************************
*
*       _CheckCollision()
*/
static int _CheckCollision(ASTEROID * pAsteroid, ASTEROID * pAsteroid2, SHIP * pShip) {
  GUI_RECT RectShip, RectAsteroid;
  int xPos, yPos;
  int i, r;
  LCD_PIXELINDEX Index;

  r = 0;
  RectShip.x0 = pShip->xPos;
  RectShip.y0 = pShip->yPos;
  RectShip.x1 = RectShip.x0 + pShip->pBitmap->XSize - 1;
  RectShip.y1 = RectShip.y0 + pShip->pBitmap->YSize - 1;
  RectAsteroid.x0 = pAsteroid->xPos;
  RectAsteroid.y0 = pAsteroid->yPos;
  RectAsteroid.x1 = RectAsteroid.x0 + bmAsteroid.XSize - 1;
  RectAsteroid.y1 = RectAsteroid.y0 + bmAsteroid.YSize - 1;
  //
  // First a simple check if rectangles of bitmaps overlap
  //
  if (GUI_RectsIntersect(&RectShip, &RectAsteroid)) {
    //
    // Check if lower row of asteroid collides with plane
    //
    yPos = RectAsteroid.y0 - RectShip.y0 + bmAsteroid.YSize - 1;
    if (yPos < pShip->pBitmap->XSize) {
      for (i = 0; i < bmAsteroid.XSize; i++) {
        xPos = RectAsteroid.x0 - RectShip.x0 + i;
        if ((xPos >= 0) && (xPos < pShip->pBitmap->XSize)) {
          Index = GUI_GetBitmapPixelIndex(pShip->pBitmap, xPos, yPos);
          if ((Index > 0) && (Index < 255))  {
            GUI_Clear();
            GUI_DrawBitmap(&bmBang, 0, 20);
            LCD_ControlCache(LCD_CC_UNLOCK);
            LCD_ControlCache(LCD_CC_LOCK);
            GUI_Delay(1000);
            GUI_Clear();
            pAsteroid->yPos = pAsteroid2->yPos - YSIZE_DISPLAY / 2;
            r = 1;
            break;
          }
        }
      }
    }
  }
  return r;
}

/*********************************************************************
*
*       _ShowTitle
*/
static void _ShowTitle(void) {
  GUI_Clear();
  GUI_DispStringHCenterAt("emWin Space Evader", XSIZE_DISPLAY / 2, 2);
  GUI_DrawHLine(YSIZE_BAR - 1, 0, XSIZE_DISPLAY - 1);
}

/*********************************************************************
*
*       _Intro()
*/
static void _Intro(void) {
  int t0, tEnd, tNow, tUsed;
  int yPos;

  _ShowTitle();
  t0 = GUI_GetTime();
  tEnd = t0 + PERIOD_INTRO;
  do {
    tNow = GUI_GetTime();
    tUsed = tNow - t0;
    tUsed = (tUsed > PERIOD_INTRO) ? PERIOD_INTRO : tUsed;
    yPos = YSIZE_DISPLAY - (tUsed * (YSIZE_DISPLAY - YSIZE_BAR)) / PERIOD_INTRO;
    GUI_DrawBitmap(&bmSpaceShip, (XSIZE_DISPLAY - bmSpaceShip.XSize) / 2, yPos);
  } while (tNow < tEnd);
  GUI_Delay(1000);
  GUI_Clear();
}

/*********************************************************************
*
*       _Explain()
*/
static void _Explain(void) {
  int yPos, ySizeFont;
  unsigned i;
  const char * apText[] = {
    "Use buttons PB0",
    "and PB1 for moving",
    "the starship.",
    "",
    "Remaining time is",
    "shown in the the",
    "lower right edge",
    "of the display.",
  };
  int Direction;

  _ShowTitle();
  ySizeFont = GUI_GetFontSizeY() + 2;
  yPos = (YSIZE_DISPLAY - ySizeFont * GUI_COUNTOF(apText)) / 2;
  for (i = 0; i < GUI_COUNTOF(apText); i++) {
    GUI_DispStringHCenterAt(apText[i], XSIZE_DISPLAY / 2, yPos);
    yPos += ySizeFont;
  }
  GUI_DispStringHCenterAt("PRESS BUTTON TO START", XSIZE_DISPLAY / 2, YSIZE_DISPLAY - 10);
  do {
    Direction = _GetDirection(NULL);
    if (Direction) {
      break;
    }
    GUI_X_Delay(10);
  } while (1);
  GUI_Clear();
	GUI_SetColor(GUI_BLACK);
  GUI_SetBkColor(GUI_WHITE);
  GUI_DispStringHCenterAt("Good luck...", XSIZE_DISPLAY / 2, YSIZE_DISPLAY / 2 - 4);
  GUI_Delay(1000);
  GUI_Clear();
}

/*********************************************************************
*
*       _ShowResult
*/
static void _ShowResult(unsigned Cnt) {
  _ShowTitle();
  if (Cnt) {
    GUI_DispStringHCenterAt("Ships lost in space:\n\n", XSIZE_DISPLAY / 2, YSIZE_DISPLAY / 2 - 10);
    GUI_GotoXY(XSIZE_DISPLAY / 2 - 4, YSIZE_DISPLAY / 2);
    GUI_DispDecMin(Cnt);
  } else {
    GUI_DispStringHCenterAt("CONGRATULATIONS\n\nNo ship lost", XSIZE_DISPLAY / 2, YSIZE_DISPLAY / 2 - 10);
  }
  GUI_Delay(2000);
}
// USER END

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreateUSER[] = {
  { FRAMEWIN_CreateIndirect, "UserApp", 0, 0, 0, 240, 320, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)

// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialogUSER(WM_MESSAGE * pMsg) {
  SHIP Ship;
  ASTEROID aAsteroid[2];
  unsigned i, Cnt;
  GUI_TIMER_TIME t0, tEnd, tNow;

  //
  // Initialize GUI
  //
  //GUI_Init();
  //
  // Set foreground color to black
  //
  GUI_SetColor(GUI_BLACK);
  GUI_SetBkColor(GUI_WHITE);
  //
  // Explanation
  //
  _Explain();
  //
  // Run forever...
  //
  while (1) {
    //
    // Initialize some structures
    //
    Ship.xPos = (XSIZE_DISPLAY - bmSpaceShipTop_Small.XSize) / 2;
    Ship.yPos = YSIZE_DISPLAY - bmSpaceShipTop_Small.YSize - 5;
    Ship.pBitmap = &bmSpaceShipTop_Small;
    for (i = 0; i < GUI_COUNTOF(aAsteroid); i++) {
      aAsteroid[i].xPos = rand() % (XSIZE_DISPLAY - bmAsteroid.XSize);
      aAsteroid[i].yPos = -((int)bmAsteroid.YSize) - i * 64;
    }
    //
    // Intro
    //
    _Intro();
    //
    // The game
    //
    t0 = GUI_GetTime();
    tEnd = t0 + PERIOD_GAME;
    Cnt = 0;
    do {
      //
      // Lock cache, output is written to cache only
      //
      LCD_ControlCache(LCD_CC_LOCK);
      //
      // Handle drawing of the ship
      //
      _Game(&Ship);
      //
      // Handle drawing of the asteroid
      //
      for (i = 0; i < GUI_COUNTOF(aAsteroid); i++) {
        _Asteroid(&aAsteroid[i]);
        //
        // Check collision
        //
        if (_CheckCollision(&aAsteroid[i], &aAsteroid[1 - i], &Ship)) {
          Cnt++;
        }
      }
      tNow = GUI_GetTime();
      //
      // Show remaining time
      //
      GUI_GotoXY(XSIZE_DISPLAY - 12 - 1, YSIZE_DISPLAY - 8 - 1);
      GUI_DispDecSpace((tEnd - tNow + 1000) / 1000, 2);
      //
      // Show content of cache
      //
      LCD_ControlCache(LCD_CC_UNLOCK);
      //
      // Wait a while...
      //
      GUI_Delay(50);
    } while (GUI_GetTime() < tEnd);
    //
    // Show result
    //
    _ShowResult(Cnt);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateUSB TEST
*/
void FUN_ICON104Clicked(void)
{
	WM_HWIN hWin;
	OS_INFO("USERapp create\n");
	hWin=GUI_CreateDialogBox(_aDialogCreateUSER, GUI_COUNTOF(_aDialogCreateUSER), _cbDialogUSER, WM_HBKWIN, 0, 0);
	
	while(Flag_ICON104)
	{					 				
		if(tpad_flag)WM_DeleteWindow(hWin);
    GUI_Delay(10); 				
	}
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
