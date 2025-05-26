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
        wxSlider* maxWaitSlider;
        wxTextCtrl* notifTextArea;
        wxCheckBox* autoRestartCheck;
        wxButton* playPauseButton;
        wxButton* restartButton;

        void CreateControls();
        void SetupSizers();
};

class App : public wxApp {
    public:
        virtual bool OnInit();
};

#endif