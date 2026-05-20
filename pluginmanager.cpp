#include "pluginmanager.h"
#include <QDebug>

PluginManager& PluginManager::instance(){
    static PluginManager ins;
    return ins;
}

PluginManager::PluginManager(QObject *parent): QObject(parent) {}
PluginManager::~PluginManager(){
    unloadAllPlugins();
}
void PluginManager::scanPlugins(const QString &dirPath){
    QDir dir(dirPath);
    dir.setNameFilters({"*.dll"});
    dir.setFilter(QDir::Files);
    for(const QString& file:dir.entryList()){
        QString fullPath=dir.filePath(file);
        IPlugin* plugin=loadPlugin(fullPath);
        if(plugin){
            m_plugins.append(plugin);
            qInfo()<<"成功加载插件："<<plugin->getPluginName();
        }
    }
}
IPlugin* PluginManager::loadPlugin(const QString &dllPath){
    QLibrary* lib=new QLibrary(dllPath);
    if(!lib->load()){
        qCritical()<<"插件DLL加载失败："<<lib->errorString();
        delete lib;
        return nullptr;
    }
    //匹配DLL中导出的创建函数
    typedef IPlugin* (*CreatePluginFunc)();
    CreatePluginFunc createFunc=(CreatePluginFunc)lib->resolve("createPlugin");
    if(!createFunc){
        qCritical()<<"未找到插件DLL入口函数："<<dllPath;
        lib->unload();
        delete lib;
        return nullptr;
    }
    IPlugin* plugin=createFunc();
    m_libraries.append(lib);
    return plugin;
}

bool PluginManager::initAllPlugins(){
    for(IPlugin* plugin:m_plugins){
        if(!plugin->init()){
            qCritical()<<"插件DLL初始化失败："<<plugin->getPluginName();
            return false;
        }
    }
    return true;
}

void PluginManager::updateAllPlugins(float deltaTime){
    for(IPlugin* plugin:m_plugins) {plugin->updata(deltaTime);}
}

void PluginManager::unloadAllPlugins(){
    for(IPlugin* plugin:m_plugins){
        plugin->destroy();
        delete plugin;
    }
    m_plugins.clear();
    for(QLibrary* lib:m_libraries){
        lib->unload();
        delete lib;
    }
    m_libraries.clear();
}