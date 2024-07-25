#ifndef MQTT_H
#define MQTT_H

#include <amqpcpp.h>

class ConnectionHandler : public AMQP::ConnectionHandler {
    virtual void onData(AMQP::Connection *connection, const char *data, size_t size) { }
    virtual void onReady(AMQP::Connection *connection) { }
    virtual void onError(AMQP::Connection *connection, const char *message) { }
    virtual void onClosed(AMQP::Connection *connection) { }
};

AMQP::Channel setup(const std::string& username, const std::string& password);
void wait_order(AMQP::Channel channel);

#endif //MQTT_H
