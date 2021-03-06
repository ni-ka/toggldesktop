// Copyright 2014 Toggl Desktop developers.

#ifndef SRC_UI_LINUX_TOGGLDESKTOP_MAINWINDOWCONTROLLER_H_
#define SRC_UI_LINUX_TOGGLDESKTOP_MAINWINDOWCONTROLLER_H_

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMessageBox>  // NOLINT
#include <QShortcut>

#include <stdbool.h>
#include <stdint.h>

#include "./toggl.h"
#include "./preferencesdialog.h"
#include "./aboutdialog.h"
#include "./feedbackdialog.h"
#include "./qxtglobalshortcut.h"
#include "./systemtray.h"
#include "./powermanagement.h"
#include "./networkmanagement.h"
#include "./overlaywidget.h"
#include "./loginwidget.h"
#include "./timeentrylistwidget.h"
#include "./timeentryeditorwidget.h"
#include "./idlenotificationwidget.h"

namespace Ui {
class MainWindowController;
}

class MainWindowController : public QMainWindow {
    Q_OBJECT

 public:
    MainWindowController(
        QWidget *parent = 0,
        QString logPathOverride = "",
        QString dbPathOverride = "",
        QString scriptPath = "");
    ~MainWindowController();

    static MainWindowController *Instance;

    void quitApp();
    void setShortcuts();

 protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void runScript();

 private slots:  // NOLINT
    void toggleWindow(QSystemTrayIcon::ActivationReason r);

    void displayApp(const bool open);

    void displayRunningTimerState(TimeEntryView *te);

    void displayStoppedTimerState();

    void displayLogin(
        const bool open,
        const uint64_t user_id);

    void displayPomodoro(
        const QString title,
        const QString informative_text);

    void displayPomodoroBreak(
        const QString title,
        const QString informative_text);

    void displayUpdate(const QString url);

    void displayOnlineState(int64_t);
    void showHideHotkeyPressed();
    void continueStopHotkeyPressed();

    void onActionNew();
    void onActionContinue();
    void onActionStop();
    void onActionShow();
    void onActionSync();
    void onActionReports();
    void onActionPreferences();
    void onActionAbout();
    void onActionSend_Feedback();
    void onActionLogout();
    void onActionQuit();
    void onActionClear_Cache();
    void onActionHelp();

    void updateShowHideShortcut();
    void updateContinueStopShortcut();

    void onOnlineStateChanged();

    void onShortcutDelete();
    void onShortcutPause();
    void onShortcutConfirm();
    void onShortcutGroupOpen();
    void onShortcutGroupClose();

 private:
    Ui::MainWindowController *ui;

    TogglApi *togglApi;

    bool tracking;
    bool loggedIn;
    bool startInBackground;

    QxtGlobalShortcut* showHide;
    QxtGlobalShortcut* continueStop;

    PreferencesDialog *preferencesDialog;
    AboutDialog *aboutDialog;
    FeedbackDialog *feedbackDialog;

    QIcon icon;
    QIcon iconDisabled;
    SystemTray *trayIcon;

    bool pomodoro;

    QString script;

    PowerManagement *powerManagement;
    NetworkManagement *networkManagement;

    QShortcut shortcutDelete;
    QShortcut shortcutPause;
    QShortcut shortcutConfirm;
    QShortcut shortcutGroupOpen;
    QShortcut shortcutGroupClose;

    void readSettings();
    void writeSettings();

    void connectMenuActions();
    void enableMenuActions();

    bool ui_started;

    void restoreLastWindowsFrame();
};

#endif  // SRC_UI_LINUX_TOGGLDESKTOP_MAINWINDOWCONTROLLER_H_
