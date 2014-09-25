#include "hdpimageiohandler.hpp"
#include "hdpimageioplugin.hpp"

HdpImageIOPlugin::HdpImageIOPlugin(
        QObject *parent
        ) :
    QImageIOPlugin(parent)
{
    suportFormat << "hdp";
}

QImageIOPlugin::Capabilities HdpImageIOPlugin::capabilities(
        QIODevice *device,
        const QByteArray &format
        ) const
{
    Q_UNUSED(device);

    if ( format.isEmpty() ) {
        return 0;
    }

    if ( ! suportFormat.contains(format, Qt::CaseInsensitive) ) {
        return 0;
    }

    return CanRead;
}

QImageIOHandler* HdpImageIOPlugin::create(
        QIODevice *device,
        const QByteArray &format
        ) const
{
    QImageIOHandler *handler = new HdpImageIOHandler();
    handler->setDevice(device);
    handler->setFormat(format);
    return handler;
}

QStringList HdpImageIOPlugin::keys() const
{
    return suportFormat;
}

Q_EXPORT_PLUGIN2(hdp_image, HdpImageIOPlugin)
