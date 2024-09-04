#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

LoginRequestHandler* RequestHandlerFactory::creatLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::creatMenuRequestHandler()
{
    return new MenuRequestHandler(*this);
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return _roomManager;
}

LoginManager RequestHandlerFactory::getLoginManager()
{
    return _loginManager;
}
