#include "configmanager.h"
#include <QFile>
#include <QDebug>

ConfigManager& ConfigManager::GetInstance() {
    static ConfigManager ins;
    return ins;
}
bool ConfigManager::LoadJson(const QString &filePath, QJsonObject &outObj){
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qWarning()<<"配置文件打开失败："<<filePath;
        return false;
    }
    QByteArray data=file.readAll();
    file.close();
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(data,&err);
    if(err.error!=QJsonParseError::NoError){
        qWarning()<<"JSON解析错误："<<err.errorString();
        return false;
    }
    outObj=doc.object();
    return true;
}
bool ConfigManager::SaveJson(const QString &filePath,const QJsonObject &obj){
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return false;
    }
    QJsonDocument doc(obj);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}