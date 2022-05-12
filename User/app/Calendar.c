/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include  "includes.h"
#include  "app.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_LISTVIEW_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_0 (GUI_ID_USER + 0x02)
#define ID_BUTTON_1 (GUI_ID_USER + 0x03)
//#define RECOMMENDED_MEMORY (1024L * 32)

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
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Schedule", ID_FRAMEWIN_0, 0, 0, 240, 320, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 10, 20, 212, 117, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "ADD", ID_BUTTON_0, 35, 180, 70, 25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "DELETE", ID_BUTTON_1, 125, 180, 70, 25, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

static const char * _Table[][2] = {
   {"0","OS homework"},
   {"1","basketball"},
   {"2","shop"},
   {"3","You can write here"}
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
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  //ListView_SetExtendedListViewStyle(hItem, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    hItem = pMsg->hWin;
    FRAMEWIN_SetTitleHeight(hItem, 32);
    FRAMEWIN_SetText(hItem, "Schedule");
    FRAMEWIN_SetFont(hItem, GUI_FONT_32_ASCII);
    //
    // Initialization of 'Listview'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
    LISTVIEW_AddColumn(hItem, 30, "Col 0", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 180, "Col 1", GUI_TA_HCENTER | GUI_TA_VCENTER);
    for (int i = 0; i < (GUI_COUNTOF(_Table)-1); i++){
         LISTVIEW_AddRow(hItem, _Table[i]);
    }
    //LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_SetGridVis(hItem, 1);
    LISTVIEW_SetRowHeight(hItem, 25);
    //LISTVIEW_AddRow(hItem, NULL);
    //LISTVIEW_AddRow(hItem, NULL);
    //LISTVIEW_AddRow(hItem, NULL);
    //LISTVIEW_SetItemText(hItem, 0, 0, "0");
    //LISTVIEW_SetItemText(hItem, 0, 1, "1");
    //LISTVIEW_SetItemText(hItem, 0, 2, "2");
    //LISTVIEW_SetItemText(hItem, 0, 3, "3");

    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;

    typedef struct {
        char Col0[20];
        char Col1[20];
    } _ListviewItem;
  _ListviewItem ListviewItem;
  int Listview_RowNum;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_LISTVIEW_0: // Notifications sent by 'Listview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
        Listview_RowNum = LISTVIEW_GetSel(hItem);
        LISTVIEW_GetItemText(hItem, 0, Listview_RowNum,ListviewItem.Col0, 20);
        LISTVIEW_GetItemText(hItem, 1, Listview_RowNum,ListviewItem.Col1, 20);
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        //hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
        //sprintf(buf, "Col 0: %s", ListviewItem.Col0);
        //TEXT_SetText(hItem, buf);
        //hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
        //sprintf(buf, "Col 1: %s", ListviewItem.Col1);
        //TEXT_SetText(hItem, buf);
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'ADD'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
        LISTVIEW_AddRow(hItem, _Table[3]);
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'DELETE'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
        int listview_RowIndex = LISTVIEW_GetNumRows(hItem);
        if (listview_RowIndex == 1) {
            break;
        }
        listview_RowIndex = listview_RowIndex - 1;
        LISTVIEW_DeleteRow(hItem, listview_RowIndex);
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
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
*       CreateSchedule
*/
//WM_HWIN CreateSchedule(void);
//WM_HWIN CreateSchedule(void) {
//  WM_HWIN hWin;

//  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
//  return hWin;
//}
//void FUN_ICON107Clicked(void)
//{
//	WM_HWIN hWin;
//	OS_INFO("Calendar create\n");
//	hWin=GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);

//		while(Flag_ICON107)
//	{
//		if(tpad_flag)WM_DeleteWindow(hWin);
//		GUI_Delay(10);
//	}
//}

