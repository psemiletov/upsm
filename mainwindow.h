#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QStyle> 
#include <QCommonStyle>
#include <QIcon>
#include <QSettings>
#include <QTranslator>
#include <QTabWidget>
#include <QLineEdit>
#include <QTimer>
#include <QStringList>
#include <QImage>
#include <QCheckBox>


class MainWindow: public QMainWindow
{
Q_OBJECT
    
public:

  QImage *paint_rect;

  QStringList slst_log;

  QSettings *settings;
  QString command;
  QString s_config_fname;

  int polltime;
  int logsize;
    
  QTimer *timer; 

  QTranslator myappTranslator;
  QTranslator qtTranslator;

  QTabWidget main_widget;

  QCheckBox *cb_hide_from_taskbar;
  QCheckBox *cb_run_minimized;

  QPlainTextEdit editor;
  QPlainTextEdit log;
    
  QSystemTrayIcon tray_icon;
  QCommonStyle style;
  /*
  QIcon icon_green;
  QIcon icon_red;
  QIcon icon_yellow;
  */
  QLineEdit *led_polltime; 
  QLineEdit *led_command;
  QLineEdit *led_logsize;
 
  MainWindow (QWidget *parent = 0);
  ~MainWindow();
    
  void show_at_center();
    
public slots:    

  void pageChanged (int index);
  void bt_select_font_clicked();
  void bt_apply_clicked();
  void update_stats();
  void iconActivated (QSystemTrayIcon::ActivationReason reason);
    
protected:

  void closeEvent (QCloseEvent *event);    
  void changeEvent(QEvent *event);
};

#endif // MAINWINDOW_H
