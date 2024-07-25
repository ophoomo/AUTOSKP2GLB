#include "header/mqtt.h"

AMQP::Channel setup(const std::string& username, const std::string& password) {
    ConnectionHandler connection_handler;

    AMQP::Connection connection(&connection_handler, AMQP::Login(username,password), "/");

    AMQP::Channel channel(&connection);

    return channel;
}

void wait_order(AMQP::Channel channel) {

    auto startCb = [](const std::string &consumertag) {
        std::cout << "consume operation started" << std::endl;
    };

    auto errorCb = [](const char *message) {
        std::cout << "consume operation failed" << std::endl;
    };

    auto messageCb = [&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
        std::cout << "message received" << std::endl;
        channel.ack(deliveryTag);
    };

    auto cancelledCb = [](const std::string &consumertag) {
        std::cout << "consume operation cancelled by the RabbitMQ server" << std::endl;
    };

    channel.consume("queue")
    .onReceived(messageCb)
    .onSuccess(startCb)
    .onCancelled(cancelledCb)
    .onError(errorCb);
}
