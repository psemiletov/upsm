#include "mainwindow.h"

#include <QProcess>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QPixmap>
#include <QDir>
#include <QLibraryInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


void MainWindow::show_at_center()
{
  QDesktopWidget *desktop = QApplication::desktop();

  int screenWidth, width; 
  int screenHeight, height;
  
  screenWidth = desktop->width(); // get width of screen
  screenHeight = desktop->height(); // get height of screen
 
  width = size().width(); 
  height = size().height();
 
  int x  = (screenWidth - width) / 2;
  int y = (screenHeight - height) / 2;
  y -= 50;
 
  move ( x, y );
}


QHash <QString, QString> hash_load_keyval (const QString &data)
{
  QHash <QString, QString> result;
  
  QStringList l = data.split ("\n");

  foreach (QString s, l)
          {
           QStringList sl = s.split (":");
           if (sl.size() > 1)
               result.insert (sl[0], sl[1]);
          }

  return result;
}

QString hash_get_val (QHash<QString, QString> &h,
                      const QString &key,
                      const QString &def_val)
{
  QString result = h.value (key);
  if (result.isNull() || result.isEmpty())
     {
      result = def_val;
      h.insert (key, def_val);
     }

  return result;
}


MainWindow::MainWindow (QWidget *parent): QMainWindow (parent)
{
    
  qtTranslator.load (QString ("qt_%1").arg (QLocale::system().name()),
                     QLibraryInfo::location (QLibraryInfo::TranslationsPath));
       
  qApp->installTranslator (&qtTranslator);

  myappTranslator.load (":/translations/upsm_" + QLocale::system().name());
  qApp->installTranslator (&myappTranslator);
    
  QDir dr;
  QString sfilename = dr.homePath() + "/.config/upsm.conf";
  settings = new QSettings (sfilename, QSettings::IniFormat);
  command = settings->value ("command", "upsc serverups@localhost").toString();
    
  polltime = settings->value ("polltime", "5000").toInt();
  
  

  QPixmap pxm_red (64, 64);
  pxm_red.fill (Qt::red);
  
  icon_red.addPixmap (pxm_red);

  QPixmap pxm_green (64, 64);
  pxm_green.fill (Qt::green);
  
  icon_green.addPixmap (pxm_green);

  QPixmap pxm_yellow (64, 64);
  pxm_yellow.fill (Qt::yellow);
  
  icon_yellow.addPixmap (pxm_yellow);


  tray_icon.setVisible (true);
  //tray_icon.setIcon (style.standardIcon(QStyle::SP_MessageBoxQuestion));
  tray_icon.setIcon (icon_green);


  resize (800, 400);
  show_at_center();
  
  //setCentralWidget (&editor);
  
  setCentralWidget (&main_widget);
  
  main_widget.addTab (&editor, tr ("Stats"));
  
  
  editor.setFont (QFont ("Serif", 24));
  editor.setReadOnly (true);
  
  connect(&tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
  
  
  
  QWidget *settings_widget = new QWidget; 
  
  QVBoxLayout *la_settings = new QVBoxLayout; 
  settings_widget->setLayout (la_settings);
  
  QHBoxLayout *la_command = new QHBoxLayout; 
  QLabel *l_command = new QLabel (tr ("Command"));
  led_command = new QLineEdit;
  la_command->addWidget (l_command);  
  la_command->addWidget (led_command);  
  led_command->setText (settings->value ("command", "upsc serverups@localhost").toString());
  la_settings->addLayout (la_command);
  

  QHBoxLayout *la_polltime = new QHBoxLayout; 
  QLabel *l_polltime = new QLabel (tr ("Polling time, msecs"));
  led_polltime = new QLineEdit;
  la_polltime->addWidget (l_polltime);  
  la_polltime->addWidget (led_polltime);  
  led_polltime->setText (settings->value ("polltime", "5000").toString());
  la_settings->addLayout (la_polltime);

  QPushButton *bt_saveapply = new QPushButton (tr ("Apply and save")); 
  connect (bt_saveapply, SIGNAL (clicked()),this, SLOT (bt_apply_clicked()));
  
  la_settings->addWidget (bt_saveapply);

  
  main_widget.addTab (settings_widget, tr ("Settings"));
  
  
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(update_stats()));
  
   update_stats();
  
   timer->start (polltime);
   
   //setVisible (false);
}


void MainWindow::bt_apply_clicked()
{
  QDir dr;
  QString sfilename = dr.homePath() + "/.config/upsm.conf";

  settings->setValue ("command", led_command->text());
  settings->setValue ("polltime", led_polltime->text());
  
  command = settings->value ("command", "no").toString();
  polltime = settings->value ("polltime", "5000").toInt();
  
  timer->stop();
  timer->start (polltime);

//  timer->setInterval (polltime);
}
    

void MainWindow::update_stats()
{
  if (command.isNull() || command.isEmpty())
     return;

  QProcess procmon;
  //procmon.start ("upsc serverups@localhost");
  procmon.start (command);
    
  if (! procmon.waitForStarted())
        return;

  if (! procmon.waitForFinished())
       return;

  QByteArray result = procmon.readAll();
  QString data = result.data();
    
  QHash <QString, QString> h = hash_load_keyval (data);

  //qDebug() << hash_get_val (h,
    //                  "driver.name",
      //                "NOOO");
                      
  QString out;                      
  out.append (tr ("Input: ")); 
  out.append (hash_get_val (h, "input.voltage","NOOO"));
  out.append ("\n");
                    

  out.append (tr ("Output: ")); 
  out.append (hash_get_val (h, "output.voltage","NOOO"));
  out.append ("\n");
  
  out.append (tr ("Load: ")); 
  out.append ( hash_get_val (h, "ups.load","NOOO"));
  out.append ("\n");
  
  
  QString status = hash_get_val (h, "ups.status","NOOO").trimmed();
  
  //"OL" "OL TRIM"
  //OB
  
  QString t;
    
  if (status == "OL")
     {
      //t = "Напряжение норма";
      t = tr ("voltage normal");
      
      //tray_icon.setIcon (style.standardIcon(QStyle::SP_MessageBoxInformation));
      tray_icon.setIcon (icon_green);
      
      }
      
     
  if (status == "OL TRIM")
     {
//      t = "ИБП понижает напрягу";
      t = tr ("ups is trimming voltage");
      
//      tray_icon.setIcon (style.standardIcon(QStyle::SP_ArrowDown));
      tray_icon.setIcon (icon_yellow);

     } 
  
  if (status == "OB")
     {
      //t = "Работа от батареи!";
      t = tr ("battery mode");
      
      //tray_icon.setIcon (style.standardIcon(QStyle::SP_MessageBoxCritical));
       tray_icon.setIcon (icon_red);

      
     } 
  
  out.append (t);
  out.append ("\n");
  
  
  editor.setPlainText (out);
  
 
}


void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason) 
         {
          case QSystemTrayIcon::Trigger:
          case QSystemTrayIcon::DoubleClick:
          /*iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1)
                                      % iconComboBox->count());*/
                  
          if (! isVisible())        
             {     
              show_at_center();                            
              show();
              activateWindow();
              raise();
             }
          else
              hide(); 
                            
          break;
    
          case QSystemTrayIcon::MiddleClick:
             //showMessage();
             break;
          default:
                  ;
         }
}

MainWindow::~MainWindow()
{
  delete settings;  
}
