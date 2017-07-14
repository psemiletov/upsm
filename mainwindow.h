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


class MainWindow: public QMainWindow
{
    Q_OBJECT
    
public:

    QSettings *settings;
    QString command;
    int polltime;
    
    QTimer *timer; 

    QTranslator myappTranslator;
    QTranslator qtTranslator;

    QTabWidget main_widget;

    QPlainTextEdit editor;
    QSystemTrayIcon tray_icon;
    QCommonStyle style;
  
    QIcon icon_green;
    QIcon icon_red;
    QIcon icon_yellow;
  
    QLineEdit *led_polltime; 
    QLineEdit *led_command;
 
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void show_at_center();
    
public slots:    

    void bt_apply_clicked();
    
    void update_stats();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
