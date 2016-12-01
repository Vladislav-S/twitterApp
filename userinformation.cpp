#include "userinformation.h"
#include "ui_userinformation.h"
#include <QDebug>

userInformation::userInformation(QWidget *parent) :
    QDialog(parent),
    twitterClient(),
    ui(new Ui::userInformation)
{
    ui->setupUi(this);
}

userInformation::~userInformation()
{
    delete ui;
}

void userInformation::on_pushButton_clicked()
{
    getUserInfo();
    getFollowers();
    getFriends();
}

void userInformation::getUserInfo()
{
    std::string replyMsg;
    username = ui->lineEdit->text().toStdString();
    if (twitterObj.userGet(username, 0))
        twitterObj.getLastWebResponse(replyMsg);
    else twitterObj.getLastCurlError(replyMsg);
    //qDebug() << QString::fromStdString(replyMsg);
    QString qReplyInfo = QString::fromStdString(replyMsg);
    QJsonObject info;
    QJsonDocument infDoc = QJsonDocument::fromJson(qReplyInfo.toUtf8());
    if (!infDoc.isNull() && infDoc.isObject()) {
        info = infDoc.object();
        //qDebug() << info;
        if (info["id_str"].toString()=="") ui->textBrowser->setText("User not found!");
        else
            ui->textBrowser->setText("ID: " + (info["id_str"].toString()) + "\nName: " + info["name"].toString() +
                    "\nUsername: " + info["screen_name"].toString() + "\nLocation: " + info["location"].toString() +
                    "\nDescription: " + info["description"].toString() + "\nRegistered at: " + info["created_at"].toString() +
                    "\nTweets: " + QString::number(info["statuses_count"].toInt()) + "\nFavourites: " +
                    QString::number(info["favourites_count"].toInt()) +
                    "\nTime zone: " + info["time_zone"].toString() + "\nHomepage: " +
                    info["entities"].toObject()["url"].toObject()["urls"].toArray()[0].toObject()["display_url"].toString() +
                    "\nLast tweet: \"" + info["status"].toObject()["text"].toString() + "\" created at " +
                    info["status"].toObject()["created_at"].toString());
    }
}

void userInformation::getFollowers()
{
    std::string rplyMsg;
    if (twitterObj.followersIdsGet("", username, 0))
        twitterObj.getLastWebResponse(rplyMsg);
    else twitterObj.getLastCurlError(rplyMsg);
    //qDebug() << QString::fromStdString(rplyMsg);
    QString qReplyFol = QString::fromStdString(rplyMsg);
    QJsonObject fol;
    QJsonDocument folDoc = QJsonDocument::fromJson(qReplyFol.toUtf8());
    if (!folDoc.isNull() && folDoc.isObject()) {
        fol = folDoc.object();
        std::vector<std::string> folIds;
        std::vector<std::string> strIds;
        std::vector<std::string> folUsrnms;
        folIds.resize(fol["ids"].toArray().size());
        strIds.resize(folIds.size());
        if (folIds.size()>100) folIds.resize(100);
        folUsrnms.resize(folIds.size());
        for (size_t i=0; i<folIds.size(); i++) {
            //qDebug() << fol["ids"].toArray()[i];
            folIds[i]=fol["ids"].toArray()[i].toVariant().toString().toStdString();
            //qDebug() << fol["ids"].toArray()[i].toVariant().toString();
        }
        std::vector<std::string> vecReplyMsg;
        vecReplyMsg.resize(folIds.size());
        for (size_t i=0; i<folIds.size(); i++) {
            if (twitterObj.userGet(folIds[i], 1))
                twitterObj.getLastWebResponse(vecReplyMsg[i]);
            else twitterObj.getLastCurlError(vecReplyMsg[i]);
        }
        std::vector<QString> qReplyUsrnms;
        std::vector<QJsonObject> vecUsrnmsObj;
        std::vector<QJsonDocument> vecUsrnmsDoc;
        qReplyUsrnms.resize(vecReplyMsg.size());
        vecUsrnmsObj.resize(qReplyUsrnms.size());
        vecUsrnmsDoc.resize(vecUsrnmsObj.size());
        for (size_t i=0; i<qReplyUsrnms.size(); i++) {
            qReplyUsrnms[i] = QString::fromStdString(vecReplyMsg[i]);
            vecUsrnmsDoc[i] = QJsonDocument::fromJson(qReplyUsrnms[i].toUtf8());
            if (!vecUsrnmsDoc[i].isNull() && vecUsrnmsDoc[i].isObject()) {
                vecUsrnmsObj[i] = vecUsrnmsDoc[i].object();
            }
        }

        std::vector<QString> vecUsrnms;
        vecUsrnms.resize(vecUsrnmsObj.size());
        for (size_t i=0; i<vecUsrnms.size(); i++) {
            vecUsrnms[i]=(vecUsrnmsObj[i])["screen_name"].toString();
            ui->textBrowser_2->append(vecUsrnms[i]);
        }
    }
}

