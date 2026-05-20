#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

class ConfigManager : public QObject
{
    Q_OBJECT
public:
    static ConfigManager &instance();
    //加载指定配置文件
    bool loadConfig(const QString &filePath);
    //获取JSON对象
    QJsonObject getRoot() const;
    //通用值读取（自动补默认值）
    template<typename T>
    T getValue(const QStringList &keys, const T &defaultValue);

private:
    explicit ConfigManager(QObject *parent = nullptr);
    ~ConfigManager() override = default;
    ConfigManager(const ConfigManager &) = delete;
    ConfigManager &operator=(const ConfigManager &) = delete;
    QJsonObject m_root;
};

#endif // CONFIGMANAGER_H
