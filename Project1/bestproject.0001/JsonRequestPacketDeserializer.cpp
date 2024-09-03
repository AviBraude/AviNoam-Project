#include "JsonRequestPacketDeserializer.h"
#include "LoginRequestHandler.h"



LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> loginMsg)
{
    LoginRequest loginRequest;
    json jsonOb = json::parse(loginMsg);
    
    loginRequest._userName = jsonOb["username"];
    loginRequest._password = jsonOb["password"];
    
    return LoginRequest();
}

SigninRequest JsonResponsePacketDeserializer::deserializeSignUpRequest(std::vector<unsigned char> signupMsg)
{
    SigninRequest signRequest;
    json jsonOb = json::parse(signupMsg);

    signRequest._userName = jsonOb["username"];
    signRequest._password = jsonOb["password"];
    signRequest._email = jsonOb["email"];

    return SigninRequest();
}


