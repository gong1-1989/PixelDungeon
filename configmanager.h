#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
class ConfigManager
{
public:
    static ConfigManager& GetInstance();
    bool LoadJson(const QString& filePath, QJsonObject &outObj);
    bool SaveJson(const QString& filePath, const QJsonObject& obj);
private:
    ConfigManager()=default;
};

#endif // CONFIGMANAGER_H
