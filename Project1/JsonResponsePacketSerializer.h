#pragma once
#include "Communicator.h"
#include "request.h"

static class JsonResponsePacketSerializer
{
	void serializeResponse(ErrorResponse& res) ;
	void serializeResponse(LoginResponse& res) ;
	void serializeResponse(SignupResponse& res) ;
};


