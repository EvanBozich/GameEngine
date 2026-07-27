#include "pch.h"
#include "Audio.h"
#include <iostream>

namespace nu {

    bool Audio::Initialize()
    {
        FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem, FMOD_VERSION);
		if (!CheckFMODResult(result)) 
			return false;

		void* extradriverdata = nullptr;
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) 
			return false;

		return true;
    }

	bool Audio::CheckFMODResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			//std::cerr << FMOD_ErrorString(result) << std::endl;
			return false;
		}

		return true;
	}
}