#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#include <string>


bool LoginRequestHandler::isRequestRelevent(RequestInfo& a)
{
    if (a._msgCode == '1' || a._msgCode == '2')
        return true;
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo& a)
{
    RequestResult reqResult;
    if (a._msgCode == 1)
        reqResult = this->login(a);
    else if (a._msgCode == 2)
        reqResult = this->signup(a);

    return reqResult;
}

RequestResult LoginRequestHandler::login(RequestInfo& a)
{
    LoginRequest logRequest;
    RequestResult res;

    logRequest = JsonResponsePacketDeserializer::deserializeLoginRequest(a._msgInfo);
    LoginResponse logRespons;
    logRespons._status = 1;

    // here we need the manager
    res.newHandler = new LoginResponseHandler();


    res._msgBuffer = JsonResponsePacketSerializer::serializeResponse(logRespons);

    return res;
}

RequestResult LoginRequestHandler::signup(RequestInfo& a)
{
    LoginRequest signRequest;
    RequestResult res;
    signRequest = JsonResponsePacketDeserializer::deserializeLoginRequest(a._msgInfo);
    LoginResponse signRespons;
    signRespons._status = 1;

    res.newHandler = new signupResponseHandler();
    res._msgBuffer = JsonResponsePacketSerializer::serializeResponse(signRespons);

    return res;
}
