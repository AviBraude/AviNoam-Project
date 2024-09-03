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

LoginManager RequestHandlerFactory::getLoginManager()
{
    return _loginManager;
}
