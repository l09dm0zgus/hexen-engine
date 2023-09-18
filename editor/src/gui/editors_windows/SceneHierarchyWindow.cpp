//
// Created by cx9ps3 on 28.06.2023.
//

#include "SceneHierarchyWindow.hpp"
#include "../IconsFontAwesome5.hpp"
#include <misc/cpp/imgui_stdlib.h>

hexen::editor::gui::SceneHierarchyWindow::SceneHierarchyWindow(std::string name) : GUIWindow(std::move(name))
{
	setSize(glm::vec2(400, 300));
	//temporary, in future scene loading will be called in SceneFileWindow/menu bar , etc
	hexen::engine::core::SceneManager::loadScene("Main.hxscene");

	scene = hexen::engine::core::SceneManager::getCurrentScene();
}

void hexen::editor::gui::SceneHierarchyWindow::begin()
{
}

void hexen::editor::gui::SceneHierarchyWindow::draw()
{
	ImGui::Begin(getName().c_str(), &isOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);
	drawSearchBar();
	if (searchQuery.empty())
	{
		drawEntity(scene->getRootNode());
	}
	else
	{
		findedChilds.clear();
		auto result = hexen::engine::entity::SceneEntity::searchNode(scene->getRootNode(), searchQuery, findedChilds);
		if (result)
		{
			drawEntityChilds(std::move(findedChilds));
		}
	}


	drawContextMenu();

	ImGui::End();
}

void hexen::editor::gui::SceneHierarchyWindow::end()
{
}

void hexen::editor::gui::SceneHierarchyWindow::drawEntityChilds(hexen::engine::core::HashTable<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>> &&childs)
{

	for (auto &child : childs)
	{
		hexen::engine::core::i32 flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;


		if (!child.value->hasChildrens())
		{
			flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		}

		if (child.value != nullptr)
		{
			ImGui::PushID(child.key.c_str());
			bool open = ImGui::TreeNodeEx(child.value->getName().data(), flags);

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				isNodeNameEditing[child.key] = true;
			}

			if (isNodeNameEditing[child.key])
			{
				auto nodeName = child.value->getName();
				if (ImGui::InputText("##", &nodeName, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					child.value->rename(nodeName);
					isNodeNameEditing[child.key] = false;
				}
			}

			checkHoveredItem();

			ImGui::PopID();

			bool hasChilds = child.value->hasChildrens();

			if (isItemHovered)
			{
				hoveredNode = child.value;
			}

			if (open)
			{
				startDragAndDropSource(child.value);
				startDragAndDropTarget(std::move(child.value));
			}
			if (hasChilds && open)
			{
				drawEntityChilds(std::move(child.value->getChildrens()));
				ImGui::TreePop();
			}
		}
	}
}

void hexen::editor::gui::SceneHierarchyWindow::startDragAndDropSource(const std::shared_ptr<hexen::engine::entity::SceneEntity> &sceneEntity)
{
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload(PAYLOAD_NAME.c_str(), sceneEntity.get(), sizeof(*sceneEntity));
		ImGui::EndDragDropSource();
	}
}

void hexen::editor::gui::SceneHierarchyWindow::startDragAndDropTarget(std::shared_ptr<hexen::engine::entity::SceneEntity> &&sceneEntity)
{
	if (ImGui::BeginDragDropTarget())
	{
		if (auto payload = ImGui::AcceptDragDropPayload(PAYLOAD_NAME.c_str()))
		{
			auto draggedEntity = (hexen::engine::entity::SceneEntity *) (payload->Data);
			if (draggedEntity != nullptr)
			{
				if (!draggedEntity->isDescendantExist(sceneEntity->getUUID()))
				{
					draggedEntity->changeParent(sceneEntity);
				}
			}
		}
		ImGui::EndDragDropTarget();
	}
}

void hexen::editor::gui::SceneHierarchyWindow::drawSearchBar()
{
	ImGui::InputText(ICON_FA_SEARCH "", &searchQuery, ImGuiInputTextFlags_EnterReturnsTrue);
}

void hexen::editor::gui::SceneHierarchyWindow::drawEntity(const std::shared_ptr<hexen::engine::entity::SceneEntity> &entity)
{
	hexen::engine::core::i32 flags = ImGuiTreeNodeFlags_OpenOnArrow;

	ImGui::PushID(entity->getUUID().c_str());
	bool open = ImGui::TreeNodeEx(entity->getName().data(), flags);

	ImGui::PopID();
	checkHoveredItem();

	auto hasChilds = entity->hasChildrens();

	if (hasChilds && open)
	{
		drawEntityChilds(std::move(entity->getChildrens()));

		checkHoveredItem();

		ImGui::TreePop();
	}
}

void hexen::editor::gui::SceneHierarchyWindow::drawContextMenu()
{
	if (ImGui::BeginPopupContextWindow())
	{
		if (isItemHovered)
		{
			drawAddChild();
			drawDelete();
		}
		else
		{
			drawAddSceneEntity();
		}
		ImGui::EndPopup();
	}
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		isItemHovered = false;
	}
}

void hexen::editor::gui::SceneHierarchyWindow::drawAddSceneEntity()
{
	if (ImGui::MenuItem(ICON_FA_FILE " Add Scene Entity..."))
	{
		scene->spawnEntity<hexen::engine::entity::SceneEntity>("Scene Entity");
	}
}

void hexen::editor::gui::SceneHierarchyWindow::drawAddChild()
{
	if (ImGui::MenuItem(ICON_FA_FILE " Add Child..."))
	{
		if (hoveredNode != nullptr)
		{
			hoveredNode->addChild<hexen::engine::entity::SceneEntity>("Child");
		}
	}
}

void hexen::editor::gui::SceneHierarchyWindow::drawDelete()
{
	if (ImGui::MenuItem(ICON_FA_TRASH " Delete"))
	{
		if (hoveredNode != nullptr)
		{
			auto parent = hoveredNode->getParent();

			if (parent != nullptr)
			{
				parent->removeChildByUUID(hoveredNode->getUUID());
			}
		}
	}
}

void hexen::editor::gui::SceneHierarchyWindow::checkHoveredItem()
{
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
	{
		isItemHovered = true;
	}
}
