/*******************************************************************************
@Module         Control Panel (CP)

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename       CP_ControlPanel.h

--------------------------------------------------------------------------------
@Description    Represents the control panel from the wasing machine

--------------------------------------------------------------------------------
@Author         Iulian G.
@Date           15.11.2018

-------------------------------------------------------------------------------
@Copyright      Miele & Cie Copyright 2018
*******************************************************************************/

#ifndef _CP_CONTROLPANEL_H_
#define _CB_CONTROLPANEL_H_

#include <stdint.h>
#include "Arduino.h"
#include "CB_ControlButton.h"

class ControlPanel
{
private:
    ControlButton m_btnList_ao[BTN_LAST_ENTRY];         // panel button list
    bool m_ButtonCurrentState_ab[BTN_LAST_ENTRY];       // remember button state to answer when asked
public:
    ControlPanel();
    void checkButtonPress_v();
    bool getButtonState_b(ButtonsPanel_te buttonID_e);
};

#endif