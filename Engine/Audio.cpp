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

	void Audio::Shutdown()
	{
		//CheckFMODResult(/*TODO: release() fmod system*/);
	}

	void Audio::Update()
	{
		//CheckFMODResult(/*TODO: update() fmod system*/);
	}

	bool Audio::AddSound(const std::string& name, const std::string& filename)
	{
		// check if key exists in sounds map
		//if (/*TODO: check if name already exists in m_sounds*/)
		{
			std::cerr << "Audio System : name already exists " << name << std::endl;
			return false;
		}

		// create sound from key
		FMOD::Sound* sound = nullptr;
		//FMOD_RESULT result = m_fmodSystem->createSound(/*TODO: pass parameters to create sound*/);
		//if (!CheckFMODResult(result))
			return false;

		// insert sound into map
		//TODO: add sound to m_sounds using name as key

		return true;
	}

	bool Audio::PlaySound(const std::string& name)
	{
		// check if sound exists in sounds map
		//if (/*TODO: check if name doesn't exist in m_sounds*/)
		{
			std::cerr << "Audio System : name doesn't exists " << name << std::endl;
			return false;
		}

		// play sound from key
		//FMOD_RESULT result = m_fmodSystem->playSound(/*TODO: pass play sound parameters*/);
		//if (!CheckFMODResult(result))
			return false;

		return true;
	}
}