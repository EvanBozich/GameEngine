// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Engine.h"

namespace nu
{

	bool Engine::Initialize()
	{
		m_renderer.Initialize("Game engine", 1280, 1024);
		m_input.Initialize();
		m_audio.Initialize();

		return true;
	}

	void Engine::Update()
	{
		m_input.Update();
		m_time.Tick();
		m_audio.Update();
	}

	void Engine::Shutdown()
	{
		m_input.Shutdown();
		m_renderer.Shutdown();
		m_audio.Shutdown();
	}
}


