#include "main.h"

bool App::OnInit() {
    MainFrame* frame = new MainFrame(ID_MAIN_FRAME);

    wxColor bgColor(0x33, 0x28, 0x30);

    frame->SetBackgroundColour(bgColor);

    frame->Show();
    return true;
}

void MainFrame::CreateControls() {
    wxFont titleFont = wxFont(wxFontInfo(32).Bold());
    titleText = new wxStaticText(mainPanel, wxID_ANY,
                        "Random Reminder");
    titleText->SetFont(titleFont);

    minWaitSlider = new wxSlider(mainPanel, ID_MIN_SLIDER,
                                5, 1, 120, wxDefaultPosition,
                            wxSize(100, -1));

    maxWaitSlider = new wxSlider(mainPanel, ID_MAX_SLIDER,
                                45, 2, 240, wxDefaultPosition,
                            wxSize(100, -1));

    notifTextArea = new wxTextCtrl(mainPanel, ID_NOTIF_INPUT,
                                "Random Reminder", wxDefaultPosition,
                                wxSize(150, 100));
    
    autoRestartCheck = new wxCheckBox(mainPanel, ID_RESTART_CHK,
                            "Auto Restart", wxDefaultPosition, wxSize(-1, 50));

    playPauseButton = new wxButton(mainPanel, ID_PLAY_PAUSE,
                        "Toggle On/Off", wxDefaultPosition,
                        wxSize(-1, 50));
    
    restartButton = new wxButton(mainPanel, ID_RESTART,
                        "Restart", wxDefaultPosition,
                        wxSize(-1 , 50));
}

void MainFrame::SetupSizers() {
    // minWaitSlider->Hide();
    // maxWaitSlider->Hide();
    // notifTextArea->Hide();
    // autoRestartCheck->Hide();
    // playPauseButton->Hide();
    // restartButton->Hide();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(
        titleText,
        wxSizerFlags(0).CenterHorizontal()
    );

    wxBoxSizer* middleSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(
        middleSizer,
        wxSizerFlags(8).Expand().Border(wxTOP | wxBOTTOM, 25)
    );

    wxBoxSizer* sliderSizer = new wxBoxSizer(wxVERTICAL);
    wxSizerFlags sliderFlags = wxSizerFlags(1).CenterHorizontal();

    sliderSizer->AddStretchSpacer(1);

    sliderSizer->Add(
        minWaitSlider,
        sliderFlags
    );

    sliderSizer->AddStretchSpacer(1);

    sliderSizer->Add(
        maxWaitSlider,
        sliderFlags
    );

    sliderSizer->AddStretchSpacer(1);

    middleSizer->AddStretchSpacer(1);

    middleSizer->Add(
        sliderSizer,
        wxSizerFlags(2).Expand()
    );

    middleSizer->AddStretchSpacer(1);

    wxBoxSizer* notifTextCtrlSizer = new wxBoxSizer(wxVERTICAL);

    notifTextCtrlSizer->AddStretchSpacer(1);

    notifTextCtrlSizer->Add(
        notifTextArea,
        wxSizerFlags(4).Expand()
    );

    notifTextCtrlSizer->AddStretchSpacer(1);

    middleSizer->Add(
        notifTextCtrlSizer,
        wxSizerFlags(2).CenterVertical()
    );


    middleSizer->AddStretchSpacer(1);

    mainSizer->Add(
        autoRestartCheck,
        wxSizerFlags(1).CenterHorizontal()
    );

    wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);

    bottomSizer->Add(
        playPauseButton,
        wxSizerFlags().CenterVertical()
    );
    bottomSizer->Add(
        restartButton,
        wxSizerFlags().CenterVertical()
    );

    mainSizer->Add(
        bottomSizer,
        wxSizerFlags(1).CenterHorizontal()
    );

    mainPanel->SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);
}

MainFrame::MainFrame(int id) : wxFrame(NULL, id, "Hello World") {
    mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, -1));

    CreateControls();

    SetupSizers();
    // mainSizer->SetSizeHints(this);
}

wxIMPLEMENT_APP(App);