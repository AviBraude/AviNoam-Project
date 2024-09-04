#include "MenuRequestHandler.h"
#define LOG_OUT_CODE 3

bool MenuRequestHandler::isRequestRelevent(RequestInfo& a)
{
    if (a._msgCode == LOG_OUT_CODE)
        return true;
    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo& a)
{
    return RequestResult();
}
