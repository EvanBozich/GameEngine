#pragma once
#include "Actor.h"
#include <vector>
#include <string>
namespace nu
{

	class Scene
	{
	public:
		void RemoveAllActors();
		void AddActor(Actor* actor);

		void Update(float dt);

		void Draw(const class Renderer& renderer);

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		void SetGame(class Game* game) { m_game = game; }
		class Game* GetGame() { return m_game; }

	private:
		std::vector<Actor*> m_actors;
		std::vector<Actor*> m_pending_actors;
		class Game* m_game;
		void UpdateCollisions();

	};

	template<typename T = Actor>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto actor : m_actors)
		{
			T* actorT = dynamic_cast<T*>(actor);
			if (actorT && actorT->m_name == name)
			{
				return actorT;
			}
		}
		return nullptr;
	}
}
