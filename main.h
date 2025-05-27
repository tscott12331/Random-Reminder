#ifndef MAIN_H
#define MAIN_H
#include <wx/wx.h>

enum
{
    ID_MAIN_FRAME,
    ID_MIN_SLIDER,
    ID_MAX_SLIDER,
    ID_NOTIF_INPUT,
    ID_RESTART_CHK,
    ID_PLAY_PAUSE,
    ID_RESTART
};

class MainFrame : public wxFrame {
    public:
        MainFrame(int id);

    private:
        wxPanel* mainPanel;

        wxStaticText* titleText;

        wxSlider* minWaitSlider;
        wxStaticText* minWaitSliderLabel;

        wxSlider* maxWaitSlider;
        wxStaticText* maxWaitSliderLabel;
        
        wxTextCtrl* notifTextArea;

        wxCheckBox* autoRestartCheck;

        wxButton* playPauseButton;

        wxButton* restartButton;

        const wxColor titleTextColor = wxColor(0x40, 0x40, 0x40);
        const wxColor mainTextColor = wxColor(0x50, 0x50, 0x50);
        const wxColor controlBgColor = wxColor(0xee, 0xee, 0xee);

        void CreateControls();
        void SetupSizers();
};

class App : public wxApp {
    public:
        virtual bool OnInit();
    
    private:
        const wxColor mainBgColor = wxColor(0xD6, 0xB5, 0x88);
};

#endif