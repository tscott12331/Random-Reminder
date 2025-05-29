#include "main.h"

bool App::OnInit() {
    srand(time(NULL));
    MainFrame* frame = new MainFrame(wxID_ANY);
    
    frame->SetBackgroundColour(mainBgColor);

    frame->Show();
    return true;
}

void MainFrame::OnResetPressed(wxCommandEvent& event) {
    timer.Stop();
    timeRemaining = currentInterval;
    playPauseButton->SetLabelText("Start");
    wxLogStatus("Timer reset");
}

void MainFrame::OnMaxSliderChange(wxCommandEvent& event) {
    minWaitSlider->SetMax(event.GetInt());
}

void MainFrame::OnMinSliderChange(wxCommandEvent& event) {
    maxWaitSlider->SetMin(event.GetInt());
}

void MainFrame::OnPlayPause(wxCommandEvent& event) {
    if(timer.IsRunning()) {
        long currentTime = wxGetLocalTimeMillis().GetLo();
        timeRemaining = timeRemaining - (currentTime - timeStarted);
        wxLogStatus(wxString::Format("Time: %ld", timeRemaining));
        playPauseButton->SetLabelText("Start");
        timer.Stop();
    } else {
        if(timeRemaining == currentInterval) {
            currentInterval = (rand() % (maxWaitSlider->GetValue() -
                                        minWaitSlider->GetValue() + 1) +
                                        minWaitSlider->GetValue())
                                        * 60 * 1000;
            timeRemaining = currentInterval;
        }
        timeStarted = wxGetLocalTimeMillis().GetLo();
        playPauseButton->SetLabelText("Pause");
        timer.Start(timeRemaining, wxTIMER_ONE_SHOT);
    }
}

void MainFrame::OnTimerEnd(wxTimerEvent& event) {
    notification->SetMessage(notifTextArea->GetValue());
    notification->Show(wxNotificationMessage::Timeout_Auto);

    // set new random currentInterval
    currentInterval = (rand() % (maxWaitSlider->GetValue() -
                                minWaitSlider->GetValue() + 1) +
                                minWaitSlider->GetValue())
                                * 60 * 1000;
    timeRemaining = currentInterval;

    if(autoRestartCheck->IsChecked()) {
        playPauseButton->SetLabelText("Pause");
        timeStarted = wxGetLocalTimeMillis().GetLo();
        timer.Start(timeRemaining, wxTIMER_ONE_SHOT);
        // wxLogStatus(wxString::Format("Restarting"));
    } else {
        playPauseButton->SetLabelText("Start");
        // wxLogStatus(wxString::Format("Reminder at %ld", wxGetLocalTime()));
    }
}

void MainFrame::BindEventHandlers() {
    playPauseButton->Bind(wxEVT_BUTTON, &MainFrame::OnPlayPause, this);
    timer.Bind(wxEVT_TIMER, &MainFrame::OnTimerEnd, this);
    maxWaitSlider->Bind(wxEVT_SLIDER, &MainFrame::OnMaxSliderChange, this);
    minWaitSlider->Bind(wxEVT_SLIDER, &MainFrame::OnMinSliderChange, this);
    resetButton->Bind(wxEVT_BUTTON, &MainFrame::OnResetPressed, this);
}

void MainFrame::CreateControls() {
    wxFont titleFont = wxFont(wxFontInfo(32).Bold());
    titleText = new wxStaticText(mainPanel, wxID_ANY,
                        "Random Reminder", wxDefaultPosition, wxDefaultSize,
                    wxBORDER_NONE);
    titleText->SetFont(titleFont);
    titleText->SetForegroundColour(titleTextColor);

    minWaitSlider = new wxSlider(mainPanel, ID_MIN_SLIDER,
                                5, 1, 120, wxDefaultPosition,
                            wxSize(100, -1), wxSL_VALUE_LABEL);
    minWaitSlider->SetForegroundColour(mainTextColor);
    minWaitSliderLabel = new wxStaticText(mainPanel, wxID_ANY, "Minimum Wait");
    minWaitSliderLabel->SetForegroundColour(mainTextColor);

    maxWaitSlider = new wxSlider(mainPanel, ID_MAX_SLIDER,
                                45, 5, 240, wxDefaultPosition,
                            wxSize(100, -1), wxSL_VALUE_LABEL);
    maxWaitSlider->SetForegroundColour(mainTextColor);
    maxWaitSliderLabel = new wxStaticText(mainPanel, wxID_ANY, "Maximum Wait");
    maxWaitSliderLabel->SetForegroundColour(mainTextColor);

    notifTextArea = new wxTextCtrl(mainPanel, ID_NOTIF_INPUT,
                                "Random Reminder", wxDefaultPosition,
                                wxSize(150, 100), wxTE_MULTILINE);
    notifTextArea->SetBackgroundColour(controlBgColor);
    notifTextArea->SetForegroundColour(mainTextColor);
    notifTextArea->SetMaxLength(256);
    
    autoRestartCheck = new wxCheckBox(mainPanel, ID_RESTART_CHK,
                            "Auto Restart", wxDefaultPosition, wxSize(-1, -1));
    autoRestartCheck->SetForegroundColour(mainTextColor);

    playPauseButton = new wxButton(mainPanel, ID_PLAY_PAUSE,
                        "Start", wxDefaultPosition,
                        wxSize(-1, 50));
    playPauseButton->SetBackgroundColour(controlBgColor);
    playPauseButton->SetForegroundColour(mainTextColor);
    
    resetButton = new wxButton(mainPanel, ID_RESET,
                        "Reset", wxDefaultPosition,
                        wxSize(-1 , 50));
    resetButton->SetBackgroundColour(controlBgColor);
    resetButton->SetForegroundColour(mainTextColor);
}

void MainFrame::SetupSizers() {
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

    sliderSizer->AddStretchSpacer(2);

    sliderSizer->Add(
        minWaitSlider,
        sliderFlags
    );
    sliderSizer->Add(
        minWaitSliderLabel,
        sliderFlags
    );

    sliderSizer->AddStretchSpacer(2);

    sliderSizer->Add(
        maxWaitSlider,
        sliderFlags
    );
    sliderSizer->Add(
        maxWaitSliderLabel,
        sliderFlags
    );

    sliderSizer->AddStretchSpacer(2);

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
        wxSizerFlags(2).Expand()
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
        resetButton,
        wxSizerFlags().CenterVertical()
    );

    mainSizer->Add(
        bottomSizer,
        wxSizerFlags(1).CenterHorizontal()
    );

    wxGridSizer* outerSizer = new wxGridSizer(1, 1, 0);

    outerSizer->Add(
        mainSizer,
        wxSizerFlags().Expand().Border(wxALL, 25)
    );

    mainPanel->SetSizer(outerSizer);
    outerSizer->SetSizeHints(this);
}

MainFrame::MainFrame(int id) : wxFrame(nullptr, id, "Random Reminder") {
    mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, -1));

    wxIcon icon;
    icon.LoadFile("icon.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    CreateControls();

    SetupSizers();

    CreateStatusBar();

    BindEventHandlers();

    notification = new wxNotificationMessage("Random Reminder",
                            notifTextArea->GetValue(), this);
    notification->SetFlags(0);
}

wxIMPLEMENT_APP(App);