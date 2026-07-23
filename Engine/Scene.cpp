#include "pch.h"
#include "Scene.h"
#include "Actor.h"

namespace nu {


	void Scene::Update(float dt)
	{
		//update actor
		for (auto actor : m_actors)
		{
			actor->Update(dt);
		}

		std::erase_if(m_actors, [](auto actor) {return actor->m_destroyed;});

		//add pending actors
		m_actors.insert(m_actors.end(), m_pending_actors.begin(), m_pending_actors.end());
		m_pending_actors.clear();
	}

	void Scene::Draw(const class Renderer& renderer)
	{
		for (auto actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::AddActor(Actor* actor) 
	{ 
		actor->m_scene = this;
		m_pending_actors.push_back(actor); 
	}

}
