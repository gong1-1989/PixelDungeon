#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H
//插件管理器
#include <QObject>
#include <QLibrary>
#include <QList>
#include <QDir>
#include "IPlugin.h"

class PluginManager : public QObject
{
    Q_OBJECT
public:
    //单例模式
    static PluginManager& instance();
    //扫描指定目录下所有插件DLL
    void scanPlugins(const QString& dirPath);
    //初始化所有已加载插件
    bool initAllPlugins();
    //每帧更新所有插件
    void updateAllPlugins(float deltaTime);
    //卸载并销毁所有插件
    void unloadAllPlugins();
private:
    explicit PluginManager(QObject *parent=nullptr);
    ~PluginManager() override;
    PluginManager(const PluginManager&)=delete;
    PluginManager& operator=(const PluginManager&)=delete;
    //加载单个DLL
    IPlugin*loadPlugin(const QString& dllPath);
    QList<QLibrary*> m_libraries;
    QList<IPlugin*> m_plugins;
};

#endif // PLUGINMANAGER_H