void userInformation::getFriends() {
    std::string replyMsg;
    if (twitterObj.friendsIdsGet("", username, 0))
        twitterObj.getLastWebResponse(replyMsg);
    else twitterObj.getLastCurlError(replyMsg);
    qDebug() << QString::fromStdString(replyMsg);
    QString qReplyFrnd = QString::fromStdString(replyMsg);
    QJsonObject frnd;
    QJsonDocument frndDoc = QJsonDocument::fromJson(qReplyFrnd.toUtf8());
    if (!frndDoc.isNull() && frndDoc.isObject()) {
        frnd = frndDoc.object();
        std::vector<std::string> frndIds;
        std::vector<std::string> strIds;
        std::vector<std::string> frndUsrnms;
        frndIds.resize(frnd["ids"].toArray().size());
        frndIds.resize(frndIds.size());
        if (frndIds.size()>100) frndIds.resize(100);
        frndUsrnms.resize(frndIds.size());
        for (size_t i=0; i<frndIds.size(); i++) {
            //qDebug() << fol["ids"].toArray()[i];
            frndIds[i]=frnd["ids"].toArray()[i].toVariant().toString().toStdString();
            //qDebug() << frnd["ids"].toArray()[i].toVariant().toString();
        }
        std::vector<std::string> vecReplyMsg;
        vecReplyMsg.resize(frndIds.size());
        for (size_t i=0; i<frndIds.size(); i++) {
            if (twitterObj.userGet(frndIds[i], 1))
                twitterObj.getLastWebResponse(vecReplyMsg[i]);
            else twitterObj.getLastCurlError(vecReplyMsg[i]);
        }

        std::vector<QString> qReplyUsrnms;
        std::vector<QJsonObject> vecUsrnmsObj;
        std::vector<QJsonDocument> vecUsrnmsDoc;
        qReplyUsrnms.resize(vecReplyMsg.size());
        vecUsrnmsObj.resize(qReplyUsrnms.size());
        vecUsrnmsDoc.resize(vecUsrnmsObj.size());
        for (size_t i=0; i<qReplyUsrnms.size(); i++) {
            qReplyUsrnms[i] = QString::fromStdString(vecReplyMsg[i]);
            vecUsrnmsDoc[i] = QJsonDocument::fromJson(qReplyUsrnms[i].toUtf8());
            if (!vecUsrnmsDoc[i].isNull() && vecUsrnmsDoc[i].isObject()) {
                vecUsrnmsObj[i] = vecUsrnmsDoc[i].object();
            }
        }

        std::vector<QString> vecUsrnms;
        vecUsrnms.resize(vecUsrnmsObj.size());
        for (size_t i=0; i<vecUsrnms.size(); i++) {
            vecUsrnms[i]=(vecUsrnmsObj[i])["screen_name"].toString();
            ui->textBrowser_3->append(vecUsrnms[i]);
        }
    }
}
