#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int STATE_SELECT;
private slots:
    void UpdateTemp();
    void replyFinished(QNetworkReply* reply);
    void TEMP_NY();
    void TEMP_CA();
    void TEMP_TX();
};

#endif // MAINWINDOW_H
