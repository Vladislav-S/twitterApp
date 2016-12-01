#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <curl/curl.h>
#include <vector>
#include <QString>
#include "twitterclient.h"

namespace Ui {
class userInformation;
}

class userInformation : public QDialog, private twitterClient
{
    Q_OBJECT

public:
    explicit userInformation(QWidget *parent = 0);
    void getUserInfo();
    void getFollowers();
    void getFriends();
    ~userInformation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::userInformation *ui;
    std::string username;
    twitterClient twc;
};

#endif // USERINFORMATION_H
