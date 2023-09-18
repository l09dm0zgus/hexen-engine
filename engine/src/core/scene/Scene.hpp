//
// Created by cx9ps3 on 24.05.2023.
//

#pragma once

#include "../../entity/scene/SceneEntity.h"
#include <functional>
#include <iterator>
#include <vector>

namespace hexen::engine::core
{
	class Scene : public memory::AllocatedObject
	{
	private:
		glm::vec2 size;
		glm::vec2 unitSize;
		std::string name;
		std::shared_ptr<entity::SceneEntity> root {};

	public:
		class SceneIterator : public std::iterator<std::bidirectional_iterator_tag, Scene>
		{
		protected:
			u32 index {0};
			std::vector<std::string> visitedNode;
			std::shared_ptr<entity::SceneEntity> root;

			friend class Scene;
			void traverseTree(const std::shared_ptr<entity::SceneEntity> &node);

		public:
			explicit SceneIterator(const std::shared_ptr<entity::SceneEntity> &root, u32 index);

			//create iterator pointing to end()
			explicit SceneIterator(const std::shared_ptr<entity::SceneEntity> &root);
			SceneIterator(const SceneIterator &sceneIterator) = default;
			SceneIterator &operator++();
			SceneIterator &operator--();
			SceneIterator operator++(i32);
			SceneIterator operator--(i32);
			std::shared_ptr<entity::SceneEntity> operator->() const;
			std::shared_ptr<entity::SceneEntity> operator*() const;
			bool operator==(const SceneIterator &sceneIterator) const;
			bool operator!=(const SceneIterator &sceneIterator) const;
		};

		class SceneConstantIterator : public SceneIterator
		{
		public:
			explicit SceneConstantIterator(const std::shared_ptr<entity::SceneEntity> &root, u32 index);
			//create iterator pointing to end()
			explicit SceneConstantIterator(const std::shared_ptr<entity::SceneEntity> &root);
			SceneConstantIterator(const SceneConstantIterator &sceneIterator) = default;
			const std::shared_ptr<entity::SceneEntity> operator->() const;
			const std::shared_ptr<entity::SceneEntity> operator*() const;
		};

		explicit Scene(const std::string &name);
		explicit Scene(const std::string &name, const glm::vec2 &size, const glm::vec2 &unitSize);

		template<typename T, std::enable_if_t<std::is_base_of_v<entity::SceneEntity, T>, bool> = true, class... Ts>
		void spawnEntity(Ts &&...params)
		{
			root->addChild<T>(params...);
		}

		[[nodiscard]] std::shared_ptr<entity::SceneEntity> getRootNode() const noexcept;

		SceneIterator begin();
		SceneIterator end();

		[[nodiscard]] SceneConstantIterator cbegin() const;
		[[nodiscard]] SceneConstantIterator cend() const;

		[[nodiscard]] SceneConstantIterator find(const std::string &UUID) const;
		SceneIterator find(const std::string &UUID);

		void erase(const SceneIterator &sceneIterator);
		void erase(const std::string &UUID);

		void forEach(std::function<void(std::shared_ptr<entity::SceneEntity> &)> callback);

		[[nodiscard]] glm::vec2 getUnitSize() const noexcept;
		[[nodiscard]] glm::vec2 getSize() const noexcept;
	};

}// namespace hexen::engine::core
