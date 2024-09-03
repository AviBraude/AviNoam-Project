#include "JsonResponsePacketSerializer.h"
#include "request.h"
using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse)
{
	json jsonObject = { "messege: " , errorResponse._message };
	std::vector<unsigned char> res = JsonResponsePacketSerializer::helpSerial(jsonObject);
	return res;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
	json jsonObject = {"status: " , loginResponse._status };
	std::vector<unsigned char> res = JsonResponsePacketSerializer::helpSerial(jsonObject);
	return res;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signupResponse)
{
	json jsonObject = { "status: " , signupResponse._status };
	std::vector<unsigned char> res = JsonResponsePacketSerializer::helpSerial(jsonObject);
	return res;
}

std::vector<unsigned char> JsonResponsePacketSerializer::helpSerial(json jsonObject)
{
	std::string strJson = jsonObject.dump();
	int lenStr = strJson.length();
	std::vector<unsigned char> res;
	const char mycode = STATUS1;
	res.push_back(mycode);
	res.push_back(lenStr);
	for (int i = 0; i < lenStr; i++)
	{
		res.push_back(strJson[i]);
	}
	return res;
}
