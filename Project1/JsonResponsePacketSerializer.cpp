#include "JsonResponsePacketSerializer.h"

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse)
{
	/*std::string msg = std::to_string(200);
	msg += strlen("messege: error");
	msg += "messege: error";*/
	std::string m = {R"({ "messege": " Error" })" };
	//json data = json::parse(m);
	json Doc{json::parse(m) };
	//std::string messege = data.value(“messege: ”, “not found”);
	std::string msg{ Doc[messege] };

	return std::vector<unsigned char>();
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
	return std::vector<unsigned char>();
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signupResponse)
{
	return std::vector<unsigned char>();
}
