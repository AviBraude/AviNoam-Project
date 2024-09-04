#include "MenuRequestHandler.h"
#include "define.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

unsigned int _updateIDrooms = 0;

bool MenuRequestHandler::isRequestRelevent(RequestInfo& a)
{
    if (a._msgCode == LOG_OUT_CODE || a._msgCode == CREAT_ROOM_REQ || a._msgCode == GET_ROOM_REQ ||
        a._msgCode == GET_PLAYERS_IN_ROOM_REQ || a._msgCode == JOIN_ROOM_REQ || a._msgCode == GET_STATISTICS_REQ)
    {
        return true;
    }
    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo& a)
{
    RequestResult reqResult;
    if (a._msgCode == LOG_OUT_CODE)
        reqResult = this->signout(a);
    else if (a._msgCode == CREAT_ROOM_REQ)
        reqResult = this->createRoom(a);
    else if (a._msgCode == GET_ROOM_REQ)
        reqResult = this->getRooms(a);
    else if (a._msgCode == GET_PLAYERS_IN_ROOM_REQ)
        reqResult = this->getPlayerInRoom(a);
    else if (a._msgCode == JOIN_ROOM_REQ)
        reqResult = this->joinRoom(a);
    else if (a._msgCode == GET_STATISTICS_REQ)
        reqResult = this->getPersonalStats(a);

    return reqResult;
}

RequestResult MenuRequestHandler::signout(RequestInfo& a)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(RequestInfo& a)
{
    return ;
}

RequestResult MenuRequestHandler::getPlayerInRoom(RequestInfo& a)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo& a)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo& a)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo& a)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo& a)
{
    RequestResult res;
    std::string st = "{status: 1}";

    CreateRoomRequest data = JsonResponsePacketDeserializer::deserializeCreateRoomRequest(a._msgInfo);
    RoomData rd;
    rd.name = data.roomName;
    rd.maxPlayers = data.maxUsers;
    rd.numOfQuestionsInGame = data.questionCount;
    rd.timePerQuestion = data.answerTimeout;
    rd.id = _updateIDrooms + 1;
    rd.isActive = 1;

    CreateRoomRespons cr;
    cr._status = _factory.getRoomManager().createRoom(_user, rd);

    res.newHandler = _factory.creatMenuRequestHandler();
    res._msgBuffer = JsonResponsePacketSerializer::serializeResponse(cr);
    return res;
}
