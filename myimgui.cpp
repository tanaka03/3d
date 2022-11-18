#include "myimgui.h"

//imgui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"

#include "application.h"
#include "player.h"
#include "meshfield.h"

CMyImgui::CMyImgui() : 
	show_demo_window(true),
	show_another_window(false)
{
}

CMyImgui::~CMyImgui()
{
}

HRESULT CMyImgui::Init()
{
	return S_OK;
}

void CMyImgui::Uninit()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void CMyImgui::Update()
{
	show_another_window = ImGuiText(show_demo_window, show_another_window);
}

void CMyImgui::Draw()
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

bool CMyImgui::ImGuiText(bool show_demo_window, bool show_another_window)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	CPlayer *pPlayer = CApplication::GetInstance()->GetPlayer();
	m_pMesh = CApplication::GetInstance()->GetMeshField();

	m_meshPos = m_pMesh->GetIdxPos(pPlayer->GetMeshIdx());

	//ImGuiのスタイル変更
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImColor(0.0f, 0.0f, 0.1f, 0.4f);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(0.5f, 0.7f, 0.0f, 1.0f);

	// Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	if (show_demo_window)
	{
		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		//FPS表示
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

		ImGui::DragFloat3("MeshPos", m_meshPos, 0.1f, -100.0f, 500.0f );
		if (m_pMesh != nullptr)
		{
			m_pMesh->SetIdxPos(m_meshPos, pPlayer->GetMeshIdx());
		}

		//別ウィンドウを生成
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");

		if (ImGui::Button("Close Me"))
		{
			show_another_window = false;
		}

		ImGui::End();
	}

	////ここが背景ドロー
	return show_another_window;
}