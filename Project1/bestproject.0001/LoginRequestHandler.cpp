#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <string>

#include "define.h"

bool LoginRequestHandler::isRequestRelevent(RequestInfo& a)
{
    if (a._msgCode == LOG_IN_CODE || a._msgCode == SIGN_UP_CODE)
        return true;
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo& a)
{
    RequestResult reqResult;
    if (a._msgCode == LOG_IN_CODE)
        reqResult = this->login(a);
    else if (a._msgCode == SIGN_UP_CODE)
        reqResult = this->signup(a);

    return reqResult;
}

RequestResult LoginRequestHandler::login(RequestInfo& a)
{
    LoginRequest logRequest;
    RequestResult res;

    logRequest = JsonResponsePacketDeserializer::deserializeLoginRequest(a._msgInfo);
    LoginResponse logRespons;
    int checky = _factory.getLoginManager().login(logRequest);
    logRespons._status = checky;
    if (checky == CORRECT_NAME_AND_PASSWORD)
    {
        res.newHandler = _factory.creatMenuRequestHandler(); // here we will put the new state (menu)
        res._msgBuffer = JsonResponsePacketSerializer::serializeResponse(logRespons);
    }
    else
    {
        res.newHandler = _factory.creatLoginRequestHandler();
        res._msgBuffer = JsonResponsePacketSerializer::serializeResponse(logRespons);
    }

    return res;
}

RequestResult LoginRequestHandler::signup(RequestInfo& a)
{
    SigninRequest signRequest;
    RequestResult res;
    signRequest = JsonResponsePacketDeserializer::deserializeSignUpRequest(a._msgInfo);
    SignupResponse signRespons;

    int checky = _factory.getLoginManager().signup(signRequest);
    signRespons._status = checky;
    if (checky == CORRECT_NAME_AND_PASSWORD)
    {
        res.newHandler = _factory.creatMenuRequestHandler(); // here we will put the new state (menu)
        res._msgBuffer = JsonResponsePacketSerializer::serializeResponse(signRespons);
    }
    else
    {
        res.newHandler = _factory.creatLoginRequestHandler();
        res._msgBuffer = JsonResponsePacketSerializer::serializeResponse(signRespons);
    }

    return res;
}
