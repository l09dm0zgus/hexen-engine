//
// Created by cx9ps3 on 28.06.2023.
//

#include "SceneHierarchyWindow.hpp"
#include "../IconsFontAwesome5.hpp"
#include <misc/cpp/imgui_stdlib.h>

void hexen::editor::gui::SceneHierarchyWindow::begin()
{
	HEXEN_ADD_TO_PROFILE()
}

void hexen::editor::gui::SceneHierarchyWindow::draw()
{
	HEXEN_ADD_TO_PROFILE()
	ImGui::Begin(getName().c_str(), &isOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);
	drawSearchBar();
	if (searchQuery.empty())
	{
		drawEntity(scene->getRootNode());
	}
	else
	{
		foundedChilds.clear();
		auto result = hexen::engine::entity::SceneEntity::searchNode(scene->getRootNode(), searchQuery, foundedChilds);
		if (result)
		{
			drawEntityChilds(std::move(foundedChilds));
		}
	}


	drawContextMenu();

	ImGui::End();
}

void hexen::editor::gui::SceneHierarchyWindow::end()
{
	HEXEN_ADD_TO_PROFILE()
}

void hexen::editor::gui::SceneHierarchyWindow::drawEntityChilds(hexen::engine::core::HashTable<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>> &&childs)
{
	HEXEN_ADD_TO_PROFILE()

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

			if(ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				//propertyWindow->setNode(child.value);
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
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload(PAYLOAD_NAME.c_str(), sceneEntity.get(), sizeof(*sceneEntity));
		ImGui::EndDragDropSource();
	}
}

void hexen::editor::gui::SceneHierarchyWindow::startDragAndDropTarget(std::shared_ptr<hexen::engine::entity::SceneEntity> &&sceneEntity)
{
	HEXEN_ADD_TO_PROFILE()
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
	HEXEN_ADD_TO_PROFILE()
	ImGui::InputText(ICON_FA_SEARCH "", &searchQuery, ImGuiInputTextFlags_EnterReturnsTrue);
}

void hexen::editor::gui::SceneHierarchyWindow::drawEntity(const std::shared_ptr<hexen::engine::entity::SceneEntity> &entity)
{
	HEXEN_ADD_TO_PROFILE()
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
	HEXEN_ADD_TO_PROFILE()


	if (ImGui::BeginPopupContextWindow())
	{
		if (isItemHovered || isActiveNodePopUp)
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

	if(ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		isActiveNodePopUp = false;
	}
}

void hexen::editor::gui::SceneHierarchyWindow::drawAddSceneEntity()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem(ICON_FA_FILE " Add Scene Entity..."))
	{
		scene->spawnEntity<hexen::engine::entity::SceneEntity>("Scene Entity");
	}
}

void hexen::editor::gui::SceneHierarchyWindow::drawAddChild()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem(ICON_FA_FILE " Add Child..."))
	{
		if (hoveredNode != nullptr)
		{
			hoveredNode->addChild<hexen::engine::entity::SceneEntity>("Child");
		}
		isActiveNodePopUp = false;
	}
}

void hexen::editor::gui::SceneHierarchyWindow::drawDelete()
{
	HEXEN_ADD_TO_PROFILE()
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
		isActiveNodePopUp = false;
	}
}

void hexen::editor::gui::SceneHierarchyWindow::checkHoveredItem()
{
	HEXEN_ADD_TO_PROFILE();
	isItemHovered = ImGui::IsItemHovered();
	if(isItemHovered)
	{
		isActiveNodePopUp = true;
	}
}

hexen::editor::gui::SceneHierarchyWindow::SceneHierarchyWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	initialize();
}

hexen::editor::gui::SceneHierarchyWindow::SceneHierarchyWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	initialize();
}

void hexen::editor::gui::SceneHierarchyWindow::initialize()
{
	HEXEN_ADD_TO_PROFILE();
	setSize(glm::vec2(400, 300));
	//temporary, in future scene loading will be called in SceneFileWindow/menu bar , etc
	hexen::engine::core::SceneManager::loadScene("Main.hxscene");
	scene = hexen::engine::core::SceneManager::getCurrentScene();
}
