#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QUrl>
#include <QDebug>

#define NEW_YORK 0
#define SAN_FRANCISCO 1
#define DALLAS 2
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    STATE_SELECT = 0;
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTemp()));

    connect(ui->pushButton, SIGNAL (released()),this, SLOT (TEMP_NY()));
    connect(ui->pushButton_2, SIGNAL (released()),this, SLOT (TEMP_CA()));
    connect(ui->pushButton_3, SIGNAL (released()),this, SLOT (TEMP_TX()));
    timer->start(36000000);
    UpdateTemp();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TEMP_NY()
{
    STATE_SELECT = NEW_YORK;
    UpdateTemp();
}

void MainWindow::TEMP_CA()
{
    STATE_SELECT = SAN_FRANCISCO;
    UpdateTemp();
}

void MainWindow::TEMP_TX()
{
    STATE_SELECT = DALLAS;
    UpdateTemp();
}

void MainWindow::UpdateTemp()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    switch(STATE_SELECT)
    {
      case NEW_YORK:
        ui->label_3->setText("New York");
        manager->get(QNetworkRequest(QUrl("http://api.wunderground.com/api/bfa7816830eca5ea/conditions/q/NY/New_York.json")));
        break;
      case SAN_FRANCISCO:
        ui->label_3->setText("San Fran");
        manager->get(QNetworkRequest(QUrl("http://api.wunderground.com/api/bfa7816830eca5ea/conditions/q/CA/San_Francisco.json")));
        break;
      case DALLAS:
        ui->label_3->setText("Dallas");
        manager->get(QNetworkRequest(QUrl("http://api.wunderground.com/api/bfa7816830eca5ea/conditions/q/TX/Dallas.json")));
        break;
    }
}

void MainWindow::replyFinished(QNetworkReply* reply)
{
    QByteArray bytes = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(bytes);
    QJsonObject obj = jsonResponse.object();
    ui->label_2->setText(obj.value("current_observation").toObject()["feelslike_f"].toString());
    reply->deleteLater();
}

