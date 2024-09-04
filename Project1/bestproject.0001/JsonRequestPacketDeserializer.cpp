#include "JsonRequestPacketDeserializer.h"
#include "LoginRequestHandler.h"



LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> loginMsg)
{
    LoginRequest loginRequest;
    json jsonOb = json::parse(loginMsg);
    
    loginRequest._userName = jsonOb["username"];
    loginRequest._password = jsonOb["password"];
    
    return loginRequest;
}

SigninRequest JsonResponsePacketDeserializer::deserializeSignUpRequest(std::vector<unsigned char> signupMsg)
{
    SigninRequest signRequest;
    json jsonOb = json::parse(signupMsg);

    signRequest._userName = jsonOb["username"];
    signRequest._password = jsonOb["password"];
    signRequest._email = jsonOb["email"];

    return signRequest;
}

GetPlayersInRoomRequest JsonResponsePacketDeserializer::deserializeGetPlayersInRoomRequest(std::vector<unsigned char> getPlayersMsg)
{
    GetPlayersInRoomRequest playerRequest;
    json jsonOb = json::parse(getPlayersMsg);

    playerRequest.roomID = jsonOb["room_id"];
    return playerRequest;
}

JoinRoomRequest JsonResponsePacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> JoinRoomMsg)
{
    JoinRoomRequest joinRoom;
    json jsonOb = json::parse(JoinRoomMsg);

    joinRoom.roomID = jsonOb["room_id"];
    return JoinRoomRequest();
}

CreateRoomRequest JsonResponsePacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> CreateRoomMsg)
{
    CreateRoomRequest createRoom;
    json jsonOb = json::parse(CreateRoomMsg);

    createRoom.answerTimeout = jsonOb["timeout"];
    createRoom.maxUsers = jsonOb["max_users"];
    createRoom.questionCount = jsonOb["num_of_que"];
    createRoom.roomName = jsonOb["room_name"];

    return createRoom;
}


