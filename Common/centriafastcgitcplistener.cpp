#include "centriafastcgitcplistener.h"


CentriaFastCGITCPListener::CentriaFastCGITCPListener(QString tcpListenerName, QObject *parent)
{
    SCLog::AddDebug(QString("CentriaFastCGITCPListener::CentriaFastCGITCPListener(%1) start").arg(tcpListenerName));

    DTO = CentriaFastCGITCPListenerDTO(tcpListenerName);

    if(DTO.TCPPort > 0)
    {
        _qTCPServer = new QTcpServer(this);
        connect(_qTCPServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
        if(!_qTCPServer->listen(QHostAddress::Any, DTO.TCPPort))
        {
            SCLog::AddError(QString("CentriaFastCGITCPListener(%1) QTcpServer could not start").arg(DTO.ID));
        }
        else
        {
            SCLog::AddLog(QString("CentriaFastCGITCPListener(%1) started").arg(DTO.ID));
        }
    }

    SCLog::AddDebug(QString("CentriaFastCGITCPListener::CentriaFastCGITCPListener(%1) end").arg(tcpListenerName));
}

CentriaFastCGITCPListener::~CentriaFastCGITCPListener()
{
    SCLog::AddDebug(QString("CentriaFastCGITCPListener::~CentriaFastCGITCPListener(%1) start").arg(DTO.ID));

    if(_qTCPSocket != nullptr)
    {
        _qTCPSocket->close();
        _qTCPSocket->deleteLater();
    }

    if(_qTCPServer != nullptr)
    {
        _qTCPServer->close();
        _qTCPServer->deleteLater();
    }

    SCLog::AddDebug(QString("CentriaFastCGITCPListener::~CentriaFastCGITCPListener(%1) end").arg(DTO.ID));
}

void CentriaFastCGITCPListener::readyRead()
{
    if(_qTCPSocket != nullptr)
    {
        CentriaFastCGIRequest centriaFastCGIRequest;
        centriaFastCGIRequest.Request = _qTCPSocket->readAll();
        RequestParser(centriaFastCGIRequest);
        emit NewRequest(centriaFastCGIRequest);

        QByteArray buffer = CreateSendData(centriaFastCGIRequest);
        _qTCPSocket->write(buffer);
        _qTCPSocket->waitForBytesWritten();

        _qTCPSocket->flush();
        _qTCPSocket->close();
        _qTCPSocket->deleteLater();
        _qTCPSocket = nullptr;
    }
}

void CentriaFastCGITCPListener::newConnection()
{
    SCLog::AddLog(QString("CentriaFastCGITCPListener::newConnection(%1) start").arg(DTO.ID));
    if(_qTCPSocket == nullptr)
    {
        _qTCPSocket = _qTCPServer->nextPendingConnection();

        SCLog::AddLog(QString("new tcp client connection(%1) from %2:%3").arg(_qTCPSocket->socketDescriptor()).arg(_qTCPSocket->peerAddress().toString()).arg(_qTCPSocket->peerPort()));

        connect(_qTCPSocket, SIGNAL(connected()), this, SLOT(connected()));
        connect(_qTCPSocket, SIGNAL(disconnected()),this, SLOT(disconnected()));
        connect(_qTCPSocket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    }
    else
    {
        QTcpSocket *tcpSocket = _qTCPServer->nextPendingConnection();
        SCLog::AddError(QString("Cannot add new tcp connection(%1) from %2:%3 (only one connection is accepted)").arg(tcpSocket->socketDescriptor()).arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort()));
        tcpSocket->close();
        tcpSocket->deleteLater();
    }
}

void CentriaFastCGITCPListener::connected()
{

}

void CentriaFastCGITCPListener::disconnected()
{

}

void CentriaFastCGITCPListener::destroyed(QObject *)
{

}

void CentriaFastCGITCPListener::RequestParser(CentriaFastCGIRequest &centriaFastCGIRequest)
{
    int index = 0;
    unsigned int contentLength = 0;
    unsigned int bufferSize = centriaFastCGIRequest.Request.size();
    centriaFastCGIRequest.Parameters.clear();
    while(index <= bufferSize)
    {
        const FastCGI_Header& fastCGIHeader = *reinterpret_cast<const FastCGI_Header*>(centriaFastCGIRequest.Request.data() + index);
        if(fastCGIHeader.version == FastCGI_VERSION_1)
        {
            contentLength = (fastCGIHeader.contentLengthB1 << 8) + fastCGIHeader.contentLengthB0;
            if (bufferSize >= (FastCGI_HEADER_LEN + contentLength + fastCGIHeader.paddingLength))
            {
                const char* content = centriaFastCGIRequest.Request.data() + FastCGI_HEADER_LEN + index;
                unsigned int requestID = (fastCGIHeader.requestIdB1 << 8) + fastCGIHeader.requestIdB0;

                switch (fastCGIHeader.type) {
                case FastCGI_BEGIN_REQUEST:
                    if (contentLength >= sizeof(FastCGI_BeginRequestBody))
                    {
                        const FastCGI_BeginRequestBody& fastCGIBody = *reinterpret_cast<const FastCGI_BeginRequestBody*>(content);

                    }
                    break;

                case FastCGI_PARAMS:
                    if(contentLength > 2)
                    {
                        int characterIndex = 0;
                        do
                        {
                            int parameterNameLength = (int)content[characterIndex + 0];
                            int parameterValueLength = (int)content[characterIndex + 1];
                            QString parameterName = QString::fromUtf8(&content[characterIndex + 2], parameterNameLength);
                            QString parameterValue = QString::fromUtf8(&content[characterIndex + 2 + parameterNameLength], parameterValueLength);
//                            if(parameterName == "CONTENT_LENGTH")
//                            {
//                                QList<uchar> lengthCharacters;
//                                for(int lengthIndex = 0; lengthIndex < parameterValueLength; lengthIndex++)
//                                {
//                                    lengthCharacters.append(content[characterIndex + 2 + parameterNameLength] + lengthIndex);
//                                }
//                                if(parameterValueLength == 2)
//                                {
//                                    ushort contentLength = ushort(content[characterIndex + 2 + parameterNameLength]) << 8 | (ushort)(content[characterIndex + 2 + parameterNameLength] + 1);
//                                    parameterValue = QString(contentLength);
//                                }
//                            }

                            centriaFastCGIRequest.Parameters[parameterName] = parameterValue;

                            characterIndex = characterIndex + 2 + parameterNameLength + parameterValueLength;
                        } while(characterIndex < contentLength);
                    }
                    break;

                case FastCGI_STDIN:
                    if(contentLength > 0)
                    {
                        centriaFastCGIRequest.Content.append(QByteArray::fromRawData(&content[0], contentLength));
                    }
//                    QString::fromUtf8(&content[0], contentLength);
//                    QString testi = "";
//                    for(int contentIndex = 0; contentIndex < contentLength; contentIndex++)
//                    {
//                        testi.append(content[contentIndex]);
//                    }
//                    int t = 0;

//                    RequestList::iterator it = connection.requests.find(request_id);
//                    if (it == connection.requests.end())
//                        break;

//                    RequestInfo& request = *it->second;
//                    if (!request.in_closed)
//                        if (content_length != 0) {
//                            request.in.append(content, content_length);
//                            if (request.params_closed && request.status == 0) {
//                                request.status = (*handle_data)(request);
//                                process_write_request(connection, request_id, request);
//                            }
//                        } else {
//                            request.in_closed = true;
//                            if (request.params_closed && request.status == 0) {
//                                request.status = (*handle_complete)(request);
//                                process_write_request(connection, request_id, request);
//                            }
//                        }
                    break;

                }
            }
            else
            {
                SCLog::AddError(QString("Request buffer size is too short (bufferSize=%1 needed size=%2").arg(centriaFastCGIRequest.Request.size()).arg(FastCGI_HEADER_LEN + contentLength + fastCGIHeader.paddingLength));
            }
        }
        else
        {
            //SCLog::AddError(QString("FastCGI version conflict (request Version=%1 and sw version=%2").arg(fastCGIHeader.version).arg(FastCGI_VERSION_1));
        }
        index += FastCGI_HEADER_LEN + contentLength + fastCGIHeader.paddingLength;
    }
}

QByteArray CentriaFastCGITCPListener::CreateSendData(CentriaFastCGIRequest &centriaFastCGIRequest)
{
    QByteArray content;
    content.append("Content-Type: text/plain\r\n\r\n");
    content.append(centriaFastCGIRequest.Response);

    ushort id = 1;
    ushort contentSize = content.size();

    FastCGI_Header fastCGIHeader;
    bzero(&fastCGIHeader, sizeof(fastCGIHeader));
    fastCGIHeader.version = FastCGI_VERSION_1;
    fastCGIHeader.type = FastCGI_STDOUT;
    fastCGIHeader.requestIdB1 = (id >> 8) & 0xff;
    fastCGIHeader.requestIdB0 = id & 0xff;

    fastCGIHeader.contentLengthB1 = contentSize >> 8;
    fastCGIHeader.contentLengthB0 = contentSize & 0xff;
    fastCGIHeader.paddingLength = (8 - (contentSize % 8)) % 8;

    QByteArray buffer;
    buffer.append(reinterpret_cast<const char*>(&fastCGIHeader), sizeof(fastCGIHeader));
    buffer.append(content.data(), contentSize);
    //buffer.append(header.paddingLength, 0);

    return buffer;
}
