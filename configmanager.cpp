#include "configmanager.h"

ConfigManager &ConfigManager::instance()
{
    static ConfigManager ins;
    return ins;
}
ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent)
{}
bool ConfigManager::loadConfig(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "配置文件打卡失败：" << filePath;
        return false;
    }
    QByteArray data = file.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        qCritical() << "JSON解析错误：" << err.errorString();
        return false;
    }
    m_root = doc.object();
    qInfo() << "配置加载成功：" << filePath;
    return true;
}

QJsonObject ConfigManager::getRoot() const
{
    return m_root;
}

template<typename T>
T ConfigManager::getValue(const QStringList &keys, const T &defaultValue)
{
    QJsonObject obj = m_root;
    for (int i = 0; i < keys.size(); i++) {
        if (!obj.contains(keys[i]) || obj[keys[i]].isObject())
            return defaultValue;
        obj = obj[keys[i]].toObject();
    }
    QString lastKey = keys.last();
    if (!obj.contains(lastKey))
        return defaultValue;
    QJsonValue val = obj[lastKey];
    if constexpr (std::is_same_v<T, qreal>)
        return val.toDouble(defaultValue);
    else if constexpr (std::is_same_v<T, QString>)
        return val.toString(defaultValue);
    else
        return defaultValue;
}
//显式实例化常用类型
template int ConfigManager::getValue<int>(const QStringList &, const int &);
template qreal ConfigManager::getValue<qreal>(const QStringList &, const qreal &);
template QString ConfigManager::getValue<QString>(const QStringList &, const QString &);