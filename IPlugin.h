#ifndef IPLUGIN_H
#define IPLUGIN_H
//插件基类
#include <QObject>
#include <QString>
#include "eventbus.h"
//所有业务插件的统一抽象接口
class IPlugin:public QObject{
    Q_OBJECT
public:
    explicit IPlugin(QObject *parent=nullptr):QObject (parent){}
    virtual ~IPlugin()=default;
    //唯一插件名称
    virtual QString getPluginName()const=0;
    //插件初始化（加载配置、绑定事件）
    virtual bool init()=0;
    //每帧更新（游戏主循环调用）
    virtual void updata(float deltaTime)=0;
    //插件销毁（释放资源）
    virtual void destroy()=0;
};
//DLL 导出宏（MinGW兼容）
#ifdef PLUGIN_EXPORT
#define PLUGIN_API extern "C" _declspec(dllexport)
#else
#define PLUGIN_PAI extern "C"
#endif
#endif // IPLUGIN_H
